#ifndef COLLISION_H
#define COLLISION_H

/* COLLISION.H
here are all the structures and functions prototypes that involve the collision detection */


// structures


typedef struct {

    float normal[3];
    float point[3];
    float displacement; 

} Plane;

typedef struct {

    float center[3];
    float radius;
    
    float closest_point[3];
    float distance_squared;

} Sphere;

typedef struct {

    float base_center[3];
    float height;
    float radius;

} Cylinder;


typedef struct {
    
    float min[3];
    float max[3];
    float center[3];

    Plane plane;

} AABB;


typedef struct {

    float start_point[3];
    float end_point[3];
    float radius;

} Capsule;


typedef struct {

    float center[3];
    float size[3];
    float rotation[3];

    Plane plane;

} OBB;


// function prototypes

void set_point(float* dest, float* src);
float squared_distance(float *a, float *b);
float distance(float *a, float *b);
void rotate_point(float point[3], float rotation[3]);

void set_vector(float *vector, float *a, float *b);
float squared_length(const float* vector);
float length(const float* vector);
float inverse_length(const float* vector);

void project_polygon(float axis[3], float corners[8][3], float *min, float *max);
int intervals_overlap(float minA, float maxA, float minB, float maxB);
int test_axis(float axis[3], float obbCorners[8][3], float aabbCorners[8][3]);

void point_global_to_obb_space(OBB obb, float global_point[3], float local_point[3]);
void point_obb_to_global_space(OBB obb, float local_point[3], float global_point[3]);

void get_aabb_corners(AABB aabb, float corners[8][3]);
void get_obb_corners(OBB obb, float corners[8][3]);

void closest_point_on_segment_to_point(float line_start[3], float line_end[3], float point[3], float closest[3]);
float squared_distance_point_to_segment(float point[3], float segment_start[3], float segment_end[3]);


int collision_sphere_sphere(Sphere sphere1, Sphere sphere2);
int collision_aabb_aabb(AABB aabb1, AABB aabb2);
int collision_sphere_aabb(Entity* entity, Sphere sphere, AABB aabb);
int collision_capsule_sphere(Capsule capsule, Sphere sphere);
int collision_sphere_obb(Entity* entity, Sphere sphere, OBB obb);
int collision_obb_aabb(OBB obb, AABB aabb);
int collision_cylinder_aabb(Entity* entity, Cylinder cylinder, AABB aabb);
int collision_cylinder_obb(Entity* entity, Cylinder cylinder, OBB obb);
int collision_capsule_aabb(Entity* entity, Capsule capsule, AABB aabb);
int collision_capsule_obb(Entity* entity, Capsule capsule, OBB obb);
int collision_ray_aabb(float origin[3], float target[3], AABB aabb, float* hit_point);



/* init_point
sets initial values to a destinatary point */

void init_point(float* dest, float x, float y, float z) 
{
    dest[0] = x;
    dest[1] = y;
    dest[2] = z;
}


/* set_point
sets values from a source point to a destinatary */

void set_point(float* dest, float* src) 
{
    dest[0] = src[0];
    dest[1] = src[1];
    dest[2] = src[2];
}


/* distance
returns the squared distance between 2 points */

float squared_distance(float *a, float *b) 
{
    return (a[0] - b[0]) * (a[0] - b[0]) + (a[1] - b[1]) * (a[1] - b[1]) + (a[2] - b[2]) * (a[2] - b[2]);
}


/* distance
returns the distance between 2 points*/

float distance(float* a, float* b) 
{
    return 1 / qi_sqrt(squared_distance(a, b));
}


/* rotate_point
rotates a point around the X, Y, and Z axes */

void rotate_point(float point[3], float rotation[3]) 
{
    // Rotate around X axis
    float radX = rad(rotation[0]);
    float yX = point[1] * cosf(radX) - point[2] * sinf(radX);
    float zX = point[1] * sinf(radX) + point[2] * cosf(radX);

    // Rotate around Y axis
    float radY = rad(rotation[1]);
    float xY = zX * sinf(radY) + point[0] * cosf(radY);
    float zY = zX * cosf(radY) - point[0] * sinf(radY);

    // Rotate around Z axis
    float radZ = rad(rotation[2]);
    point[0] = xY * cosf(radZ) - yX * sinf(radZ);
    point[1] = xY * sinf(radZ) + yX * cosf(radZ);
    point[2] = zY;
}


