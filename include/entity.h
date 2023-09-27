#pragma once
#ifdef _LANGUAGE_C
#include <ultra64.h>

typedef struct {
    float x, y, z;
} Vector3f;

typedef struct {
    Mtx scale;
    Mtx rotation;
    Mtx translation;
} Transform;

typedef struct Entity
{
    Vector3f position;
    Vector3f rotation;
    Vector3f scale;
    Transform transform;

    void (*update)(struct Entity*);
} Entity;

Vtx quad_vtx[] =  {
        {        -2,  2, -5, 0, 0, 0, 0,    0xff,   0, 0xff	},
        {         2,  2, -5, 0, 0, 0, 0,    0,      0, 0xff	},
        {         2, -2, -5, 0, 0, 0, 0,    0,      0xff, 0xff	},
        {        -2, -2, -5, 0, 0, 0, 0xff, 0,      0, 0xff	},
};

void draw_entity(Entity* entity, Gfx** glist) {
    guScale(&(entity->transform.scale), entity->scale.x, entity->scale.y, entity->scale.z);
    guRotateRPY(&(entity->transform.rotation), entity->rotation.x, entity->rotation.y, entity->rotation.z);
    guTranslate(&(entity->transform.translation), entity->position.x, entity->position.y, entity->position.z);
    
    gSPMatrix((*glist)++, OS_K0_TO_PHYSICAL(&(entity->transform.translation)),
        G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);
    gSPMatrix((*glist)++, OS_K0_TO_PHYSICAL(&(entity->transform.rotation)),
        G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
    gSPMatrix((*glist)++, OS_K0_TO_PHYSICAL(&(entity->transform.scale)),
        G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);

    
    gDPPipeSync((*glist)++);
    gDPSetCycleType((*glist)++, G_CYC_1CYCLE);
    gDPSetRenderMode((*glist)++, G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2);
    gSPClearGeometryMode((*glist)++, 0xFFFFFFFF)
    gSPSetGeometryMode((*glist)++, G_SHADE | G_SHADING_SMOOTH);
    gSPVertex((*glist)++, &(quad_vtx[0]), 4, 0);
    gSP1Triangle((*glist)++, 0, 1, 2, 0);
    gSP1Triangle((*glist)++ ,0, 2, 3, 0);
    //gSPEndDisplayList(glist++);

    gSPPopMatrix((*glist)++, G_MTX_MODELVIEW);
};

#endif /* _LANGUAGE_C */