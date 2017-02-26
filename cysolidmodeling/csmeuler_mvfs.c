//
//  csmeuler.c
//  cysolidmodeling
//
//  Created by Manuel Fernández on 24/2/17.
//  Copyright © 2017 Manuel Fernández. All rights reserved.
//

#include "csmeuler_mvfs.inl"

#include "csmface.inl"
#include "csmhedge.inl"
#include "csmloop.inl"
#include "csmnode.inl"
#include "csmsolid.inl"

// ----------------------------------------------------------------------------------------------------

struct csmsolid_t *csmsolid_mvfs(double x, double y, double z, unsigned long *id_nuevo_elemento)
{
    struct csmsolid_t *solido;
    struct csmvertex_t *vertex;
    struct csmface_t *face;
    struct csmloop_t *loop;
    struct csmhedge_t *hedge;
    
    solido = csmsolid_crea_vacio(id_nuevo_elemento);
    
    csmsolid_crea_nueva_cara(solido, id_nuevo_elemento, &face);
    loop = csmloop_crea(face, id_nuevo_elemento);
    hedge = csmhedge_crea(id_nuevo_elemento);
    csmsolid_crea_nuevo_vertice(solido, x, y, z, id_nuevo_elemento, &vertex);
    
    csmface_set_flout(face, loop);

    csmloop_set_ledge(loop, hedge);
    
    csmhedge_set_vertex(hedge, vertex);
    csmhedge_set_loop(hedge, loop);
    csmhedge_set_next(hedge, hedge);
    csmhedge_set_prev(hedge, hedge);
    
    csmnode_release_ex(&hedge, csmhedge_t);
    csmnode_release_ex(&loop, csmloop_t);
    
    return solido;
}
