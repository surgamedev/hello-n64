#include "renderer.h"

Camera camera;

void clear_framebuffer(Gfx **glist)
{
	gDPSetCycleType((*glist)++, G_CYC_FILL);
	gDPSetColorImage((*glist)++, G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WD, rsp_cfb);
	gDPSetFillColor((*glist)++, GPACK_RGBA5551(64, 64, 255, 1) << 16 | GPACK_RGBA5551(64, 64, 255, 1));
	gDPFillRectangle((*glist)++, 0, 0, SCREEN_WD, SCREEN_HT);
	gDPPipeSync((*glist)++);
}

void setup_world(Gfx **glist)
{
	guOrtho(&camera.projection,
			-(float)SCREEN_WD / 2.0F, (float)SCREEN_WD / 2.0F,
			-(float)SCREEN_HT / 2.0F, (float)SCREEN_HT / 2.0F,
			0.1F, 100.0F, 1.0F);
	gSPMatrix((*glist)++, OS_K0_TO_PHYSICAL(&(camera.projection)),
			  G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
	guMtxIdent(&camera.modelview);
	// guMtxIdent(&camera.world.rotation);
	// guMtxIdent(&camera.world.scale);
	// gSPMatrix((*glist)++, OS_K0_TO_PHYSICAL(&camera.world.scale),
	// 	G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
	// gSPMatrix((*glist)++, OS_K0_TO_PHYSICAL(&camera.world.rotation),
	// 	G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);
	gSPMatrix((*glist)++, OS_K0_TO_PHYSICAL(&camera.modelview),
			  G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
}

Gfx rdpinit_dl[] = {
	gsDPSetCycleType(G_CYC_1CYCLE),
	gsDPPipelineMode(G_PM_1PRIMITIVE),
	gsDPSetScissor(G_SC_NON_INTERLACE, 0, 0, SCREEN_WD, SCREEN_HT),
	gsDPSetTextureLOD(G_TL_TILE),
	gsDPSetTextureLUT(G_TT_NONE),
	gsDPSetTextureDetail(G_TD_CLAMP),
	gsDPSetTexturePersp(G_TP_PERSP),
	gsDPSetTextureFilter(G_TF_BILERP),
	gsDPSetTextureConvert(G_TC_FILT),
	gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
	gsDPSetCombineKey(G_CK_NONE),
	gsDPSetAlphaCompare(G_AC_NONE),
	gsDPSetRenderMode(G_RM_OPA_SURF, G_RM_OPA_SURF2),
	gsDPSetColorDither(G_CD_DISABLE),
	gsDPPipeSync(),
	gsSPEndDisplayList(),
};

Gfx rspinit_dl[] = {
	gsSPViewport(&vp),
	gsSPClearGeometryMode(0xFFFFFFFF),
	gsSPTexture(0, 0, 0, 0, G_OFF),
	gsSPSetGeometryMode(G_SHADE | G_SHADING_SMOOTH),
	gsSPEndDisplayList(),
};
