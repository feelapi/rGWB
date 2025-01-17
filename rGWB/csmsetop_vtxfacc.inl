// Vertex - face classifier...

#include "csmfwddecl.hxx"

// Intersections...

CONSTRUCTOR(struct csmsetop_vtxfacc_inters_t *, csmsetop_vtxfacc_create_inters, (unsigned long intersection_id, struct csmvertex_t *vertex, struct csmface_t *face));

void csmsetop_vtxfacc_free_inters(struct csmsetop_vtxfacc_inters_t **vf_inters);

CSMBOOL csmsetop_vtxfacc_equals(const struct csmsetop_vtxfacc_inters_t *vf_inters1, const struct csmsetop_vtxfacc_inters_t *vf_inters2);


// Classifier...

void csmsetop_vtxfacc_append_null_edges(
                        const csmArrayStruct(csmsetop_vtxfacc_inters_t) *vf_intersections,
                        enum csmsetop_operation_t set_operation, enum csmsetop_a_vs_b_t a_vs_b,
                        const struct csmtolerance_t *tolerances,
                        csmArrayStruct(csmedge_t) *set_of_null_edges,
                        csmArrayStruct(csmedge_t) *set_of_null_edges_other_solid);
