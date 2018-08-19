#include "CMenu.h"
#include "SDK.h"
#include "CDrawManager.h"
#include "Util.h"

CCheatMenu gCheatMenu;

int ScreenH;
int ScreenW;

char* szKeyNames[] = {
	"None", "Mouse 1", "Mouse 2", "Mouse 3", "Mouse 4", "Mouse 5", "Shift", "Alt", "F",
};

char* szKeyNames2[] = {
	"None", "Mouse 3", "Mouse 4", "Mouse 5", "Shift", "Alt", "F",
};

char* szHealthModes[] = {
	"OFF", "Text", "Bar", "Both",
};

char* szBoneModes[] = {
	"OFF", "White", "Health", "Team",
};

char* szTextPos[] = {
	"Top Right", "Bottom Right",
};

char* szHands[] = {
	"OFF", "None", "Transparent",
};

char* szWeapons[] = {
	"OFF", "None", "Transparent",
};

char* szBox[] = {
	"OFF", "Normal", "Outline", "Corner",
};

char* szChams[] = {
	"OFF", "Normal", "Flat",
};

char* szPitch[] = {
	"None", "FUp", "Up", "FDown", "Down",
};

char* szYaw[] = {
	"None", "Right", "Left", "Back", "Emotion", "Random", "Spin", "Jitter", "FSideways",
};

char* szAimMethod[] = {
	"Plain", "Silent",
};

char* szFont[] = {
	"Tahoma", "Arial", "Comic Sans",
};

char* szColorScheme[] = {
	"Default", "Femboy",
};

int CCheatMenu::AddItem(int nIndex, char szTitle[30], float* value, float flMin, float flMax, float flStep, bool isClassSwitch)
{
	strcpy(pMenu[nIndex].szTitle, szTitle);
	pMenu[nIndex].value = value;
	pMenu[nIndex].flMin = flMin;
	pMenu[nIndex].flMax = flMax;
	pMenu[nIndex].flStep = flStep;
	pMenu[nIndex].isClassSwitch = isClassSwitch;
	return (nIndex + 1);
}

