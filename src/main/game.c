#include "game/game.h"

static void rotate_entity(Entity *entity)
{
    static Vector3f rot = {0, 0, 0.1f};
    entity->rotation = Vector3f_add_vector(entity->rotation, rot);
}

static void move_entity(Entity *entity)
{
    Vector3f pos = {
        .x = getStickX() / 20,
        .y = getStickY() / 20,
        .z = 0
    };

    entity->position = Vector3f_add_vector(entity->position, pos);
}

static Entity entities[2] = {
    {.position = {10.0f, 0.0f, -5.0f},
     .rotation = {0.0f, 0.0f, 0.0f},
     .scale = 5.0f,
     .update = &move_entity,
     .mesh = basic_mesh
    },
    {.position = {0.0f, 0.0f, -5.0f},
     .rotation = {0.0f, 0.0f, 10.0f},
     .scale = 64.0f,
     .update = &rotate_entity,
     .mesh = basic_mesh
     }};

void renderGame()
{
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
