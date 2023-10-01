#pragma once
#ifdef _LANGUAGE_C

#include <ultra64.h>

typedef struct
{
    float x, y, z;
} Vector3f;

inline Vector3f Vector3f_init(Vector3f vec, float x, float y, float z)
{
    vec.x = x;
    vec.y = y;
    vec.z = z;
    return vec;
}

inline Vector3f Vector3f_add_vector(Vector3f dst, Vector3f src)
{
    dst.x += src.x;
    dst.y += src.y;
    dst.z += src.z;
    return dst;
}

inline Vector3f Vector3f_add_scalar(Vector3f dst, float src)
{
    dst.x += src;
    dst.y += src;
    dst.z += src;
    return dst;
}

inline Vector3f Vector3f_sub_vector(Vector3f dst, Vector3f src)
{
    dst.x -= src.x;
    dst.y -= src.y;
    dst.z -= src.z;
    return dst;
}

inline Vector3f Vector3f_sub_scalar(Vector3f dst, float src)
{
    dst.x -= src;
    dst.y -= src;
    dst.z -= src;
    return dst;
}

inline Vector3f Vector3f_mul_vector(Vector3f dst, Vector3f src)
{
    dst.x *= src.x;
    dst.y *= src.y;
    dst.z *= src.z;
    return dst;
}

inline Vector3f Vector3f_mul_scalar(Vector3f dst, float src)
{
    dst.x *= src;
    dst.y *= src;
    dst.z *= src;
    return dst;
}

inline float Vector3f_dist(Vector3f dst, Vector3f src)
{
    return sqrtf(
        (src.x - dst.x) * (src.x - dst.x) + (src.y - dst.y) * (src.y - dst.y) + (src.z - dst.z) * (src.z - dst.z));
}

inline Vector3f Vector3f_norm(Vector3f dst)
{
    float len = sqrtf((dst.x * dst.x) + (dst.y * dst.y) + (dst.z * dst.z));
    dst.x /= len;
    dst.y /= len;
    dst.z /= len;
    return dst;
}

#define Vector3f_unpack(vec) (vec).x, (vec).y, (vec).z

#endif /* _LANGUAGE_C */