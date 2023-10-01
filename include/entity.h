#pragma once
#ifdef _LANGUAGE_C
#include <ultra64.h>

#include "vector.h"

typedef struct Entity
{
    Vector3f position;
    Vector3f rotation;
    float scale;
    Mtx transform;

    void (*update)(struct Entity *);
} Entity;

static Vtx quad_vtx[] = {
    {-2, 2, 0, 0, 0, 0, 0, 0xff, 0, 0xff},
    {2, 2, 0, 0, 0, 0, 0, 0, 0, 0xff},
    {2, -2, 0, 0, 0, 0, 0, 0, 0xff, 0xff},
    {-2, -2, 0, 0, 0, 0, 0xff, 0, 0, 0xff},
};

void draw_entity(Entity *entity, Gfx **glist)
{
    guPosition(
        &entity->transform,
        Vector3f_unpack(entity->rotation),
        entity->scale,
        Vector3f_unpack(entity->position));

    gSPMatrix((*glist)++, OS_K0_TO_PHYSICAL(&(entity->transform)),
              G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);

    gDPPipeSync((*glist)++);
    gDPSetCycleType((*glist)++, G_CYC_1CYCLE);
    gDPSetRenderMode((*glist)++, G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2);
    // gSPClearGeometryMode((*glist)++, 0xFFFFFFFF);
    gSPSetGeometryMode((*glist)++, G_SHADE | G_SHADING_SMOOTH);
    gSPVertex((*glist)++, &(quad_vtx[0]), 4, 0);
    gSP1Triangle((*glist)++, 0, 1, 2, 0);
    gSP1Triangle((*glist)++, 0, 2, 3, 0);
    // gSPEndDisplayList(glist++);

    gDPPipeSync((*glist)++);
    gSPPopMatrix((*glist)++, G_MTX_MODELVIEW);
};

#endif /* _LANGUAGE_C */