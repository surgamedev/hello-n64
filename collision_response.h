#ifndef COLLISION_RESPONSE_H
#define COLLISION_RESPONSE_H

/* COLLISION_RESPONSE_H
here are all the structures and functions prototypes that involve the collision response */

void set_collision_plane_aabb(Entity* entity, AABB* aabb);
void get_collision_normal_obb(Entity* entity, OBB obb) ;
void collide_and_slide(Entity* entity);
void set_collission_response(Entity* entity, Capsule capsule, AABB aabb, OBB obb);


/* get_collision_normal_aabb
Computes the collision normal for an AABB collision and stores it in the entity's collision normal */

void set_collision_plane_aabb(Entity* entity, AABB* aabb)
{
    null_vector(entity->collision.normal); // Initialize the normal vector to zero

    float distance[6]; // Distances from the entity collision point to each face of the AABB

    // Calculate distance from the collision point to each AABB face
    distance[0] = fabs(entity->collision.point[0] - aabb->min[0]); // Left face
    distance[1] = fabs(entity->collision.point[0] - aabb->max[0]); // Right face
    distance[2] = fabs(entity->collision.point[1] - aabb->min[1]); // Bottom face
    distance[3] = fabs(entity->collision.point[1] - aabb->max[1]); // Top face
    distance[4] = fabs(entity->collision.point[2] - aabb->min[2]); // Front face
    distance[5] = fabs(entity->collision.point[2] - aabb->max[2]); // Back face

    // Find the minimum distance and its corresponding face
    float minDistance = FLT_MAX;
    int faceIndex = -1;
    for (int i = 0; i < 6; ++i) {
        if (distance[i] < minDistance) {
            minDistance = distance[i];
            faceIndex = i;
        }
    }

    // Assign the normal based on the closest face and calculate the bottom-left point of the face
    switch (faceIndex) {
        case 0: // Left face
            entity->collision.normal[0] = -1;
            init_point(aabb->plane.point, aabb->min[0], aabb->min[1], aabb->min[2]);
            break;
        case 1: // Right face
            entity->collision.normal[0] = 1;
            init_point(aabb->plane.point, aabb->max[0], aabb->min[1], aabb->min[2]);
            break;
        case 2: // Bottom face
            entity->collision.normal[1] = -1;
            init_point(aabb->plane.point, aabb->min[0], aabb->min[1], aabb->min[2]);
            break;
        case 3: // Top face
            entity->collision.normal[1] = 1;
            init_point(aabb->plane.point, aabb->min[0], aabb->max[1], aabb->min[2]);
            break;
        case 4: // Front face
            entity->collision.normal[2] = -1;
            init_point(aabb->plane.point, aabb->min[0], aabb->min[1], aabb->min[2]);
            break;
        case 5: // Back face
            entity->collision.normal[2] = 1;
            init_point(aabb->plane.point, aabb->min[0], aabb->min[1], aabb->max[2]);
            break;
    }

    set_point(aabb->plane.normal, entity->collision.normal);

    aabb->plane.displacement = dot_product(aabb->plane.normal, aabb->plane.point);
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


void set_collision_point(Entity* entity, Capsule capsule, AABB aabb)
{
    float direction[3];
    set_vector(direction, entity->previous_position, entity->position);
    
    // Normalize the direction vector
    normalize_vector(direction);
    
    // Distance from the initial point to the plane
    float distance_from_plane = -(dot_product(aabb.plane.normal, entity->previous_position) - aabb.plane.displacement);
    
    // Calculate the denominator to prevent division by zero
    float denominator = dot_product(aabb.plane.normal, direction);
    
    // Prevent the case where t is -inf or NaN using a small threshold instead of FLT_MIN
    if (fabs(denominator) < 1e-6) { // FLT_MIN could be used, but 1e-6 is more practical for this check
        // The direction vector is parallel to the plane, handle accordingly
        return; // Choose how to handle this case
    }
    
    // t for the intersection with the plane
    float t = distance_from_plane / denominator;
    
    // Exact intersection point on the plane without adjusting for the radius
    for (int i = 0; i < 3; i++) {
        entity->collision.point[i] = entity->previous_position[i] + t * direction[i];
    }
    
    // Adjust the collision point by the capsule's radius perpendicular to the plane
    for (int i = 0; i < 3; i++) {
        entity->previous_position[i] = entity->collision.point[i] + aabb.plane.normal[i] * (capsule.radius + 1);
    }
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
    for (int i = 0; i < 1; i++) {

        if(collision_capsule_aabb(entity, capsule, aabb)){
                set_collision_plane_aabb(entity, &aabb);
                set_collision_point(entity, capsule, aabb);
                collide_and_slide(entity);
        }

        if(collision_capsule_obb(entity, capsule, obb)){
                get_collision_normal_obb(entity, obb);
                collide_and_slide(entity);
        }
    }
}


#endif