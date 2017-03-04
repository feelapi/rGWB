// Sólido euleriano...

#include "csmfwddecl.hxx"

CONSTRUCTOR(struct csmsolid_t *, csmsolid_crea_vacio, (unsigned long *id_nuevo_elemento));

void csmsolid_append_new_face(struct csmsolid_t *solido, unsigned long *id_nuevo_elemento, struct csmface_t **face);

void csmsolid_append_new_edge(struct csmsolid_t *solido, unsigned long *id_nuevo_elemento, struct csmedge_t **edge);

void csmsolid_append_new_vertex(struct csmsolid_t *solido, double x, double y, double z, unsigned long *id_nuevo_elemento, struct csmvertex_t **vertex);
