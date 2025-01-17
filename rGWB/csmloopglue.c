//
//  cmsloopglue.c
//  rGWB
//
//  Created by Manuel Fernández on 1/4/17.
//  Copyright © 2017 Manuel Fernández. All rights reserved.
//

#include "csmloopglue.inl"

#include "csmdebug.inl"
#include "csmeuler_lkef.inl"
#include "csmeuler_lkev.inl"
#include "csmeuler_lkfmrh.inl"
#include "csmeuler_lmef.inl"
#include "csmeuler_lmekr.inl"
#include "csmface.inl"
#include "csmhedge.inl"
#include "csmloop.inl"
#include "csmopbas.inl"
#include "csmsolid.inl"
#include "csmtolerance.inl"
#include "csmvertex.inl"

#ifdef RGWB_STANDALONE_DISTRIBUTABLE
#include "csmassert.inl"
#else
#include "cyassert.h"
#endif

// ----------------------------------------------------------------------------------------------------

static CSMBOOL i_does_face2_outer2_a_common_vertex_with_face1(
                        struct csmloop_t *flout_face2,
                        struct csmvertex_t *vertex_face1,
                        double tolerance,
                        struct csmhedge_t **scan_hedge_face2)
{
    struct csmhedge_t *scan_hedge_face2_loc;
    struct csmhedge_t *lhedge_face2, *iterator_hedge_face2;
    CSMBOOL found_common_vertex;
    
    assert_no_null(scan_hedge_face2);
    
    lhedge_face2 = csmloop_ledge(flout_face2);
    iterator_hedge_face2 = lhedge_face2;
    
    found_common_vertex = CSMFALSE;
    scan_hedge_face2_loc = NULL;
    
    do
    {
        struct csmvertex_t *vertex2;
        
        vertex2 = csmhedge_vertex(iterator_hedge_face2);
        
        if (csmvertex_equal_coords(vertex_face1, vertex2, tolerance) == CSMTRUE)
        {
            found_common_vertex = CSMTRUE;
            scan_hedge_face2_loc = iterator_hedge_face2;
        }
        else
        {
            iterator_hedge_face2 = csmhedge_next(iterator_hedge_face2);
        }
        
    } while (found_common_vertex == CSMFALSE && iterator_hedge_face2 != lhedge_face2);
    
    *scan_hedge_face2 = scan_hedge_face2_loc;
    
    return found_common_vertex;
}

// ----------------------------------------------------------------------------------------------------

static CSMBOOL i_is_possible_to_merge_loops(
                        struct csmloop_t *flout_face1, struct csmloop_t *flout_face2,
                        const struct csmtolerance_t *tolerances,
                        struct csmhedge_t **common_hedge_face1, struct csmhedge_t **common_hedge_face2)
{
    CSMBOOL is_possible_to_merge_loops;
    struct csmhedge_t *common_hedge_face1_loc, *common_hedge_face2_loc;
    struct csmhedge_t *lhedge_face1, *lhedge_face2;
    struct csmvertex_t *vertex_face1;
    double tolerance;
    
    assert_no_null(common_hedge_face1);
    assert_no_null(common_hedge_face2);
    
    lhedge_face1 = csmloop_ledge(flout_face1);
    vertex_face1 = csmhedge_vertex(lhedge_face1);
    tolerance = csmtolerance_equal_coords(tolerances);
    
    if (i_does_face2_outer2_a_common_vertex_with_face1(flout_face2, vertex_face1, tolerance, &lhedge_face2) == CSMFALSE)
    {
        is_possible_to_merge_loops = CSMFALSE;
        
        common_hedge_face1_loc = NULL;
        common_hedge_face2_loc = NULL;
    }
    else
    {
        struct csmhedge_t *iterator_hedge1, *iterator_hedge2;
        unsigned long num_iters;
        
        iterator_hedge1 = lhedge_face1;
        iterator_hedge2 = lhedge_face2;
        
        is_possible_to_merge_loops = CSMTRUE;
        num_iters = 0;
        
        do
        {
            struct csmvertex_t *vertex1, *vertex2;
            
            assert(num_iters < 100000);
            num_iters++;
            
            vertex1 = csmhedge_vertex(iterator_hedge1);
            vertex2 = csmhedge_vertex(iterator_hedge2);
            
            if (csmvertex_equal_coords(vertex1, vertex2, tolerance) == CSMFALSE)
            {
                is_possible_to_merge_loops = CSMFALSE;
            }
            else
            {
                iterator_hedge1 = csmhedge_next(iterator_hedge1);
                iterator_hedge2 = csmhedge_prev(iterator_hedge2);
                
                if (iterator_hedge1 == lhedge_face1 && iterator_hedge2 != lhedge_face2)
                    is_possible_to_merge_loops = CSMFALSE;
                else if (iterator_hedge1 != lhedge_face1 && iterator_hedge2 == lhedge_face2)
                    is_possible_to_merge_loops = CSMFALSE;
                else if (iterator_hedge1 == lhedge_face1 && iterator_hedge2 == lhedge_face2)
                    break;
            }
            
        } while(is_possible_to_merge_loops == CSMTRUE);
        
        if (is_possible_to_merge_loops == CSMTRUE)
        {
            common_hedge_face1_loc = iterator_hedge1;
            common_hedge_face2_loc = iterator_hedge2;
        }
        else
        {
            common_hedge_face1_loc = NULL;
            common_hedge_face2_loc = NULL;
        }
    }
    
