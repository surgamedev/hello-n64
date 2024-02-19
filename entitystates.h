#ifndef ENTITYSTATES_H
#define ENTITYSTATES_H

/* ENTITYSTATES.H
here are all the entity state machine related functions */

// entity properties



// variables


// function prototypes

void calculate_acceleration (Entity *entity, float target_speed, float acceleration_rate);

void calculate_acceleration_forward (Entity *entity, float target_speed, float acceleration_rate);

void calculate_jump_acceleration (Entity *entity, float target_speed, float acceleration_rate);

void set_entity_state (Entity *entity, EntityState new_state);

void set_idle_state (Entity *entity);

void set_walking_state (Entity *entity);
            
void set_running_state (Entity *entity);
            
void set_sprinting_state (Entity *entity);

void set_roll_state (Entity *entity);

void set_jump_state (Entity *entity);

void set_fall_state (Entity *entity);

void set_grounded_foot (Entity *entity);



void calculate_acceleration(Entity *entity, float target_speed, float acceleration_rate)
{
    entity->target_velocity[0] = target_speed * sinf(rad(entity->target_yaw));
    entity->target_velocity[1] = target_speed * -cosf(rad(entity->target_yaw));

    entity->acceleration[0] = acceleration_rate * (entity->target_velocity[0] - entity->velocity[0]);
    entity->acceleration[1] = acceleration_rate * (entity->target_velocity[1] - entity->velocity[1]);
}


void calculate_acceleration_forward(Entity *entity, float target_speed, float acceleration_rate)
{
    entity->target_velocity[0] = target_speed * sinf(rad(entity->yaw));
    entity->target_velocity[1] = target_speed * -cosf(rad(entity->yaw));

    entity->acceleration[0] = acceleration_rate * (entity->target_velocity[0] - entity->velocity[0]);
    entity->acceleration[1] = acceleration_rate * (entity->target_velocity[1] - entity->velocity[1]);
}


void calculate_jump_acceleration(Entity *entity, float target_speed, float acceleration_rate)
{
    entity->acceleration[2] = acceleration_rate * (target_speed - entity->velocity[2]);
}


void set_entity_state(Entity *entity, EntityState new_state) 
{
    switch(new_state) {

        case STAND_IDLE: {
            set_idle_state (entity);
            break;
        }
        case WALKING: {
            set_walking_state (entity);
            break;
        }
        case RUNNING: {
            set_running_state (entity);
            break;
        }
        case SPRINTING: {
            set_sprinting_state (entity);
            break;
        }
        case ROLL: {
            set_roll_state (entity);
            break;
        }
        case JUMP: {
            set_jump_state (entity);
            break;
        }
        case FALL: {
            set_fall_state (entity);
            break;
        }   
    }
}


void set_idle_state(Entity *entity)
{
    if  (fabs(entity->velocity[0]) < 1 && fabs(entity->velocity[1]) < 1){
        entity->velocity[0] = 0;
        entity->velocity[1] = 0;
    }
    
    entity->acceleration[0] = entity->settings.idle_acceleration_rate * (0 - entity->velocity[0]);
    entity->acceleration[1] = entity->settings.idle_acceleration_rate * (0 - entity->velocity[1]);

    if (entity->state == STAND_IDLE) return;
    
    entity->target_yaw = entity->yaw;
    entity->state = STAND_IDLE;

    if (entity->grounded_foot == LEFT){
    sausage64_set_anim(&entity->model, ANIMATION_nick_look_around_left);
    }

    if (entity->grounded_foot == RIGHT){
    sausage64_set_anim(&entity->model, ANIMATION_nick_look_around_right);
    }

    entity->previous_state = STAND_IDLE;
}


void set_walking_state(Entity *entity)
{
    calculate_acceleration(entity, entity->settings.walk_target_speed, entity->settings.walk_acceleration_rate);

    if (entity->state == WALKING) return;
    
    entity->state = WALKING;
    sausage64_set_anim(&entity->model, ANIMATION_nick_walk_right);
    entity->previous_state = WALKING;
}


void set_running_state(Entity *entity)
{
    calculate_acceleration (entity, entity->settings.run_target_speed, entity->settings.run_acceleration_rate);

    if (entity->state == RUNNING) return;
    
    entity->state = RUNNING;
    sausage64_set_anim(&entity->model, ANIMATION_nick_jog_right);
    entity->previous_state = RUNNING;
}


void set_sprinting_state(Entity *entity)
{
    calculate_acceleration (entity, entity->settings.sprint_target_speed, entity->settings.run_acceleration_rate);

    if (entity->state == SPRINTING) return;
    
    entity->state = SPRINTING;
    sausage64_set_anim(&entity->model, ANIMATION_nick_run_right);
    entity->previous_state = SPRINTING;
}


