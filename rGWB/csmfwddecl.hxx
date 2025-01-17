//
//  csmfwddecl.h
//  rGWB
//
//  Created by Manuel Fernández on 22/2/17.
//  Copyright © 2017 Manuel Fernández. All rights reserved.
//

#ifndef csmfwddecl_hxx
#define csmfwddecl_hxx

#include "csmtypes.hxx"

#ifdef __cplusplus
extern "C" {
#endif

#define IS_TRUE(condicion) ((condicion) ? CSMTRUE: CSMFALSE)
#define INVERT_BOOLEAN(valor) (((valor) == CSMTRUE) ? CSMFALSE: CSMTRUE)

#include "csmmath.tli"
#include "csmhashtb.hxx"
#include "csmarrayc.hxx"

#ifdef RGWB_STANDALONE_DISTRIBUTABLE

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#define CONSTRUCTOR(type, name, params) type name params

#ifndef UNREFERENCED
    
    #define UNREFERENCED(x) (void)(x)
    
#endif
    
#define ASSIGN_OPTIONAL_VALUE(a, b) if ((a) != NULL) *(a) = (b)
    
#define DLL_RGWB

struct csmnode_t;
struct csmvertex_t;
struct csmhedge_t;
struct csmedge_t;
struct csmloop_t;
struct csmface_t;
struct csmsolid_t;
struct csmtransform_t;
struct csmmaterial_t;
struct csmtolerance_t;
struct csmshape2d_t;
struct csmsurface_t;
struct csmsweep_path_t;
struct csmoptree_t;
struct csmfacbrep2solid_t;
struct csmfacbrep2solid_face_t;
struct csmfacbrep2solid_loop_t;
struct csmsave_t;
struct csmsave_item_t;
struct csmwriteablesolid_t;
struct csmwriteablesolid_vertex_t;
struct csmwriteablesolid_hedge_t;
struct csmwriteablesolid_loop_t;
struct csmwriteablesolid_face_t;
struct csmwriteablesolid_edge_t;
struct csmoctree_t;
struct csmoctree_element_t;

#ifdef __cplusplus
enum csmedge_hedge_side_t: int;
enum csmsetop_operation_t: int;
enum csmsetop_classify_resp_solid_t: int;
enum csmsetop_a_vs_b_t: int;
enum csmoptree_result_t: int;
enum csmnode_object_t: int;
enum csmstlimporter_result_t: int;
enum csmoctree_bbox_inters_t: int;
#else
enum csmedge_hedge_side_t;
enum csmsetop_operation_t;
enum csmsetop_classify_resp_solid_t;
enum csmsetop_a_vs_b_t;
enum csmoptree_result_t;
enum csmnode_object_t;
enum csmstlimporter_result_t;
enum csmoctree_bbox_inters_t;
#endif

struct csmbbox_t;
struct csmtransform_t;
    
struct bsgraphics2_t;
struct csmviewer_t;

struct csmhashtb(csmface_t);
struct csmhashtb(csmedge_t);
struct csmhashtb(csmvertex_t);
struct csmhashtb(csmhedge_t);
struct csmhashtb2id(csmsetop_vtxfacc_inters_t);
    
csmArrayStruct(csmvertex_t);
csmArrayStruct(csmedge_t);
csmArrayStruct(csmface_t);
csmArrayStruct(csmhedge_t);
csmArrayStruct(csmsetop_vtxvtx_inters_t);
csmArrayStruct(csmedge_t);
csmArrayStruct(csmsetop_vtxvtx_inters_t);
csmArrayStruct(csmsetop_vtxfacc_inters_t);
csmArrayStruct(csmedge_t);
csmArrayStruct(csmsave_item_t);
csmArrayStruct(csmwriteablesolid_vertex_t);
csmArrayStruct(csmwriteablesolid_hedge_t);
csmArrayStruct(csmwriteablesolid_loop_t);
csmArrayStruct(csmwriteablesolid_faces_t);
    
struct bsmaterial_t;
    
csmArrPoint2D;
csmArrPoint3D;
csmArrULong;

#else
    
#include "intsafe.hxx"
#include "windows.tlh"
    
#define csmshape2d_t Contorno2D
#define csmshape2d_polygon_count Cnt2D_GetNumPoligonos
#define csmshape2d_point_polygon_count Cnt2D_Plg2D_GetNumPuntos
#define csmshape2d_polygon_is_hole i_polygon_is_hole
#define csmshape2d_point_polygon_coords Cnt2D_Plg2D_GetPunto
#define csmshape2d_copy Cnt2D_Copiar
#define csmshape2d_free Cnt2D_Destruir

#define csmArrPoint2D ArrPunto2D
#define csmArrPoint2D_new arr_CreaPunto2D
#define csmArrPoint2D_count arr_NumElemsPunto2D
#define csmArrPoint2D_get arr_GetPunto2D
#define csmArrPoint2D_free arr_DestruyePunto2D
    
#define ASSIGN_POINTER_PP_NOT_NULL ASIGNA_PUNTERO_PP_NO_NULL
#define ASSIGN_POINTER_PP ASIGNA_PUNTERO_PP
#define ASSIGN_OPTIONAL_VALUE ASIGNA_OPC
    
#endif

#ifdef __cplusplus
}
#endif

#define __attribute__(A)

#endif /* csmfwddecl_hxx */