    *common_hedge_face1 = common_hedge_face1_loc;
    *common_hedge_face2 = common_hedge_face2_loc;
    
    return is_possible_to_merge_loops;
}

// ----------------------------------------------------------------------------------------------------

static CSMBOOL i_is_possible_to_merge_faces(
                        struct csmface_t *face1, struct csmface_t *face2,
                        const struct csmtolerance_t *tolerances,
                        struct csmhedge_t **common_hedge_face1, struct csmhedge_t **common_hedge_face2)
{
    CSMBOOL is_possible_to_merge_faces;
    struct csmhedge_t *common_hedge_face1_loc, *common_hedge_face2_loc;
    
    assert_no_null(common_hedge_face1);
    assert_no_null(common_hedge_face2);
    
    if (csmface_has_holes(face1) == CSMTRUE || csmface_has_holes(face2) == CSMTRUE)
    {
        is_possible_to_merge_faces = CSMFALSE;
        
        common_hedge_face1_loc = NULL;
        common_hedge_face2_loc = NULL;
    }
    else
    {
        struct csmloop_t *flout_face1, *flout_face2;
        
        flout_face1 = csmface_flout(face1);
        flout_face2 = csmface_flout(face2);
        
        is_possible_to_merge_faces = i_is_possible_to_merge_loops(
                        flout_face1, flout_face2,
                        tolerances,
                        &common_hedge_face1_loc, &common_hedge_face2_loc);
    }

    *common_hedge_face1 = common_hedge_face1_loc;
    *common_hedge_face2 = common_hedge_face2_loc;
    
    return is_possible_to_merge_faces;
}

// ----------------------------------------------------------------------------------------------------

CSMBOOL csmloopglue_can_merge_faces(
                        struct csmface_t *face1, struct csmface_t *face2,
                        const struct csmtolerance_t *tolerances)
{
    struct csmhedge_t *common_hedge_face1, *common_hedge_face2;
    
    return i_is_possible_to_merge_faces(face1, face2, tolerances, &common_hedge_face1, &common_hedge_face2);
}

// ----------------------------------------------------------------------------------------------------

