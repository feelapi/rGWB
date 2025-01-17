// Half-Edge...

#include "csmhedge.inl"

#include "csmhashtb.inl"
#include "csmid.inl"
#include "csmnode.inl"
#include "csmvertex.inl"
#include "csmwriteablesolid.tli"

#ifdef RGWB_STANDALONE_DISTRIBUTABLE
#include "csmassert.inl"
#include "csmmem.inl"
#else
#include "cyassert.h"
#include "cypespy.h"
#endif

struct csmhedge_t
{
    struct csmnode_t super;
    
    struct csmedge_t *edge;
    struct csmvertex_t *vertex;
    struct csmloop_t *loop;

    CSMBOOL setop_is_loose_end;
};

// --------------------------------------------------------------------------------------------------------------

static void i_csmhedge_destruye(struct csmhedge_t **hedge)
{
    assert_no_null(hedge);
    assert_no_null(*hedge);
    
    csmnode_dealloc(&(*hedge)->super);
    
    FREE_PP(hedge, struct csmhedge_t);
}

// --------------------------------------------------------------------------------------------------------------

CONSTRUCTOR(static struct csmhedge_t *, i_new, (
                        unsigned long id,
                        struct csmedge_t *edge,
                        struct csmvertex_t *vertex,
                        struct csmloop_t *loop,
                        CSMBOOL setop_is_loose_end))
{
    struct csmhedge_t *hedge;
    
    hedge = MALLOC(struct csmhedge_t);
    
    csmnode_init(&hedge->super, id, i_csmhedge_destruye, csmhedge_t);
    
    hedge->edge = edge;
    hedge->vertex = vertex;
    hedge->loop = loop;
    
    hedge->setop_is_loose_end = setop_is_loose_end;
    
    return hedge;
}

// --------------------------------------------------------------------------------------------------------------

struct csmhedge_t *csmhedge_new(unsigned long *id_new_element)
{
    unsigned long id;
    struct csmedge_t *edge;
    struct csmvertex_t *vertex;
    struct csmloop_t *loop;
    CSMBOOL setop_is_loose_end;
    
    id = csmid_new_id(id_new_element, NULL);

    edge = NULL;
    vertex = NULL;
    loop = NULL;
    
    setop_is_loose_end = CSMFALSE;
    
    return i_new(id, edge, vertex, loop, setop_is_loose_end);
}

// --------------------------------------------------------------------------------------------------------------

CONSTRUCTOR(static struct csmhedge_t *, i_duplicate_hedge, (struct csmloop_t *loop, unsigned long *id_new_element))
{
    unsigned long id;
    struct csmedge_t *edge;
    struct csmvertex_t *vertex;
    CSMBOOL setop_is_loose_end;
    
    id = csmid_new_id(id_new_element, NULL);

    edge = NULL;
    vertex = NULL;
    setop_is_loose_end = CSMFALSE;
    
    return i_new(id, edge, vertex, loop, setop_is_loose_end);
}

// --------------------------------------------------------------------------------------------------------------

struct csmhedge_t *csmhedge_duplicate(
                        const struct csmhedge_t *hedge,
                        struct csmloop_t *loop,
                        unsigned long *id_new_element,
                        struct csmhashtb(csmvertex_t) *relation_svertexs_old_to_new,
                        struct csmhashtb(csmhedge_t) *relation_shedges_old_to_new)
{
    struct csmhedge_t *new_hedge;
    unsigned long id_old_vertex;
    
    assert_no_null(hedge);
    
    new_hedge = i_duplicate_hedge(loop, id_new_element);
    assert_no_null(new_hedge);
    assert(new_hedge->edge == NULL);
    assert(new_hedge->vertex == NULL);
    
    id_old_vertex = csmvertex_id(hedge->vertex);
    new_hedge->vertex = csmhashtb_ptr_for_id(relation_svertexs_old_to_new, id_old_vertex, csmvertex_t);
    new_hedge->setop_is_loose_end = hedge->setop_is_loose_end;
    
