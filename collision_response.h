#ifndef COLLISION_RESPONSE_H
#define COLLISION_RESPONSE_H

/* COLLISION_RESPONSE_H
here are all the structures and functions prototypes that involve the collision response */

void get_collision_normal_aabb(Entity* entity, AABB aabb);
void get_collision_normal_obb(Entity* entity, OBB obb) ;
void collide_and_slide(Entity* entity);
void set_collission_response(Entity* entity, Capsule capsule, AABB aabb, OBB obb);


/* get_collision_normal_aabb
Computes the collision normal for an AABB collision and stores it in the entity's collision normal */

void get_collision_normal_aabb(Entity* entity, AABB aabb) 
{
    float normal[3] = {0, 0, 0}; // Normal vector initialized to zero
    float distance[6]; // Distances from the entity collision point to each face of the AABB

    // Calculate distance from the collision point to each AABB face
    distance[0] = fabs(entity->collision.point[0] - aabb.min[0]);
    distance[1] = fabs(entity->collision.point[0] - aabb.max[0]);
    distance[2] = fabs(entity->collision.point[1] - aabb.min[1]);
    distance[3] = fabs(entity->collision.point[1] - aabb.max[1]);
    distance[4] = fabs(entity->collision.point[2] - aabb.min[2]);
    distance[5] = fabs(entity->collision.point[2] - aabb.max[2]);

    // Find the minimum distance and its corresponding face
    float minDistance = FLT_MAX;
    int faceIndex = -1;
    for (int i = 0; i < 6; ++i) {
        if (distance[i] < minDistance) {
            minDistance = distance[i];
            faceIndex = i;
        }
    }

    // Assign the normal based on the closest face
    switch (faceIndex) {
        case 0: normal[0] = -1; break;
        case 1: normal[0] = 1; break; 
        case 2: normal[1] = -1; break;
        case 3: normal[1] = 1; break; 
        case 4: normal[2] = -1; break;
        case 5: normal[2] = 1; break; 
    }

    // Store the computed normal in the entity's collision structure
    set_point(entity->collision.normal, normal);
}


/* get_collision_normal_obb
Computes the collision normal for an OBB collision and stores it in the entity's collision normal */

void get_collision_normal_obb(Entity* entity, OBB obb) 
{
    float normal[3] = {0, 0, 0}; // Normal vector initialized to zero
    float distance[6]; // Distances from the entity collision point to each face of the AABB

    // Convert collision point to OBB's local space
    float local_collision_point[3];
    point_global_to_obb_space(obb, entity->collision.point, local_collision_point);

    // Calculate distance from the collision point to each AABB face
    distance[0] = fabs(local_collision_point[0] + obb.size[0] / 2);
    distance[1] = fabs(local_collision_point[0] - obb.size[0] / 2);
    distance[2] = fabs(local_collision_point[1] + obb.size[1] / 2);
    distance[3] = fabs(local_collision_point[1] - obb.size[1] / 2);
    distance[4] = fabs(local_collision_point[2] + obb.size[2] / 2);
    distance[5] = fabs(local_collision_point[2] - obb.size[2] / 2);

    // Find the minimum distance and its corresponding face
    float minDistance = FLT_MAX;
    int faceIndex = -1;
    for (int i = 0; i < 6; ++i) {
        if (distance[i] < minDistance) {
            minDistance = distance[i];
            faceIndex = i;
        }
    }

    // Assign the normal based on the closest face
    switch (faceIndex) {
        case 0: normal[0] = -1; break;
        case 1: normal[0] = 1; break; 
        case 2: normal[1] = -1; break;
        case 3: normal[1] = 1; break; 
        case 4: normal[2] = -1; break;
        case 5: normal[2] = 1; break; 
    }

    rotate_point(normal, obb.rotation);
    set_point(entity->collision.normal, normal);
}


void collide_and_slide(Entity* entity)
{
    float intended_displacement[3];

    set_vector(intended_displacement, entity->previous_position, entity->position);

    float dotProduct = dot_product(intended_displacement, entity->collision.normal);
    
    float slideVector[3] = {
        intended_displacement[0] - dotProduct * entity->collision.normal[0],
        intended_displacement[1] - dotProduct * entity->collision.normal[1],
        intended_displacement[2] - dotProduct * entity->collision.normal[2]
    };
    
    entity->position[0] = entity->previous_position[0] + slideVector[0];
    entity->position[1] = entity->previous_position[1] + slideVector[1];
    entity->position[2] = entity->previous_position[2] + slideVector[2];
}


void set_collission_response(Entity* entity, Capsule capsule, AABB aabb, OBB obb)
{
    if(collision_capsule_aabb(entity, capsule, aabb)){
            get_collision_normal_aabb(entity, aabb);
            collide_and_slide(entity);
    }

    if(collision_capsule_obb(entity, capsule, obb)){
            get_collision_normal_obb(entity, obb);
            collide_and_slide(entity);
    }
}


#endif