static void i_glue_loops_given_hedges(struct csmhedge_t *common_hedge_face1, struct csmhedge_t *common_hedge_face2)
{
    struct csmsolid_t *solid;
    struct csmhedge_t *he_prev_common_edge_face1, *he_prev_common_edge_face2;
    struct csmhedge_t *he1_next, *he2_next, *he_iterator;
    unsigned long num_iters;
    struct csmhedge_t *he_iterator_mate;
    
    solid = csmface_fsolid(csmopbas_face_from_hedge(common_hedge_face1));
    
    if (csmdebug_debug_enabled() == CSMTRUE)
        csmsolid_print_complete_debug(solid, CSMTRUE);

    csmeuler_lmekr(common_hedge_face1, common_hedge_face2, &he_prev_common_edge_face1, &he_prev_common_edge_face2);
    csmsolid_print_complete_debug(solid, CSMTRUE);
    csmeuler_lkev(&he_prev_common_edge_face1, &he_prev_common_edge_face2, NULL, &he1_next, NULL, &he2_next);
    assert(he1_next == common_hedge_face1);
    assert(he2_next == common_hedge_face2);
    
    he_iterator = common_hedge_face1;
    num_iters = 0;
    
    if (csmdebug_debug_enabled() == CSMTRUE)
        csmsolid_print_complete_debug(solid, CSMTRUE);

    while (csmhedge_next(he_iterator) != common_hedge_face2)
    {
        struct csmhedge_t *he_next, *he_prev;
        struct csmhedge_t *he_iterator_next, *he_iterator_next_mate;
        
        assert(num_iters < 10000);
        num_iters++;
        
        he_next = csmhedge_next(he_iterator);
        he_prev = csmhedge_prev(he_iterator);

        csmeuler_lmef(he_next, he_prev, NULL, NULL, NULL);
        
        if (csmdebug_debug_enabled() == CSMTRUE)
           csmsolid_print_complete_debug(solid, CSMTRUE);
        
        he_iterator_next = csmhedge_next(he_iterator);
        he_iterator_next_mate = csmopbas_mate(he_iterator_next);
        
        if (csmdebug_debug_enabled() == CSMTRUE)
            csmdebug_print_debug_info("loopglue lkev: (%lu, %lu)\n", csmhedge_id(he_iterator_next), csmhedge_id(he_iterator_next_mate));
        
        csmeuler_lkev(&he_iterator_next, &he_iterator_next_mate, NULL, NULL, NULL, NULL);
        
        he_iterator_mate = csmopbas_mate(he_iterator);
        
        if (csmdebug_debug_enabled() == CSMTRUE)
        {
            csmsolid_print_complete_debug(solid, CSMTRUE);
            csmdebug_print_debug_info("loopglue lkef: (%lu, %lu)\n", csmhedge_id(he_iterator_mate), csmhedge_id(he_iterator));
        }
        
        csmeuler_lkef(&he_iterator_mate, &he_iterator);

        if (csmdebug_debug_enabled() == CSMTRUE)
            csmsolid_print_debug(solid, CSMTRUE);
        
        he_iterator = he_next;
    }

    if (csmdebug_debug_enabled() == CSMTRUE)
        csmsolid_print_debug(solid, CSMTRUE);
    
    he_iterator_mate = csmopbas_mate(he_iterator);
    csmeuler_lkef(&he_iterator_mate, &he_iterator);
}

// ----------------------------------------------------------------------------------------------------

void csmloopglue_merge_faces(
                        struct csmface_t *face1, struct csmface_t **face2,
                        const struct csmtolerance_t *tolerances)
{
    CSMBOOL can_merge_faces;
    struct csmhedge_t *common_hedge_face1, *common_hedge_face2;
    
    assert_no_null(face2);
    
    can_merge_faces = i_is_possible_to_merge_faces(face1, *face2, tolerances, &common_hedge_face1, &common_hedge_face2);
    assert(can_merge_faces == CSMTRUE);
    
    csmeuler_lkfmrh(face1, face2);
    assert(csmloop_lface(csmhedge_loop(common_hedge_face2)) == face1);
    
    i_glue_loops_given_hedges(common_hedge_face1, common_hedge_face2);
}

// ----------------------------------------------------------------------------------------------------

void csmloopglue_merge_face_loops(
                        struct csmface_t *face,
                        const struct csmtolerance_t *tolerances)
{
    struct csmloop_t *loop1, *loop2;
    CSMBOOL did_find_compatible_loop2;
    struct csmhedge_t *common_hedge_loop1, *common_hedge_loop2;
    
    assert_no_null(face);
    
    loop1 = csmface_floops(face);
    loop2 = csmloop_next(loop1);
    assert_no_null(loop2);

    if (csmdebug_debug_enabled() == CSMTRUE)
    {
        //csmdebug_show_face(face, NULL);
        csmdebug_print_debug_info("Begin loopglue, face %lu, loops %lu-%lu\n", csmface_id(face), csmloop_id(loop1), csmloop_id(loop2));
    }
    
    did_find_compatible_loop2 = CSMFALSE;
    
    do
    {
        if (i_is_possible_to_merge_loops(loop1, loop2, tolerances, &common_hedge_loop1, &common_hedge_loop2) == CSMTRUE)
        {
            did_find_compatible_loop2 = CSMTRUE;
            break;
        }
        else
        {
            loop2 = csmloop_next(loop2);
        }
        
    } while (loop2 != NULL && did_find_compatible_loop2 == CSMFALSE);

    assert(did_find_compatible_loop2 == CSMTRUE);
    i_glue_loops_given_hedges(common_hedge_loop1, common_hedge_loop2);

    //assert(loop1 == csmface_floops(face));
    //assert(csmloop_next(loop1) == NULL);
}













