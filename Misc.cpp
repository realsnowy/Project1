#include "Misc.h"
#include "Util.h"
#include "Client.h"

CMisc gMisc;

void CMisc::Run(CBaseEntity* pLocal, CUserCmd* pCommand)
{


	if (!(pLocal->GetFlags() & FL_ONGROUND) && pCommand->buttons & IN_JUMP)
	{
		//Autostrafe	
		if (gCvars.misc_autostrafe)
			if (pCommand->mousedx > 1 || pCommand->mousedx < -1)  //> 1 < -1 so we have some wiggle room
				pCommand->sidemove = pCommand->mousedx > 1 ? 450.f : -450.f;

		//Bunnyhop
		if (gCvars.misc_bunnyhop)
			pCommand->buttons &= ~IN_JUMP;
	}

	Vector m_vOldViewAngle = pCommand->viewangles;
	float m_fOldSideMove = pCommand->sidemove;
	float m_fOldForwardMove = pCommand->forwardmove;

	if (gCvars.misc_angles)
	{
		if (pCommand->buttons & IN_ATTACK)
			return;

		if (gCvars.misc_aax > 0) //Pitch
		{
			if (gCvars.misc_aax == 1)//Fake Up
				pCommand->viewangles.x = -271.0;
			if (gCvars.misc_aax == 2)//Up
				pCommand->viewangles.x = -89.0f;
			if (gCvars.misc_aax == 3)//Fake Down
				pCommand->viewangles.x = 271.0;
			if (gCvars.misc_aax == 4)//Down
				pCommand->viewangles.x = 89.0f;
		}

		if (gCvars.misc_aay > 0) //Yaw
		{
			if (gCvars.misc_aay == 1)//Right
				pCommand->viewangles.y -= 90.0f;

			if (gCvars.misc_aay == 2)//Left
				pCommand->viewangles.y += 90.0f;

			if (gCvars.misc_aay == 3)//Back
				pCommand->viewangles.y -= 180;

			if (gCvars.misc_aay == 4)//Emotion
				pCommand->viewangles.y = (float)-89.99985719438652715;

			if (gCvars.misc_aay == 5)//Random
				pCommand->viewangles.y = Util->RandFloatRange(-180.0f, 180.0f);

			if (gCvars.misc_aay == 6)//Spin
				pCommand->viewangles.y = pCommand->tick_count * 11 % 360;

			if (gCvars.misc_aay == 7) //Jitter
				pCommand->viewangles.y = pCommand->tick_count * 90 % 360;

			if (gCvars.misc_aay == 8) //Fake Sideways
				pCommand->viewangles.y = pCommand->tick_count * 180 % 360;
		}
	}



	ConVar* viewmodel_fov = gInts.cvar->FindVar("viewmodel_fov");
	if (gCvars.misc_viewmodelfovoverride)
		viewmodel_fov->SetValue(gCvars.misc_viewmodelfov_value);

	/*if (gCvars.misc_norecoil)
	{
		Vector punchAngle = *(Vector*)(pLocal + gNetVars.get_offset("DT_BasePlayer", "localdata", "m_vecPunchAngle"));
		pCommand->viewangles.x -= (punchAngle.x *2.0f);
		pCommand->viewangles.y -= (punchAngle.y *2.0f);
	}*/


	if (gCvars.misc_serverlag && Util->IsKeyPressed2(gCvars.misc_serverlag_key))
		for (int i = 0; i < (int)gCvars.misc_serverlag_value; i++)
			gInts.Engine->ServerCmd("use", false);


	if (gCvars.misc_speedhack && (pCommand->buttons & IN_DUCK))
	{
		if (pCommand->buttons & IN_ATTACK)
			return;

		Vector vLocalAngles = pCommand->viewangles;
		float speed = pCommand->forwardmove;
		if (fabs(speed) > 0.0f) {
			pCommand->forwardmove = -speed;
			pCommand->sidemove = 0.0f;
			pCommand->viewangles.y = vLocalAngles.y;
			pCommand->viewangles.y -= 180.0f;
			if (pCommand->viewangles.y < -180.0f) pCommand->viewangles.y += 360.0f;
			pCommand->viewangles.z = 90.0f;
		}
	}

	Util->FixMove(pCommand, m_vOldViewAngle, m_fOldForwardMove, m_fOldSideMove);
}
