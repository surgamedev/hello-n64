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

extern Gfx basic_mesh[];

void draw_entity(Entity*, Gfx**);