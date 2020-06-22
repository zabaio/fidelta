#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "types.h"
#include "display.h"

#ifndef RESPATHNOEXT
    #define RESPATHNOEXT "result"
#endif
#ifndef CORLIM
    #define CORLIM 200000000
#endif
#ifndef PTSLIM
    #define PTSLIM 300000
#endif

//--------------------------------------//
//  Input output and user interaction   //
//--------------------------------------//

// Command line read. Returns 1 if random mode is selected
int init_cmd (int argc, char *argv[], FILE **node, FILE **extnode, int *n_pts, float *max_cor){
    
    *node = fopen (RESPATHNOEXT ".node" , "w+");
    if (*node == NULL){
        printf ("ERROR: Could not open output file\n");
        exit(EXIT_FAILURE);
    }
    
    if (argc < 3){
        printf ("ERROR: Not enough arguments\n");
        man(0);
        exit(EXIT_FAILURE);
    }
    if (argv[2][0] == '-'){
        if(argv[2][1] == 'r' && argv[2][2] == '\0' && argc == 5){
            *n_pts = atoi (argv[3]);
            *max_cor = atoi (argv[4]);
            if (*n_pts <= 0 || *max_cor <= 0){
                printf("ERROR: Parameters must be positive\n");
                man(1);
                exit(EXIT_FAILURE);
            }
            if (*n_pts > PTSLIM || *max_cor > CORLIM){
                printf ("ERROR: Parameters exceed limits\n");
                man(1);
                exit(EXIT_FAILURE);
            }
            return 1;
        }
        else{
            printf ("ERROR: Incompatible arguments\n");
            man(0);
            exit(EXIT_FAILURE);
        }
    }
    else if (argc == 3){
        *extnode = fopen (argv[2], "r");
        if (*extnode == NULL){
            printf("ERROR: Could not open file\n");
            man(0);
            exit(EXIT_FAILURE);
        }
        return 0;
    }
    else{
        printf ("ERROR: Too many arguments\n");
        man(0);
        exit(EXIT_FAILURE);
    }
}

void init_random(FILE **node, int n_pts, float max_cor){

    // In random mode we generate a random square cloud of points 
    // whose max coordinate has absolute value max_cor.
    // We then write in result.node three points that wrap the cloud
    // and then all the other points
    
    point prov;
    fprintf (*node, "%d 2 0 0\n", n_pts+3);
    srand((unsigned)time(NULL));

    set_pt(&prov, -max_cor*3, -max_cor*3, 0);
    fprint_pt (*node, &prov);
    set_pt(&prov, 0, max_cor*3, 1);
    fprint_pt (*node, &prov);
    set_pt(&prov, max_cor*3, 0, 2);
    fprint_pt (*node, &prov);        
    #ifdef LOG
    	printf("Mock point 0 = " PT_FRMT "\n", (float)-max_cor*3, (float)-max_cor*3);
        printf("Mock point 1 = " PT_FRMT "\n", (float)0, (float)max_cor*3);
        printf("Mock point 2 = " PT_FRMT "\n", (float)max_cor*3, (float)0);
    #endif

    int i;
    for(i = 3; i < n_pts+3; i++){
        prov.x = (float)rand()/(float)(RAND_MAX/(max_cor*2))-max_cor;
        prov.y = (float)rand()/(float)(RAND_MAX/(max_cor*2))-max_cor;
        prov.id = i;
        fprint_pt (*node, &prov);
        #ifdef LOG
            printf("Point");
            print_pt_id(prov);
            printf("= ");
            print_pt(prov);
        #endif
    }

    return;
}

