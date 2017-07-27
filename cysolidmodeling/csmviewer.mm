//
//  csmviewer.c
//  SolidModelingTester
//
//  Created by Manuel Fernandez on 23/7/17.
//  Copyright © 2017 Manuel Fernández. All rights reserved.
//

#include "csmviewer.inl"

extern "C"
{
    #include "csmsolid.h"
    #include "csmsolid.inl"
    #include "csmdebug.inl"
}

#include <basicSystem/bsmaterial.h>
#include <basicGraphics/bsgraphics2.h>
#include <basicSystem/bsassert.h>
#include <basicSystem/bsmem.h>
#include <cypearrays/a_punter.h>
#include <WinFrames2/wf2DlgUtil.h>
#include <WinFrames2/wf2pnutil.h>
#include <WinFrames3/wf3Visor.h>
#include <WinFrames3/wf3Vista.h>
#include <cysolidmodeling/cysolidmodeling.h>

struct csmviewer_t
{
    struct csmsolid_t *solid1, *solid2;
    struct csmsolid_t *solid_res1, *solid_res2;
    
    struct wf3Visor_t *viewer_widget;
};

// ------------------------------------------------------------------------------------------

static struct csmviewer_t *i_new(
                    struct csmsolid_t **solid1, struct csmsolid_t **solid2,
                    struct csmsolid_t **solid_res1, struct csmsolid_t **solid_res2)
{
    struct csmviewer_t *viewer;
    
    viewer = bsmem_malloc(struct csmviewer_t);
    
    viewer->solid1 = bsmem_asigna_puntero_pp(solid1, struct csmsolid_t);
    viewer->solid2 = bsmem_asigna_puntero_pp(solid2, struct csmsolid_t);
    
    viewer->solid_res1 = bsmem_asigna_puntero_pp(solid_res1, struct csmsolid_t);
    viewer->solid_res2 = bsmem_asigna_puntero_pp(solid_res2, struct csmsolid_t);
    
    viewer->viewer_widget = NULL;
    
    return viewer;
}

// ------------------------------------------------------------------------------------------

struct csmviewer_t *csmviewer_new(void)
{
    struct csmsolid_t *solid1, *solid2;
    struct csmsolid_t *solid_res1, *solid_res2;
    
    solid1 = NULL;
    solid2 = NULL;
    solid_res1 = NULL;
    solid_res2 = NULL;
    
    return i_new(&solid1, &solid2, &solid_res1, &solid_res2);
}

// ------------------------------------------------------------------------------------------

void csmviewer_free(struct csmviewer_t **viewer)
{
    bsassert_not_null(viewer);
    bsassert_not_null(*viewer);
    
    bsmem_destruye(viewer, struct csmviewer_t);
}

// ------------------------------------------------------------------------------------------

static void i_draw_solid_with_material(struct csmsolid_t *solid, struct bsmaterial_t **material, struct bsgraphics2_t *graphics)
{
    bsassert_not_null(material);
    
    if (solid != NULL)
    {
        bsgraphics2_escr_color(graphics, *material);
        bsmaterial_destruye(material);
                
        csmsolid_draw(solid, graphics);
    }
}

// ------------------------------------------------------------------------------------------

static void i_draw_scene(struct csmviewer_t *viewer, struct bsgraphics2_t *graphics)
{
    bsassert_not_null(viewer);
    
    if (viewer->solid_res1 != NULL || viewer->solid_res2 != NULL)
    {
        struct bsmaterial_t *material;
            
        material = bsmaterial_crea_rgb(0., 1., 0.);
        i_draw_solid_with_material(viewer->solid_res1, &material, graphics);

        material = bsmaterial_crea_rgb(0., 0., 1.);
        i_draw_solid_with_material(viewer->solid_res2, &material, graphics);
    }
    else
    {
        struct bsmaterial_t *material;
            
        material = bsmaterial_crea_rgb(0., 1., 0.);
        i_draw_solid_with_material(viewer->solid1, &material, graphics);

        material = bsmaterial_crea_rgb(0., 0., 1.);
        i_draw_solid_with_material(viewer->solid2, &material, graphics);
        
        csmdebug_draw_debug_info(graphics);
    }
}

// ------------------------------------------------------------------------------------------

static void i_show_viewer(struct csmviewer_t *viewer)
{
    struct wf3Visor_t *viewer_widget;
    struct wf3Vista_delegado_dibujo_t *delegado;
    struct wfPanel_t *panel_area, *panel_toolbar, *panel;
    
    bsassert_not_null(viewer);
    
    viewer_widget = wf3Visor_crea_csgrenderer(500, 500, WF3VISTA_GESTION_DIBUJO_SIN_BDD);
    
    delegado = wf3Vista_crea_delegado_dibujo(viewer, i_draw_scene, csmviewer_t);
    wf3Visor_set_delegado_dibujo(viewer_widget, &delegado);
    
    wf3Visor_ventana_completa(viewer_widget);

    panel_area = wf3Visor_panel_area_dibujo(viewer_widget);
    panel_toolbar = wf3Visor_panel_toolbar(viewer_widget);
    panel = wf2pnutil_encapsula_en_bordes_norte_centro(panel_toolbar, panel_area);
    wf2DlgUtil_lanza_dialogo_aceptado("Solid Operation", panel, true);
    
    wf3Visor_destruye(&viewer_widget);
}

// ------------------------------------------------------------------------------------------

void csmviewer_set_parameters(struct csmviewer_t *viewer, struct csmsolid_t *solid1, struct csmsolid_t *solid2)
{
    bsassert_not_null(viewer);
    
    viewer->solid1 = solid1;
    viewer->solid2 = solid2;
}

// ------------------------------------------------------------------------------------------

void csmviewer_set_results(struct csmviewer_t *viewer, struct csmsolid_t *solid1, struct csmsolid_t *solid2)
{
    bsassert_not_null(viewer);
    
    viewer->solid_res1 = solid1;
    viewer->solid_res2 = solid2;
}

// ------------------------------------------------------------------------------------------

void csmviewer_show(struct csmviewer_t *viewer)
{
    bsassert_not_null(viewer);
    i_show_viewer(viewer);
}
