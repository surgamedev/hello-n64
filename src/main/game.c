#include "game/game.h"

static void rotate_entity(Entity *entity)
{
    static Vector3f rot = {0, 0, 0.1f};
    entity->rotation = Vector3f_add_vector(entity->rotation, rot);
}

static void move_entity(Entity *entity)
{
    entity->position.x = (entity->position.x > SCREEN_WD / 2) ? -SCREEN_WD / 2 : entity->position.x + 1;
}

static Entity entities[2] = {
    {.position = {10.0f, 0.0f, -5.0f},
     .rotation = {0.0f, 0.0f, -5.0f},
     .scale = 1.0f,
     .update = &move_entity,
     .mesh = basic_mesh
    },
    {.position = {0.0f, 0.0f, -5.0f},
     .rotation = {0.0f, 0.0f, 10.0f},
     .scale = 1.0f,
     .update = &rotate_entity,
     .mesh = basic_mesh
     }};

void renderGame()
{
    nuDebConClear(NU_DEB_CON_WINDOW0);
    nuDebConTextPos(NU_DEB_CON_WINDOW0, 1, 1);
    nuDebConPrintf(NU_DEB_CON_WINDOW0, "X: %d", getStickX());
    nuDebConTextPos(NU_DEB_CON_WINDOW0, 1, 2);
    nuDebConPrintf(NU_DEB_CON_WINDOW0, "X: %d", getStickY());

    nuDebConTextPos(NU_DEB_CON_WINDOW0, 1, 3);
    if (isAPressed()) {
        nuDebConPrintf(NU_DEB_CON_WINDOW0, "A");
    }else {
        nuDebConPrintf(NU_DEB_CON_WINDOW0, "no A");
    }

    nuDebConTextPos(NU_DEB_CON_WINDOW0, 1, 4);
    if (isBPressed()) {
        nuDebConPrintf(NU_DEB_CON_WINDOW0, "B");
    }else {
        nuDebConPrintf(NU_DEB_CON_WINDOW0, "no B");
    }

    for (int i = 0; i < 2; i++)
    {
        draw_entity(&entities[i], &glistp);
    }
}

void updateGame()
{
    nuContDataGetEx(inputData, 0);
    for (int i = 0; i < 2; i++)
    {
        if (entities[i].update != NULL)
        {
            entities[i].update(&entities[i]);
        }
    }
}