/* point_global_to_obb_space
transforms a point from global to OBB's local space using Euler angles */

void point_global_to_obb_space(OBB obb, float global_point[3], float local_point[3]) 
{
    // Translate point by the inverse of OBB's center
    local_point[0] = global_point[0] - obb.center[0];
    local_point[1] = global_point[1] - obb.center[1];
    local_point[2] = global_point[2] - obb.center[2];

    // Rotate the translated point by the inverse of OBB's rotation
    float inverse_rotation[3] = {-obb.rotation[0], -obb.rotation[1], -obb.rotation[2]};
    rotate_point(local_point, inverse_rotation);
}


/* point_obb_to_global_space
converts a point from OBB's local space to global space using Euler angles */

void point_obb_to_global_space(OBB obb, float local_point[3], float global_point[3]) 
{
    // Apply rotation to the local point to get it in the global space orientation
    rotate_point(local_point, obb.rotation);

    // Translate the rotated point by adding the OBB's center
    global_point[0] = local_point[0] + obb.center[0];
    global_point[1] = local_point[1] + obb.center[1];
    global_point[2] = local_point[2] + obb.center[2];
}


/* null_vector
sets a vector given 2 points */

void null_vector(float* vector)
{
    vector[0] = 0;
    vector[1] = 0;
    vector[2] = 0; 
}


/* set_vector
sets a vector given 2 points */

void set_vector(float *vector, float *a, float *b)
{
    vector[0] = b[0] - a[0];
    vector[1] = b[1] - a[1];
    vector[2] = b[2] - a[2]; 
}


/* subtract_vector
sets a vector given 2 points */

void set_inverse_vector(float *vector, float *a, float *b)
{
    vector[0] = a[0] - b[0];
    vector[1] = a[1] - b[1];
    vector[2] = a[2] - b[2];
}

/* squared_lenght
returns the squared lenght of a vector */

float squared_length(const float* vector) 
{
    return vector[0] * vector[0] + vector[1] * vector[1] + vector[2] * vector[2];
}


/* lenght
returns the lenght of a vector */

float length(const float* vector) 
{
    return 1 / qi_sqrt(squared_length(vector));
}

/* inverse_lenght
returns the lenght of a vector */

float inverse_length(const float* vector) 
{
    return qi_sqrt(squared_length(vector));
}


/* normalize_vector
normalize a vector */

void normalize_vector(float* vector) 
{
    float inv_len = inverse_length(vector);

    if (inv_len != 0) {

        for (int i = 0; i < 3; i++) {
            vector[i] *= inv_len;
        }
    }
}

/* project_polygon
projects a 3D polygon onto an axis */

void project_polygon(float axis[3], float corners[8][3], float *min, float *max) {
    *min = *max = dot_product(corners[0], axis);
    for (int i = 1; i < 8; i++) {
        float projection = dot_product(corners[i], axis);
        if (projection < *min) *min = projection;
        if (projection > *max) *max = projection;
    }
}


/* intervals_overlap
checks if two scalar intervals overlap */

int intervals_overlap(float minA, float maxA, float minB, float maxB) {
    return minA <= maxB && minB <= maxA;
}

/* test_axis
tests if projections of two polygons on an axis overlap */

int test_axis(float axis[3], float obbCorners[8][3], float aabbCorners[8][3])
{
    float minOBB, maxOBB;
    project_polygon(axis, obbCorners, &minOBB, &maxOBB);

    float minAABB, maxAABB;
    project_polygon(axis, aabbCorners, &minAABB, &maxAABB);

    return intervals_overlap(minOBB, maxOBB, minAABB, maxAABB);
}


