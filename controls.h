#ifndef CONTROLS_H
#define CONTROLS_H

/* CONTROLS.H
here are all the input related functions */


// function prototypes

int input(u32 input);
void move_viewport_stick(Viewport *viewport, Entity entity, NUContData *contdata);
void move_viewport_c_buttons(Viewport *viewport, NUContData *contdata, TimeData timedata);
void move_entity_stick(Entity *entity, Viewport viewport, NUContData *contdata);
void set_entity_actions(Entity *entity, NUContData *contdata, TimeData timedata);



/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/



/* input
 auxiliary function for 8 directional movement*/

int input(u32 input){
    if (input == 0) {return 0;}
    else {return 1;}
}


/* move_viewport_stick
changes the viewport variables depending on controller input*/

void move_viewport_stick(Viewport *viewport, Entity entity, NUContData *contdata)
{
    int deadzone = 8;
    float stick_x = 0;
    float stick_y = 0;

    if (fabs(contdata->stick_x) >= deadzone || fabs(contdata->stick_y) >= deadzone) {
        stick_x = contdata->stick_x;
        stick_y = contdata->stick_y;
    }

    if (stick_x == 0 && stick_y == 0) {
        viewport->rotational_target_speed[0] = 0;
        viewport->rotational_target_speed[1] = 0;
    }
    
    else if (stick_x != 0 || stick_y != 0) {
        viewport->rotational_target_speed[0] = stick_x;
        viewport->rotational_target_speed[1] = stick_y;
    }
    
    if (contdata->button & Z_TRIG && entity.state != ROLL) set_viewport_state (viewport, THIRD_PERSON_SHOOTER_AIMING);
    else set_viewport_state (viewport, THIRD_PERSON_SHOOTER);
}


void move_viewport_c_buttons(Viewport *viewport, NUContData *contdata, TimeData timedata)
{
    float stick_x = 0;
    float stick_y = 0;

    if ((contdata->button & R_CBUTTONS) || (contdata->button & L_CBUTTONS) || (contdata->button & U_CBUTTONS) || (contdata->button & D_CBUTTONS)){
        
        stick_x = input(contdata->button & R_CBUTTONS) - input(contdata->button & L_CBUTTONS);
        stick_y = input(contdata->button & U_CBUTTONS) - input(contdata->button & D_CBUTTONS);
    }

    if (stick_x == 0) viewport->rotational_target_speed[0] = 0; 
    else viewport->rotational_target_speed[0] = stick_x * viewport->settings.rotational_max_speed[0];

	if (stick_y == 0) viewport->rotational_target_speed[1] = 0; 
    else viewport->rotational_target_speed[1] = stick_y * viewport->settings.rotational_max_speed[1];

    if (contdata->button & Z_TRIG) set_viewport_state (viewport, THIRD_PERSON_SHOOTER_AIMING);
    else set_viewport_state (viewport, THIRD_PERSON_SHOOTER);
}


void set_entity_actions(Entity *entity, NUContData *contdata, TimeData timedata)
{    
    if (contdata->trigger & A_BUTTON && entity->state != ROLL && entity->state != JUMP) {
        
        entity->input.hold = 1; 
        set_entity_state(entity, JUMP);
    }

    if (contdata->button & A_BUTTON && entity->state == JUMP) {

        entity->input.hold = 1; 
        entity->input.time_held += timedata.frame_duration;
    }
    else {
        
        entity->input.hold = 0;    
    }

    if (contdata->trigger & B_BUTTON && entity->state != JUMP) set_entity_state(entity, ROLL);
}


/*move_entity_stick
changes the entity state and target yaw depending on controller input */

void move_entity_stick(Entity *entity, Viewport viewport, NUContData *contdata)
{
    int deadzone = 8;
    float stick_total = 0; 

    if (fabs(contdata->stick_x) >= deadzone || fabs(contdata->stick_y) >= deadzone) {
        stick_total = calculate_diagonal(contdata->stick_x ,contdata->stick_y);
        entity->target_yaw = deg(atan2(contdata->stick_x, -contdata->stick_y) - rad(viewport.angle_around_entity - (viewport.offset_angle / 2)));
    }

    //debug data collecting
    entity->input.stick_total = stick_total;
    
    if (stick_total == 0 && entity->state != ROLL && entity->state != JUMP){
        set_entity_state(entity, STAND_IDLE);
    }

    else if (stick_total > 0 && stick_total <= 64 && entity->state != ROLL && entity->state != JUMP){
        set_entity_state(entity, WALKING);
    }

    else if (stick_total > 64 && entity->state != ROLL && entity->state != JUMP){
        set_entity_state(entity, RUNNING);
    }
}


#endif