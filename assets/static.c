
/**************************************************************************
 *                                                                        *
 *               Copyright (C) 1995, Silicon Graphics, Inc.               *
 *                                                                        *
 *  These coded instructions, statements, and computer programs  contain  *
 *  unpublished  proprietary  information of Silicon Graphics, Inc., and  *
 *  are protected by Federal copyright  law.  They  may not be disclosed  *
 *  to  third  parties  or copied or duplicated in any form, in whole or  *
 *  in part, without the prior written consent of Silicon Graphics, Inc.  *
 *                                                                        *
 *************************************************************************/

/*
 * File:	static.c
 * Create Date:	Tue Apr 11 17:45:53 PDT 1995
 *
 * This file holds display list segments that are 'static' data.
 *
 */

#include <ultra64.h>
#include "demo_stage.h"

/* 
 * This group of vertices, and accompanying display list, demonstrate
 * simple textured triangles.
 *
 * The texture coordinates are texel-space coordinates that
 * are shifted up 6 bits; 5 bits because the texture coordinates
 * are S10.5 format, and 1 more bit so we can use a texture scaling
 * of 0.5, and get exact coordinates.
 *
 * The coordinates larger than the texture resolution, along with the
 * proper mode settings, cause the texture to repeat on itself.
 */
static Vtx tex_vtx[] =  {
        { -64,  64, -5, 0, (  0 << 6), (  0 << 6), 0xff, 0xff, 0xff, 0xff},
        {  64,  64, -5, 0, (127 << 6), (  0 << 6), 0xff, 0xff, 0xff, 0xff},
        {  64, -64, -5, 0, (127 << 6), (127 << 6), 0xff, 0xff, 0xff, 0xff},
        { -64, -64, -5, 0, (  0 << 6), (127 << 6), 0xff, 0xff, 0xff, 0xff},
};

/* a 32x32 RGBA16 texture: */
#include "brick.h"

/*Gfx textri_dl[] = {
    gsSPMatrix(OS_K0_TO_PHYSICAL(&(dynamic.projection)),
	       G_MTX_PROJECTION|G_MTX_LOAD|G_MTX_NOPUSH),
    gsSPMatrix(OS_K0_TO_PHYSICAL(&(dynamic.modeling)),
	       G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH),
    gsDPPipeSync(),
    gsDPSetCycleType(G_CYC_1CYCLE),
    gsDPSetRenderMode(G_RM_AA_OPA_SURF, G_RM_AA_OPA_SURF2),
    gsSPClearGeometryMode(G_SHADE | G_SHADING_SMOOTH),
    /*
     * The texture scaling parameters are .16 format. In order to
     * get an exact texture scale of 1.0, we scale above by 2.0, and
     * scale down here by 0.5
     */
    /*
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetCombineMode(G_CC_DECALRGB, G_CC_DECALRGB),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPLoadTextureBlock(brick, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0,
			 G_TX_WRAP | G_TX_MIRROR, G_TX_WRAP | G_TX_MIRROR,
			 5, 5, G_TX_NOLOD, G_TX_NOLOD),
    gsSPVertex(&(tex_vtx[0]), 4, 0),
    gsSP1Triangle(0, 1, 2, 0),
    gsSP1Triangle(0, 2, 3, 0),
    gsSPTexture(0, 0, 0, 0, G_OFF), /* done; turn texture off */
    /*
    gsSPEndDisplayList(),
};*/