void get_aabb_corners(AABB aabb, float corners[8][3]) 
{
    corners[0][0] = aabb.min[0]; corners[0][1] = aabb.min[1]; corners[0][2] = aabb.min[2];
    corners[1][0] = aabb.max[0]; corners[1][1] = aabb.min[1]; corners[1][2] = aabb.min[2];
    corners[2][0] = aabb.max[0]; corners[2][1] = aabb.max[1]; corners[2][2] = aabb.min[2];
    corners[3][0] = aabb.min[0]; corners[3][1] = aabb.max[1]; corners[3][2] = aabb.min[2];
    corners[4][0] = aabb.min[0]; corners[4][1] = aabb.min[1]; corners[4][2] = aabb.max[2];
    corners[5][0] = aabb.max[0]; corners[5][1] = aabb.min[1]; corners[5][2] = aabb.max[2];
    corners[6][0] = aabb.max[0]; corners[6][1] = aabb.max[1]; corners[6][2] = aabb.max[2];
    corners[7][0] = aabb.min[0]; corners[7][1] = aabb.max[1]; corners[7][2] = aabb.max[2];
}


void get_obb_corners(OBB obb, float corners[8][3])
{
    // calculates corners as if no rotation
    float localCorners[8][3] = {
        {-obb.size[0] / 2, -obb.size[1] / 2, -obb.size[2] / 2},
        { obb.size[0] / 2, -obb.size[1] / 2, -obb.size[2] / 2},
        { obb.size[0] / 2,  obb.size[1] / 2, -obb.size[2] / 2},
        {-obb.size[0] / 2,  obb.size[1] / 2, -obb.size[2] / 2},
        {-obb.size[0] / 2, -obb.size[1] / 2,  obb.size[2] / 2},
        { obb.size[0] / 2, -obb.size[1] / 2,  obb.size[2] / 2},
        { obb.size[0] / 2,  obb.size[1] / 2,  obb.size[2] / 2},
        {-obb.size[0] / 2,  obb.size[1] / 2,  obb.size[2] / 2}
    };

    // then rotates and traslates each one
    for (int i = 0; i < 8; i++) {
        rotate_point(localCorners[i], obb.rotation);
        corners[i][0] = localCorners[i][0] + obb.center[0];
        corners[i][1] = localCorners[i][1] + obb.center[1];
        corners[i][2] = localCorners[i][2] + obb.center[2];
    }
}


/* closest_point_on_segment_to_point
finds the closest point on a line segment to a point */

void closest_point_on_segment_to_point(float line_start[3], float line_end[3], float point[3], float closest[3])
{
    float line_vector[3];
    set_vector(line_vector, line_start, line_end);

    float point_vector[3];
    set_vector(point_vector, point, line_start);

    float line_length_squared = squared_distance(line_start, line_end);
    float t = clamp(dot_product(point_vector, line_vector) / line_length_squared, 0.0f, 1.0f);

    closest[0] = line_start[0] + t * line_vector[0];
    closest[1] = line_start[1] + t * line_vector[1];
    closest[2] = line_start[2] + t * line_vector[2];
}


/* squared_distance_point_to_segment
calculates the squared distance from a point to a line segment */

float squared_distance_point_to_segment(float point[3], float segment_start[3], float segment_end[3])
{
    float segment_vector[3];
    set_vector(segment_vector, segment_start, segment_end);

    float point_vector[3];
    set_vector(point_vector, segment_start, point);

    float segment_length_squared = squared_distance(segment_start, segment_end);

    float t = clamp(dot_product(point_vector, segment_vector) / segment_length_squared, 0.0f, 1.0f);

    float closest[3] = {
        segment_start[0] + t * segment_vector[0],
        segment_start[1] + t * segment_vector[1],
        segment_start[2] + t * segment_vector[2]
    };

    return squared_distance(point, closest);
}


/* init_plane
Function to initialize a plane given a point and a normal */

void init_plane(Plane *plane, float normal[3], float point[3]) 
{
    set_point(plane->normal, normal);
    set_point(plane->point, point);
    plane->displacement = dot_product(plane->normal, plane->point);
}


/* collision_sphere_sphere
detects collision between 2 shperes */

int collision_sphere_sphere(Sphere sphere1, Sphere sphere2) 
{
    float distance_squared = squared_distance(sphere1.center, sphere2.center);
    float radius_sum = sphere1.radius + sphere2.radius;
    return distance_squared <= radius_sum * radius_sum ? 1 : 0;
}


