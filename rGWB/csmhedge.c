// Half-Edge...

#include "csmhedge.inl"
#include "csmhedge.tli"

#include "csmhashtb.inl"
#include "csmnode.inl"
#include "csmvertex.inl"

#include "csmassert.inl"
#include "csmid.inl"
#include "csmmem.inl"

// --------------------------------------------------------------------------------------------------------------

static void i_csmhedge_destruye(struct csmhedge_t **hedge)
{
    assert_no_null(hedge);
    assert_no_null(*hedge);

    FREE_PP(hedge, struct csmhedge_t);
}

// --------------------------------------------------------------------------------------------------------------

CONSTRUCTOR(static struct csmhedge_t *, i_crea, (
                        unsigned long id,
                        struct csmedge_t *edge,
                        struct csmvertex_t *vertex,
                        struct csmloop_t *loop))
{
    struct csmhedge_t *hedge;
    
    hedge = MALLOC(struct csmhedge_t);
    
    hedge->clase_base = csmnode_crea_node(id, hedge, i_csmhedge_destruye, csmhedge_t);
    
    hedge->edge = edge;
    hedge->vertex = vertex;
    hedge->loop = loop;
    
    return hedge;
}

// --------------------------------------------------------------------------------------------------------------

struct csmhedge_t *csmhedge_crea(unsigned long *id_nuevo_elemento)
{
    unsigned long id;
    struct csmedge_t *edge;
    struct csmvertex_t *vertex;
    struct csmloop_t *loop;
    
    id = csmid_new_id(id_nuevo_elemento, NULL);

    edge = NULL;
    vertex = NULL;
    loop = NULL;
    
    return i_crea(id, edge, vertex, loop);
}

// --------------------------------------------------------------------------------------------------------------

CONSTRUCTOR(static struct csmhedge_t *, i_duplicate_hedge, (struct csmloop_t *loop, unsigned long *id_nuevo_elemento))
{
    unsigned long id;
    struct csmedge_t *edge;
    struct csmvertex_t *vertex;
    
    id = csmid_new_id(id_nuevo_elemento, NULL);

    edge = NULL;
    vertex = NULL;
    
    return i_crea(id, edge, vertex, loop);
}

// --------------------------------------------------------------------------------------------------------------

struct csmhedge_t *csmhedge_duplicate(
                        const struct csmhedge_t *hedge,
                        struct csmloop_t *loop,
                        unsigned long *id_nuevo_elemento,
                        struct csmhashtb(csmvertex_t) *relation_svertexs_old_to_new,
                        struct csmhashtb(csmhedge_t) *relation_shedges_old_to_new)
{
    struct csmhedge_t *new_hedge;
    unsigned long id_old_vertex;
    
    assert_no_null(hedge);
    
    new_hedge = i_duplicate_hedge(loop, id_nuevo_elemento);
    assert_no_null(new_hedge);
    assert(new_hedge->edge == NULL);
    assert(new_hedge->vertex == NULL);
    
    id_old_vertex = csmvertex_id(hedge->vertex);
    new_hedge->vertex = csmhashtb_ptr_for_id(relation_svertexs_old_to_new, id_old_vertex, csmvertex_t);
    
    if (csmvertex_hedge(hedge->vertex) == hedge)
        csmvertex_set_hedge(new_hedge->vertex, new_hedge);
    
    csmhashtb_add_item(relation_shedges_old_to_new, hedge->clase_base.id, new_hedge, csmhedge_t);
    
    return new_hedge;
}

// --------------------------------------------------------------------------------------------------------------

unsigned long csmhedge_id(const struct csmhedge_t *hedge)
{
    assert_no_null(hedge);
    return hedge->clase_base.id;
}

// --------------------------------------------------------------------------------------------------------------

void csmhedge_reassign_id(struct csmhedge_t *hedge, unsigned long *id_nuevo_elemento, unsigned long *new_id_opc)
{
    assert_no_null(hedge);
    hedge->clase_base.id = csmid_new_id(id_nuevo_elemento, new_id_opc);
}

// --------------------------------------------------------------------------------------------------------------

CSMBOOL csmhedge_id_igual(const struct csmhedge_t *hedge1, const struct csmhedge_t *hedge2)
{
    assert_no_null(hedge1);
    assert_no_null(hedge2);
    
    return IS_TRUE(hedge1->clase_base.id == hedge2->clase_base.id);
}

// --------------------------------------------------------------------------------------------------------------

struct csmedge_t *csmhedge_edge(struct csmhedge_t *hedge)
{
    assert_no_null(hedge);
    return hedge->edge;
}

// --------------------------------------------------------------------------------------------------------------

void csmhedge_set_edge(struct csmhedge_t *hedge, struct csmedge_t *edge)
{
    assert_no_null(hedge);
    hedge->edge = edge;
}

// --------------------------------------------------------------------------------------------------------------

struct csmvertex_t *csmhedge_vertex(struct csmhedge_t *hedge)
{
    assert_no_null(hedge);
    return hedge->vertex;
}

// --------------------------------------------------------------------------------------------------------------

const struct csmvertex_t *csmhedge_vertex_const(const struct csmhedge_t *hedge)
{
    assert_no_null(hedge);
    return hedge->vertex;
}

// --------------------------------------------------------------------------------------------------------------

void csmhedge_set_vertex(struct csmhedge_t *hedge, struct csmvertex_t *vertex)
{
    assert_no_null(hedge);
    hedge->vertex = vertex;
}

// --------------------------------------------------------------------------------------------------------------

struct csmloop_t *csmhedge_loop(struct csmhedge_t *hedge)
{
    assert_no_null(hedge);
    return hedge->loop;
}

// --------------------------------------------------------------------------------------------------------------

void csmhedge_set_loop(struct csmhedge_t *hedge, struct csmloop_t *loop)
{
    assert_no_null(hedge);
    hedge->loop = loop;
}

// ----------------------------------------------------------------------------------------------------

struct csmhedge_t *csmhedge_next(struct csmhedge_t *hedge)
{
    assert_no_null(hedge);
    return csmnode_downcast(csmnode_next(CSMNODE(hedge)), csmhedge_t);
}

// ----------------------------------------------------------------------------------------------------

void csmhedge_set_next(struct csmhedge_t *hedge, struct csmhedge_t *next_hedge)
{
    assert_no_null(hedge);
    csmnode_set_ptr_next(CSMNODE(hedge), CSMNODE(next_hedge));
}

// ----------------------------------------------------------------------------------------------------

struct csmhedge_t *csmhedge_prev(struct csmhedge_t *hedge)
{
    assert_no_null(hedge);
    return csmnode_downcast(csmnode_prev(CSMNODE(hedge)), csmhedge_t);
}

// ----------------------------------------------------------------------------------------------------

void csmhedge_set_prev(struct csmhedge_t *hedge, struct csmhedge_t *prev_hedge)
{
    assert_no_null(hedge);
    csmnode_set_ptr_prev(CSMNODE(hedge), CSMNODE(prev_hedge));
}






