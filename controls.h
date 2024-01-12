#ifndef CONTROLS_H
#define CONTROLS_H

/* CONTROLS.H
here are all the input related functions */


// function prototypes

void move_viewport_stick(Viewport *viewport, NUContData contdata[1]);
void move_entity_stick(Entity *entity, Viewport viewport, NUContData contdata[1]);



/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/



/* move_viewport_stick
changes the viewport variables depending on controller input*/

void move_viewport_stick(Viewport *viewport, NUContData *contdata)
{
    if (fabs(contdata->stick_x) < 7) contdata->stick_x = 0;
    if (fabs(contdata->stick_y) < 7) contdata->stick_y = 0;

    viewport->angle_around_target += contdata->stick_x / 20;
    viewport->pitch += contdata->stick_y / 20;

    if (viewport->angle_around_target > 360) {viewport->angle_around_target  = viewport->angle_around_target - 360;}
    if (viewport->angle_around_target < 0) {viewport->angle_around_target  = viewport->angle_around_target + 360;}

    if (viewport->pitch > 85) viewport->pitch = 85;
    if (viewport->pitch < -85) viewport->pitch = -85;
}


/*move_entity_stick
changes the entity position variables depending on controller input */

void move_entity_stick(Entity *entity, Viewport viewport, NUContData *contdata)
{
    float input_amount;

	if (fabs(contdata->stick_x) < 9) {contdata->stick_x = 0;}
	if (fabs(contdata->stick_y) < 9) {contdata->stick_y = 0;}


    if (fabs(contdata->stick_x) > 0 || fabs(contdata->stick_y) > 0) {
        
        input_amount = 1 / qi_sqrt(contdata->stick_x * contdata->stick_x +  contdata->stick_y * contdata->stick_y);
        entity->target_yaw = deg(atan2(contdata->stick_x, -contdata->stick_y) - rad(viewport.angle_around_target));
    }    
    
    entity->input_amount = input_amount; //debug data collecting
    
    if (input_amount == 0){
        
        if  (fabs(entity->speed[0]) < 1 && fabs(entity->speed[1]) < 1){
            entity->speed[0] = 0;
            entity->speed[1] = 0;
        }

        entity->acceleration[0] = 9 * (0 - entity->speed[0]);
        entity->acceleration[1] = 9 * (0 - entity->speed[1]);
    }

    else if (input_amount > 0 && input_amount <= 60){

        entity->target_speed[0] = 80 * sinf(rad(entity->target_yaw));
        entity->target_speed[1] = 80 * -cosf(rad(entity->target_yaw));

        entity->acceleration[0] = 4 * (entity->target_speed[0] - entity->speed[0]);
        entity->acceleration[1] = 4 * (entity->target_speed[1] - entity->speed[1]);
    }
    else if (input_amount > 60){

        entity->target_speed[0] = 200 * sinf(rad(entity->target_yaw));
        entity->target_speed[1] = 200 * -cosf(rad(entity->target_yaw));

        entity->acceleration[0] = 4 * (entity->target_speed[0] - entity->speed[0]);
        entity->acceleration[1] = 4 * (entity->target_speed[1] - entity->speed[1]);
    }
    
    if (entity->speed[0] != 0 || entity->speed[1] != 0) entity->yaw = deg(atan2(entity->speed[0], -entity->speed[1]));
}


#endif