#include "SDK.h"
#include "CGlobalVars.hpp"
#include <Windows.h>
#include "CFileManager.h"

CGlobalVariables gCvars;

void CGlobalVariables::Save(void)
{
	//
	// Save Aimbot
	//
	if (GAME_HL2 || GAME_HL2_LC || GAME_HL2_EP1 || GAME_HL2_EP2 || GAME_HLS || GAME_SYN)
	{
		gFileManager.WriteFloat("Aimbot", "Enabled", aimbot_active);
		gFileManager.WriteFloat("Aimbot", "FOV", aimbot_fov);
		gFileManager.WriteFloat("Aimbot", "Autoshoot", aimbot_autoshoot);
	}
	else
	{
		gFileManager.WriteFloat("Aimbot", "Enabled", aimbot_active);
		gFileManager.WriteFloat("Aimbot", "Hitscan", aimbot_hitscan);
		gFileManager.WriteFloat("Aimbot", "FOV", aimbot_fov);
		gFileManager.WriteFloat("Aimbot", "Smooth", aimbot_smooth);
		gFileManager.WriteFloat("Aimbot", "Smooth Amt", aimbot_smooth_amt);
		gFileManager.WriteFloat("Aimbot", "Method", aimbot_mode);
		if (GAME_TF2)
		{
			gFileManager.WriteFloat("Aimbot", "Zoomed Only", aimbot_zoomedonly);
			gFileManager.WriteFloat("Aimbot", "Wait For Charge", aimbot_waitforcharge);
		}
		gFileManager.WriteFloat("Aimbot", "Deathmatch", aimbot_deathmatch);
		gFileManager.WriteFloat("Aimbot", "Resolver", aimbot_resolver);
		gFileManager.WriteFloat("Aimbot", "Autoshoot", aimbot_autoshoot);
		gFileManager.WriteFloat("Aimbot", "Ignore Health > 100", aimbot_ignoreabove100);
		gFileManager.WriteFloat("Aimbot", "Ignore Cloaked", aimbot_ignorecloaked);
	}

	//
	// Save Triggerbot
	//
	if (GAME_HL2 || GAME_HL2_LC || GAME_HL2_EP1 || GAME_HL2_EP2 || GAME_HLS || GAME_SYN)
	{
		//planning on adding Triggerbot support soon
	}
	else
	{
		gFileManager.WriteFloat("Triggerbot", "Hitscan", triggerbot_active);
		gFileManager.WriteFloat("Triggerbot", "Head Only", triggerbot_headonly);
		gFileManager.WriteFloat("Triggerbot", "Ignore Cloaked", triggerbot_ignorecloaked);
	}

	//
	// Save Visuals
	//
	if (GAME_HL2 || GAME_HL2_LC || GAME_HL2_EP1 || GAME_HL2_EP2 || GAME_HLS || GAME_SYN)
	{
		gFileManager.WriteFloat("ESP", "Enabled", esp_active);
		gFileManager.WriteFloat("ESP", "Name", esp_name);
	}
	else
	{
		gFileManager.WriteFloat("ESP", "Enabled", esp_active);
		gFileManager.WriteFloat("ESP", "Enemies Only", esp_enemyonly);
		gFileManager.WriteFloat("ESP", "Box", esp_box);
		gFileManager.WriteFloat("ESP", "Name", esp_name);
		if (GAME_TF2)
		{
			gFileManager.WriteFloat("ESP", "Class", esp_class);
			gFileManager.WriteFloat("ESP", "Chams", esp_chams);
		}
		gFileManager.WriteFloat("ESP", "Health", esp_health);
		gFileManager.WriteFloat("ESP", "Position", esp_pos);
	}

	//
	// Save Time Shift
	//
    gFileManager.WriteFloat("Time Shift", "Enabled", timeshift_enabled);
	gFileManager.WriteFloat("Time Shift", "Value", timeshift_value);

	//
	// Save Misc
	//
	gFileManager.WriteFloat("Misc", "Bunnyhop", misc_bunnyhop);
	gFileManager.WriteFloat("Misc", "Autostrafe", misc_autostrafe);
	if (GAME_TF2)
	{
		gFileManager.WriteFloat("Misc", "Hands", gCvars.misc_hands);
		gFileManager.WriteFloat("Misc", "No Hats", gCvars.misc_nohats);
		gFileManager.WriteFloat("Misc", "Crouch Exploit", gCvars.misc_speedhack);
		gFileManager.WriteFloat("Misc", "No Scope", gCvars.misc_noscope);
		gFileManager.WriteFloat("Misc", "Disable Crosshair", gCvars.misc_noscope_disablecrosshair);
	}
	gFileManager.WriteFloat("Misc", "Server Lagger", misc_serverlag);
	gFileManager.WriteFloat("Misc", "Server Lagger Value", misc_serverlag_value);
	gFileManager.WriteFloat("Misc", "No Zoom", misc_nozoom);
	gFileManager.WriteFloat("Misc", "FOV Override", misc_fov_value);
	gFileManager.WriteFloat("Misc", "Viewmodel FOV Override", misc_viewmodelfov_value);
	if (GAME_HL2 || GAME_HL2_LC || GAME_HL2_EP1 || GAME_HL2_EP2 || GAME_HLS || GAME_SYN)
	{
		//maybe smth here eventually
	}
	else
	{
		gFileManager.WriteFloat("Misc", "Thirdperson", misc_thirdperson);
		gFileManager.WriteFloat("Misc", "Pitch Angles", misc_aax);
		gFileManager.WriteFloat("Misc", "Yaw Angles", misc_aay);
		gFileManager.WriteFloat("Misc", "Backtracking", misc_backtracking);
		gFileManager.WriteFloat("Misc", "Backtrack Teammates", misc_backtracking_deathmatch);
	}

	gFileManager.WriteFloat("Settings", "Position X", iMenu_Pos_X);
	gFileManager.WriteFloat("Settings", "Position Y", iMenu_Pos_Y);
	gFileManager.WriteFloat("Settings", "Color Scheme", iMenu_Color_Scheme);
	gFileManager.WriteFloat("Settings", "Font", iMenu_Font);

	//
	// Save Hotkeys
	//
	gFileManager.WriteFloat("Hotkeys", "Aimbot", aimbot_key);
	gFileManager.WriteFloat("Hotkeys", "Triggerbot", triggerbot_key);
	gFileManager.WriteFloat("Hotkeys", "Time Shift", timeshift_key);
	gFileManager.WriteFloat("Hotkeys", "Server Lagger", misc_serverlag_key);
}
//===================================================================================
void CGlobalVariables::Load(void)
{
	//
	// Load Aimbot
	//
	if (GAME_HL2 || GAME_HL2_LC || GAME_HL2_EP1 || GAME_HL2_EP2 || GAME_HLS || GAME_SYN)
	{
		aimbot_active = gFileManager.ReadFloat("Aimbot", "Enabled", aimbot_active);
		aimbot_fov = gFileManager.ReadFloat("Aimbot", "FOV", aimbot_fov);
		aimbot_autoshoot = gFileManager.ReadFloat("Aimbot", "Autoshoot", aimbot_autoshoot);
	}
	else
	{
		aimbot_active = gFileManager.ReadFloat("Aimbot", "Enabled", aimbot_active);
		aimbot_hitscan = gFileManager.ReadFloat("Aimbot", "Hiscan", aimbot_hitscan);
		aimbot_fov = gFileManager.ReadFloat("Aimbot", "FOV", aimbot_fov);
		aimbot_smooth = gFileManager.ReadFloat("Aimbot", "Smooth", aimbot_smooth);
		aimbot_smooth_amt = gFileManager.ReadFloat("Aimbot", "Smooth Amt", aimbot_smooth_amt);
		aimbot_mode = gFileManager.ReadFloat("Aimbot", "Method", aimbot_mode);
		if (GAME_TF2)
		{
			aimbot_zoomedonly = gFileManager.ReadFloat("Aimbot", "Zoomed Only", aimbot_zoomedonly);
			aimbot_waitforcharge = gFileManager.ReadFloat("Aimbot", "Wait For Charge", aimbot_waitforcharge);
		}
		aimbot_deathmatch = gFileManager.ReadFloat("Aimbot", "Deathmatch", aimbot_deathmatch);
		aimbot_resolver = gFileManager.ReadFloat("Aimbot", "Resolver", aimbot_resolver);
		aimbot_autoshoot = gFileManager.ReadFloat("Aimbot", "Autoshoot", aimbot_autoshoot);
		aimbot_ignorecloaked = gFileManager.ReadFloat("Aimbot", "Ignore Cloaked", aimbot_ignorecloaked);
	}

	//
	// Load Triggerbot
	//
	if (GAME_HL2 || GAME_HL2_LC || GAME_HL2_EP1 || GAME_HL2_EP2 || GAME_HLS || GAME_SYN)
	{
		//planning on adding Triggerbot support soon
	}
	else
	{
		triggerbot_active = gFileManager.ReadFloat("Triggerbot", "Hitscan", triggerbot_active);
		triggerbot_headonly = gFileManager.ReadFloat("Triggerbot", "Head Only", triggerbot_headonly);
	}


	//
	// Load Visuals
	//
	if (GAME_HL2 || GAME_HL2_LC || GAME_HL2_EP1 || GAME_HL2_EP2 || GAME_HLS || GAME_SYN)
	{
		esp_active = gFileManager.ReadFloat("ESP", "Enabled", esp_active);
		esp_name = gFileManager.ReadFloat("ESP", "Name", esp_name);
	}
	else
	{
		esp_active = gFileManager.ReadFloat("ESP", "Enabled", esp_active);
		esp_enemyonly = gFileManager.ReadFloat("ESP", "Enemies Only", esp_enemyonly);
		esp_box = gFileManager.ReadFloat("ESP", "Box", esp_box);
		esp_name = gFileManager.ReadFloat("ESP", "Name", esp_name);
		if (GAME_TF2)
		{
			esp_class = gFileManager.ReadFloat("ESP", "Class", esp_class);
			esp_chams = gFileManager.ReadFloat("ESP", "Chams", esp_chams);
		}
		esp_health = gFileManager.ReadFloat("ESP", "Health", esp_health);
		esp_pos = gFileManager.ReadFloat("ESP", "Position", esp_pos);
	}


	//
	// Load Time Shift
	//
	timeshift_enabled = gFileManager.ReadFloat("Time Shift", "Enabled", timeshift_enabled);
	timeshift_value = gFileManager.ReadFloat("Time Shift", "Value", timeshift_value);

	//
	// Load Misc
	//
	misc_bunnyhop = gFileManager.ReadFloat("Misc", "Bunnyhop", misc_bunnyhop);
	misc_autostrafe = gFileManager.ReadFloat("Misc", "Autostrafe", misc_autostrafe);
	if (GAME_TF2)
	{
		misc_hands = gFileManager.ReadFloat("Misc", "Hands", gCvars.misc_hands);
		misc_nohats = gFileManager.ReadFloat("Misc", "No Hats", gCvars.misc_nohats);
		misc_speedhack = gFileManager.ReadFloat("Misc", "Crouch Exploit", gCvars.misc_speedhack);
		misc_noscope = gFileManager.ReadFloat("Misc", "No Scope", gCvars.misc_noscope);
		misc_noscope_disablecrosshair = gFileManager.ReadFloat("Misc", "Disable Crosshair", gCvars.misc_noscope_disablecrosshair);
	}
	misc_serverlag = gFileManager.ReadFloat("Misc", "Server Lagger", misc_serverlag);
	misc_serverlag_value = gFileManager.ReadFloat("Misc", "Server Lagger Value", misc_serverlag_value);
	misc_nozoom = gFileManager.ReadFloat("Misc", "No Zoom", misc_nozoom);
	misc_fov_value = gFileManager.ReadFloat("Misc", "FOV Override", misc_fov_value);
	misc_viewmodelfov_value = gFileManager.ReadFloat("Misc", "Viewmodel FOV Override", misc_viewmodelfov_value);
	if (GAME_HL2 || GAME_HL2_LC || GAME_HL2_EP1 || GAME_HL2_EP2 || GAME_HLS || GAME_SYN)
	{
		//maybe something here eventually
	}
	else
	{
		misc_thirdperson = gFileManager.ReadFloat("Misc", "Thirdperson", misc_thirdperson);
		misc_angles = gFileManager.ReadFloat("Misc", "Angles", misc_angles); //This doesn't save but it does load incase you want to manually load it via a config for games like Synergy
		misc_aax = gFileManager.ReadFloat("Misc", "Pitch Angles", misc_aax);
		misc_aay = gFileManager.ReadFloat("Misc", "Yaw Angles", misc_aay);
		misc_backtracking = gFileManager.ReadFloat("Misc", "Backtracking", misc_backtracking);
		misc_backtracking_deathmatch = gFileManager.ReadFloat("Misc", "Backtrack Teammates", misc_backtracking_deathmatch);
	}

	iMenu_Pos_X = gFileManager.ReadFloat("Settings", "Position X", iMenu_Pos_X);
	iMenu_Pos_Y = gFileManager.ReadFloat("Settings", "Position Y", iMenu_Pos_Y);
	iMenu_Color_Scheme = gFileManager.ReadFloat("Settings", "Color Scheme", iMenu_Color_Scheme);
	iMenu_Font = gFileManager.ReadFloat("Settings", "Font", iMenu_Font);

	//
	// Load Hotkeys
	//
	aimbot_key = gFileManager.ReadFloat("Hotkeys", "Aimbot", aimbot_key);
	triggerbot_key = gFileManager.ReadFloat("Hotkeys", "Triggerbot", triggerbot_key);
	timeshift_key = gFileManager.ReadFloat("Hotkeys", "Time Shift", timeshift_key);
	misc_serverlag_key = gFileManager.ReadFloat("Hotkeys", "Server Lagger", misc_serverlag_key);
}
