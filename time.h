#ifndef TIME_H
#define TIME_H

/* TIME.H
here are all the structures and functions prototypes that involve the calculations for the timing */


// structures

typedef struct{

	OSTime currrent_frame;
	OSTime last_frame;
	float frame_time;
	f32 frame_rate;

}TimeData;


// functions prototypes

float get_time();
float cycles_to_sec(OSTime cycles);
void time_management(TimeData *time);



/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/



/* get_time
returns time in seconds */

float get_time()
{
    float time = (s32)OS_CYCLES_TO_USEC(osGetTime()) / 1000000.0f;
    return time;
}


/* cycles_to_sec
converts cycles to seconds */

float cycles_to_sec(OSTime cycles)
{
    float time = (s32)OS_CYCLES_TO_USEC(cycles) / 1000000.0f;
    return time;
}


/* ime_management
calculates frame_rate and frame_time variable */

void time_management(TimeData *time)
{
    time->currrent_frame = osGetTime();

    time->frame_time = cycles_to_sec(time->currrent_frame - time->last_frame);

    time->frame_rate = 1 / time->frame_time;

    time->last_frame = time->currrent_frame;
}


#endif