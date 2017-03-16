// Test básicos...

#include "csmtest.h"

#include "csmedge.inl"
#include "csmedge.tli"
#include "csmhedge.inl"
#include "csmsolid.inl"
#include "csmeuler_mvfs.inl"
#include "csmeuler_kvfs.inl"
#include "csmeuler_lmef.inl"
#include "csmeuler_lmev.inl"
#include "csmeuler_lkef.inl"
#include "csmeuler_lkev.inl"
#include "csmeuler_lkemr.inl"
#include "csmeuler_lmekr.inl"

#include "csmnode.inl"
#include "csmopbas.inl"

#include "cyassert.h"

// ------------------------------------------------------------------------------------------

static void i_test_crea_destruye_solido_vacio(void)
{
    struct csmsolid_t *solido;
    unsigned long id_nuevo_elemento;
    
    id_nuevo_elemento = 0;
    
    solido = csmeuler_mvfs(0., 0., 0., &id_nuevo_elemento, NULL);
    
    csmeuler_kvfs(solido);
    
    csmsolid_destruye(&solido);
}

// ------------------------------------------------------------------------------------------

static void i_test_basico_solido_una_arista(void)
{
    struct csmsolid_t *solido;
    unsigned long id_nuevo_elemento;
    struct csmhedge_t *hedge;
    struct csmhedge_t *he1, *he2;
    
    id_nuevo_elemento = 0;
    
    solido = csmeuler_mvfs(0., 0., 0., &id_nuevo_elemento, &hedge);
    
    csmeuler_lmev(hedge, hedge, 1., 0., 0., &id_nuevo_elemento, NULL, NULL, &he1, &he2);
    
    csmeuler_lkev(&he1, &he2, &he1, NULL, &he2, NULL);
    assert(he1 == he2);

    csmeuler_kvfs(solido);
    
    csmsolid_destruye(&solido);
}

// ------------------------------------------------------------------------------------------

static void i_test_crea_lamina(void)
{
    struct csmsolid_t *solido;
    unsigned long id_nuevo_elemento;
    struct csmhedge_t *initial_hedge, *hedge_from_vertex1, *hedge_from_vertex2, *hedge_from_vertex3;
    struct csmhedge_t *he_pos, *he_neg;
    struct csmhedge_t *he1, *he2;
    
    id_nuevo_elemento = 0;
    
    solido = csmeuler_mvfs(0., 0., 0., &id_nuevo_elemento, &initial_hedge);
    
    csmeuler_lmev_strut_edge(initial_hedge, 1., 0., 0., &id_nuevo_elemento, &hedge_from_vertex1);
    csmeuler_lmev_strut_edge(hedge_from_vertex1, 1., 1., 0., &id_nuevo_elemento, &hedge_from_vertex2);
    csmeuler_lmev_strut_edge(hedge_from_vertex2, 0., 1., 0., &id_nuevo_elemento, &hedge_from_vertex3);
    csmeuler_lmef(initial_hedge, hedge_from_vertex3, &id_nuevo_elemento, NULL, &he_pos, &he_neg);
    
    csmeuler_lkef(&he_pos, &he_neg);
    assert(he_pos != NULL);
    assert(he_neg != NULL);
    assert(he_pos == hedge_from_vertex3);
    
    he1 = he_pos;
    he2 = csmopbas_mate(he1);
    csmeuler_lkev(&he1, &he2, NULL, &he1, &he2, NULL);
    assert(he1 == hedge_from_vertex2);

    he2 = csmopbas_mate(he1);
    csmeuler_lkev(&he1, &he2, NULL, &he1, &he2, NULL);
    assert(he1 == hedge_from_vertex1);

    he2 = csmopbas_mate(he1);
    csmeuler_lkev(&he1, &he2, NULL, &he1, &he2, NULL);
    assert(he1 == he2);
    assert(he1 == initial_hedge);
    
    csmeuler_kvfs(solido);
    
    csmsolid_destruye(&solido);
}

// ------------------------------------------------------------------------------------------

