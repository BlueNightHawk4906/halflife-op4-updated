//========= Copyright © 1996-2002, Valve LLC, All rights reserved. ============
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================

// Triangle rendering, if any

#include "hud.h"
#include "cl_util.h"

// Triangle rendering apis are in gEngfuncs.pTriAPI

#include "const.h"
#include "entity_state.h"
#include "cl_entity.h"
#include "triangleapi.h"
#include "Exports.h"

#include "particleman.h"
#include "tri.h"
extern IParticleMan *g_pParticleMan;

//RENDERERS START
#include "bsprenderer.h"
#include "propmanager.h"
#include "particle_engine.h"
#include "watershader.h"
#include "mirrormanager.h"

#include "studio.h"
#include "StudioModelRenderer.h"
#include "GameStudioModelRenderer.h"

extern CGameStudioModelRenderer g_StudioRenderer;
//RENDERERS END

/*
=================
HUD_DrawNormalTriangles

Non-transparent triangles-- add them here
=================
*/
void DLLEXPORT HUD_DrawNormalTriangles()
{
//	RecClDrawNormalTriangles();

//	if (gHUD.m_flTime > 1 && g_StudioRenderer.legs.index == 999)
	//	g_StudioRenderer.StudioDrawCustomEntity(&g_StudioRenderer.legs);

	//RENDERERS START
	//2012-02-25
	R_DrawNormalTriangles();
	//RENDERERS END

	gHUD.m_Spectator.DrawOverview();
}

#if defined( _TFC )
void RunEventList();
#endif

/*
=================
HUD_DrawTransparentTriangles

Render any triangles with transparent rendermode needs here
=================
*/
void DLLEXPORT HUD_DrawTransparentTriangles()
{
//	RecClDrawTransparentTriangles();

#if defined( _TFC )
	RunEventList();
#endif

	//RENDERERS START
	//2012-02-25
	R_DrawTransparentTriangles();
	//RENDERERS END

	if ( g_pParticleMan )
		 g_pParticleMan->Update();
}

/*
=================
HUD_DrawOrthoTriangles
Orthogonal Triangles -- (relative to resolution,
smackdab on the screen) add them here
=================
*/
void HUD_DrawOrthoTriangles(void)
{
	static int reset = 0;
	static float flConcussionEffect = 0.0f;

	if (gHUD.m_iConcussionEffect > 0) {

		if (reset == 0)
		{
			flConcussionEffect = gHUD.m_iConcussionEffect;
			reset = 1;
		}

		gHUD.m_iConcussionEffect -= gHUD.m_flTimeDelta*(flConcussionEffect/5);
		if (gHUD.m_iConcussionEffect < 0)
			gHUD.m_iConcussionEffect = 0;

		if (gHUD.m_iConcussionEffect == 0 && reset)
			reset = 0;
	}
}