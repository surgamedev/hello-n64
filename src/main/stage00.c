/*
   stage00.c

   Copyright (C) 1997-1999, NINTENDO Co,Ltd.
*/

#include <assert.h>
#include <nusys.h>
#include "main.h"
#include "graphic.h"
#include "game/game.h"

/* The initialization of stage 0 */
void initStage00(void)
{
}

/* Make the display list and activate the task */
void makeDL00(void)
{
  Camera *camerap;

  /* Specify the display list buffer */
  camerap = &gfx_camera[gfx_gtask_no];
  glistp = &gfx_glist[gfx_gtask_no][0];

  initGfx();
  setupCamera(camerap);

  renderGame();

  gDPFullSync(glistp++);
  gSPEndDisplayList(glistp++);

  assert((glistp - gfx_glist[gfx_gtask_no]) < GFX_GLIST_LEN);

  /* Activate the task and
     switch display buffers */
  nuGfxTaskStart(&gfx_glist[gfx_gtask_no][0],
                 (s32)(glistp - gfx_glist[gfx_gtask_no]) * sizeof(Gfx),
                 NU_GFX_UCODE_F3DEX, NU_SC_NOSWAPBUFFER);

  /* Display characters on the frame buffer */
  nuDebConDisp(NU_SC_SWAPBUFFER);

  /* Switch display list buffers */
  gfx_gtask_no ^= 1;
}

/* The game progressing process for stage 0 */
void updateGame00(void)
{
  updateGame();
}