void CCheatMenu::Render(void)
{
	gInts.Engine->GetScreenSize(ScreenW, ScreenH);

	int i = 0;
	if (gInts.Engine->GetAppId() != 4000)
	{
		if (gInts.Engine->GetAppId() != 265630) //Doesn't show Aimbot/Triggerbot if the game is Fistful of Frags
		{
			i = AddItem(i, "Aimbot", &gCvars.aimbot_switch, 0, 1, 1, true);
			if (gCvars.aimbot_switch)
			{
				i = AddItem(i, " - Enabled", &gCvars.aimbot_active, 0, 1, 1, false);
				if (gCvars.aimbot_active)
				{
					if (GAME_HL2 || GAME_HL2_LC || GAME_HL2_EP1 || GAME_HL2_EP2 || GAME_HLS || GAME_SYN)
					{
						i = AddItem(i, "  * FOV", &gCvars.aimbot_fov, 1, 180, 1, false);
						i = AddItem(i, "  * Autoshoot", &gCvars.aimbot_autoshoot, 0, 1, 1, false);
					}
					else
					{
						i = AddItem(i, "  * Hitscan", &gCvars.aimbot_hitscan, 0, 1, 1, false);
						i = AddItem(i, "  * FOV", &gCvars.aimbot_fov, 1, 180, 1, false);
						i = AddItem(i, "  * Smooth", &gCvars.aimbot_smooth, 0, 1, 1, false);
						if (gCvars.aimbot_smooth)
							i = AddItem(i, "   > Amount", &gCvars.aimbot_smooth_amt, 1, 180, 1, false);
						i = AddItem(i, "  * Method", &gCvars.aimbot_mode, 0, 1, 1, false);
						i = AddItem(i, "  * Autoshoot", &gCvars.aimbot_autoshoot, 0, 1, 1, false);
						if (GAME_TF2)
						{
							//i = AddItem(i, "  * Projectile Prediction", &gCvars.aimbot_projectile, 0, 1, 1, false);
							i = AddItem(i, "  * Wait For Charge", &gCvars.aimbot_waitforcharge, 0, 1, 1, false);
							i = AddItem(i, "  * Zoomed Only", &gCvars.aimbot_zoomedonly, 0, 1, 1, false);
						}
						i = AddItem(i, "  * Deathmatch", &gCvars.aimbot_deathmatch, 0, 1, 1, false);
						if (GAME_TF2)
						{
							i = AddItem(i, "  * Resolver", &gCvars.aimbot_resolver, 0, 1, 1, false);
							i = AddItem(i, "  * Ignore Cloaked", &gCvars.aimbot_ignorecloaked, 0, 1, 1, false);
						}
						i = AddItem(i, "  * Ignore HP > 100", &gCvars.aimbot_ignoreabove100, 0, 1, 1, false);
					}

				}
			}

			if (GAME_HL2 || GAME_HL2_LC || GAME_HL2_EP1 || GAME_HL2_EP2 || GAME_HLS || GAME_SYN)
			{
				//planning on adding Triggerbot support soon
			}
			else
			{
				i = AddItem(i, "Triggerbot", &gCvars.triggerbot_switch, 0, 1, 1, true);
				if (gCvars.triggerbot_switch)
				{
					i = AddItem(i, " - Enabled", &gCvars.triggerbot_active, 0, 1, 1, false);
					if (gCvars.triggerbot_active)
					{
						i = AddItem(i, "  * Head Only", &gCvars.triggerbot_headonly, 0, 1, 1, false);
						i = AddItem(i, "  * Deathmatch", &gCvars.aimbot_deathmatch, 0, 1, 1, false);
						if (GAME_TF2)
						{
							i = AddItem(i, "  * Ignore Cloaked", &gCvars.triggerbot_ignorecloaked, 0, 1, 1, false);
						}
					}
				}

				i = AddItem(i, "Player List", &gCvars.playerlist_switch, 0, 1, 1, true);
				for (int p = 1; p <= gInts.Engine->GetMaxClients(); p++)
				{
					if (p == me)
						continue;

					CBaseEntity *pPlayer = GetBaseEntity(p);

					if (pPlayer == NULL)
						continue;

					player_info_t pInfo;
					gInts.Engine->GetPlayerInfo(p, &pInfo);

					char szString[256];
					sprintf(szString, " - %s", pInfo.name);

					if (gCvars.playerlist_switch)
						i = AddItem(i, szString, &gCvars.PlayerMode[pPlayer->GetIndex()], 0, 2, 1, false);
				}
			}
		}
	}

	i = AddItem(i, "ESP", &gCvars.esp_switch, 0, 1, 1, true);
	if (gCvars.esp_switch)
	{
		i = AddItem(i, " - Enabled", &gCvars.esp_active, 0, 1, 1, false);
		if (gCvars.esp_active)
		{
			if (GAME_HL2 || GAME_HL2_LC || GAME_HL2_EP1 || GAME_HL2_EP2 || GAME_HLS || GAME_SYN)
				i = AddItem(i, "  * Name", &gCvars.esp_name, 0, 1, 1, false);
			else
			{
				i = AddItem(i, "  * Position", &gCvars.esp_pos, 0, 1, 1, false);
				i = AddItem(i, "  * Enemies Only", &gCvars.esp_enemyonly, 0, 1, 1, false);
				i = AddItem(i, "  * Box", &gCvars.esp_box, 0, 3, 1, false);
				i = AddItem(i, "  * Name", &gCvars.esp_name, 0, 1, 1, false);
				if (GAME_TF2)
				{
					i = AddItem(i, "  * Class", &gCvars.esp_class, 0, 1, 1, false);
				}
				i = AddItem(i, "  * Health", &gCvars.esp_health, 0, 3, 1, false);
				if (GAME_TF2)
				{
					i = AddItem(i, "  * Glow", &gCvars.esp_glow, 0, 1, 1, false);
					i = AddItem(i, "  * Chams", &gCvars.esp_chams, 0, 2, 1, false);
				}
			}

		}
	}

	if (gInts.Engine->GetAppId() != 4000)
	{
		if (gInts.Engine->GetAppId() != 440)
		{
			i = AddItem(i, "Time Shift", &gCvars.timeshift_switch, 0, 1, 1, true);
			if (gCvars.timeshift_switch)
			{
				i = AddItem(i, " - Enabled", &gCvars.timeshift_enabled, 0, 1, 1, false);
				if (gCvars.timeshift_enabled)
				{
					i = AddItem(i, "  * Value", &gCvars.timeshift_value, 1, 1200, 1, false);
				}
			}
		}
		i = AddItem(i, "Misc", &gCvars.misc_switch, 0, 1, 1, true);
		if (gCvars.misc_switch)
		{

			i = AddItem(i, " - Bunnyhop", &gCvars.misc_bunnyhop, 0, 1, 1, false);
			i = AddItem(i, " - Autostrafe", &gCvars.misc_autostrafe, 0, 1, 1, false);
			if (GAME_TF2)
			{
				i = AddItem(i, " - Hands", &gCvars.misc_hands, 0, 2, 1, false);
				i = AddItem(i, " - No Hats", &gCvars.misc_nohats, 0, 1, 1, false);
				i = AddItem(i, " - Crouch Exploit", &gCvars.misc_speedhack, 0, 1, 1, false);
			}
			i = AddItem(i, " - Server Lagger", &gCvars.misc_serverlag, 0, 1, 1, false);
			if (gCvars.misc_serverlag)
			{
				i = AddItem(i, "  * Value", &gCvars.misc_serverlag_value, 100, 3000, 1, false);
			}
			if (GAME_TF2)
			{
				i = AddItem(i, " - No Scope", &gCvars.misc_noscope, 0, 1, 1, false);
				if (gCvars.misc_noscope)
					i = AddItem(i, "  * Disable Crosshair", &gCvars.misc_noscope_disablecrosshair, 0, 1, 1, false);
			}
			i = AddItem(i, " - No Zoom", &gCvars.misc_nozoom, 0, 1, 1, false);
			i = AddItem(i, " - FOV Override", &gCvars.misc_fovoverride, 0, 1, 1, false);
			if (gCvars.misc_fovoverride)
				i = AddItem(i, "  * Value", &gCvars.misc_fov_value, 75, 200, 1, false);
			i = AddItem(i, " - VM FOV Override", &gCvars.misc_viewmodelfovoverride, 0, 1, 1, false);
			if (gCvars.misc_viewmodelfovoverride)
				i = AddItem(i, "  * Value", &gCvars.misc_viewmodelfov_value, 54, 200, 1, false);
			if (GAME_HL2 || GAME_HL2_LC || GAME_HL2_EP1 || GAME_HL2_EP2 || GAME_HLS || GAME_SYN)
			{
				//nothin yet
			}
			else
			{
				i = AddItem(i, " - Thirdperson", &gCvars.misc_thirdperson, 0, 1, 1, false);
				i = AddItem(i, " - Angles", &gCvars.misc_angles, 0, 1, 1, false);
				if (gCvars.misc_angles)
				{
					i = AddItem(i, "  * Pitch", &gCvars.misc_aax, 0, 4, 1, false);
					i = AddItem(i, "  * Yaw", &gCvars.misc_aay, 0, 8, 1, false);
				}
				i = AddItem(i, " - Fake Lag", &gCvars.misc_fakelag, 0, 1, 1, false);
				if (gCvars.misc_fakelag)
				{
					i = AddItem(i, "  * Value", &gCvars.misc_fakelag_value, 1, 14, 1, false);
					i = AddItem(i, "  * While Attacking", &gCvars.misc_fakelag_onattack, 0, 1, 1, false);
				}
				i = AddItem(i, " - Backtrack", &gCvars.misc_backtracking, 0, 1, 1, false);
				if (gCvars.misc_backtracking)
				{
					i = AddItem(i, "  * Deathmatch", &gCvars.misc_backtracking_deathmatch, 0, 1, 1, false);
				}
			}
		}

		i = AddItem(i, "Hotkeys", &gCvars.hotkeys_switch, 0, 1, 1, true);
		if (gCvars.hotkeys_switch)
		{
			i = AddItem(i, " - Aimbot", &gCvars.aimbot_key, 0, 8, 1, false);
			i = AddItem(i, " - Triggerbot", &gCvars.triggerbot_key, 0, 8, 1, false);
			i = AddItem(i, " - Time Shift", &gCvars.timeshift_key, 0, 6, 1, false);
			i = AddItem(i, " - Server Lagger", &gCvars.misc_serverlag_key, 0, 6, 1, false);
		}
	}
	else
	{
		i = AddItem(i, "Misc", &gCvars.misc_switch, 0, 1, 1, true);
		if (gCvars.misc_switch)
		{
			i = AddItem(i, " - FOV Override", &gCvars.misc_fovoverride, 0, 1, 1, false);
			if (gCvars.misc_fovoverride)
				i = AddItem(i, "  * Value", &gCvars.misc_fov_value, 75, 200, 1, false);
			i = AddItem(i, " - VM FOV Override", &gCvars.misc_viewmodelfovoverride, 0, 1, 1, false);
			if (gCvars.misc_viewmodelfovoverride)
				i = AddItem(i, "  * Value", &gCvars.misc_viewmodelfov_value, 54, 200, 1, false);
			i = AddItem(i, " - Thirdperson", &gCvars.misc_thirdperson, 0, 1, 1, false);
		}
	}

	i = AddItem(i, "Settings", &gCvars.settings_switch, 0, 1, 1, true);
	if (gCvars.settings_switch)
	{
		i = AddItem(i, " - Menu Postion X", &gCvars.iMenu_Pos_X, 0, ScreenW, 25, false);
		i = AddItem(i, " - Menu Postion Y", &gCvars.iMenu_Pos_Y, 0, ScreenH, 25, false);
		i = AddItem(i, " - Color Scheme", &gCvars.iMenu_Color_Scheme, 0, 1, 1, false);
		i = AddItem(i, " - Font", &gCvars.iMenu_Font, 0, 2, 1, false);
	}

	iMenuItems = i;
}

