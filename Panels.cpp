#include "SDK.h"
#include "Panels.h"
#include "CDrawManager.h"
#include "Util.h"
#include "ESP.h"

CScreenSize gScreenSize;

bool Key(INT vKey)
{
	if (GetAsyncKeyState(vKey) & 1)
		return true;

	return false;
}

//===================================================================================
void __fastcall Hooked_PaintTraverse( PVOID pPanels, int edx, unsigned int vguiPanel, bool forceRepaint, bool allowForce )
{
	try
	{
		CBaseEntity* pLocal = gInts.EntList->GetClientEntity(me);
		auto crosshair = gInts.cvar->FindVar("crosshair");
		if (!strcmp("HudScope", gInts.Panels->GetName(vguiPanel)) && gCvars.misc_noscope)
		{
			if (gCvars.misc_noscope_disablecrosshair)
			{
				if (pLocal->GetCond() & tf_cond::TFCond_Zoomed)
				{
					crosshair->SetValue(0);
				}
				else
				{
					crosshair->SetValue(1);
				}

			}

			return;
		}
		VMTManager& hook = VMTManager::GetHook(pPanels); 
		hook.GetMethod<void(__thiscall*)(PVOID, unsigned int, bool, bool)>(gOffsets.iPaintTraverseOffset)(pPanels, vguiPanel, forceRepaint, allowForce); //Call the original.

		static unsigned int vguiFocusOverlayPanel;

		if (vguiFocusOverlayPanel == NULL)
		{											//FocusOverlayPanel
			const char* szName = gInts.Panels->GetName(vguiPanel);
			if( szName[0] == 'F' && szName[5] == 'O' &&  szName[12] == 'P' )
			{
				vguiFocusOverlayPanel = vguiPanel;
				Intro();
			}
		}
		
		if (vguiFocusOverlayPanel == vguiPanel)
		{
			int iWidth, iHeight; //Resolution fix, so this can work in Fullscreen
			gInts.Engine->GetScreenSize(iWidth, iHeight);
			if (gScreenSize.iScreenWidth != iWidth || gScreenSize.iScreenHeight != iHeight)
				gInts.Engine->GetScreenSize(gScreenSize.iScreenWidth, gScreenSize.iScreenHeight);

			if (Key(VK_F8))
				gCvars.Load();

		   /*if (gInts.Engine->IsInGame() && gInts.Engine->IsConnected())
			{
				static INetChannel* pNetChannel = (INetChannel*)gInts.Engine->GetNetChannelInfo();

				if (!pNetChannel)
					return;

				gDrawManager.DrawString(5, 5, Color(250, 173, 200, 255), "Server IP: %i", pNetChannel->GetAddress());
			}*/ //This draws the current server IP but it doesn't seperate numbers so I just commented it out

			if (!gInts.Engine->IsInGame() || !gInts.Engine->IsConnected())
			{
				if (!gCvars.iMenu_Color_Scheme)
					gDrawManager.DrawString(5, 5, Color::Blue(), "ProjectZ || Menu Is Only Accessible In-Game", gInts.Engine->GetAppId());
				else if (gCvars.iMenu_Color_Scheme == 1)
					gDrawManager.DrawString(5, 5, Color::Violet(), "ProjectZ || Menu Is Only Accessible In-Game", gInts.Engine->GetAppId());
			}

			if( gInts.Engine->IsDrawingLoadingImage() || !gInts.Engine->IsInGame( ) || !gInts.Engine->IsConnected() || gInts.Engine->Con_IsVisible( ) )
				return; //No need to draw the rest.

			

			CBaseEntity* pLocal = gInts.EntList->GetClientEntity(me); 

			if (!pLocal)
				return;

			if (Key(VK_INSERT)) //insert
			{
				gCheatMenu.bMenuActive = !gCheatMenu.bMenuActive;
				gCvars.Save();
			}

			if (gCheatMenu.bMenuActive) //We do keyboard buttons for the menu with VKs to allow the ability to hold down a key for value changing
			{
				if (Key(VK_UP)) // Up
				{

					if (gCheatMenu.iMenuIndex > 0) gCheatMenu.iMenuIndex--;
					else gCheatMenu.iMenuIndex = gCheatMenu.iMenuItems - 1;
					return;

				}
				else if (Key(VK_DOWN)) // Down
				{
					if (gCheatMenu.iMenuIndex < gCheatMenu.iMenuItems - 1) gCheatMenu.iMenuIndex++;
					else gCheatMenu.iMenuIndex = 0;
					return;

				}
				else if (Key(VK_LEFT)) // Left
				{
					if (gCheatMenu.pMenu[gCheatMenu.iMenuIndex].value)
					{
						gCheatMenu.pMenu[gCheatMenu.iMenuIndex].value[0] -= gCheatMenu.pMenu[gCheatMenu.iMenuIndex].flStep;
						if (gCheatMenu.pMenu[gCheatMenu.iMenuIndex].value[0] < gCheatMenu.pMenu[gCheatMenu.iMenuIndex].flMin)
							gCheatMenu.pMenu[gCheatMenu.iMenuIndex].value[0] = gCheatMenu.pMenu[gCheatMenu.iMenuIndex].flMax;
					}
					return;

				}
				else if (Key(VK_RIGHT)) // Right
				{
					if (gCheatMenu.pMenu[gCheatMenu.iMenuIndex].value)
					{
						gCheatMenu.pMenu[gCheatMenu.iMenuIndex].value[0] += gCheatMenu.pMenu[gCheatMenu.iMenuIndex].flStep;
						if (gCheatMenu.pMenu[gCheatMenu.iMenuIndex].value[0] > gCheatMenu.pMenu[gCheatMenu.iMenuIndex].flMax)
							gCheatMenu.pMenu[gCheatMenu.iMenuIndex].value[0] = gCheatMenu.pMenu[gCheatMenu.iMenuIndex].flMin;
					}
					return;

				}
			}

			if (gCheatMenu.bMenuActive)
			{
				gCheatMenu.DrawMenu();
				gCheatMenu.Render();
			}

			gESP.Run(pLocal);

			if (Key(VK_F9))
				gDrawManager.Initialize();

		}
	}
	catch(...)
	{
		Log::Fatal("Failed PaintTraverse");
	}
}
//===================================================================================
void Intro( void )
{
	try
	{
		gDrawManager.Initialize(); //Initalize the drawing class.

		gNetVars.Initialize();
	}
	catch(...)
	{
		Log::Fatal("Failed Intro");
	}
}