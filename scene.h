#ifndef SCENE_H
#define SCENE_H


/* SCENE.H
here are all the structures and functions prototypes that involve the setting up of an entity */

// macros

#define USB_BUFFER_SIZE 256

#define GRAVITY 1000


// structures

/*

typedef struct {

	Mtx	position_mtx;
	Mtx	rotation_mtx[3];
	Mtx scale_mtx;

	float scale[3];
	float position[3];

	float pitch;
	float yaw;
    float roll;

	Gfx *model;

} Scenery;
*/


typedef struct {

	Mtx	position_mtx;
	Mtx	rotation_mtx[3];
	Mtx scale_mtx;

	float scale[3];
	float scale_speed;

	float position[3];
	float acceleration[3];
	float speed[3];

	float rotation[3];
	float rotational_speed[3];
	float rotational_acceleration[3];

	Gfx *model;

} Scenery;


// function prototypes

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/



#endif
