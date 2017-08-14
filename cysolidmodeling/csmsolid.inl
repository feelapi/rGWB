// Sólido euleriano...

#include "csmfwddecl.hxx"

CONSTRUCTOR(struct csmsolid_t *, csmsolid_crea_vacio, (unsigned long start_id_of_new_element));

void csmsolid_set_name(struct csmsolid_t *solido, const char *name);


// General...

unsigned long *csmsolid_id_new_element(struct csmsolid_t *solido);

CYBOOL csmsolid_is_empty(const struct csmsolid_t *solido);

void csmsolid_clear_algorithm_vertex_mask(struct csmsolid_t *solid);

void csmsolid_redo_geometric_generated_data(struct csmsolid_t *solid);

void csmsolid_merge_solids(struct csmsolid_t *solid, struct csmsolid_t *solid_to_merge);

void csmsolid_revert(struct csmsolid_t *solid);


// Faces...

void csmsolid_append_new_face(struct csmsolid_t *solido, struct csmface_t **face);

void csmsolid_remove_face(struct csmsolid_t *solido, struct csmface_t **face);

void csmsolid_move_face_to_solid(struct csmsolid_t *face_solid, struct csmface_t *face, struct csmsolid_t *destination_solid);

struct csmface_t *csmsolid_get_face(struct csmsolid_t *solid, unsigned long id_face);

CONSTRUCTOR(struct csmhashtb_iterator(csmface_t) *, csmsolid_face_iterator, (struct csmsolid_t *solid));


// Edges...

void csmsolid_append_new_edge(struct csmsolid_t *solido, struct csmedge_t **edge);

void csmsolid_remove_edge(struct csmsolid_t *solido, struct csmedge_t **edge);

void csmsolid_move_edge_to_solid(struct csmsolid_t *edge_solid, struct csmedge_t *edge, struct csmsolid_t *destination_solid);

CYBOOL csmsolid_contains_edge(const struct csmsolid_t *solid, const struct csmedge_t *edge);

CONSTRUCTOR(struct csmhashtb_iterator(csmedge_t) *, csmsolid_edge_iterator, (struct csmsolid_t *solid));


// Vertexs...

void csmsolid_append_new_vertex(struct csmsolid_t *solido, double x, double y, double z, struct csmvertex_t **vertex);

void csmsolid_remove_vertex(struct csmsolid_t *solido, struct csmvertex_t **vertex);

void csmsolid_move_vertex_to_solid(struct csmsolid_t *vertex_solid, struct csmvertex_t *vertex, struct csmsolid_t *destination_solid);

CYBOOL csmsolid_contains_vertex(const struct csmsolid_t *solid, const struct csmvertex_t *vertex);

CONSTRUCTOR(struct csmhashtb_iterator(csmvertex_t) *, csmsolid_vertex_iterator, (struct csmsolid_t *solid));

CYBOOL csmsolid_contains_vertex_in_same_coordinates_as_given(
                        struct csmsolid_t *solid,
                        const struct csmvertex_t *vertex,
                        double tolerance,
                        struct csmvertex_t **coincident_vertex);


// Debug...

void csmsolid_print_debug(struct csmsolid_t *solido, CYBOOL assert_si_no_es_integro);
