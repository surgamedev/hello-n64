#ifndef ENTITY_H
#define ENTITY_H

/* ENTITY.H
here are all the structures and functions prototypes that involve the setting up of an entity */


// structures

typedef enum {

	EMPTY,
    STAND_IDLE,
    WALKING,
    RUNNING,
	ROLL,
	JUMP,

} EntityState;

typedef enum {

	LEFT,
    RIGHT,

} Foot;

typedef struct {

	float idle_acceleration_rate;
	float walk_acceleration_rate;
	float run_acceleration_rate;
	float roll_acceleration_rate;
	float roll_acceleration_grip_rate;
	float jump_acceleration_rate;
	float aerial_control_rate;

	float walk_target_speed;
	float run_target_speed;
	float idle_to_roll_target_speed;
	float walk_to_roll_target_speed;
	float run_to_roll_target_speed;
	float jump_target_speed;
	
	u32 idle_to_roll_change_grip_tick;
	u32 walk_to_roll_change_grip_tick;
	u32 run_to_roll_change_grip_tick;
	u32 walk_grounded_foot_change_tick;
	u32 run_grounded_foot_change_tick;
	float jump_timer_max;

}EntitySettings;


typedef struct {

	float stick_total;
	float stick_x;
	float stick_y;
	float time_held;
	int hold;
	int released;
	int invalid_input;

}Entityinput;

typedef struct {

	float point[3];
	float normal[3];

}EntityCollision; 


typedef struct {

	Mtx	position_mtx;
	Mtx	rotation_mtx[3];
	Mtx scale_mtx;

	EntityState previous_state;
	EntityState state;

	Foot grounded_foot;
	int grounded;
	
	float scale;
	float previous_position[3];
	float position[3];
	
	float target_yaw;
	float yaw;
    
	float acceleration[3];
	float target_speed[3];
	float speed[3];
	float directional_speed;

    float framerate;
	s64ModelHelper model;
	EntitySettings settings;
	Entityinput input;
	EntityCollision collision;

	Mtx model_mtx[];

} Entity;


// functions prototypes

//void init_entity(Entity *entity, int idle, Mtx *entityMtx, void (*animcallback)(u16));
void set_entity_position(Entity *entity, TimeData time_data);



/* init_entity
this is a not working pototype function that i left behind because its driving me crazy

void init_entity(Entity *entity, int idle, Mtx *entityMtx, void (*animcallback)(u16))
{
    sausage64_initmodel(&entity->model, entity->model.mdldata, entityMtx);
    sausage64_set_anim(&entity->model, idle); 
    sausage64_set_animcallback(&entity->model, animcallback);
}
*/


/* set_entity_position
calculates the entity position given the speed and the available frame duration*/

void set_entity_position(Entity *entity, TimeData time_data)
{	
	
	entity->previous_position[0] = entity->position[0];
	entity->previous_position[1] = entity->position[1];
	entity->previous_position[2] = entity->position[2];
	
    entity->speed[0] += (entity->acceleration[0] * time_data.frame_duration);
    entity->speed[1] += (entity->acceleration[1] * time_data.frame_duration);
    entity->speed[2] += (entity->acceleration[2] * time_data.frame_duration);

    if (entity->speed[0] != 0 || entity->speed[1] != 0) {
		
		entity->yaw = deg(atan2(entity->speed[0], -entity->speed[1]));
		entity->directional_speed = calculate_diagonal(entity->speed[0], entity->speed[1]);
	}

    entity->position[0] += entity->speed[0] * time_data.frame_duration;
    entity->position[1] += entity->speed[1] * time_data.frame_duration;
    entity->position[2] += entity->speed[2] * time_data.frame_duration;

}


#endif
