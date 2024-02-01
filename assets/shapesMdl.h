#ifndef SHAPES_H
#define SHAPES_H

/* SHAPES.H
here are all the structures and functions prototypes that involve the terrain generation */


/* gfx_axis                             
An axis model which was useful for getting calculations right.
Red represents X, Green represents Y, Blue represents Z. */

Vtx vtx_axis[] = {
  {-2, -2, -2, 0, 0, 0, -73, -73, -73, 255},
  { 50, -2, -2, 0, 0, 0,  73, -73, -73, 255},
  { 50,  2, -2, 0, 0, 0,  73,  73, -73, 255},
  {-2,  2, -2, 0, 0, 0, -73,  73, -73, 255},
  {-2, -2,  2, 0, 0, 0, -73, -73,  73, 255},
  { 50, -2,  2, 0, 0, 0,  73, -73,  73, 255},
  { 50,  2,  2, 0, 0, 0,  73,  73,  73, 255},
  {-2,  2,  2, 0, 0, 0, -73,  73,  73, 255},
  {-2, -2, -2, 0, 0, 0, -73, -73, -73, 255},
  { 2, -2, -2, 0, 0, 0,  73, -73, -73, 255},
  { 2,  50, -2, 0, 0, 0,  73,  73, -73, 255},
  {-2,  50, -2, 0, 0, 0, -73,  73, -73, 255},
  {-2, -2,  2, 0, 0, 0, -73, -73,  73, 255},
  { 2, -2,  2, 0, 0, 0,  73, -73,  73, 255},
  { 2,  50,  2, 0, 0, 0,  73,  73,  73, 255},
  {-2,  50,  2, 0, 0, 0, -73,  73,  73, 255},
  {-2, -2, -2, 0, 0, 0, -73, -73, -73, 255},
  { 2, -2, -2, 0, 0, 0,  73, -73, -73, 255},
  { 2,  2, -2, 0, 0, 0,  73,  73, -73, 255},
  {-2,  2, -2, 0, 0, 0, -73,  73, -73, 255},
  {-2, -2,  50, 0, 0, 0, -73, -73,  73, 255},
  { 2, -2,  50, 0, 0, 0,  73, -73,  73, 255},
  { 2,  2,  50, 0, 0, 0,  73,  73,  73, 255},
  {-2,  2,  50, 0, 0, 0, -73,  73,  73, 255},
};

Gfx gfx_axis[] = {
    gsDPSetPrimColor(0, 0, 255, 0, 0, 255),
    gsDPPipeSync(),
    gsSPVertex(vtx_axis, 8, 0),
    gsSP2Triangles(4, 6, 7, 0, 4, 5, 6, 0),
    gsSP2Triangles(6, 5, 2, 1, 2, 5, 1, 1),
    gsSP2Triangles(1, 3, 2, 0, 0, 3, 1, 2),
    gsSP2Triangles(3, 0, 7, 2, 0, 4, 7, 2),
    gsSP2Triangles(2, 7, 6, 0, 2, 3, 7, 0),
    gsSP2Triangles(0, 5, 4, 0, 0, 1, 5, 0),
    gsDPSetPrimColor(0, 0, 0, 255, 0, 255),
    gsDPPipeSync(),
    gsSPVertex(vtx_axis+8, 8, 0),
    gsSP2Triangles(4, 6, 7, 0, 4, 5, 6, 0),
    gsSP2Triangles(6, 5, 2, 1, 2, 5, 1, 1),
    gsSP2Triangles(1, 3, 2, 0, 0, 3, 1, 2),
    gsSP2Triangles(3, 0, 7, 2, 0, 4, 7, 2),
    gsSP2Triangles(2, 7, 6, 0, 2, 3, 7, 0),
    gsSP2Triangles(0, 5, 4, 0, 0, 1, 5, 0),
    gsDPSetPrimColor(0, 0, 0, 0, 255, 255),
    gsDPPipeSync(),
    gsSPVertex(vtx_axis+16, 8, 0),
    gsSP2Triangles(4, 6, 7, 0, 4, 5, 6, 0),
    gsSP2Triangles(6, 5, 2, 1, 2, 5, 1, 1),
    gsSP2Triangles(1, 3, 2, 0, 0, 3, 1, 2),
    gsSP2Triangles(3, 0, 7, 2, 0, 4, 7, 2),
    gsSP2Triangles(2, 7, 6, 0, 2, 3, 7, 0),
    gsSP2Triangles(0, 5, 4, 0, 0, 1, 5, 0),
    gsSPEndDisplayList(),
};


/* gfx_mirror_axis                              
mirrored axis */

