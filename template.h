#ifndef TEMPLATE_H
#define TEMPLATE_H


void entity_collide_and_slide(Entity *entity, CollisionPackage collision_package, const float *vel[3], const float *gravity[3])
{
    // Do collision detection:
    set_point(collision_package->r3_position, entity->position);
    set_point(collision_package->r3_velocity, vel);


    // calculate position and velocity in eSpace
    float e_space_position[3] = collision_package->r3_position / collision_package->e_radius;
    float e_space_velocity[3] = collision_package->r3_velocity / collision_package->e_radius;

    // Iterate until we have our final position.
    int collision_recursion_depth = 0;

    float final_position; 
    collideWithWorld(final_position, e_space_position, e_space_velocity);
    
    // Add gravity pull:
    // To remove gravity uncomment from here .....
    // Set the new R3 position (convert back from eSpace to R3
    collision_package->r3_position = finalPosition * collision_package->e_radius;
    collision_package->r3_velocity = gravity;

    e_space_velocity = gravity/collision_package->e_radius;
    collisionRecursionDepth = 0;

    finalPosition = collideWithWorld(finalPosition,
    e_space_velocity);
    // ... to here
    // Convert final result back to R3:
    finalPosition = finalPosition * collision_package->e_radius;
    // Move the entity (application specific function)
    MoveTo(finalPosition);
}






void rotate_cube(){

    if ( cube.rotational_speed[0] > 270){

        cube.rotational_speed[0] -= 50;
        cube.rotational_speed[1] -= 50;
        cube.rotational_speed[2] -= 50;
    }

    cube.rotation[0] += cube.rotational_speed[0] * timedata.frame_duration;
    cube.rotation[1] -= cube.rotational_speed[1] * timedata.frame_duration;
    cube.rotation[2] += cube.rotational_speed[2] * timedata.frame_duration;
}

/*
int swap_cube_index = 0;

void swap_cube(){

    cube.scale_speed = 0;

    if ( cube.rotational_speed[0] < 1270){

        cube.rotational_speed[0] += 50;
        cube.rotational_speed[1] += 50;
        cube.rotational_speed[2] += 50;
    }

    cube.yaw += cube.rotational_speed[0] * timedata.frame_duration;
    cube.pitch -= cube.rotational_speed[1] * timedata.frame_duration;
    cube.roll += cube.rotational_speed[2] * timedata.frame_duration;

    swap_cube_index = 0;

    cube.model = gfx_n64_logo;
}
*/




    // Set this to match application scale..
    const float unitsPerMeter = 100.0f;
    
