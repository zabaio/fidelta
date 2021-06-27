#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
#include <sstream>
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
        exit (1);
    }
    
    if (argc < 2){
        printf ("ERROR: Not enough arguments\n");
        man(0);
        exit(EXIT_FAILURE);
    }
    if (argv[1][0] == '-'){
        if(argv[1][1] == 'r' && argv[1][2] == '\0' && argc == 4){
            *n_pts = atoi (argv[2]);
            *max_cor = atoi (argv[3]);
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
    else if (argc == 2){
        *extnode = fopen (argv[1], "r");
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

    fprintf (*node, "%d 2 0 0\n", n_pts+3);
    srand((unsigned)time(NULL));

    fprint_pt (*node, 0, -max_cor*3, -max_cor*3);
    fprint_pt (*node, 1, 0, max_cor*3);
    fprint_pt (*node, 2, max_cor*3, 0);
    #ifdef LOG
        printf("Mock point 0 = "PT_FRMT"\n", (float)-max_cor*3, (float)-max_cor*3);
        printf("Mock point 1 = "PT_FRMT"\n", (float)0, (float)max_cor*3);
        printf("Mock point 2 = "PT_FRMT"\n", (float)max_cor*3, (float)0);
    #endif

    for(int i = 3; i < n_pts+3; i++){
        fprint_pt (*node, i,
                (float)rand()/(float)(RAND_MAX/(max_cor*2))-max_cor,
                (float)rand()/(float)(RAND_MAX/(max_cor*2))-max_cor);
        #ifdef LOG
            printf("Point");
            print_pt_id(prov);
            printf("= ");
            print_pt(prov);
        #endif
    }
}

void init_from_file(FILE **extnode, FILE **node, int *n_pts_ptr){

    // From file mode first scans the given .node file, checking for formatting errors
    // and finding the max coordinate of the points listed.
    // After that we write in result.node the three points wrapping all input points,
    // which we then copy as well

    int n_pts;
    float max_cor = 0;

    if(fscanf (*extnode, "%d %*[^\n]\n", &n_pts) == EOF){
        printf("ERROR: Input file is empty\n");
        man(0);
        exit(EXIT_FAILURE);
    }

    point prov;
    for (int i = 0; i < n_pts; i++){

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
    fprint_pt (*node, 0, -max_cor*3, -max_cor*3);
    fprint_pt (*node, 1, 0, max_cor*3);
    fprint_pt (*node, 2, max_cor*3, 0);

    fseek (*extnode, 0, SEEK_SET);
    fscanf (*extnode, "%*[^\n]\n");
    for (int i = 0; i < n_pts; i++){
        fscanf (*extnode, "%d %f %f \n", &prov.id, &prov.x, &prov.y);
        fprint_pt (*node, prov.id + 3, prov.x, prov.y);
    }

    (*n_pts_ptr) = n_pts;
    fclose (*extnode);
}


// prints manual
void man (int verbose){
    printf("\nAvaiable modes:\n");
    printf("From file:\t./fidelta [PATH_TO_FILE]\n");
    printf("Random: \t./fidelta -r [N_PTS] [MAX_COORDINATE]\n\n");
    printf("Input files must follow .node convention defined in README\n");

    if(verbose){
        printf("[N_PTS] range is [1; %d]\n", PTSLIM);
        printf("[MAX_COORDINATE] range is [1; %d]\n", CORLIM);
    }
    printf("\n");
}

// prints point on file following .node format
void fprint_pt(FILE *f, int id, float x, float y){
    fprintf(f,"%d %f %f\n",id, x, y);
}

// prints triangulation, omitting initial bounding points
void print_result(t_node *tris, int n_pts){
    
    // Output section
    // soldim and gendim are the dimension of the triangulation with and without dummy points,
    // The triangles obtained are all part of the correct Delaunay triangulation,
    // but some external edges that form the convex hull may be missing

    std::ostringstream result;
    int soldim = 0, gendim = 0, totdim = 0, tot2 = 0;
    std::ofstream outFile;

    outFile.open(RESPATHNOEXT ".ele", std::ios::trunc);
    if (!outFile.is_open()){
        printf("ERROR: Could not create output file\n");
        exit(EXIT_FAILURE);
    }

    while (tris != nullptr){
        totdim++;
        if (tris->lives <= 0) tot2++;
        if (tris->dim == 0){
            gendim++;
            if (tris->p1.id >= 3 && tris->p2.id >= 3 && tris->p3.id >= 3){
                soldim++;
                result << soldim << " " << tris->p1.id << " " << tris->p2.id << " " << tris->p3.id << std::endl;
            }
        }

        tris = tris->next;
    }
    outFile << soldim << " 3 0\n" << result.str();
    outFile.close();

    // From the theory we know that a correct triangulation must have 2*(points)-5 triangles.
    // Note that that takes into account the three bounding points

    if (gendim == 2*(n_pts + 3) - 5) {
        printf("Generated %d triangles\n", totdim);
        printf("Still deletable triangles: %d\n", tot2);
        printf("Dimension of the solution: %d - correct\n", soldim);
    }else
        printf ("Generated %d triangles: Incorrect\n", soldim);
}

//--------------------------------------//
// Functions for log and debug purposes //
//--------------------------------------//

void print_pt(point pt){
    printf( PT_FRMT "\n", pt.x, pt.y);
}

void print_pt_id(point pt){
    printf("%2d ", pt.id);
}

void print_seg(segment seg){
    printf(PT_FRMT "-" PT_FRMT, seg.a.x, seg.a.y, seg.b.x, seg.b.y);
}

void print_seg_id(segment seg){
    printf("(%d %d)", seg.a.id, seg.b.id);
}

void print_t(t_node t){
    printf(PT_FRMT "-" PT_FRMT "-" PT_FRMT "\n", t.p1.x, t.p1.y, t.p2.x, t.p2.y, t.p3.x, t.p3.y);
}

void print_t_id(t_node t){
    printf("(%d %d %d)", t.p1.id, t.p2.id, t.p3.id);
}

void print_t_exp(t_node t){
    printf("Tri:\n\t" PT_FRMT "-" PT_FRMT "\n\t" PT_FRMT "-" PT_FRMT "\n\t" PT_FRMT "-" PT_FRMT "\n",
           t.p1.x, t.p1.y, t.p2.x, t.p2.y,
           t.p2.x, t.p2.y, t.p3.x, t.p3.y,
           t.p1.x, t.p1.y, t.p3.x, t.p3.y);
}

void print_tris(t_node *tris){
    printf("\nTriangoli in tris:\n");
    while(tris != nullptr){
        print_t(*tris);
        int i;
        for(i = 0; i < tris->dim; i++){
            printf("\t" PT_FRMT "\n", tris->enc[i].x, tris->enc[i].y);
        }
        tris = tris->next;
    }
}

void print_tris_id(t_node *tris){
    while(tris != nullptr){
        print_t_id(*tris);
        printf(" %d -->", tris->lives);
        int i;
        for(i = 0; i < tris->dim; i++){
            printf(" %d", tris->enc[i].id);
        }
        printf ("\n");
        tris = tris->next;
    }
}

void print_segs(segment *iter){
    printf("\n Elements in segs:\n");
    while(iter != nullptr){
        print_seg(*iter);
        if(iter->tfirst){
            printf("\t");
            print_t(*iter->tfirst);
        } 
        else printf("\tnil\n");
        
        if(iter->tsecond) {
            printf("\t");
            print_t(*iter->tsecond);
        }    
        else printf("\tnil\n");
        
        iter = (segment *) iter->hh.next;
    }
}

void print_segs_id(segment *iter){

    while(iter != NULL){
        print_pt_id(iter->a);
        print_pt_id(iter->b);
        printf(" --> (");
        if(iter->tfirst){
            print_pt_id(iter->tfirst->p1);
            print_pt_id(iter->tfirst->p2);
            print_pt_id(iter->tfirst->p3);
        } 
        else printf("     (nil");
        
        if(iter->tsecond) {
            printf(") (");
            print_pt_id(iter->tsecond->p1);
            print_pt_id(iter->tsecond->p2);
            print_pt_id(iter->tsecond->p3);
            printf(")"); 
        }    
        else printf(") (nil)");
        printf("\n");
        iter = (segment *) iter->hh.next;
    }
}

void print_acts_id(act_node *acts){
    while(acts != NULL){
        print_seg_id(*acts->seg);
        printf(" -> ");
        print_pt_id(acts->father->enc[0]);
        printf(", ");
        print_t_id(*acts->father);
        if(acts->uncle != NULL){
            printf(", ");
            print_t_id(*acts->uncle);
        }
        printf("\n");
        acts = acts->next;
    }
}