#include "game/game.h"

#include "graphic.h"
#include "entity.h"

static void rotate_entity(Entity *entity)
{
    static Vector3f rot = {.x = 0.0f, .y = 0.0f, .z = 0.1f};
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
     .update = &move_entity},
    {.position = {0.0f, 0.0f, -5.0f},
     .rotation = {0.0f, 0.0f, 10.0f},
     .scale = 1.0f,
     .update = &rotate_entity}};

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