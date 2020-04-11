#ifndef DISPLAY_H_INCLUDED
#define DISPLAY_H_INCLUDED

// prints a point (x,y)
void print_pt(point pt);

// prints a segment (xa,ya)-(xb,yb)
void print_seg(segment seg);

// prints a triangle (xa,ya)-(xb,yb)-(xc,yc)
void print_t(triangle t);

// prints a triangle (seg1) (seg2) (seg3)
void print_t_exp(triangle t);

// prints all triangles in tris
void print_tris(t_node *tris);

// prints the entire hash table
void print_segs(record_segs *elem);

// printf an array of points
void fprint_pts(point* pts, int num_pts);

#endif // DISPLAY_H_INCLUDED