static void i_test_crea_lamina_con_hueco(void)
{
    struct csmsolid_t *solido;
    unsigned long id_nuevo_elemento;
    struct csmhedge_t *initial_hedge, *hedge_from_vertex1, *hedge_from_vertex2, *hedge_from_vertex3;
    struct csmhedge_t *he_pos, *he_neg;
    struct csmhedge_t *he1, *he2;
    
    id_nuevo_elemento = 0;
    
    solido = csmeuler_mvfs(0., 0., 0., &id_nuevo_elemento, &initial_hedge);
    
    csmeuler_lmev_strut_edge(initial_hedge, 10., 0., 0., &id_nuevo_elemento, &hedge_from_vertex1);
    csmeuler_lmev_strut_edge(hedge_from_vertex1, 10., 1.0, 0., &id_nuevo_elemento, &hedge_from_vertex2);
    csmeuler_lmev_strut_edge(hedge_from_vertex2, 0., 10., 0., &id_nuevo_elemento, &hedge_from_vertex3);
    csmeuler_lmef(initial_hedge, hedge_from_vertex3, &id_nuevo_elemento, NULL, &he_pos, &he_neg);
    
    // Hueco de un sólo vértice...
    {
        struct csmhedge_t *he_from_vertex, *he_to_vertex;
        struct csmhedge_t *he1_hole_pos_next, *he2_hole_pos_next;
        struct csmhedge_t *hedge_lado_neg, *hedge_lado_pos;
        
        csmeuler_lmev(he_pos, he_pos, 1., 1., 0., &id_nuevo_elemento, NULL, NULL, &he_from_vertex, &he_to_vertex);
        csmeuler_lkemr(&he_to_vertex, &he_from_vertex, &id_nuevo_elemento, &he1_hole_pos_next, &he2_hole_pos_next);
        
        csmeuler_lmekr(he1_hole_pos_next, he2_hole_pos_next, &id_nuevo_elemento, &hedge_lado_neg, &hedge_lado_pos);
        csmeuler_lkev(&hedge_lado_neg, &hedge_lado_pos, &hedge_lado_neg, NULL, NULL, &hedge_lado_pos);
        assert(hedge_lado_neg != NULL);
        assert(hedge_lado_pos != NULL);
        assert(hedge_lado_pos == he_pos);
        assert(hedge_lado_neg == hedge_from_vertex1);
    }
    
    csmeuler_lkef(&he_pos, &he_neg);
    assert(he_pos != NULL);
    assert(he_neg != NULL);
    assert(he_pos == hedge_from_vertex3);
    
    he1 = he_pos;
    he2 = csmopbas_mate(he1);
    csmeuler_lkev(&he1, &he2, NULL, &he1, &he2, NULL);
    assert(he1 == hedge_from_vertex2);

    he2 = csmopbas_mate(he1);
    csmeuler_lkev(&he1, &he2, NULL, &he1, &he2, NULL);
    assert(he1 == hedge_from_vertex1);

    he2 = csmopbas_mate(he1);
    csmeuler_lkev(&he1, &he2, NULL, &he1, &he2, NULL);
    assert(he1 == he2);
    assert(he1 == initial_hedge);
    
    csmeuler_kvfs(solido);
    
    csmsolid_destruye(&solido);
}

// ------------------------------------------------------------------------------------------

static void i_test_crea_hexaedro(void)
{
    struct csmsolid_t *solido;
    unsigned long id_nuevo_elemento;
    struct csmhedge_t *hei, *he1, *he2, *he3, *he4_pos, *he4;
    struct csmhedge_t *he1_top, *he2_top, *he3_top, *he4_top;
    struct csmhedge_t *he1_top_next, *he1_top_next_next, *he1_top_next_next_next;
    
    id_nuevo_elemento = 0;
    
    solido = csmeuler_mvfs(0., 0., 0., &id_nuevo_elemento, &hei);
    csmsolid_print_debug(solido, CIERTO);
    
    // Cara inferior...
    {
        csmeuler_lmev_strut_edge(hei, 10.,  0., 0., &id_nuevo_elemento, &he1);
        csmeuler_lmev_strut_edge(he1, 10., 10., 0., &id_nuevo_elemento, &he2);
        csmeuler_lmev_strut_edge(he2,  0., 10., 0., &id_nuevo_elemento, &he3);
        csmeuler_lmef(hei, he3, &id_nuevo_elemento, NULL, &he4, NULL);
        assert(csmopbas_mate(he1) == hei);
    }

    csmsolid_print_debug(solido, CIERTO);
    
    // Aristas verticales...
    {
        csmeuler_lmev_strut_edge(he1, 10.,  0., 10., &id_nuevo_elemento, &he1_top);
        csmeuler_lmev_strut_edge(he2, 10., 10., 10., &id_nuevo_elemento, &he2_top);
        csmeuler_lmev_strut_edge(he3,  0., 10., 10., &id_nuevo_elemento, &he3_top);
        csmeuler_lmev_strut_edge(he4,  0.,  0., 10., &id_nuevo_elemento, &he4_top);
        
        assert(csmhedge_loop(he1_top) == csmhedge_loop(he2_top));
        assert(csmhedge_loop(he1_top) == csmhedge_loop(he3_top));
        assert(csmhedge_loop(he1_top) == csmhedge_loop(he4_top));
    }

    csmsolid_print_debug(solido, CIERTO);
    
    csmeuler_lmef(he4_top, he3_top, &id_nuevo_elemento, NULL, NULL, NULL);
    csmeuler_lmef(he3_top, he2_top, &id_nuevo_elemento, NULL, NULL, NULL);
    csmeuler_lmef(he2_top, he1_top, &id_nuevo_elemento, NULL, NULL, NULL);

    //csmeuler_lmef(he1_top, he4_top, &id_nuevo_elemento, NULL, NULL, NULL);
    
    he1_top_next = csmhedge_next(he1_top);
    assert(he1_top_next == he1);
    
    he1_top_next_next = csmhedge_next(he1_top_next);
    he1_top_next_next_next = csmhedge_next(he1_top_next_next);
    assert(csmhedge_vertex(he1_top_next_next_next) == csmhedge_vertex(he4_top));

    csmsolid_print_debug(solido, CIERTO);
    
    csmeuler_lmef(he1_top, he1_top_next_next_next, &id_nuevo_elemento, NULL, NULL, NULL);
    
    csmsolid_print_debug(solido, CIERTO);
    
    csmsolid_destruye(&solido);
}

// ------------------------------------------------------------------------------------------

void csmtest_test(void)
{
    i_test_crea_destruye_solido_vacio();
    i_test_basico_solido_una_arista();
    i_test_crea_lamina();
    i_test_crea_lamina_con_hueco();
    i_test_crea_hexaedro();
}





