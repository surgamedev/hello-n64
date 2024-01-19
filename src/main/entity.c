#include "entity.h"

void draw_entity(Entity *entity, Gfx **glistp)
{
    guPosition(
        &entity->transform,
        Vector3f_unpack(entity->rotation),
        entity->scale,
        Vector3f_unpack(entity->position));
    
    gSPMatrix((*glistp)++, OS_K0_TO_PHYSICAL(&(entity->transform)),
              G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);

    //gSPDisplayList((*glistp)++, basic_mesh);
    gSPDisplayList((*glistp)++, entity->mesh);
}

Vtx quad_vtx[] = {
    {{{-64, 64, -5},  0, {0, 0}, {0, 0xFF, 0, 0xFF}}},
    {{{ 64, 64, -5},  0, {0, 0}, {0, 0,    0, 0xff}}},
    {{{ 64, -64, -5}, 0, {0, 0}, {0, 0, 0xff, 0xff}}},
    {{{-64, -64, -5}, 0, {0, 0}, {0xff, 0, 0, 0xff}}},
};

Gfx basic_mesh[] = {
    gsSPVertex(quad_vtx+0, 4, 0),

    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2),
    gsSPClearGeometryMode(0xFFFFFFFF),
    gsSPSetGeometryMode(G_SHADE | G_SHADING_SMOOTH),

    gsSP2Triangles(0, 1, 2, 0, 0, 2, 3, 0),
    gsSPEndDisplayList()
};