void collide_with_world(Entity *entity, CollisionPackage collision_package, const float *pos, const float *vel)
{
    // All hard-coded distances in this function is
    // scaled to fit the setting above..
    float unitScale = unitsPerMeter / 100.0f;
    float veryCloseDistance = 0.005f * unitScale;
    // do we need to worry?
    if (collisionRecursionDepth>5)
    return pos;
    // Ok, we need to worry:
    set_point(collision_package->velocity, vel);
    set_point(collision_package->normalized_velocity, vel);
    set_point(collision_package->basePoint, pos);

    collision_package->normalizedVelocity.normalize();

    collision_package->foundCollision = 0;
    // Check for collision (calls the collision routines)
    // Application specific!!
    world->checkCollision(collision_package);
    // If no collision we just move along the velocity
    if (collision_package->foundCollision == false) {
    return pos + vel;
    }
    // *** Collision occured ***
    // The original destination point
    VECTOR destinationPoint = pos + vel;
    VECTOR newBasePoint = pos;
    // only update if we are not already very close
    // and if so we only move very close to intersection..not
    // to the exact spot.
    if (collision_package->nearestDistance>=veryCloseDistance)
    {
    VECTOR V = vel;
    V.SetLength(collision_package->nearestDistanceveryCloseDistance);
    newBasePoint = collision_package->basePoint + V;
    // Adjust polygon intersection point (so sliding
    // plane will be unaffected by the fact that we
    // move slightly less than collision tells us)
    V.normalize();
    collision_package->intersectionPoint -=
    veryCloseDistance * V;
    }
    // Determine the sliding plane
    VECTOR slidePlaneOrigin =
    46
    collision_package->intersectionPoint;
    VECTOR slidePlaneNormal =
    newBasePoint-collision_package->intersectionPoint;
    slidePlaneNormal.normalize();
    PLANE slidingPlane(slidePlaneOrigin,slidePlaneNormal);
    // Again, sorry about formatting.. but look carefully ;)
    VECTOR newDestinationPoint = destinationPoint -
    slidingPlane.signedDistanceTo(destinationPoint)*
    slidePlaneNormal;
    // Generate the slide vector, which will become our new
    // velocity vector for the next iteration
    VECTOR newVelocityVector = newDestinationPoint -
    collision_package->intersectionPoint;
    // Recurse:
    // dont recurse if the new velocity is very small
    if (newVelocityVector.length() < veryCloseDistance) {
    return newBasePoint;
    }
    collisionRecursionDepth++;
    return collideWithWorld(newBasePoint,newVelocityVector);











































#include <math.h>

typedef struct {
    float x;
    float y;
    float z;
} VECTOR;

typedef struct {
    VECTOR r3_position;
    VECTOR r3_velocity;
    float e_radius;
    VECTOR velocity;
    VECTOR normalizedVelocity;
    VECTOR basePoint;
    int foundCollision;
    float nearestDistance;
    VECTOR intersectionPoint;
} Collision_package;

typedef struct {
    VECTOR origin;
    VECTOR normal;
} PLANE;

void MoveTo(VECTOR finalPosition);

const float unitsPerMeter = 100.0f;
Collision_package* collision_package;

void CharacterEntity_collideAndSlide(const VECTOR* vel, const VECTOR* gravity) {
    // Do collision detection:
    collision_package->r3_position = position;
    collision_package->r3_velocity = *vel;
    // calculate position and velocity in eSpace
    VECTOR e_space_position;
    e_space_position.x = collision_package->r3_position.x / collision_package->e_radius;
    e_space_position.y = collision_package->r3_position.y / collision_package->e_radius;
    e_space_position.z = collision_package->r3_position.z / collision_package->e_radius;
    VECTOR e_space_velocity;
    e_space_velocity.x = collision_package->r3_velocity.x / collision_package->e_radius;
    e_space_velocity.y = collision_package->r3_velocity.y / collision_package->e_radius;
    e_space_velocity.z = collision_package->r3_velocity.z / collision_package->e_radius;
    // Iterate until we have our final position.
    int collisionRecursionDepth = 0;
    VECTOR finalPosition = CharacterEntity_collideWithWorld(&e_space_position, &e_space_velocity);
    // Add gravity pull:
    // To remove gravity, uncomment from here ...
    // Set the new R3 position (convert back from eSpace to R3)
    collision_package->r3_position.x = finalPosition.x * collision_package->e_radius;
    collision_package->r3_position.y = finalPosition.y * collision_package->e_radius;
    collision_package->r3_position.z = finalPosition.z * collision_package->e_radius;
    collision_package->r3_velocity = *gravity;
    e_space_velocity = *gravity / collision_package->e_radius;
    collisionRecursionDepth = 0;
    finalPosition = CharacterEntity_collideWithWorld(&finalPosition, &e_space_velocity);
    // ... to here
    // Convert final result back to R3:
    collision_package->r3_position.x = finalPosition.x * collision_package->e_radius;
    collision_package->r3_position.y = finalPosition.y * collision_package->e_radius;
    collision_package->r3_position.z = finalPosition.z * collision_package->e_radius;
    // Move the entity (application-specific function)
    MoveTo(finalPosition);
}

// Set this to match application scale...
const float unitsPerMeter = 100.0f;

VECTOR CharacterEntity_collideWithWorld(const VECTOR* pos, const VECTOR* vel) {
    // All hard-coded distances in this function are scaled to fit the setting above...
    float unitScale = unitsPerMeter / 100.0f;
    float veryCloseDistance = 0.005f * unitScale;
    // Do we need to worry?
    if (collisionRecursionDepth > 5)
        return *pos;
    // OK, we need to worry:
    collision_package->velocity = *vel;
    collision_package->normalizedVelocity = *vel;
    collision_package->normalizedVelocity.normalize();
    collision_package->basePoint = *pos;
    collision_package->foundCollision = 0;
    // Check for collision (calls the collision routines)
    // Application specific!!
    world->checkCollision(collision_package);
    // If no collision, we just move along the velocity
    if (!collision_package->foundCollision) {
        VECTOR result;
        result.x = pos->x + vel->x;
        result.y = pos->y + vel->y;
        result.z = pos->z + vel->z;
        return result;
    }
    // *** Collision occurred ***
    // The original destination point
    VECTOR destinationPoint;
    destinationPoint.x = pos->x + vel->x;
    destinationPoint.y = pos->y + vel->y;
    destinationPoint.z = pos->z + vel->z;
    VECTOR newBasePoint = *pos;
    // Only update if we are not already very close
    // And if so, we only move very close to intersection, not
    // to the exact spot.
    if (collision_package->nearestDistance >= veryCloseDistance) {
        VECTOR V = *vel;
        float factor = collision_package->nearestDistance * veryCloseDistance;
        V.x *= factor;
        V.y *= factor;
        V.z *= factor;
        newBasePoint.x = collision_package->basePoint.x + V.x;
        newBasePoint.y = collision_package->basePoint.y + V.y;
        newBasePoint.z = collision_package->basePoint.z + V.z;
        // Adjust polygon intersection point (so sliding
        // plane will be unaffected by the fact that we
        // move slightly less than collision tells us)
        V.normalize();
        collision_package->intersectionPoint.x -= veryCloseDistance * V.x;
        collision_package->intersectionPoint.y -= veryCloseDistance * V.y;
        collision_package->intersectionPoint.z -= veryCloseDistance * V.z;
    }
    // Determine the sliding plane
    VECTOR slidePlaneOrigin = collision_package->intersectionPoint;
    VECTOR slidePlaneNormal;
    slidePlaneNormal.x = newBasePoint.x - collision_package->intersectionPoint.x;
    slidePlaneNormal.y = newBasePoint.y - collision_package->intersectionPoint.y;
    slidePlaneNormal.z = newBasePoint.z - collision_package->intersectionPoint.z;
    float length = sqrt(slidePlaneNormal.x * slidePlaneNormal.x +
                        slidePlaneNormal.y * slidePlaneNormal.y +
                        slidePlaneNormal.z * slidePlaneNormal.z);
    slidePlaneNormal.x /= length;
    slidePlaneNormal.y /= length;
    slidePlaneNormal.z /= length;
    PLANE slidingPlane;
    slidingPlane.origin = slidePlaneOrigin;
    slidingPlane.normal = slidePlaneNormal;
    // Again, sorry about formatting... but look carefully ;)
    VECTOR newDestinationPoint;
    float distance = slidingPlaneDistanceTo(&slidingPlane, &destinationPoint);
    newDestinationPoint.x = destinationPoint.x - distance * slidePlaneNormal.x;
    newDestinationPoint.y = destinationPoint.y - distance * slidePlaneNormal.y;
    newDestinationPoint.z = destinationPoint.z - distance * slidePlaneNormal.z;
    // Generate the slide vector, which will become our new
    // velocity vector for the next iteration
    VECTOR newVelocityVector;
    newVelocityVector.x = newDestinationPoint.x - collision_package->intersectionPoint.x;
    newVelocityVector.y = newDestinationPoint.y - collision_package->intersectionPoint.y;
    newVelocityVector.z = newDestinationPoint.z - collision_package->intersectionPoint.z;
    // Recurse:
    // Don't recurse if the new velocity is very small
    if (lengthOfVector(&newVelocityVector) < veryCloseDistance) {
        return newBasePoint;
    }
    collisionRecursionDepth++;
    return CharacterEntity_collideWithWorld(&newBasePoint, &newVelocityVector);
}








#include <math.h>

typedef struct {
    float r3_position[3];
    float r3_velocity[3];
    float e_radius;
    float velocity[3];
    float normalizedVelocity[3];
    float basePoint[3];
    int foundCollision;
    float nearestDistance;
    float intersectionPoint[3];
} Collision_package;

typedef struct {
    float origin[3];
    float normal[3];
} PLANE;

void MoveTo(float finalPosition[3]);

const float unitsPerMeter = 100.0f;
Collision_package* collision_package;


void CharacterEntity_collideAndSlide(const float vel[3], const float gravity[3]) {
    // Do collision detection:
    for (int i = 0; i < 3; i++) {
        collision_package->r3_position[i] = position[i];
        collision_package->r3_velocity[i] = vel[i];
    }
    // calculate position and velocity in eSpace
    float e_space_position[3];
    float e_space_velocity[3];
    for (int i = 0; i < 3; i++) {
        e_space_position[i] = collision_package->r3_position[i] / collision_package->e_radius;
        e_space_velocity[i] = collision_package->r3_velocity[i] / collision_package->e_radius;
    }
    // Iterate until we have our final position.
    int collisionRecursionDepth = 0;
    float finalPosition[3] = CharacterEntity_collideWithWorld(e_space_position, e_space_velocity);
    // Add gravity pull:
    // To remove gravity, uncomment from here ...
    // Set the new R3 position (convert back from eSpace to R3)
    for (int i = 0; i < 3; i++) {
        collision_package->r3_position[i] = finalPosition[i] * collision_package->e_radius;
    }
    for (int i = 0; i < 3; i++) {
        collision_package->r3_velocity[i] = gravity[i];
    }
    for (int i = 0; i < 3; i++) {
        e_space_velocity[i] = gravity[i] / collision_package->e_radius;
    }
    collisionRecursionDepth = 0;
    finalPosition = CharacterEntity_collideWithWorld(finalPosition, e_space_velocity);
    // ... to here
    // Convert final result back to R3:
    for (int i = 0; i < 3; i++) {
        collision_package->r3_position[i] = finalPosition[i] * collision_package->e_radius;
    }
    MoveTo(finalPosition);
}

// Set this to match application scale..
const float unitsPerMeter = 100.0f;

float* CharacterEntity_collideWithWorld(const float pos[3], const float vel[3]) {
    // All hard-coded distances in this function are
    // scaled to fit the setting above..
    float unitScale = unitsPerMeter / 100.0f;
    float veryCloseDistance = 0.005f * unitScale;
    // do we need to worry?
    if (collisionRecursionDepth > 5)
        return pos;
    // Ok, we need to worry:
    for (int i = 0; i < 3; i++) {
        collision_package->velocity[i] = vel[i];
    }
    for (int i = 0; i < 3; i++) {
        collision_package->normalizedVelocity[i] = vel[i];
    }
    // Normalize the normalizedVelocity vector
    float normalizedVelocityLength = 0.0f;
    for (int i = 0; i < 3; i++) {
        normalizedVelocityLength += vel[i] * vel[i];
    }
    normalizedVelocityLength = sqrt(normalizedVelocityLength);
    for (int i = 0; i < 3; i++) {
        collision_package->normalizedVelocity[i] /= normalizedVelocityLength;
    }
    for (int i = 0; i < 3; i++) {
        collision_package->basePoint[i] = pos[i];
    }
    collision_package->foundCollision = 0;
    // Check for collision (calls the collision routines)
    // Application specific!!
    world->checkCollision(collision_package);
    // If no collision we just move along the velocity
    if (collision_package->foundCollision == 0) {
        float newPos[3];
        for (int i = 0; i < 3; i++) {
            newPos[i] = pos[i] + vel[i];
        }
        return newPos;
    }
    // *** Collision occurred ***
    // The original destination point
    float destinationPoint[3];
    for (int i = 0; i < 3; i++) {
        destinationPoint[i] = pos[i] + vel[i];
    }
    float newBasePoint[3];
    for (int i = 0; i < 3; i++) {
        newBasePoint[i] = pos[i];
    }
    // only update if we are not already very close
    // and if so we only move very close to intersection..not
    // to the exact spot.
    if (collision_package->nearestDistance >= veryCloseDistance) {
        float V[3];
        for (int i = 0; i < 3; i++) {
            V[i] = vel[i];
        }
        for (int i = 0; i < 3; i++) {
            V[i] *= collision_package->nearestDistance / veryCloseDistance;
        }
        for (int i = 0; i < 3; i++) {
            newBasePoint[i] = collision_package->basePoint[i] + V[i];
        }
        // Adjust polygon intersection point (so sliding
        // plane will be unaffected by the fact that we
        // move slightly less than collision tells us)
        float VLength = 0.0f;
        for (int i = 0; i < 3; i++) {
            VLength += V[i] * V[i];
        }
        VLength = sqrt(VLength);
        for (int i = 0; i < 3; i++) {
            V[i] /= VLength;
        }
        for (int i = 0; i < 3; i++) {
            collision_package->intersectionPoint[i] -= veryCloseDistance * V[i];
        }
    }
    // Determine the sliding plane
    float slidePlaneOrigin[3];
    for (int i = 0; i < 3; i++) {
        slidePlaneOrigin[i] = collision_package->intersectionPoint[i];
    }
    float slidePlaneNormal[3];
    for (int i = 0; i < 3; i++) {
        slidePlaneNormal[i] = newBasePoint[i] - collision_package->intersectionPoint[i];
    }
    // Normalize the slidePlaneNormal vector
    float slidePlaneNormalLength = 0.0f;
    for (int i = 0; i < 3; i++) {
        slidePlaneNormalLength += slidePlaneNormal[i] * slidePlaneNormal[i];
    }
    slidePlaneNormalLength = sqrt(slidePlaneNormalLength);
    for (int i = 0; i < 3; i++) {
        slidePlaneNormal[i] /= slidePlaneNormalLength;
    }
    PLANE slidingPlane;
    for (int i = 0; i < 3; i++) {
        slidingPlane.origin[i] = slidePlaneOrigin[i];
        slidingPlane.normal[i] = slidePlaneNormal[i];
    }
    float newDestinationPoint[3];
    for (int i = 0; i < 3; i++) {
        newDestinationPoint[i] = destinationPoint[i] - slidingPlane.signedDistanceTo(destinationPoint) * slidePlaneNormal[i];
    }
    // Generate the slide vector, which will become our new
    // velocity vector for the next iteration
    float newVelocityVector[3];
    for (int i = 0; i < 3; i++) {
        newVelocityVector[i] = newDestinationPoint[i] - collision_package->intersectionPoint[i];
    }
    // Recurse:
    // don't recurse if the new velocity is very small
    float newVelocityVectorLength = 0.0f;
    for (int i = 0; i < 3; i++) {
        newVelocityVectorLength += newVelocityVector[i] * newVelocityVector[i];
    }
    newVelocityVectorLength = sqrt(newVelocityVectorLength);
    if (newVelocityVectorLength < veryCloseDistance) {
        return newBasePoint;
    }
    collisionRecursionDepth++;
    return CharacterEntity_collideWithWorld(newBasePoint, newVelocityVector);
}




// Check if a solution exists
int get_lowest_root(float *root, float max_r, float a, float b, float c) 
{

    float determinant = b * b - 4.0f * a * c;

    // If determinant is negative, it means no solutions.
    if (determinant < 0.0f) return 0; 
    

    // Calculate the two roots: (if determinant == 0 then
    // x1==x2, but let’s disregard that slight optimization)
    float sqrt_d = 1 / qi_sqrt(determinant);
    float r1 = (-b - sqrt_d) / (2 * a);
    float r2 = (-b + sqrt_d) / (2 * a);

    // Sort so x1 <= x2
    if (r1 > r2) {
        float temp = r2;
        r2 = r1;
        r1 = temp;
    }

    // Get lowest root:
    if (r1 > 0 && r1 < max_r) {
        *root = r1;
        return 1; // True, a valid solution was found.
    }

    // It is possible that we want x2 - this can happen
    // if x1 < 0
    if (r2 > 0 && r2 < max_r) {
        *root = r2;
        return 1; // True, a valid solution was found.
    }

    // No (valid) solutions
    return 0; // False, no valid solutions.
}


void check_triangle(CollisionPackage *collision_package, float* p1, float* p2, float* p3)
{
    // Make the plane containing this triangle.
    Plane triangle_plane;
    set_plane_from_triangle(&triangle_plane, p1, p2, p3);

    // Is the triangle front-facing to the velocity vector?
    if (is_plane_facing_velocity(&triangle_plane, collision_package->normalized_velocity)) {
        // Get interval of plane intersection:
        double t0, t1;
        int embedded_in_plane = 0;

        // Calculate the signed distance from the ellipsoid position to the triangle plane
        double signed_dist_to_triangle_plane = signed_distance_point_to_plane(&triangle_plane, collision_package->base_point);

        // Cache this as we’re going to use it a few times below:
        float normal_dot_velocity = dot_product(triangle_plane.normal, collision_package->velocity);

        // If the ellipsoid is traveling parallel to the plane:
        if (normal_dot_velocity == 0.0f) {
            if (fabs(signed_dist_to_triangle_plane) >= 1.0f) {
                // The ellipsoid is not embedded in the plane.
                // No collision possible.
                return;
            } else {
                // The ellipsoid is embedded in the plane.
                // It intersects in the whole range [0..1]
                embedded_in_plane = 1;
                t0 = 0.0;
                t1 = 1.0;
            }
        } else {
            // N dot D is not 0. Calculate the intersection interval:
            t0 = (-1.0 - signed_dist_to_triangle_plane) / normal_dot_velocity;
            t1 = (1.0 - signed_dist_to_triangle_plane) / normal_dot_velocity;

            // Swap so t0 < t1
            if (t0 > t1) {
                double temp = t1;
                t1 = t0;
                t0 = temp;
            }

            // Check that at least one result is within range:
            if (t0 > 1.0f || t1 < 0.0f) {
                // Both t values are outside values [0,1].
                // No collision possible.
                return;
            }

            // Clamp to [0,1]
            t0 = (t0 < 0.0) ? 0.0 : t0;
            t1 = (t1 < 0.0) ? 0.0 : t1;
            t0 = (t0 > 1.0) ? 1.0 : t0;
            t1 = (t1 > 1.0) ? 1.0 : t1;
        }

        // At this point, we have two time values t0 and t1
        // between which the swept ellipsoid intersects with the
        // triangle plane. If any collision is to occur, it must
        // happen within this interval.
        float collision_point[3];
        int found_collision = 0;
        float t = 1.0;

        // First, check for the easy case - collision inside
        // the triangle. If this happens, it must be at time t0
        // as this is when the ellipsoid rests on the front side
        // of the triangle plane. Note, this can only happen if
        // the ellipsoid is not embedded in the triangle plane.
        if (!embedded_in_plane) {

            float *plane_intersection_point;
            subtract_vectors(plane_intersection_point, collision_package->base_point, triangle_plane.normal);
            add_scaled_vector(plane_intersection_point, plane_intersection_point, collision_package->velocity, t0);

            if (collision_point_and_triangle(plane_intersection_point, p1, p2, p3)) {
                found_collision = 1;
                t = t0;
                set_point(collision_point, plane_intersection_point);
            }
        }

        // If we haven’t found a collision already, sweep the ellipsoid against points and edges of the triangle.
        // Note: A collision inside the triangle (the check above) will always happen before a vertex or edge collision!
        // This is why we can skip the swept test if the above gives a collision!
        if (!found_collision) {

            float *substracted_vector;
            float velocity_squared_length = squared_length(collision_package->velocity);
            float a, b, c; // Params for equation
            float new_t;

            // For each vertex or edge, a quadratic equation has to
            // be solved. We parameterize this equation as
            // a*t^2 + b*t + c = 0, and below we calculate the
            // parameters a, b, and c for each test.

            // Check against points:

            // P1
            a = velocity_squared_length;
            subtract_vectors(substracted_vector, collision_package->base_point, p1);
            b = 2.0 * dot_product(collision_package->velocity, substracted_vector);
            subtract_vectors(substracted_vector, p1, collision_package->base_point);
            c = squared_length(substracted_vector) - 1.0;
            if (get_lowest_root(&new_t, a, b, c, t)) {
                t = new_t;
                found_collision = 1;
                set_point(collision_point, p1);
            }

            // P2
            subtract_vectors(substracted_vector, collision_package->base_point, p2);
            b = 2.0 * dot_product(collision_package->velocity, substracted_vector);
            subtract_vectors(substracted_vector, p2, collision_package->base_point);
            c = squared_length(substracted_vector) - 1.0;

            if (get_lowest_root(&new_t, a, b, c, t)) {
                t = new_t;
                found_collision = 1;
                set_point(collision_point, p2);
            }

            // P3
            subtract_vectors(substracted_vector, collision_package->base_point, p3);
            b = 2.0 * dot_product(collision_package->velocity, substracted_vector);
            subtract_vectors(substracted_vector, p3, collision_package->base_point);
            c = squared_length(substracted_vector) - 1.0;
            if (get_lowest_root(&new_t, a, b, c, t)) {
                t = new_t;
                found_collision = 1;
                set_point(collision_point, p3);
            }

            // Check against edges:

            // p1 -> p2:
            float edge[3];
            subtract_vectors(edge, p2, p1);
            float base_to_vertex[3];
            subtract_vectors(base_to_vertex, p1, collision_package->base_point);
            float edge_squared_length = squared_length(edge);
            float edge_dot_velocity = dot_product(edge, collision_package->velocity);
            float edge_dot_base_to_vertex = dot_product(edge, base_to_vertex);

            // Calculate parameters for equation
            a = edge_squared_length * -velocity_squared_length + edge_dot_velocity * edge_dot_velocity;
            b = edge_squared_length * (2 * dot_product(collision_package->velocity, base_to_vertex)) -
                2.0 * edge_dot_velocity * edge_dot_base_to_vertex;
            c = edge_squared_length * (1 - squared_length(base_to_vertex)) + edge_dot_base_to_vertex * edge_dot_base_to_vertex;

            // Does the swept ellipsoid collide against an infinite edge?
            if (get_lowest_root(&new_t, a, b, c, t)) {
                // Check if the intersection is within the line segment:
                float f = (edge_dot_velocity * new_t - edge_dot_base_to_vertex) / edge_squared_length;
                if (f >= 0.0 && f <= 1.0) {
                    // Intersection took place within the segment.
                    t = new_t;
                    found_collision = 1;
                    add_scaled_vector(collision_point, p1, edge, f);
                }
            }

            // p2 -> p3:
            subtract_vectors(edge, p3, p2);
            subtract_vectors(base_to_vertex, p2, collision_package->base_point);
            edge_squared_length = squared_length(edge);
            edge_dot_velocity = dot_product(edge, collision_package->velocity);
            edge_dot_base_to_vertex = dot_product(edge, base_to_vertex);

            a = edge_squared_length * -velocity_squared_length + edge_dot_velocity * edge_dot_velocity;
            b = edge_squared_length * (2 * dot_product(collision_package->velocity, base_to_vertex)) -
                2.0 * edge_dot_velocity * edge_dot_base_to_vertex;
            c = edge_squared_length * (1 - squared_length(base_to_vertex)) + edge_dot_base_to_vertex * edge_dot_base_to_vertex;

            if (get_lowest_root(&new_t, a, b, c, t)) {
                float f = (edge_dot_velocity * new_t - edge_dot_base_to_vertex) / edge_squared_length;
                if (f >= 0.0 && f <= 1.0) {
                    t = new_t;
                    found_collision = 1;
                    add_scaled_vector(collision_point, p2, edge, f);
                }
            }

            // p3 -> p1:
            subtract_vectors(edge, p1, p3);
            subtract_vectors(base_to_vertex, p3, collision_package->base_point);
            edge_squared_length = squared_length(edge);
            edge_dot_velocity = dot_product(edge, collision_package->velocity);
            edge_dot_base_to_vertex = dot_product(edge, base_to_vertex);

            a = edge_squared_length * -velocity_squared_length + edge_dot_velocity * edge_dot_velocity;
            b = edge_squared_length * (2 * dot_product(collision_package->velocity, base_to_vertex)) -
                2.0 * edge_dot_velocity * edge_dot_base_to_vertex;
            c = edge_squared_length * (1 - squared_length(base_to_vertex)) + edge_dot_base_to_vertex * edge_dot_base_to_vertex;

            if (get_lowest_root(&new_t, a, b, c, t)) {
                float f = (edge_dot_velocity * new_t - edge_dot_base_to_vertex) / edge_squared_length;
                if (f >= 0.0 && f <= 1.0) {
                    t = new_t;
                    found_collision = 1;
                    add_scaled_vector(collision_point, p3, edge, f);
                }
            }
        }

        // Set result:
        if (found_collision) {
            // Distance to collision: ’t’ is the time of collision
            float dist_to_collision = t * length(collision_package->velocity);

            // Does this triangle qualify for the closest hit?
            // It does if it’s the first hit or the closest
            if (!collision_package->found_collision || dist_to_collision < collision_package->nearest_distance) {
                // Collision information necessary for sliding
                collision_package->nearest_distance = dist_to_collision;
                set_point(collision_package->intersection_point, collision_point);
                collision_package->found_collision = 1;
            }
        }
    } // if not backface
}




int is_plane_facing_velocity(Plane *plane, float *direction)
{
    return (0 >= dot_product(plane->normal, direction));
}




/* set_plane_from_normal
sets a plane given an origin point and a vector*/
void set_plane_from_normal(Plane* plane, float origin[3], float normal[3])
{
    set_point(plane->normal, normal);
    set_point(plane->origin, origin);
    set_point(plane->equation, normal);
    plane->equation[3] = -dot_product(normal, origin);
}


void set_plane_from_triangle(Plane *plane, float *a, float *b, float *c)
{
    float *vec1;
    float *vec2;

    set_vector(vec1, a, b);
    set_vector(vec2, a, c);

    plane->normal[0] = vec1[1] * vec2[2] - vec1[2] * vec2[1];
    plane->normal[1] = vec1[2] * vec2[0] - vec1[0] * vec2[2];
    plane->normal[2] = vec1[0] * vec2[1] - vec1[1] * vec2[0];

    // Normalize the normal float

    float length = 1 / qi_sqrt(dot_product (plane->normal, plane->normal));

    plane->normal[0] /= length;
    plane->normal[1] /= length;
    plane->normal[2] /= length;

    set_point(plane->origin, a);

    set_point(plane->equation, plane->normal);
    plane->equation[3] = -dot_product(plane->normal, plane->origin);
}


/*
void detect_collisions(Entity *entity, Scenery object, TimeData timedata) 
{
    if ( collision_point_and_rectangle(entity->position, object.position, 100, 100)) {

        float A[3]; float B[3]; float C[3]; float D[3];

        int width = 100;
        int depth = 100;

        A[0] = entity->position[0] + width / 2;
        A[1] = entity->position[1] + depth / 2;
        
        B[0] = entity->position[0] - width / 2;
        B[1] = entity->position[1] + depth / 2;
        
        C[0] = entity->position[0] - width / 2;
        C[1] = entity->position[1] - depth / 2;
        
        D[0] = entity->position[0] + width / 2;
        D[1] = entity->position[1] - depth / 2;

        min_dist_to_wall_old =

        min(minimum_distance(A, D, entity->position),
            min(minimum_distance(C, D, entity->position),
                min(minimum_distance(A, B, entity->position), 
                    minimum_distance(B, C, entity->position)
                )
            )
        );

        min_dist_to_wall_new = 
        
        min(minimum_distance(A, D, new_pos),
            min(minimum_distance(C, D, new_pos),
                min(minimum_distance(A, B, new_pos), 
                    minimum_distance(B, C, new_pos)
                )
            )
        );

        if (collision_point_and_rectangle(new_pos, object.position, 500, 500))
        {
            if (min_dist_to_wall_new != min_dist_to_wall_old) {
                
                entity.speed[0] = 0;
                entity.speed[1] = 0;
            }
        }
    }
}
*/



/*
returns the minimum distance between a line segment ab and point c */ 

float distance_point_and_line(float *a, float *b, float *c) 
{
 float l2 = distance_squared(a, b);

    float c_a[3];
    float b_a[3];
    float projection[3];
    
    if (l2 == 0.0) return distance(c, a);
    
    c_a[0] = c[0] - a[0];
    c_a[1] = c[1] - a[1];
    
    b_a[0] = b[0] - a[0];
    b_a[1] = b[1] - a[1];

 float t = max(0, min(1, dot_product(c_a, b_a) / l2));

    projection[0] = a[0] + t * (b[0] - a[0]);
    projection[1] = a[1] + t * (b[1] - a[1]);
    
    return distance(c, projection);
}

/* squared_distance_point_to_segment
calculates the squared distance from a point to a line segment */
float squared_distance_point_to_segment(float point[3], float segment_start[3], float segment_end[3])
{
    float segment_vector[3] = {segment_end[0] - segment_start[0], segment_end[1] - segment_start[1], segment_end[2] - segment_start[2]};
    float point_vector[3] = {point[0] - segment_start[0], point[1] - segment_start[1], point[2] - segment_start[2]};
    float segment_length_squared = squared_distance(segment_start, segment_end);

    float t = dot_product(point_vector, segment_vector) / segment_length_squared;
    t = (t < 0.0f) ? 0.0f : ((t > 1.0f) ? 1.0f : t);  // Clamp t to the range [0, 1]

    float closest[3] = {segment_start[0] + t * segment_vector[0], segment_start[1] + t * segment_vector[1], segment_start[2] + t * segment_vector[2]};
    return squared_distance(point, closest);
}


// https://stackoverflow.com/questions/2752725/finding-whether-a-point-lies-inside-a-rectangle-or-not/37865332#37865332
// currently only looks at x and y, despite passing in 3d points

int collision_point_and_rectangle(float point_position[3], float rectangle_position[3], float width, float depth) 
{
    float   a[3], b[3], c[3], d[3], 
            AB[3], AM[3], BC[3], BM[3];

    a[0] = rectangle_position[0] + width / 2;
    a[1] = rectangle_position[1] + depth / 2;
    b[0] = rectangle_position[0] - width / 2;
    b[1] = rectangle_position[1] + depth / 2;
    c[0] = rectangle_position[0] - width / 2;
    c[1] = rectangle_position[1] - depth / 2;
    d[0] = rectangle_position[0] + width / 2;
    d[1] = rectangle_position[1] - depth / 2;
    set_vector(AB, a, b);
    set_vector(AM, a, point_position);
    set_vector(BC, b, c);
    set_vector(BM, b, point_position);
    float dotABAM = dot_product(AB, AM);
    float dotABAB = dot_product(AB, AB);
    float dotBCBM = dot_product(BC, BM);
    float dotBCBC = dot_product(BC, BC);
    return 0 <= dotABAM && dotABAM <= dotABAB && 0 <= dotBCBM && dotBCBM <= dotBCBC;
}




/* signed_distance_point_to_plane
returns the signed distance of a point from a plane*/
float signed_distance_point_to_plane (Plane *plane, float* point) 
{
    return (point[0] * plane->normal[0] + point[1] * plane->normal[1] + point[2] * plane->normal[2]) + plane->equation[3];
}



/* collision_point_and_triangle
check if a point is inside a circle in the horizontal plane */
int collision_point_and_circle(float point_position[3], float circle_center[3], float radius) 
{

    return radius >= distance(point_position, circle_center);
}


/* collision_point_and_triangle
checks if a point is inside a triangle in 3D space */
float collision_point_and_triangle(const float point[3], const float pa[3], const float pb[3], const float pc[3]) 
{
    float e10[3] = {pb[0] - pa[0], pb[1] - pa[1], pb[2] - pa[2]};
    float e20[3] = {pc[0] - pa[0], pc[1] - pa[1], pc[2] - pa[2]};
    float a = e10[0] * e10[0] + e10[1] * e10[1] + e10[2] * e10[2];
    float b = e10[0] * e20[0] + e10[1] * e20[1] + e10[2] * e20[2];
    float c = e20[0] * e20[0] + e20[1] * e20[1] + e20[2] * e20[2];
    float ac_bb = (a * c) - (b * b);
    float vp[3] = {point[0] - pa[0], point[1] - pa[1], point[2] - pa[2]};
    float d = vp[0] * e10[0] + vp[1] * e10[1] + vp[2] * e10[2];
    float e = vp[0] * e20[0] + vp[1] * e20[1] + vp[2] * e20[2];
    float x = (d * c) - (e * b);
    float y = (e * a) - (d * b);
    float z = x + y - ac_bb;
    return ((in(z) & ~(in(x) | in(y))) & 0x80000000);
}


#endif