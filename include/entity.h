#ifndef _ENTITY_H_
#define _ENTITY_H_

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
    {-64, 64, -5, 0, 0, 0, 0, 0xff, 0, 0xff},
    {64, 64, -5, 0, 0, 0, 0, 0, 0, 0xff},
    {64, -64, -5, 0, 0, 0, 0, 0, 0xff, 0xff},
    {-64, -64, -5, 0, 0, 0, 0xff, 0, 0, 0xff},
};

void draw_entity(Entity *entity, Gfx **glistp)
{
    guPosition(
        &entity->transform,
        Vector3f_unpack(entity->rotation),
        entity->scale,
        Vector3f_unpack(entity->position));
    
    gSPMatrix((*glistp)++, OS_K0_TO_PHYSICAL(&(entity->transform)),
              G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);

    gSPVertex((*glistp)++, &(quad_vtx[0]), 4, 0);

    gDPPipeSync((*glistp)++);
    gDPSetCycleType((*glistp)++, G_CYC_1CYCLE);
    gDPSetRenderMode((*glistp)++, G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2);
    gSPClearGeometryMode((*glistp)++, 0xFFFFFFFF);
    gSPSetGeometryMode((*glistp)++, G_SHADE | G_SHADING_SMOOTH);

    gSP2Triangles((*glistp)++, 0, 1, 2, 0, 0, 2, 3, 0);
}

#endif /* _ENTITY_H_ */