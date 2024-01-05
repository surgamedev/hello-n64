#pragma once

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

extern void draw_entity(Entity*, Gfx**);