Vtx vtx_mirror_axis[] = {
  {-2, -2, -2, 0, 0, 0, -73, -73, -73, 255},
  { 50, -2, -2, 0, 0, 0,  73, -73, -73, 255},
  { 50,  2, -2, 0, 0, 0,  73,  73, -73, 255},
  {-2,  2, -2, 0, 0, 0, -73,  73, -73, 255},
  {-2, -2,  2, 0, 0, 0, -73, -73,  73, 255},
  { 50, -2,  2, 0, 0, 0,  73, -73,  73, 255},
  { 50,  2,  2, 0, 0, 0,  73,  73,  73, 255},
  {-2,  2,  2, 0, 0, 0, -73,  73,  73, 255},
  {-2, -2, -2, 0, 0, 0, -73, -73, -73, 255},
  { 2, -2, -2, 0, 0, 0,  73, -73, -73, 255},
  { 2,  50, -2, 0, 0, 0,  73,  73, -73, 255},
  {-2,  50, -2, 0, 0, 0, -73,  73, -73, 255},
  {-2, -2,  2, 0, 0, 0, -73, -73,  73, 255},
  { 2, -2,  2, 0, 0, 0,  73, -73,  73, 255},
  { 2,  50,  2, 0, 0, 0,  73,  73,  73, 255},
  {-2,  50,  2, 0, 0, 0, -73,  73,  73, 255},
  {-2, -2, -2, 0, 0, 0, -73, -73, -73, 255},
  { 2, -2, -2, 0, 0, 0,  73, -73, -73, 255},
  { 2,  2, -2, 0, 0, 0,  73,  73, -73, 255},
  {-2,  2, -2, 0, 0, 0, -73,  73, -73, 255},
  {-2, -2,  50, 0, 0, 0, -73, -73,  73, 255},
  { 2, -2,  50, 0, 0, 0,  73, -73,  73, 255},
  { 2,  2,  50, 0, 0, 0,  73,  73,  73, 255},
  {-2,  2,  50, 0, 0, 0, -73,  73,  73, 255},
};

Gfx gfx_mirror_axis[] = {
    gsDPSetPrimColor(0, 0, 0, 255, 0, 255),
    gsDPPipeSync(),
    gsSPVertex(vtx_mirror_axis, 8, 0),
    gsSP2Triangles(4, 6, 7, 0, 4, 5, 6, 0),
    gsSP2Triangles(6, 5, 2, 1, 2, 5, 1, 1),
    gsSP2Triangles(1, 3, 2, 0, 0, 3, 1, 2),
    gsSP2Triangles(3, 0, 7, 2, 0, 4, 7, 2),
    gsSP2Triangles(2, 7, 6, 0, 2, 3, 7, 0),
    gsSP2Triangles(0, 5, 4, 0, 0, 1, 5, 0),

    gsDPSetPrimColor(0, 0, 255, 0, 0, 255),
    gsDPPipeSync(),
    gsSPVertex(vtx_mirror_axis+8, 8, 0),
    gsSP2Triangles(4, 6, 7, 0, 4, 5, 6, 0),
    gsSP2Triangles(6, 5, 2, 1, 2, 5, 1, 1),
    gsSP2Triangles(1, 3, 2, 0, 0, 3, 1, 2),
    gsSP2Triangles(3, 0, 7, 2, 0, 4, 7, 2),
    gsSP2Triangles(2, 7, 6, 0, 2, 3, 7, 0),
    gsSP2Triangles(0, 5, 4, 0, 0, 1, 5, 0),

    gsDPSetPrimColor(0, 0, 0, 0, 255, 255),
    gsDPPipeSync(),
    gsSPVertex(vtx_mirror_axis+16, 8, 0),
    gsSP2Triangles(4, 6, 7, 0, 4, 5, 6, 0),
    gsSP2Triangles(6, 5, 2, 1, 2, 5, 1, 1),
    gsSP2Triangles(1, 3, 2, 0, 0, 3, 1, 2),
    gsSP2Triangles(3, 0, 7, 2, 0, 4, 7, 2),
    gsSP2Triangles(2, 7, 6, 0, 2, 3, 7, 0),
    gsSP2Triangles(0, 5, 4, 0, 0, 1, 5, 0),
    
    gsSPEndDisplayList(),
};


/* gfx_cube                              
black cube of mystery */

Vtx vtx_cube[] = {
  {-50, -50, -50, 0, 0, 0, -73, -73, -73, 255},
  { 50, -50, -50, 0, 0, 0,  73, -73, -73, 255},
  { 50,  50, -50, 0, 0, 0,  73,  73, -73, 255},
  {-50,  50, -50, 0, 0, 0, -73,  73, -73, 255},
  {-50, -50,  50, 0, 0, 0, -73, -73,  73, 255},
  { 50, -50,  50, 0, 0, 0,  73, -73,  73, 255},
  { 50,  50,  50, 0, 0, 0,  73,  73,  73, 255},
  {-50,  50,  50, 0, 0, 0, -73,  73,  73, 255},
};


Gfx gfx_cube[] = {

    gsSPVertex(vtx_cube+0, 8, 0),

    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2),
    gsDPSetCombineMode(G_CC_PRIMLITE, G_CC_PRIMLITE),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsSPClearGeometryMode(0xFFFFFFFF),
    gsSPSetGeometryMode(G_SHADE | G_ZBUFFER | G_CULL_BACK | G_SHADING_SMOOTH | G_LIGHTING),

    gsDPSetPrimColor(0, 0, 15, 15, 15, 255),
    gsDPPipeSync(),

    gsSP2Triangles(4, 6, 7, 0, 4, 5, 6, 0),
    gsSP2Triangles(6, 5, 2, 1, 2, 5, 1, 1),
    gsSP2Triangles(1, 3, 2, 0, 0, 3, 1, 2),
    gsSP2Triangles(3, 0, 7, 2, 0, 4, 7, 2),
    gsSP2Triangles(2, 7, 6, 0, 2, 3, 7, 0),
    gsSP2Triangles(0, 5, 4, 0, 0, 1, 5, 0),
    
    gsSPEndDisplayList(),
};

#endif