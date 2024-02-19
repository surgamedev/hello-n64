#ifndef VIEWPORT_H
#define VIEWPORT_H

/* VIEWPORT.H
here are all the structures and functions prototypes that involve the setting up of the viewport */


// structures

typedef enum {
	INTRO,
	MENU,
	PAUSE,
    THIRD_PERSON_SHOOTER,
	THIRD_PERSON_SHOOTER_LOOKING,
	THIRD_PERSON_SHOOTER_AIMING,

} ViewportState;

typedef struct {

	float rotational_acceleration_rate;
	float rotational_max_speed[2];

	float zoom_acceleration_rate;
	float zoom_deceleration_rate;
	float zoom_max_speed;

	float target_zoom;
	float target_zoom_aim;

	float offset_acceleration_rate;
	float offset_deceleration_rate;
	float offset_max_speed;

	float target_offset;
	float target_offset_aim;
	
	float max_pitch;

} ViewportSettings;


typedef struct {
	
	Mtx modeling;

	u16 normal;
	Mtx projection;
	Mtx position_mtx;

	float distance_from_entity;
	float horizontal_distance_from_entity;
	float vertical_distance_from_entity;

	float target_distance;
	float horizontal_target_distance;
	float vertical_target_distance;

	float angle_around_entity;
	float offset_angle;

	float offset_acceleration;
	float offset_speed;
	int offset_direction;

	float rotational_acceleration [3];
	float rotational_speed[3];
	float rotational_target_speed[3];

	float zoom_acceleration;
	float zoom_speed;
	int zoom_direction;

	float position[3];
	float target[3];
	float pitch;
	float yaw;
	float roll;

	float height;

	ViewportSettings settings;
	
} Viewport;

typedef struct{

    Light amb;
    Light dir;
	float angle[3];
	
} LightData;


// functions prototypes

void set_viewport_position(Viewport *viewport, Entity entity, TimeData timedata);



/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/



/*set_viewport_position
calculates the viewport position given the input controlled variables*/

void set_viewport_position(Viewport *viewport, Entity entity, TimeData timedata)
{
	viewport->rotational_speed[0] += viewport->rotational_acceleration[0] * timedata.frame_time;
    viewport->rotational_speed[1] += viewport->rotational_acceleration[1] * timedata.frame_time;
	viewport->zoom_speed += viewport->zoom_acceleration * timedata.frame_time;
	viewport->offset_speed += viewport->offset_acceleration * timedata.frame_time;

	if (fabs(viewport->rotational_speed[0]) < 0.1f && fabs(viewport->rotational_speed[1]) < 0.1f && fabs(viewport->zoom_speed) < 0.1f && fabs(viewport->offset_speed) < 0.1f){

		viewport->rotational_speed[0] = 0;
		viewport->rotational_speed[1] = 0;
		viewport->zoom_speed = 0;
		viewport->offset_speed = 0;

	}

	viewport->angle_around_entity += (viewport->rotational_speed[0] * timedata.frame_time);
    viewport->pitch += (viewport->rotational_speed[1] * timedata.frame_time);
	viewport->distance_from_entity += (viewport->zoom_direction * viewport->zoom_speed * timedata.frame_time);
	viewport->offset_angle += (viewport->offset_direction * viewport->offset_speed * timedata.frame_time);

	if (viewport->angle_around_entity > 360) viewport->angle_around_entity -= 360;
    if (viewport->angle_around_entity < 0) viewport->angle_around_entity  += 360;

    if (viewport->pitch > viewport->settings.max_pitch) viewport->pitch = viewport->settings.max_pitch;
    if (viewport->pitch < -viewport->settings.max_pitch) viewport->pitch = -viewport->settings.max_pitch;

    viewport->horizontal_distance_from_entity = viewport->distance_from_entity * cosf(rad(viewport->pitch));
	viewport->vertical_distance_from_entity = viewport->distance_from_entity * sinf(rad(viewport->pitch));

	viewport-> horizontal_target_distance = viewport->target_distance * cosf(rad(viewport->pitch));
	viewport->vertical_target_distance = viewport->target_distance * sinf(rad(viewport->pitch + 180));

    viewport->position[0] = entity.position[0] - (viewport->horizontal_distance_from_entity * sinf(rad(viewport->angle_around_entity - viewport->offset_angle)));
    viewport->position[1] = entity.position[1] - (viewport->horizontal_distance_from_entity * cosf(rad(viewport->angle_around_entity - viewport->offset_angle)));
    viewport->position[2] = entity.position[2] + viewport->height + viewport->vertical_distance_from_entity;
	
    /* this makes the camera collide with an horizontal plane at height 0 simulating the floor,
    will be modyfied when camera collision happens */
	while (viewport->position[2] < entity.grounding_height + 5)  {

		viewport->distance_from_entity--; 
		viewport->horizontal_distance_from_entity = viewport->distance_from_entity * cosf(rad(viewport->pitch));
		viewport->vertical_distance_from_entity = viewport->distance_from_entity * sinf(rad(viewport->pitch));

		viewport->position[0] = entity.position[0] - viewport->horizontal_distance_from_entity * sinf(rad(viewport->angle_around_entity - viewport->offset_angle));
		viewport->position[1] = entity.position[1] - viewport->horizontal_distance_from_entity * cosf(rad(viewport->angle_around_entity - viewport->offset_angle));
		viewport->position[2] = entity.position[2] + viewport->height + viewport->vertical_distance_from_entity;
	}
	
	viewport->target[0] = entity.position[0] - viewport-> horizontal_target_distance * sinf(rad(viewport->angle_around_entity + 180));
	viewport->target[1] = entity.position[1] - viewport-> horizontal_target_distance * cosf(rad(viewport->angle_around_entity + 180));
	viewport->target[2] = entity.position[2] + viewport->height + viewport->vertical_target_distance;
}


#endif
