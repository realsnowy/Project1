#ifndef _CONTROL_VARIABLES_H_
#define _CONTROL_VARIABLES_H_
#include "SDK.h"

class IMaterial;
class CGlobalVariables
{
public:
    void Load(void);
	void Save(void);

	int iAimbotIndex = -1;
	
	float settings_switch;
	float iMenu_Pos_X = 300;
	float iMenu_Pos_Y = 75;
	float iMenu_Font;
	float iMenu_Color_Scheme;

	float hotkeys_switch;

	float aimbot_switch;
	float aimbot_active;
	float aimbot_key;
	float aimbot_melee;
	float aimbot_hitscan;
	float aimbot_fov = 1;
	float aimbot_smooth;
	float aimbot_smooth_amt = 1;
	float aimbot_hitbox;
	float aimbot_silent;
	float aimbot_mode;
	float aimbot_autoshoot;
	float aimbot_deathmatch;
	float aimbot_waitforcharge;
	float aimbot_zoomedonly;
	float aimbot_hitboxdebug;
	float aimbot_ignorecloaked;
	float aimbot_ignoreabove100;
	float aimbot_resolver;
	float aimbot_projectile;

	float triggerbot_switch;
	float triggerbot_active;
	float triggerbot_key;
	float triggerbot_headonly;
	float triggerbot_ignorecloaked;
	float triggerbot_deathmatch;

	float esp_switch;
	float esp_active;
	float esp_pos;
	float esp_speclist;
	float esp_enemyonly;
	float esp_box;
	float esp_name;
	float esp_class;
	float esp_status;
	float esp_health;
	float esp_bones;
	float esp_glow;
	float esp_historyticks;
	float esp_chams;

	float misc_switch;
	float misc_bunnyhop;
	float misc_autostrafe;
	float misc_speedhack;
	float misc_achiev_spam;
	float misc_spinbot;
	float misc_angles;
	float misc_aax;
	float misc_aay;
	float misc_thirdperson;
	float misc_thirdperson_key;
	float misc_nozoom;
	float misc_noscope;
	float misc_noscope_disablecrosshair;
	float misc_nospread;
	float misc_serverlag;
	float misc_serverlag_key;
	float misc_serverlag_value = 100;
	float misc_nohands;
	float misc_transparenthands;
	float misc_nohats;
	float misc_transparenthats;
	float misc_hands;
	float misc_weapons;
	float misc_backtracking;
	float misc_backtracking_deathmatch;
	float misc_norecoil;
	float misc_fovoverride;
	float misc_fov_value = 75;
	float misc_viewmodelfovoverride;
	float misc_viewmodelfov_value = 54;
	float misc_tauntslide;
	float misc_fakelag;
	float misc_fakelag_value = 1;
	float misc_fakelag_onattack;

	float timeshift_switch;
	float timeshift_enabled;
	float timeshift_key;
	float timeshift_value = 800;

	float playerlist_switch;
	float PlayerMode[64] = {
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	};


	IMaterial* Vis_MatLit;
	IMaterial* Hid_MatLit;

	IMaterial* Vis_MatUnLit;
	IMaterial* Hid_MatUnLit;
};
extern CGlobalVariables gCvars;
//===================================================================================
#endif


