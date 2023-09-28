
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
 * File:	onetri.h
 * Create Date:	Mon Apr 17 11:45:47 PDT 1995
 *
 */

#define	STATIC_SEGMENT		1
#define	CFB_SEGMENT		2

/* this stack size is in bytes, and is a lot larger
 * than this program needs.
 */
#define	STACKSIZE	0x2000
/*
 * ifdef needed because this file is included by "spec"
 */
#ifdef _LANGUAGE_C
/*
 * Layout of camera data.
 *
 * This structure holds the things which change per frame. It is advantageous
 * to keep camera data together so that we may selectively write back dirty
 * data cache lines to DRAM prior to processing by the RCP.
 *
 */

/* these are the static display lists */
/* RSP task data that is modified by the RSP and read the the CPU */

extern u64 dram_stack[];	/* used for matrix stack */
extern u64 rdp_output[];	/* RSP writes back RDP data */
#define RDP_OUTPUT_LEN (4096*16)

#endif	/* _LANGUAGE_C */