    if (csmvertex_hedge(hedge->vertex) == hedge)
        csmvertex_set_hedge(new_hedge->vertex, new_hedge);
    
    csmhashtb_add_item(relation_shedges_old_to_new, hedge->super.id, new_hedge, csmhedge_t);
    
    return new_hedge;
}

// --------------------------------------------------------------------------------------------------------------

struct csmhedge_t *csmhedge_new_from_writeable_hedge(
                        const struct csmwriteablesolid_hedge_t *w_hedge,
                        struct csmloop_t *loop,
                        struct csmhashtb(csmvertex_t) *svertexs,
                        struct csmhashtb(csmhedge_t) *created_shedges)
{
    struct csmhedge_t *hedge;
    struct csmedge_t *edge;
    struct csmvertex_t *vertex;
    CSMBOOL setop_is_loose_end;
    
    assert_no_null(w_hedge);

    edge = NULL;
    vertex = csmhashtb_ptr_for_id(svertexs, w_hedge->vertex_id, csmvertex_t);
    setop_is_loose_end = CSMFALSE;
    
    hedge = i_new(w_hedge->hedge_id, edge, vertex, loop, setop_is_loose_end);
    
    if (w_hedge->is_reference_hedge_of_vertex == CSMTRUE)
    {
        assert(csmvertex_hedge(vertex) == NULL);
        csmvertex_set_hedge(vertex, hedge);
    }
    
    csmhashtb_add_item(created_shedges, hedge->super.id, hedge, csmhedge_t);
    
    return hedge;
}

// --------------------------------------------------------------------------------------------------------------

unsigned long csmhedge_id(const struct csmhedge_t *hedge)
{
    assert_no_null(hedge);
    return hedge->super.id;
}

// --------------------------------------------------------------------------------------------------------------

void csmhedge_reassign_id(struct csmhedge_t *hedge, unsigned long *id_new_element, unsigned long *new_id_opc)
{
    assert_no_null(hedge);
    hedge->super.id = csmid_new_id(id_new_element, new_id_opc);
}

// --------------------------------------------------------------------------------------------------------------

CSMBOOL csmhedge_equal_id(const struct csmhedge_t *hedge1, const struct csmhedge_t *hedge2)
{
    assert_no_null(hedge1);
    assert_no_null(hedge2);
    
    return IS_TRUE(hedge1->super.id == hedge2->super.id);
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

void csmhedge_clear_algorithm_mask(struct csmhedge_t *hedge)
{
    assert_no_null(hedge);
    
    hedge->setop_is_loose_end = CSMFALSE;
}

// ----------------------------------------------------------------------------------------------------

void csmhedge_setop_set_loose_end(struct csmhedge_t *hedge, CSMBOOL is_loose_end)
{
    assert_no_null(hedge);
    hedge->setop_is_loose_end = is_loose_end;
}

// ----------------------------------------------------------------------------------------------------

CSMBOOL csmhedge_setop_is_loose_end(const struct csmhedge_t *hedge)
{
    assert_no_null(hedge);
    return hedge->setop_is_loose_end;
}

// ----------------------------------------------------------------------------------------------------

struct csmhedge_t *csmhedge_next(struct csmhedge_t *hedge)
{
    assert_no_null(hedge);
    return (struct csmhedge_t *)hedge->super.next;
}

// ----------------------------------------------------------------------------------------------------

void csmhedge_set_next(struct csmhedge_t *hedge, struct csmhedge_t *next_hedge)
{
    assert_no_null(hedge);
    csmnode_set_ptr_next(&hedge->super, &next_hedge->super);
}

// ----------------------------------------------------------------------------------------------------

struct csmhedge_t *csmhedge_prev(struct csmhedge_t *hedge)
{
    assert_no_null(hedge);
    return (struct csmhedge_t *)hedge->super.prev;
}

// ----------------------------------------------------------------------------------------------------

void csmhedge_set_prev(struct csmhedge_t *hedge, struct csmhedge_t *prev_hedge)
{
    assert_no_null(hedge);
    csmnode_set_ptr_prev(&hedge->super, &prev_hedge->super);
}