void init_from_file(FILE **extnode, FILE **node, int *n_pts_ptr){

    // From file mode first scans the given .node file, checking for formatting errors
    // and finding the max coordinate of the points listed.
    // After that we write in result.node the three points wrapping all input points,
    // which we then copy as well

    int n_pts;
    float max_cor = 0;

    point prov;
    if(fscanf (*extnode, "%d %*[^\n]\n", &n_pts) == EOF){
        printf("ERROR: Input file is empty\n");
        man(0);
        exit(EXIT_FAILURE);
    }

    int i;
    for (i = 0; i < n_pts; i++){
        if (fscanf (*extnode, "%d %f %f \n", &prov.id, &prov.x, &prov.y) != 3 || prov.id != i){
            printf("ERROR: Error in input file format at line %d\n", i+2);
            man(1);
            exit(EXIT_FAILURE);
        }

        if (prov.x > max_cor) max_cor = prov.x;
        if (-prov.x > max_cor) max_cor = -prov.x;
        if (prov.y > max_cor) max_cor = prov.y;
        if (-prov.y > max_cor) max_cor = -prov.y;
        
        if(max_cor > CORLIM){
            printf("ERROR: Error in input file: coordinate too big at line %d\n", i+2);
            man(1);
            exit(EXIT_FAILURE);
        }
    }

    fprintf (*node, "%d 2 0 0\n", n_pts+3);
    set_pt(&prov, -max_cor*3, -max_cor*3, 0);
    fprint_pt (*node, &prov);
    set_pt(&prov, 0, max_cor*3, 1);
    fprint_pt (*node, &prov);
    set_pt(&prov, max_cor*3, 0, 2);
    fprint_pt (*node, &prov);

    fseek (*extnode, 0, SEEK_SET);
    fscanf (*extnode, "%*[^\n]\n");
    for (i = 0; i < n_pts; i++){
        fscanf (*extnode, "%d %f %f \n", &prov.id, &prov.x, &prov.y);
        prov.id += 3;
        fprint_pt (*node, &prov);
    }

    (*n_pts_ptr) = n_pts;
    fclose (*extnode);
}

int load_xclbin (const char *filename, char **result){
	uint size = 0;
	FILE *f = fopen(filename, "rb");
	if (f == NULL){
		printf ("ERROR: Could not open xclbin file\n");
		man (0);
		exit(EXIT_FAILURE);
	}
	fseek (f, 0, SEEK_END);
	size = ftell(f);
	fseek (f, 0, SEEK_SET);
	*result = (char *)malloc(size+1);
	if(size != fread(*result, sizeof(char), size, f)){
		free (*result);
		printf("ERROR: Could not read xclbin file\n");
		man (0);
		exit(EXIT_FAILURE);
	}
	fclose(f);
	(*result)[size] = 0;
	return size;
}

// prints manual
void man (int verbose){
    printf("\nAvaiable modes:\n");
    printf("From file:\t./fidelta [PATH_TO_XCLBIN] [PATH_TO_FILE]\n");
    printf("Random: \t./fidelta [PATH_TO_XCLBIN] -r [N_PTS] [MAX_COORDINATE]\n\n");
    printf("Input files must follow .node convention defined in README\n");

    if(verbose){
        printf("[N_PTS] range is [1; %d]\n", PTSLIM);
        printf("[MAX_COORDINATE] range is [1; %d]\n", CORLIM);
    }
    printf("\n");
    return;
}

// prints point on file following .node format
void fprint_pt(FILE *f, point *pt){
    fprintf(f,"%d %f %f\n",pt->id, pt->x, pt->y);
    return;
}

// prints triangle on file following .ele format
void fprint_t(FILE *f, triangle *t){
    fprintf(f, "%d %d %d\n", t->p1.id, t->p2.id, t->p3.id);
    return;
}

// deletes wrong triangles and prints correct ones on ele file
void print_result(t_node *tris, int n_pts){
    
    // Output section
    // soldim and gendim are the dimension of the triangulation with and without dummy points, 
    // tridim the dimension of the list tris:
    // We scan through tris, every triangle who hasn't encroaching points
    // is part of the triangulation and we print it

    FILE *ele = fopen (RESPATHNOEXT ".ele", "w");
    if (ele == NULL){
        printf ("ERROR: Could not create result.ele\n");
        exit(EXIT_FAILURE);
    }

    int soldim=0, tridim=0, gendim=0;
    t_node *tprobe = tris, *temp;
    
    // We screw triangles with vertices on artificial bound. 
    // The triangles obtained are all part of the correct Delaunay triangulation, 
    // but some external edges that form the convex hull may be missing 

    while (tprobe != NULL){

        tridim++;

        if (tprobe->dim != 0){
            temp = tprobe;
            tprobe = tprobe->next;
            pop_t (temp, &tris);
        }      

        else if (tprobe->t.p1.id < 3 || tprobe->t.p2.id < 3 || tprobe->t.p3.id < 3){
            temp = tprobe;
            tprobe = tprobe->next;
            pop_t (temp, &tris);
            gendim++;
        }
        
        else{
            tprobe = tprobe->next;
            gendim++;
            soldim++;
        }

    }

    fprintf (ele, "%d 3 0\n", soldim);
    tprobe = tris;

    int i = 0;
    while (tprobe != NULL){

        fprintf (ele, "%d ", i);
        fprint_t (ele, &tprobe->t);
        tprobe = tprobe->next;
        i++;

    }
  
    fclose (ele);
    
    // From the theory we know that a correct triangulation must have 2*(points)-5 triangles.
    // Note that we added the three bounding points

    if (gendim == 2*(n_pts + 3) - 5)   
        printf ("Generated %d triangles: Correct\n", soldim);
    else
        printf ("Generated %d triangles: Incorrect\n", soldim);

    return;
}

