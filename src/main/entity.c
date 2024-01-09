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
