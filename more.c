﻿#include "csmfwddecl.hxx"

void csmdebug_set_treat_improper_solid_operations_as_errors(CSMBOOL value){}
    
CSMBOOL csmdebug_get_treat_improper_solid_operations_as_errors(void){return CSMTRUE;}

CSMBOOL csmdebug_get_debug_screen(void) { return CSMTRUE; }

void csmdebug_set_debug_screen(CSMBOOL value){}
    
void csmdebug_configure_for_fast_testing(void){}
    
void csmdebug_configure(CSMBOOL debug_screen, CSMBOOL debug_visual, CSMBOOL debug_file){}

void csmdebug_set_enabled_by_code(CSMBOOL enabled){}

void csmdebug_enable_visual_debug(void){}
    
CSMBOOL csmdebug_debug_enabled(void) { return CSMTRUE; }

CSMBOOL csmdebug_debug_visual_enabled(void) { return CSMTRUE; }

void csmdebug_set_setop_debug_level(unsigned long debug_level){}

CSMBOOL csmdebug_setop_show_debug_level(unsigned long debug_level) { return CSMTRUE; }

void csmdebug_begin_context(const char *context){}

void csmdebug_end_context(void){}

void csmdebug_print_debug_info(const char *format, ...){}


// Textual debug...

void csmdebug_set_ouput_file(const char *file_path){}
    
void csmdebug_close_output_file(void){}


CSMBOOL csmdebug_is_print_solid_unblocked(void) { return CSMTRUE; }
    
void csmdebug_block_print_solid(void){}
    
void csmdebug_unblock_print_solid(void){}
    

// Graphical debug...

void csmdebug_set_viewer(
                    struct csmviewer_t *viewer,
                    void (*func_show_viewer)(struct csmviewer_t *),
                    void (*func_show_viewer_face)(struct csmviewer_t *, struct csmface_t *, struct csmface_t *),
                    void (*func_set_parameters)(struct csmviewer_t *, struct csmsolid_t *solid1, struct csmsolid_t *solid2),
                    void (*func_set_results)(struct csmviewer_t *, struct csmsolid_t *solid1, struct csmsolid_t *solid2)){}

void csmdebug_set_viewer_parameters(struct csmsolid_t *solid1, struct csmsolid_t *solid2){}
    
void csmdebug_set_viewer_results(struct csmsolid_t *solid_res1, struct csmsolid_t *solid2_res2){}
    
void csmdebug_show_viewer(void){}

void csmdebug_show_face(struct csmface_t *face1, struct csmface_t *face2){}
    
void csmdebug_clear_debug_points(void){}
void csmdebug_append_debug_point(double x, double y, double z, char **description){}
void csmdebug_append_debug_point_const(double x, double y, double z, const char *description){}
    
void csmdebug_clear_plane(void){}
void csmdebug_set_plane(double A, double B, double C, double D){}

void csmdebug_clear_inters_sector(void){}

void csmdebug_set_inters_sector(
                    double x, double y, double z,
                    CSMBOOL with_intersection_line, double Wx_inters, double Wy_inters, double Wz_inters,
                    double Ux1, double Uy1, double Uz1, double Vx1, double Vy1, double Vz1,
                    double Ux2, double Uy2, double Uz2, double Vx2, double Vy2, double Vz2){}
    
CSMBOOL csmdebug_get_enable_face_edge_filter(void) { return CSMTRUE; }
void csmdebug_set_enable_face_edge_filter(CSMBOOL enabled){}
void csmdebug_add_edge_to_filter(unsigned long edge_id){}
void csmdebug_add_face_to_filter(unsigned long face_id){}
CSMBOOL csmdebug_draw_edge(unsigned long edge_id) { return CSMTRUE; }
CSMBOOL csmdebug_draw_face(unsigned long face_id) { return CSMTRUE; }
    
void csmdebug_set_draw_segments(CSMBOOL draw){}
void csmdebug_clear_segments(void){}
void csmdebug_append_segment(double x1, double y1, double z1, double x2, double y2, double z2){}

    
void csmdebug_draw_debug_info(struct bsgraphics2_t *graphics){}

struct csmshape2d_t *csmshape2d_new() {return 0;}

void csmshape2d_free(struct csmshape2d_t **shape2d){}
void csmshape2d_append_new_polygon_with_points_and_normals(struct csmshape2d_t *shape2d, csmArrPoint2D **points, csmArrPoint3D **normals)
{}

void csmshape2d_append_new_polygon_with_points(struct csmshape2d_t *shape2d, csmArrPoint2D **points){}

void csmshape2d_draw_3D(
                        const struct csmshape2d_t *shape2d,
                        double Xo, double Yo, double Zo,
                        double Ux, double Uy, double Uz, double Vx, double Vy, double Vz,
                        CSMBOOL draw_edges,
                        struct bsgraphics2_t *graficos){}

unsigned long csmshape2d_polygon_count(const struct csmshape2d_t* shape2d) { return 0; }

struct csmshape2d_t * csmshape2d_copy (const struct csmshape2d_t *shape2d)
{
    return 0;
}

unsigned long csmshape2d_point_polygon_count(const struct csmshape2d_t *shape2d, unsigned long idx_polygon)
{
    return 0;
}

void csmshape2d_point_polygon_coords(
						const struct csmshape2d_t *shape2d,
						unsigned long idx_polygon, unsigned long idx_point,
						double *x, double *y) {}

CSMBOOL csmshape2d_polygon_is_hole(const struct csmshape2d_t* shape2d, unsigned long idx_polygon) { return CSMTRUE; }