//--------------------------------------//
// Functions for log and debug purposes //
//--------------------------------------//

void print_pt(point pt){
    printf( PT_FRMT "\n", pt.x, pt.y);
    return;
}

void print_pt_id(point pt){
    printf("%2d ", pt.id);
    return;
}

void print_seg(segment seg){
    printf(PT_FRMT "-" PT_FRMT, seg.a.x, seg.a.y, seg.b.x, seg.b.y);
    return;
}

void print_seg_id(segment seg){
    printf("(%d %d)", seg.a.id, seg.b.id);
    return;
}

void print_t(triangle t){
    printf(PT_FRMT "-" PT_FRMT "-" PT_FRMT "\n", t.p1.x, t.p1.y, t.p2.x, t.p2.y, t.p3.x, t.p3.y);
    return;
}

void print_t_id(triangle t){
    printf("(%d %d %d)", t.p1.id, t.p2.id, t.p3.id);
    return;
}

void print_t_exp(triangle t){
    printf("Tri:\n\t" PT_FRMT "-" PT_FRMT "\n\t" PT_FRMT "-" PT_FRMT "\n\t" PT_FRMT "-" PT_FRMT "\n",
           t.p1.x, t.p1.y, t.p2.x, t.p2.y,
           t.p2.x, t.p2.y, t.p3.x, t.p3.y,
           t.p1.x, t.p1.y, t.p3.x, t.p3.y);
    return;
}

void print_tris(t_node *tris){
    printf("\nTriangoli in tris:\n");
    while(tris != NULL){
        print_t(tris->t);
        int i;
        for(i = 0; i < tris->dim; i++){
            printf("\t" PT_FRMT "\n", tris->enc[i].x, tris->enc[i].y);
        }
        tris = tris->next;
    }
}

void print_tris_id(t_node *tris){
    printf("\nTriangoli in tris:\n");
    while(tris != NULL){
        printf("%2d %2d %2d  -->",tris->t.p1.id, tris->t.p2.id, tris->t.p3.id);
        int i;
        for(i = 0; i < tris->dim; i++){
            printf(" %d", tris->enc[i].id);
        }
        printf ("\n");
        tris = tris->next;
    }
    return;
}

void print_segs(record_segs *elem){
    printf("\n Elements in segs:\n");
    while(elem != NULL){
        print_seg(elem->seg);
        if(elem->tfirst){
            printf("\t");
            print_t(elem->tfirst->t);
        } 
        else printf("\tnil\n");
        
        if(elem->tsecond) {
            printf("\t");
            print_t(elem->tsecond->t); 
        }    
        else printf("\tnil\n");
        
        elem = (record_segs *) elem->hh.next;
    }
    return;
}

void print_segs_id(record_segs *elem){
    printf("\n Elements in segs:\n");
    while(elem != NULL){
        print_pt_id(elem->seg.a);
        print_pt_id(elem->seg.b);
        printf(" --> (");
        if(elem->tfirst){
            print_pt_id(elem->tfirst->t.p1);
            print_pt_id(elem->tfirst->t.p2);
            print_pt_id(elem->tfirst->t.p3);
        } 
        else printf(" --> (nil");
        
        if(elem->tsecond) {
            printf(") (");
            print_pt_id(elem->tsecond->t.p1);
            print_pt_id(elem->tsecond->t.p2);
            print_pt_id(elem->tsecond->t.p3);
            printf(")"); 
        }    
        else printf(") (nil)");
        printf("\n");
        elem = (record_segs *) elem->hh.next;
    }
    return;
}

void print_acts_id(act_node *acts){
    printf("\nElements in act: \n");
    while(acts != NULL){
        print_seg_id(acts->act->seg);
        printf(" -> ");
        print_pt_id(acts->father->enc[0]); 
        printf(", ");
        print_t_id(acts->father->t);
        if(acts->uncle != NULL){
            printf(", ");
            print_t_id(acts->uncle->t);
        }
        printf("\n");
        acts = acts->next;
    }
}
