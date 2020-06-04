#include <stdio.h>
#include <stdlib.h>
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

// initialization based on command line. Returns 1 if random mode is selected
int init (int argc, char *argv[], FILE **node, FILE **ele, FILE **extnode, int *n_pts, float *max_cor){
    
    *node = fopen (RESPATHNOEXT ".node" , "w+");
    if (*node == NULL){
        printf ("ERROR: Could not find output folder. Go inside serial/ or try building again\n");
        exit (1);
    }
    
    *ele = fopen (RESPATHNOEXT ".ele", "w");
    if (*ele == NULL){
        printf ("ERROR: Could not create result.ele\n");
        exit(EXIT_FAILURE);
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

// prints manual
void man (int verbose){
    printf("\nAvaiable modes:\n");
    printf("From file:\t./serial [PATH_TO_FILE]\n");
    printf("Random: \t./serial -r [N_PTS] [MAX_COORDINATE]\n\n");
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
        
        elem = elem->hh.next;
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
        elem = elem->hh.next;
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