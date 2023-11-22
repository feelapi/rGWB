cmake_minimum_required (VERSION 3.16)

project(RGWB C)

set(SRC_LIST
rGWB/csmapto2d.c
rGWB/csmapto3d.c
rGWB/csmarqsort.c
rGWB/csmarrayc.c
rGWB/csmassert.c
rGWB/csmaulong.c
rGWB/csmbasicshape2d.c
rGWB/csmbbox.c
rGWB/csmedge.c
rGWB/csmeuler_kvfs.c
rGWB/csmeuler_laringmv.c
rGWB/csmeuler_lkef.c
rGWB/csmeuler_lkemr.c
rGWB/csmeuler_lkev.c
rGWB/csmeuler_lkfmrh.c
rGWB/csmeuler_lmef.c
rGWB/csmeuler_lmekr.c
rGWB/csmeuler_lmev.c
rGWB/csmeuler_lmfkrh.c
rGWB/csmeuler_lringmv.c
rGWB/csmeuler_mvfb.c
rGWB/csmeuler_mvfs.c
rGWB/csmexplode.c
rGWB/csmfacbrep2solid.c
rGWB/csmface.c
rGWB/csmgeom.c
rGWB/csmglue.c
rGWB/csmhashtb.c
rGWB/csmhashtb2id.c
rGWB/csmhedge.c
rGWB/csmid.c
rGWB/csmloop.c
rGWB/csmloopglue.c
rGWB/csmmaterial.c
rGWB/csmmath.c
rGWB/csmmem.c
rGWB/csmnode.c
rGWB/csmoctree.c
rGWB/csmopbas.c
rGWB/csmoptree.c
rGWB/csmquadrics.c
rGWB/csmquaternion.c
rGWB/csmsave.c
rGWB/csmsavetxt.c
rGWB/csmsetop.c
rGWB/csmsetopcom.c
rGWB/csmsetop_join.c
rGWB/csmsetop_procedges.c
rGWB/csmsetop_vtxfacc.c
rGWB/csmsetop_vtxvtx.c
#rGWB/csmshape2d.c
rGWB/csmsimplifysolid.c
rGWB/csmsolid.c
#rGWB/csmsolid_vis.c
rGWB/csmsplit.c
rGWB/csmstlimporter.c
rGWB/csmstmodeler.c
rGWB/csmstring.c
rGWB/csmsubdvfaces.c
rGWB/csmsurface.c
rGWB/csmsweep.c
# rGWB/csmtest.c
# rGWB/csmtest2.c
# rGWB/csmtest_array.c
# rGWB/csmtest_octree.c
# rGWB/csmtest_quaternion.c
rGWB/csmtolerance.c
rGWB/csmtransform.c
rGWB/csmvertex.c
rGWB/csmwriteablesolid.c
more.c
)

add_library( RGWB SHARED ${SRC_LIST} )

include_directories(./rGWB)
add_definitions(-DRGWB_STANDALONE_DISTRIBUTABLE)