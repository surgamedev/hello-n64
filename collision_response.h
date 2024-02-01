#ifndef COLLISION_RESPONSE_H
#define COLLISION_RESPONSE_H

/* COLLISION_RESPONSE_H
here are all the structures and functions prototypes that involve the collision response */

void get_collision_normal_aabb(Entity* entity, AABB aabb);
void get_collision_normal_obb(Entity* entity, OBB obb) ;
void collision_response(Entity* entity);
void set_collissions(Entity* entity, Capsule capsule, AABB aabb, OBB obb);


/* get_collision_normal_aabb
Computes the collision normal for an AABB collision and stores it in the entity's collision normal */

void get_collision_normal_aabb(Entity* entity, AABB aabb) 
{
    float normal[3] = {0, 0, 0}; // Default normal
    float minDistance = FLT_MAX; // Initialize with maximum possible distance
    float distance;

    // Check each face of the AABB to find the closest to the collision point
    // Left face
    distance = fabs(entity->collision.point[0] - aabb.min[0]);
    if (distance < minDistance) {
        minDistance = distance;
        normal[0] = -1; normal[1] = 0; normal[2] = 0;
    }

    // Right face
    distance = fabs(entity->collision.point[0] - aabb.max[0]);
    if (distance < minDistance) {
        minDistance = distance;
        normal[0] = 1; normal[1] = 0; normal[2] = 0;
    }

    // Bottom face
    distance = fabs(entity->collision.point[1] - aabb.min[1]);
    if (distance < minDistance) {
        minDistance = distance;
        normal[0] = 0; normal[1] = -1; normal[2] = 0;
    }

    // Top face
    distance = fabs(entity->collision.point[1] - aabb.max[1]);
    if (distance < minDistance) {
        minDistance = distance;
        normal[0] = 0; normal[1] = 1; normal[2] = 0;
    }

    // Front face (lower Z)
    distance = fabs(entity->collision.point[2] - aabb.min[2]);
    if (distance < minDistance) {
        minDistance = distance;
        normal[0] = 0; normal[1] = 0; normal[2] = -1;
    }

    // Back face (higher Z)
    distance = fabs(entity->collision.point[2] - aabb.max[2]);
    if (distance < minDistance) {
        normal[0] = 0; normal[1] = 0; normal[2] = 1;
    }

    // Store the computed normal in the entity's collision structure
    set_point(entity->collision.normal, normal);
}


/* get_collision_normal_obb
Computes the collision normal for an OBB collision and stores it in the entity's collision normal */

void get_collision_normal_obb(Entity* entity, OBB obb) 
{
    float normal[3] = {0, 0, 0}; // Default normal
    float minDistance = FLT_MAX; // Initialize with maximum possible distance
    float distance;

    // Convert collision point to OBB's local space
    float local_collision_point[3];
    point_global_to_obb_space(obb, entity->collision.point, local_collision_point);

    // Check each face of the OBB in its local space
    // Local left face (x-axis)
    distance = fabs(local_collision_point[0] + obb.size[0] / 2);
    if (distance < minDistance) {
        minDistance = distance;
        normal[0] = -1; normal[1] = 0; normal[2] = 0;
    }

    // Local right face (x-axis)
    distance = fabs(local_collision_point[0] - obb.size[0] / 2);
    if (distance < minDistance) {
        minDistance = distance;
        normal[0] = 1; normal[1] = 0; normal[2] = 0;
    }

    // Local bottom face (y-axis)
    distance = fabs(local_collision_point[1] + obb.size[1] / 2);
    if (distance < minDistance) {
        minDistance = distance;
        normal[0] = 0; normal[1] = -1; normal[2] = 0;
    }

    // Local top face (y-axis)
    distance = fabs(local_collision_point[1] - obb.size[1] / 2);
    if (distance < minDistance) {
        minDistance = distance;
        normal[0] = 0; normal[1] = 1; normal[2] = 0;
    }

    // Local front face (z-axis)
    distance = fabs(local_collision_point[2] + obb.size[2] / 2);
    if (distance < minDistance) {
        minDistance = distance;
        normal[0] = 0; normal[1] = 0; normal[2] = -1;
    }

    // Local back face (z-axis)
    distance = fabs(local_collision_point[2] - obb.size[2] / 2);
    if (distance < minDistance) {
        normal[0] = 0; normal[1] = 0; normal[2] = 1;
    }

    rotate_point(normal, obb.rotation);
    set_point(entity->collision.normal, normal);
}



void collision_response(Entity* entity)
{
    // Paso 1: Calcular el vector de desplazamiento
    float displacement[3] = {
        entity->position[0] - entity->previous_position[0],
        entity->position[1] - entity->previous_position[1],
        entity->position[2] - entity->previous_position[2]
    };

    // Supongamos que ya hemos detectado una colisión y tenemos la normal de la colisión almacenada en entity->collision.normal

    // Paso 2: Calcular el vector de deslizamiento (slide vector)
    // Esto se hace proyectando el vector de desplazamiento sobre el plano de colisión
    float dotProduct = displacement[0] * entity->collision.normal[0] +
                       displacement[1] * entity->collision.normal[1] +
                       displacement[2] * entity->collision.normal[2];
    
    float slideVector[3] = {
        displacement[0] - dotProduct * entity->collision.normal[0],
        displacement[1] - dotProduct * entity->collision.normal[1],
        displacement[2] - dotProduct * entity->collision.normal[2]
    };

    // Paso 3: Aplicar el vector de deslizamiento a partir de la posición anterior de la entidad
    entity->position[0] = entity->previous_position[0] + slideVector[0];
    entity->position[1] = entity->previous_position[1] + slideVector[1];
    entity->position[2] = entity->previous_position[2] + slideVector[2];

    // Nota: Es posible que necesites realizar más verificaciones de colisión después de aplicar el vector de deslizamiento
    // para manejar casos donde el movimiento resultante pueda causar nuevas colisiones.
}


void set_collissions(Entity* entity, Capsule capsule, AABB aabb, OBB obb)
{
    if(collision_capsule_aabb(entity, capsule, aabb)){
            get_collision_normal_aabb(entity, aabb);
            collision_response(entity);
    }
    if(collision_capsule_obb(entity, capsule, obb)){
            get_collision_normal_obb(entity, obb);
            collision_response(entity);
    }
}
#endif