/* collision_aabb_aabb
detects collision between 2 boxes */

int collision_aabb_aabb(AABB aabb1, AABB aabb2) 
{
    if (aabb1.max[0] < aabb2.min[0] || aabb1.min[0] > aabb2.max[0])
        return 0;

    if (aabb1.max[1] < aabb2.min[1] || aabb1.min[1] > aabb2.max[1])
        return 0;

    if (aabb1.max[2] < aabb2.min[2] || aabb1.min[2] > aabb2.max[2])
        return 0;

    return 1;
}


/* collision_sphere_aabb
detects collision between a sphere and a box */

int collision_sphere_aabb(Entity* entity, Sphere sphere, AABB aabb) 
{
    // Find the closest point on the AABB to the sphere's center using clamp
    float closest_point[3] = {
        clamp(sphere.center[0], aabb.min[0], aabb.max[0]),
        clamp(sphere.center[1], aabb.min[1], aabb.max[1]),
        clamp(sphere.center[2], aabb.min[2], aabb.max[2])
    };

    // Calculate the squared distance from this point to the sphere's center
    float distance_squared = squared_distance(sphere.center, closest_point);

    // Check if the distance is less than or equal to the sphere's radius squared
    if (distance_squared <= sphere.radius * sphere.radius) {
        // Assign the closest point to the entity's collision point
        set_point(entity->collision.point, closest_point);
        return 1; // Collision detected
    } 
    
    else return 0; // No collision
}


/* collision_capsule_sphere
detects collision between a capsule and a sphere */

int collision_capsule_sphere(Capsule capsule, Sphere sphere) 
{
    float capsule_vector[3];
    set_vector(capsule_vector, capsule.start_point, capsule.end_point);
    
    float sphere_to_start[3];
    set_vector(sphere_to_start, sphere.center, capsule.start_point);

    float dot = dot_product(sphere_to_start, capsule_vector);
    float length_squared = squared_distance(capsule.start_point, capsule.end_point);

    float t = clamp(dot / length_squared, 0.0f, 1.0f);
    float closest_point[3] = {
        capsule.start_point[0] + t * capsule_vector[0],
        capsule.start_point[1] + t * capsule_vector[1],
        capsule.start_point[2] + t * capsule_vector[2]
    };

    float distance_squared = squared_distance(sphere.center, closest_point);
    float radius_sum = capsule.radius + sphere.radius;
    return distance_squared <= radius_sum * radius_sum;
}


/* collision_obb_sphere
detects collision between an OBB and a sphere */

int collision_sphere_obb(Entity* entity, Sphere sphere, OBB obb) 
{
    float local_sphere_center[3];
    point_global_to_obb_space(obb, sphere.center, local_sphere_center);

    // Find the closest point on the OBB to the sphere's center in OBB's local space
    float closest_point[3] = {
        clamp(local_sphere_center[0], -obb.size[0] / 2, obb.size[0] / 2),
        clamp(local_sphere_center[1], -obb.size[1] / 2, obb.size[1] / 2),
        clamp(local_sphere_center[2], -obb.size[2] / 2, obb.size[2] / 2),
    };

    // Calculate the squared distance from this point to the sphere's center in local space
    float distance_squared = squared_distance(local_sphere_center, closest_point);

    // Check if the distance is less than or equal to the sphere's radius squared
    if (distance_squared <= sphere.radius * sphere.radius) {
        // Convert the closest point back to global space before assigning it
        float global_closest_point[3];
        point_obb_to_global_space(obb, closest_point, global_closest_point);
        
        // Assign the global closest point to the entity's collision point
        set_point(entity->collision.point, global_closest_point);
        return 1; // Collision detected
    } 
    
    else return 0; // No collision
}


/* collision_obb_aabb
detects collision between an OBB and an AABB */

