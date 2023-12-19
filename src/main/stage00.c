/*
   stage00.c 

   Copyright (C) 1997-1999, NINTENDO Co,Ltd.
*/

#include <assert.h>
#include <nusys.h>
#include "main.h"
#include "graphic.h"
#include "entity.h"

void rotate_entity(Entity *entity)
{
	static Vector3f rot = {.x = 0.0f, .y = 0.0f, .z = 0.1f};
	entity->rotation = Vector3f_add_vector(entity->rotation, rot);
}

void move_entity(Entity *entity)
{
	entity->position.x = (entity->position.x > SCREEN_WD / 2) ? -SCREEN_WD / 2 : entity->position.x + 1;
}

static Entity entities[2] = {
	{.position = {10.0f, 0.0f, -5.0f},
	 .rotation = {0.0f, 0.0f, -5.0f},
	 .scale = 1.0f,
	 .update = &move_entity},
	{.position = {0.0f, 0.0f, -5.0f},
	 .rotation = {0.0f, 0.0f, 10.0f},
	 .scale = 1.0f,
	 .update = &rotate_entity}};

/* The initialization of stage 0 */
void initStage00(void)
{
}

/* Make the display list and activate the task */
void makeDL00(void)
{
  Dynamic* dynamicp;
  char conbuf[20]; 

  /* Specify the display list buffer */
  dynamicp = &gfx_dynamic[gfx_gtask_no];
  glistp = &gfx_glist[gfx_gtask_no][0];

  /* Initialize RCP */
  gfxRCPInit();

  /* Clear the frame and Z-buffer */
  gfxClearCfb();

  /* projection,modeling matrix set */
  guOrtho(&dynamicp->projection,
	  -(float)SCREEN_WD/2.0F, (float)SCREEN_WD/2.0F,
	  -(float)SCREEN_HT/2.0F, (float)SCREEN_HT/2.0F,
	  1.0F, 10.0F, 1.0F);
  guRotate(&dynamicp->modeling, entities[0].rotation.z, 0.0F, 0.0F, 1.0F);

  gSPMatrix(glistp++,OS_K0_TO_PHYSICAL(&(dynamicp->projection)),
		G_MTX_PROJECTION|G_MTX_LOAD|G_MTX_NOPUSH);
  for (int i = 0; i < 2; i++)
  {
    if (entities[i].update != NULL)
    {
      entities[i].update(&entities[i]);
    }
    draw_entity(&entities[i], &glistp);
  }

  gDPFullSync(glistp++);
  gSPEndDisplayList(glistp++);

  assert((glistp - gfx_glist[gfx_gtask_no]) < GFX_GLIST_LEN);

  /* Activate the task and 
     switch display buffers */
  nuGfxTaskStart(&gfx_glist[gfx_gtask_no][0],
		 (s32)(glistp - gfx_glist[gfx_gtask_no]) * sizeof (Gfx),
		 NU_GFX_UCODE_F3DEX , NU_SC_NOSWAPBUFFER);
    
  /* Display characters on the frame buffer */
  nuDebConDisp(NU_SC_SWAPBUFFER);

  /* Switch display list buffers */
  gfx_gtask_no ^= 1;
}


/* The game progressing process for stage 0 */
void updateGame00(void)
{  

}