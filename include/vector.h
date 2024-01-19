#pragma once

#include <ultra64.h>

typedef struct
{
    float x, y, z;
} Vector3f;

#define Vector3f_unpack(vec) (vec).x, (vec).y, (vec).z

Vector3f Vector3f_init(Vector3f vec, float x, float y, float z);
Vector3f Vector3f_add_vector(Vector3f dst, Vector3f src);
Vector3f Vector3f_add_scalar(Vector3f dst, float src);
Vector3f Vector3f_sub_vector(Vector3f dst, Vector3f src);
Vector3f Vector3f_sub_scalar(Vector3f dst, float src);
Vector3f Vector3f_mul_vector(Vector3f dst, Vector3f src);
Vector3f Vector3f_mul_scalar(Vector3f dst, float src);
float Vector3f_dist(Vector3f dst, Vector3f src);
Vector3f Vector3f_norm(Vector3f dst);