int collision_obb_aabb(OBB obb, AABB aabb) {
    float obbCorners[8][3], aabbCorners[8][3];

    get_obb_corners(obb, obbCorners);
    get_aabb_corners(aabb, aabbCorners);

    // AABB axes
    float aabbAxes[3][3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};

    // Rotated OBB axes
    float obbAxes[3][3];

    for (int i = 0; i < 3; i++) {
        float axis[3] = {0, 0, 0};
        axis[i] = 1;
        rotate_point(axis, obb.rotation);
        obbAxes[i][0] = axis[0];
        obbAxes[i][1] = axis[1];
        obbAxes[i][2] = axis[2];
    }

    // Collision checks
    for (int i = 0; i < 3; i++) {
        if (!test_axis(aabbAxes[i], obbCorners, aabbCorners)) return 0;
        if (!test_axis(obbAxes[i], obbCorners, aabbCorners)) return 0;
    }

    // Check collisions on cross products of OBB and AABB axes
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            float crossAxis[3];
            cross_product(aabbAxes[i], obbAxes[j], crossAxis);
            if (!test_axis(crossAxis, obbCorners, aabbCorners)) return 0;
        }
    }

    return 1; // Collision detected
}


/* collision_cylinder_aabb
Detects collision between a cylinder and an AABB */

int collision_cylinder_aabb(Entity* entity, Cylinder cylinder, AABB aabb) 
{
    // Calculate the closest point on AABB to the cylinder's base center
    float closest_point[3] = {
        clamp(cylinder.base_center[0], aabb.min[0], aabb.max[0]),
        clamp(cylinder.base_center[1], aabb.min[1], aabb.max[1]),
        clamp(cylinder.base_center[2], aabb.min[2], aabb.max[2])
    };

    // Check horizontal collision
    float horizontal_distance_squared = (closest_point[0] - cylinder.base_center[0]) * (closest_point[0] - cylinder.base_center[0]) +
                                        (closest_point[1] - cylinder.base_center[1]) * (closest_point[1] - cylinder.base_center[1]);
    if (horizontal_distance_squared > (cylinder.radius * cylinder.radius))
        return 0;  // No horizontal collision

    // Check vertical collision
    if (closest_point[2] < cylinder.base_center[2] || closest_point[2] > cylinder.base_center[2] + cylinder.height)
        return 0;  // No vertical collision

    set_point(entity->collision.point, closest_point);
    
    return 1; // Collision detected
}

/* collision_cylinder_obb
Detects collision between a cylinder and an OBB */

int collision_cylinder_obb(Entity* entity, Cylinder cylinder, OBB obb) 
{
    // Transform cylinder base center to OBB local space
    float local_base_center[3];
    point_global_to_obb_space(obb, cylinder.base_center, local_base_center);

    // Calculate the closest point in OBB local space
    float closest_point[3] = {
        clamp(local_base_center[0], -obb.size[0] / 2, obb.size[0] / 2),
        clamp(local_base_center[1], -obb.size[1] / 2, obb.size[1] / 2),
        clamp(local_base_center[2], -obb.size[2] / 2, obb.size[2] / 2)
    };

    // Check horizontal collision
    float horizontal_distance_squared = (closest_point[0] - local_base_center[0]) * (closest_point[0] - local_base_center[0]) +
                                        (closest_point[1] - local_base_center[1]) * (closest_point[1] - local_base_center[1]);
    if (horizontal_distance_squared > (cylinder.radius * cylinder.radius))
        return 0;  // No horizontal collision

    // Check vertical collision
    if (closest_point[2] < local_base_center[2] || closest_point[2] > local_base_center[2] + cylinder.height)
        return 0;  // No vertical collision

    // Convert the closest point back to global space
    float closest_point_global[3];
    point_obb_to_global_space(obb, closest_point, closest_point_global);
    set_point(entity->collision.point, closest_point_global);

    return 1; // Collision detected
}


/* collision_capsule_aabb
Detects collision between a capsule and an AABB */