void CCheatMenu::DrawMenu(void)
{
	int x = gCvars.iMenu_Pos_X,
		xx = x + 150,
		y = gCvars.iMenu_Pos_Y,
		w = 225,
		h = 14;

	CBaseEntity *pLocal = GetBaseEntity(me);

	Color clrColor = gDrawManager.GetPlayerColor(pLocal);

	gDrawManager.OutlineRect(x, y - (h + 4), w, iMenuItems * h + 21, clrColor);

	gDrawManager.OutlineRect(x - 1, (y - (h + 4)) - 1, w + 2, (iMenuItems * h + 21) + 2, Color(0, 0, 0, 255));
	gDrawManager.OutlineRect(x + 1, (y - (h + 4)) + 1, w - 2, (iMenuItems * h + 21) - 2, Color(0, 0, 0, 255));

	gDrawManager.DrawString(x + 4, y - 16, clrColor, "ProjectZ || Multi-Source Version");

	for (int i = 0; i < iMenuItems; i++)
	{
		if (i != iMenuIndex)
		{
			if (pMenu[i].isClassSwitch)
			{
				if (!(pMenu[i].value[0]))
				{
					gDrawManager.DrawString(x + 2, y + (h * i), clrColor, "[+] %s", pMenu[i].szTitle);
				}
				else if (pMenu[i].value[0])
				{
					gDrawManager.DrawString(x + 2, y + (h * i), clrColor, "[-] %s", pMenu[i].szTitle);
				}
			}
			else
			{
				gDrawManager.DrawString(x + 4, y + (h * i), Color::White(), pMenu[i].szTitle);

				if (!strcmp(pMenu[i].szTitle, "  * Health"))
				{
					gDrawManager.DrawString(xx, y + (h * i), pMenu[i].value[0] ? Color::White() : Color(105, 105, 105, 255), "%s", szHealthModes[(int)pMenu[i].value[0]]);
				}
				
				else if (!strcmp(pMenu[i].szTitle, "  * Method"))
				{
					gDrawManager.DrawString(xx, y + (h * i), pMenu[i].value[0] ? Color::White() : Color(105, 105, 105, 255), "%s", szAimMethod[(int)pMenu[i].value[0]]);
				}

				else if (!strcmp(pMenu[i].szTitle, "  * Position"))
				{
					gDrawManager.DrawString(xx, y + (h * i), pMenu[i].value[0] ? Color::White() : Color::White(), "%s", szTextPos[(int)pMenu[i].value[0]]);
				}

				else if (!strcmp(pMenu[i].szTitle, " - Color Scheme"))
				{
					gDrawManager.DrawString(xx, y + (h * i), pMenu[i].value[0] ? Color::White() : Color::White(), "%s", szColorScheme[(int)pMenu[i].value[0]]);
				}

				else if (!strcmp(pMenu[i].szTitle, "  * Box"))
				{
					gDrawManager.DrawString(xx, y + (h * i), pMenu[i].value[0] ? Color::White() : Color(105, 105, 105, 255), "%s", szBox[(int)pMenu[i].value[0]]);
				}

				else if (!strcmp(pMenu[i].szTitle, "  * Chams"))
				{
					gDrawManager.DrawString(xx, y + (h * i), pMenu[i].value[0] ? Color::White() : Color(105, 105, 105, 255), "%s", szChams[(int)pMenu[i].value[0]]);
				}

				else if (!strcmp(pMenu[i].szTitle, " - Hands"))
				{
					gDrawManager.DrawString(xx, y + (h * i), pMenu[i].value[0] ? Color::White() : Color(105, 105, 105, 255), "%s", szHands[(int)pMenu[i].value[0]]);
				}

				else if (!strcmp(pMenu[i].szTitle, " - Weapons"))
				{
					gDrawManager.DrawString(xx, y + (h * i), pMenu[i].value[0] ? Color::White() : Color::White(), "%s", szWeapons[(int)pMenu[i].value[0]]);
				}

				else if (!strcmp(pMenu[i].szTitle, " - Font"))
				{
					gDrawManager.DrawString(xx, y + (h * i), pMenu[i].value[0] ? Color::White() : Color(105, 105, 105, 255), "%s", szFont[(int)pMenu[i].value[0]]);
				}

				else if (!strcmp(pMenu[i].szTitle, "  * Pitch"))
				{
					gDrawManager.DrawString(xx, y + (h * i), pMenu[i].value[0] ? Color::White() : Color(105, 105, 105, 255), "%s", szPitch[(int)pMenu[i].value[0]]);
				}

				else if (!strcmp(pMenu[i].szTitle, "  * Yaw"))
				{
					gDrawManager.DrawString(xx, y + (h * i), pMenu[i].value[0] ? Color::White() : Color(105, 105, 105, 255), "%s", szYaw[(int)pMenu[i].value[0]]);
				}

				else if (pMenu[i].flMax == 3)
				{
					gDrawManager.DrawString(xx, y + (h * i), Color::White(), "%s", szHealthModes[(int)pMenu[i].value[0]]);
				}

				else if (pMenu[i].flMax == 8)
				{
					gDrawManager.DrawString(xx, y + (h * i), Color::White(), "%s", szKeyNames[(int)pMenu[i].value[0]]);
				}

				else if (pMenu[i].flMax == 6)
				{
					gDrawManager.DrawString(xx, y + (h * i), Color::White(), "%s", szKeyNames2[(int)pMenu[i].value[0]]);
				}

				else if (pMenu[i].flMax == 2)
				{
					gDrawManager.DrawString(xx, y + (h * i), Color::White(), !pMenu[i].value[0] ? "Ignore" : pMenu[i].value[0] == 1 ? "Normal" : "Rage");
				}

				else if (pMenu[i].flMax == 1)
				{
					gDrawManager.DrawString(xx, y + (h * i), pMenu[i].value[0] ? Color::White() : Color(105, 105, 105, 255), pMenu[i].value[0] ? "ON" : "OFF");
				}

				else if (pMenu[i].value[0] >= 1 && pMenu[i].flMax > 1)
				{
					gDrawManager.DrawString(xx, y + (h * i), pMenu[i].value[0] >= 1 ? Color::White() : Color(105, 105, 105, 255), "%0.0f", pMenu[i].value[0]);
				}
			}
		}
		else
		{
			gDrawManager.DrawRect(x + 1, y + (h * i), w - 2, h, Color(255, 255, 255, 80));

			if (pMenu[i].isClassSwitch)
			{
				if (!(pMenu[i].value[0]))
				{
					gDrawManager.DrawString(x + 2, y + (h * i), clrColor, "[+] %s", pMenu[i].szTitle);
				}
				else if (pMenu[i].value[0])
				{
					gDrawManager.DrawString(x + 2, y + (h * i), clrColor, "[-] %s", pMenu[i].szTitle);
				}
			}
			else
			{
				gDrawManager.DrawString(x + 4, y + (h * i), clrColor, pMenu[i].szTitle);

				if (!strcmp(pMenu[i].szTitle, "  * Health"))
				{
					gDrawManager.DrawString(xx, y + (h * i), clrColor, "%s", szHealthModes[(int)pMenu[i].value[0]]);
				}

				if (!strcmp(pMenu[i].szTitle, "  * Method"))
				{
					gDrawManager.DrawString(xx, y + (h * i), clrColor, "%s", szAimMethod[(int)pMenu[i].value[0]]);
				}

				else if (!strcmp(pMenu[i].szTitle, "  * Position"))
				{
					gDrawManager.DrawString(xx, y + (h * i), clrColor, "%s", szTextPos[(int)pMenu[i].value[0]]);
				}

				else if (!strcmp(pMenu[i].szTitle, " - Color Scheme"))
				{
					gDrawManager.DrawString(xx, y + (h * i), clrColor, "%s", szColorScheme[(int)pMenu[i].value[0]]);
				}

				else if (!strcmp(pMenu[i].szTitle, "  * Box"))
				{
					gDrawManager.DrawString(xx, y + (h * i), clrColor, "%s", szBox[(int)pMenu[i].value[0]]);
				}

				else if (!strcmp(pMenu[i].szTitle, "  * Chams"))
				{
					gDrawManager.DrawString(xx, y + (h * i), clrColor, "%s", szChams[(int)pMenu[i].value[0]]);
				}

				else if (!strcmp(pMenu[i].szTitle, " - Hands"))
				{
					gDrawManager.DrawString(xx, y + (h * i), clrColor, "%s", szHands[(int)pMenu[i].value[0]]);
				}

				else if (!strcmp(pMenu[i].szTitle, " - Weapons"))
				{
					gDrawManager.DrawString(xx, y + (h * i), clrColor, "%s", szWeapons[(int)pMenu[i].value[0]]);
				}

				else if (!strcmp(pMenu[i].szTitle, " - Font"))
				{
					gDrawManager.DrawString(xx, y + (h * i), clrColor, "%s", szFont[(int)pMenu[i].value[0]]);
				}

				else if (!strcmp(pMenu[i].szTitle, "  * Pitch"))
				{
					gDrawManager.DrawString(xx, y + (h * i), clrColor, "%s", szPitch[(int)pMenu[i].value[0]]);
				}

				else if (!strcmp(pMenu[i].szTitle, "  * Yaw"))
				{
					gDrawManager.DrawString(xx, y + (h * i), clrColor, "%s", szYaw[(int)pMenu[i].value[0]]);
				}

				else if (pMenu[i].flMax == 3)
				{
					gDrawManager.DrawString(xx, y + (h * i), clrColor, "%s", szHealthModes[(int)pMenu[i].value[0]]);
				}


				else if (pMenu[i].flMax == 8)
				{
					gDrawManager.DrawString(xx, y + (h * i), clrColor, "%s", szKeyNames[(int)pMenu[i].value[0]]);
				}

				else if (pMenu[i].flMax == 6)
				{
					gDrawManager.DrawString(xx, y + (h * i), clrColor, "%s", szKeyNames2[(int)pMenu[i].value[0]]);
				}

				else if (pMenu[i].flMax == 2)
				{
					gDrawManager.DrawString(xx, y + (h * i), clrColor, !pMenu[i].value[0] ? "Ignore" : pMenu[i].value[0] == 1 ? "Normal" : "Rage");
				}

				else if (pMenu[i].flMax == 1)
				{
					gDrawManager.DrawString(xx, y + (h * i), clrColor, pMenu[i].value[0] ? "ON" : "OFF");
				}

				else
				{
					gDrawManager.DrawString(xx, y + (h * i), clrColor, "%0.0f", pMenu[i].value[0]);
				}
			}
		}
	}
}