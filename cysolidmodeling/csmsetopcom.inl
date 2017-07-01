// Commons operations for Set Operators...

#include "csmfwddecl.hxx"

#include "a_punter.h"
ArrEstructura(csmvertex_t);
ArrEstructura(csmedge_t);
ArrEstructura(csmface_t);
ArrEstructura(csmhedge_t);

// Vertexs...

void csmsetopcom_append_vertex_if_not_exists(struct csmvertex_t *vertex, ArrEstructura(csmvertex_t) *set_of_on_vertices);


// Hedges...

CYBOOL csmsetopcom_is_edge_on_cycle_of_edges_with_a_side_on_a_hole(struct csmedge_t *edge);

CYBOOL csmsetopcom_hedges_are_neighbors(struct csmhedge_t *he1, struct csmhedge_t *he2);


// Edges...

void csmsetopcom_sort_edges_lexicographically_by_xyz(ArrEstructura(csmedge_t) *set_of_null_edges);

void csmsetopcom_print_set_of_null_edges(const ArrEstructura(csmedge_t) *set_of_null_edges);

CYBOOL csmsetopcom_is_loose_end(struct csmhedge_t *hedge, ArrEstructura(csmhedge_t) *loose_ends);

void csmsetopcom_print_debug_info_loose_ends(const ArrEstructura(csmhedge_t) *loose_ends);

void csmsetopcom_join_hedges(struct csmhedge_t *he1, struct csmhedge_t *he2);

void csmsetopcom_cut_he(
                    struct csmhedge_t *hedge,
                    ArrEstructura(csmedge_t) *set_of_null_edges,
                    ArrEstructura(csmface_t) *set_of_null_faces,
                    unsigned long *no_null_edges_deleted);


// Faces...

CONSTRUCTOR(ArrEstructura(csmface_t) *, csmsetopcom_convert_inner_loops_of_null_faces_to_faces_solid_below, (ArrEstructura(csmface_t) *set_of_null_faces));

void csmsetopcom_reintroduce_holes_in_corresponding_faces(ArrEstructura(csmface_t) *set_of_null_faces);

void csmsetopcom_move_face_to_solid(
                        unsigned long recursion_level,
                        struct csmface_t *face, struct csmsolid_t *face_solid,
                        struct csmsolid_t *destination_solid);

enum csmsetop_classify_resp_solid_t csmsetopcom_classify_value_respect_to_plane(double value, double tolerance);


// Finish algorithm...

void csmsetopcom_revert_solid(struct csmsolid_t *solid);

void csmsetopcom_cleanup_solid(struct csmsolid_t *origin_solid, struct csmsolid_t *destination_solid);

void csmsetopcom_cleanup_solid_setop(
                        struct csmsolid_t *origin_solid_A, struct csmsolid_t *origin_solid_B,
                        struct csmsolid_t *destination_solid);
