#ifndef DISPLAY_H_INCLUDED
#define DISPLAY_H_INCLUDED

// format of all displayed points
#define PT_FRMT "( %.2f , %.2f )"

// initialization based on command line. Returns 1 if random mode is selected
int init_cmd (int argc, char *argv[], FILE **node, FILE **extnode, int *n_pts, float *max_cor);

// initializing node file with n_pts random points
void init_random(FILE **node, int n_pts, float max_cor);

// initializing node file with n_pts points read from extnode and 3 dummy points
void init_from_file(FILE **extnode, FILE **node, int *n_pts_ptr);

// deletes wrong triangles and prints correct ones on ele file
void print_result(t_node *tris, int n_pts);

// prints manual
void man(int verbose);

// fprints a point (id x y), id shifted by 3
void fprint_pt(FILE *f, int id, float x, float y);

// fprintfs a triangle (id1 id2 id3), ids shifted by 3
void fprint_t(FILE *f, t_node *pt);

// prints a point (x,y)
void print_pt(point pt);

// prints a point (id)
void print_pt_id(point pt);

// prints a segment (xa,ya)-(xb,yb)
void print_seg(segment seg);

void print_seg_id(segment seg);

// prints a triangle (xa,ya)-(xb,yb)-(xc,yc)
void print_t(t_node t);

void print_t_id(t_node t);

// prints a triangle (seg1) (seg2) (seg3)
void print_t_exp(t_node t);

// prints all triangles in tris (xa,ya)-(xb,yb)-(xc,yc)
void print_tris(t_node *tris);

// printf all triangles in tris (id1)-(id2)-(id3)
void print_tris_id(t_node *tris);

// prints the entire hash table (xa,ya)-(xb,yb)
void print_segs(segment *elem);

// prints the entire hash table (id1)-(id2)
void print_segs_id(segment *elem);

void print_acts_id(act_node *acts);

#endif // DISPLAY_H_INCLUDED
