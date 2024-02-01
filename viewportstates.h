#ifndef VIEWPORTSTATES_H
#define VIEWPORTSTATES_H

/* VIEWPORTSTATES.H
here are all the viewport state machine related functions */

// function prototypes

void set_viewport_state(Viewport *viewport, ViewportState new_state);

void set_third_person_shooter_viewport(Viewport *viewport);

void set_third_person_shooter_aiming_viewport(Viewport *viewport);

void set_third_person_shooter_looking_viewport(Viewport *viewport);


void set_viewport_state(Viewport *viewport, ViewportState new_state) 
{
    switch(new_state) {

        case THIRD_PERSON_SHOOTER: {
            set_third_person_shooter_viewport(viewport);
            break;
        }
        case THIRD_PERSON_SHOOTER_AIMING: {
            set_third_person_shooter_aiming_viewport(viewport);
            break;
        }
        case THIRD_PERSON_SHOOTER_LOOKING: {
            set_third_person_shooter_looking_viewport(viewport);
            break;
        }
    }
}


void set_third_person_shooter_viewport(Viewport *viewport)
{
    if (viewport->distance_from_entity < viewport->settings.target_zoom) 
        viewport->zoom_acceleration = viewport->settings.zoom_acceleration_rate * (viewport->settings.zoom_max_speed - viewport->zoom_speed);
    
    else viewport->zoom_acceleration =  (viewport->settings.zoom_deceleration_rate + 10) * (0 - viewport->zoom_speed);
    
    viewport->zoom_direction = 1;
    
    if (viewport->offset_angle > viewport->settings.target_offset) 
        viewport->offset_acceleration = viewport->settings.offset_acceleration_rate * (viewport->settings.offset_max_speed  - viewport->offset_speed);
    
    else viewport->offset_acceleration = viewport->settings.offset_deceleration_rate * (0 - viewport->offset_speed);
    
    viewport->offset_direction = -1;

    viewport->rotational_acceleration[0] = viewport->settings.rotational_acceleration_rate * (viewport->rotational_target_speed[0] - viewport->rotational_speed[0]);
    viewport->rotational_acceleration[1] = viewport->settings.rotational_acceleration_rate * (viewport->rotational_target_speed[1] - viewport->rotational_speed[1]);
}


void set_third_person_shooter_aiming_viewport(Viewport *viewport)
{
    if (viewport->distance_from_entity > viewport->settings.target_zoom_aim) 
        viewport->zoom_acceleration = (viewport->settings.zoom_acceleration_rate + 10) * (viewport->settings.zoom_max_speed - viewport->zoom_speed);
    
    else viewport->zoom_acceleration = viewport->settings.zoom_deceleration_rate * (0 - viewport->zoom_speed);
    
    viewport->zoom_direction = -1;

    if (viewport->offset_angle < viewport->settings.target_offset_aim) 
        viewport->offset_acceleration = viewport->settings.offset_acceleration_rate * (viewport->settings.offset_max_speed  - viewport->offset_speed);
   
    else viewport->offset_acceleration = viewport->settings.offset_deceleration_rate * (0 - viewport->offset_speed);

    viewport->offset_direction = 1;

    viewport->rotational_acceleration[0] = viewport->settings.rotational_acceleration_rate * ((viewport->rotational_target_speed[0] / 2) - viewport->rotational_speed[0]);
    viewport->rotational_acceleration[1] = viewport->settings.rotational_acceleration_rate * ((viewport->rotational_target_speed[1] / 2) - viewport->rotational_speed[1]);
}


void set_third_person_shooter_looking_viewport(Viewport *viewport){}


#endif
