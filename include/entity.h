#pragma once

#include <ultra64.h>
#include "vector.h"

typedef struct Entity
{
    Vector3f position;
    Vector3f rotation;
    float scale;
    
    Mtx transform;
    Gfx* mesh;

    void (*update)(struct Entity *);
} Entity;

extern void draw_entity(Entity*, Gfx**);

static Vtx quad_vtx[] = {
    {-64, 64, -5, 0, 0, 0, 0, 0xff, 0, 0xff},
    {64, 64, -5, 0, 0, 0, 0, 0, 0, 0xff},
    {64, -64, -5, 0, 0, 0, 0, 0, 0xff, 0xff},
    {-64, -64, -5, 0, 0, 0, 0xff, 0, 0, 0xff},
};

static Gfx basic_mesh[] = {
    gsSPVertex(quad_vtx+0, 4, 0),

    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2),
    gsSPClearGeometryMode(0xFFFFFFFF),
    gsSPSetGeometryMode(G_SHADE | G_SHADING_SMOOTH),

    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSPEndDisplayList()
};