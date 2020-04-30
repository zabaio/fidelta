#ifndef DISPLAY_H_INCLUDED
#define DISPLAY_H_INCLUDED

// initialization based on command line. Returns 1 if random mode is selected
int init (int argc, char *argv[], FILE **node, FILE **ele, FILE **extnode, int *n_pts, int *max_cor);

// prints manual
void man(int verbose);

// prints a point (x,y)
void print_pt(point pt);
void print_pt_id(point pt);

// prints a segment (xa,ya)-(xb,yb)
void print_seg(segment seg);

// prints a triangle (xa,ya)-(xb,yb)-(xc,yc)
void print_t(triangle t);

// prints a triangle (seg1) (seg2) (seg3)
void print_t_exp(triangle t);

// prints all triangles in tris
void print_tris(t_node *tris);
void print_tris_id(t_node *tris);

// prints the entire hash table
void print_segs(record_segs *elem);
void print_segs_id(record_segs *elem);

// fprints a point (id x y), id shifted by 3
void fprint_pt(FILE *f, point *pt);

// fprintfs a triangle (id1 id2 id3), ids shifted by 3
void fprint_t(FILE *f, triangle *pt);

#endif // DISPLAY_H_INCLUDED
