#ifndef ENTITY_H
#define ENTITY_H

/* ENTITY.H
here are all the structures and functions prototypes that involve the setting up of an entity */


// structures

typedef struct {

	Mtx	position_mtx;
	Mtx	rotation_mtx[3];
	Mtx scale_mtx;

    float scale;
	float position[3];
	float pitch;

	float target_yaw;
	float yaw;
    
	float acceleration[3];
	float target_speed[3];
	float speed[3];

	s64ModelHelper model;

    float framerate;

	float input_amount;

} Entity;


// functions prototypes

void init_entity(Entity *entity, int idle, Mtx *entityMtx, void (*animcallback)(u16));
void set_entity_position(Entity *entity, TimeData time_data);



/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/



/* init_entity
this is a not working pototype function that i left behind because its driving me crazy*/

void init_entity(Entity *entity, int idle, Mtx *entityMtx, void (*animcallback)(u16))
{
    sausage64_initmodel(&entity->model, entity->model.mdldata, entityMtx);
    sausage64_set_anim(&entity->model, idle); 
    sausage64_set_animcallback(&entity->model, animcallback);
}


/* set_entity_position
calculates the entity position given the speed and the available frame duration*/

void set_entity_position(Entity *entity, TimeData time_data)
{
    entity->speed[0] += (entity->acceleration[0] * time_data.frame_duration);
    entity->speed[1] += (entity->acceleration[1] * time_data.frame_duration);
    entity->speed[2] += (entity->acceleration[2] * time_data.frame_duration);

    entity->position[0] += entity->speed[0] * time_data.frame_duration;
    entity->position[1] += entity->speed[1] * time_data.frame_duration;
    entity->position[2] += entity->speed[2] * time_data.frame_duration;
}


#endif