int collision_capsule_aabb(Entity* entity, Capsule capsule, AABB aabb)
{
    // Check collision with spheres at the ends of the capsule
    Sphere lower_sphere = {.center = {capsule.start_point[0], capsule.start_point[1], capsule.start_point[2]}, .radius = capsule.radius};
    Sphere upper_sphere = {.center = {capsule.end_point[0], capsule.end_point[1], capsule.end_point[2]}, .radius = capsule.radius};

    if (collision_sphere_aabb(entity, lower_sphere, aabb) || collision_sphere_aabb(entity, upper_sphere, aabb))
        return 1;  // Collision with one of the end spheres

    // Check collision with the cylindrical body
    Cylinder cylinder = {
        .base_center = {capsule.start_point[0], capsule.start_point[1], capsule.start_point[2]},
        .height = length(capsule.end_point) - length(capsule.start_point),
        .radius = capsule.radius
    };

    return collision_cylinder_aabb(entity, cylinder, aabb);
}

/* collision_capsule_obb
Detects collision between a capsule and an OBB */

int collision_capsule_obb(Entity* entity, Capsule capsule, OBB obb)
{
    // Check collision with spheres at the ends of the capsule
    Sphere lower_sphere = {.center = {capsule.start_point[0], capsule.start_point[1], capsule.start_point[2]}, .radius = capsule.radius};
    Sphere upper_sphere = {.center = {capsule.end_point[0], capsule.end_point[1], capsule.end_point[2]}, .radius = capsule.radius};

    if (collision_sphere_obb(entity, lower_sphere, obb) || collision_sphere_obb(entity, upper_sphere, obb))
        return 1;  // Collision with one of the end spheres

    // Check collision with the cylindrical body
    Cylinder cylinder = {
        .base_center = {capsule.start_point[0], capsule.start_point[1], capsule.start_point[2]},
        .height = length(capsule.end_point) - length(capsule.start_point),
        .radius = capsule.radius
    };

    return collision_cylinder_obb(entity, cylinder, obb);
}


/* collision_ray_aabb checks if a ray intersects with an AABB and calculates the distance of the intersection.
   returns 1 if there is an intersection, 0 otherwise. 
   additionally calculates the precise hit point if an intersection is detected. */

int collision_ray_aabb(float origin[3], float target[3], AABB aabb, float* hit_point)
{
    float len = qi_sqrt(pow(target[0] - origin[0], 2) + pow(target[1] - origin[1], 2) + pow(target[2] - origin[2], 2)); // I've inverted len so we can multiply instead of divide with it
    float inverse_direction[3];
    float t1[3], t2[3], tmin, tmax;

    // Calculate inverse direction and handle division by zero for rays parallel to AABB planes
    for (int i = 0; i < 3; i++) {
        if (fabs(target[i] - origin[i]) < 0.001f) { // Avoid division by zero by checking if direction is almost parallel to the plane
            if (origin[i] < aabb.min[i] || origin[i] > aabb.max[i]) return 0; // Ray is parallel and outside AABB, no intersection
            inverse_direction[i] = FLT_MAX; // Use a large number to represent infinity
        } else {
            inverse_direction[i] = 1.0f / ((target[i] - origin[i])*len);
        }
    }

    // Calculate intersections with the AABB planes
    for (int i = 0; i < 3; i++) {
        t1[i] = (aabb.min[i] - origin[i]) * inverse_direction[i];
        t2[i] = (aabb.max[i] - origin[i]) * inverse_direction[i];

        // Ensure t1 is the intersection with the near plane, and t2 with the far plane
        if (t1[i] > t2[i]) {
            float temp = t1[i];
            t1[i] = t2[i];
            t2[i] = temp;
        }
    }

    // Find the largest tmin and the smallest tmax
    tmin = max(max(t1[0], t1[1]), t1[2]);
    tmax = min(min(t2[0], t2[1]), t2[2]);

    // If tmax < tmin, ray doesn't intersect AABB
    if (tmax < tmin) {
        return 0;
    }

    // If there's an intersection, the hit distance is tmin (if tmin >= 0) or tmax (if tmin < 0 and thus the ray starts inside the AABB)
    float hit_distance = (tmin >= 0.0f) ? tmin : tmax;

    // Calculate the precise hit point using hit_distance
    for (int i = 0; i < 3; i++) {
        hit_point[i] = origin[i] + (target[i] - origin[i]) * len * hit_distance;
    }

    return 1;
}


#endif