void set_roll_state(Entity *entity)
{
    switch(entity->previous_state) {

        case STAND_IDLE: {

            if(entity->model.animtick < entity->settings.idle_to_roll_change_grip_tick) 
                calculate_acceleration_forward (entity, entity->settings.idle_to_roll_target_speed, entity->settings.roll_acceleration_rate);

            if(entity->model.animtick >= entity->settings.idle_to_roll_change_grip_tick) 
                calculate_acceleration (entity, entity->settings.idle_to_roll_grip_target_speed, entity->settings.roll_acceleration_grip_rate);
        
            if (entity->state == ROLL) return;

            entity->state = ROLL;
            sausage64_set_anim_tick(&entity->model, ANIMATION_nick_stand_to_roll_left, 0);           

            break;
        }

        case WALKING: {

            if(entity->model.animtick < entity->settings.walk_to_roll_change_grip_tick) 
                calculate_acceleration_forward (entity, entity->settings.walk_to_roll_target_speed, entity->settings.roll_acceleration_rate); 

            if (entity->model.animtick >= entity->settings.walk_to_roll_change_grip_tick) 
                calculate_acceleration (entity, entity->settings.walk_target_speed, entity->settings.roll_acceleration_grip_rate); 
        
            if (entity->state == ROLL) return;
        
            entity->state = ROLL;
            sausage64_set_anim(&entity->model, ANIMATION_nick_run_to_roll_left);

            break;
        }

        case RUNNING: {
            

            if(entity->model.animtick < entity->settings.run_to_roll_change_grip_tick) 
                calculate_acceleration_forward (entity, entity->settings.run_to_roll_target_speed, entity->settings.roll_acceleration_rate); 

            if(entity->model.animtick >= entity->settings.run_to_roll_change_grip_tick) 
                calculate_acceleration (entity, entity->settings.run_target_speed, entity->settings.roll_acceleration_grip_rate);

            if (entity->state == ROLL) return;
        
            entity->state = ROLL;
            sausage64_set_anim(&entity->model, ANIMATION_nick_run_to_roll_left);

            break;
        }

        case SPRINTING: {
            

            if(entity->model.animtick < entity->settings.run_to_roll_change_grip_tick) 
                calculate_acceleration_forward (entity, entity->settings.sprint_to_roll_target_speed, entity->settings.roll_acceleration_rate); 

            if(entity->model.animtick >= entity->settings.run_to_roll_change_grip_tick) 
                calculate_acceleration (entity, entity->settings.sprint_target_speed, entity->settings.roll_acceleration_grip_rate);

            if (entity->state == ROLL) return;
        
            entity->state = ROLL;
            sausage64_set_anim(&entity->model, ANIMATION_nick_run_to_roll_left);

            break;
        }
    }
}


void set_jump_state(Entity *entity) 
{   
    entity->grounded = 0;
    entity->grounding_height = -FLT_MAX;
    
    if (entity->input.hold == 1 && entity->input.released == 0 && entity->input.time_held < entity->settings.jump_timer_max){

        calculate_jump_acceleration (entity, entity->settings.jump_target_speed, entity->settings.jump_acceleration_rate);
        calculate_acceleration (entity, entity->directional_speed, entity->settings.aerial_control_rate);
    } 
    
    else if (entity->velocity[2] >= 0){

        calculate_acceleration (entity, entity->directional_speed, entity->settings.aerial_control_rate);
        entity->acceleration[2] = -GRAVITY;
    }
    
    else {

        set_entity_state(entity, FALL);
        entity->input.time_held = 0;
        return;
    }

    if (entity->state == JUMP) return;
    
    entity->state = JUMP;
    sausage64_set_anim (&entity->model, ANIMATION_nick_jump_left);
}


void set_fall_state (Entity *entity)
{   
    entity->grounded = 0;
    calculate_acceleration (entity, entity->directional_speed, entity->settings.aerial_control_rate);
    entity->acceleration[2] = -GRAVITY;

    if (entity->position[2] < entity->grounding_height) {

        entity->grounded = 1;
        entity->acceleration[2] = 0;
        entity->velocity[2] = 0;
        entity->position[2] = entity->grounding_height;

        set_entity_state (entity, entity->previous_state);

        return;
    }

    entity->grounding_height = -FLT_MAX;

    if (entity->state == FALL ) return;

    entity->state = FALL;

    if (sausage64_get_curranim(&entity->model) != ANIMATION_nick_fall_idle_left 
        && sausage64_get_curranim(&entity->model) != ANIMATION_nick_jump_left)
         
        sausage64_set_anim (&entity->model, ANIMATION_nick_fall_idle_left);
}


void set_grounded_foot(Entity *entity)
{
    // TO DO 
}


#endif