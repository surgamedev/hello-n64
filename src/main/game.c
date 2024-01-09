#include "game/game.h"

#include "graphic.h"
#include "entity.h"

static void rotate_entity(Entity *entity)
{
    entity->rotation.z += 0.1f;
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
    for (int i = 0; i < 2; i++)
    {
        draw_entity(&entities[i], &glistp);
    }
}

void updateGame()
{
    for (int i = 0; i < 2; i++)
    {
        if (entities[i].update != NULL)
        {
            entities[i].update(&entities[i]);
        }
    }
}