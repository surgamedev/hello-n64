#pragma once
#ifdef _LANGUAGE_C
#include <ultra64.h>

#define	SCREEN_HT	240
#define	SCREEN_WD	320
#define	GLIST_LEN	2048

/* RSP address for the color frame buffer */
extern u16	rsp_cfb[];


/* CPU addresses for the color frame buffer */
extern u16	cfb[][SCREEN_WD*SCREEN_HT];

typedef struct {
	Mtx	projection;
	Mtx modelview;
	Gfx	glist[GLIST_LEN];
} Camera;

static Vp vp = {
	SCREEN_WD*2, SCREEN_HT*2, G_MAXZ/2, 0,	/* scale */
	SCREEN_WD*2, SCREEN_HT*2, G_MAXZ/2, 0,	/* translate */
};

extern Camera camera;

void clear_framebuffer(Gfx** glist);
void setup_world(Gfx** glist);

/*
 * Remember, viewport structures have 2 bits of fraction in them.
 */
/* initialize the RSP state: */
extern Gfx rspinit_dl[];

/* initialize the RDP state: */
extern Gfx rdpinit_dl[];

#endif /* _LANGUAGE_C */