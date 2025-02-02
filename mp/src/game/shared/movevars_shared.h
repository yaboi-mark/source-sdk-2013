//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
//=============================================================================//

#ifndef MOVEVARS_SHARED_H
#define MOVEVARS_SHARED_H
#ifdef _WIN32
#pragma once
#endif

#include "convar.h"

float GetCurrentGravity( void );

extern ConVar sv_gravity;
extern ConVar sv_stopspeed;
extern ConVar sv_noclipaccelerate;
extern ConVar sv_noclipspeed;
extern ConVar sv_maxspeed;
extern ConVar sv_accelerate;
extern ConVar sv_airaccelerate;
extern ConVar sv_wateraccelerate;
extern ConVar sv_waterfriction;
extern ConVar sv_footsteps;
extern ConVar sv_rollspeed;
extern ConVar sv_rollangle;
extern ConVar sv_friction;
extern ConVar sv_bounce;
extern ConVar sv_maxvelocity;
extern ConVar sv_stepsize;
extern ConVar sv_skyname;
extern ConVar sv_backspeed;
extern ConVar sv_waterdist;
extern ConVar sv_specaccelerate;
extern ConVar sv_specspeed;
extern ConVar sv_specnoclip;

// Vehicle convars
extern ConVar r_VehicleViewDampen;

// Jeep convars
extern ConVar r_JeepViewDampenFreq;
extern ConVar r_JeepViewDampenDamp;
extern ConVar r_JeepViewZHeight;

// Airboat convars
extern ConVar r_AirboatViewDampenFreq;
extern ConVar r_AirboatViewDampenDamp;
extern ConVar r_AirboatViewZHeight;

// tea for two convars

extern ConVar tea_bhop_dampen_start;
extern ConVar tea_bhop_dampen_severity;
extern ConVar tea_airdash_zvel_influence;
extern ConVar tea_q3accelerate;
extern ConVar tea_movementmode;
extern ConVar tea_overspeed_friction;
extern ConVar tea_airdash_zvel_influence_horizontal_dampening;
extern ConVar tea_flagcarrier_universal_accelerate_multiplier;
extern ConVar tea_flagcarrier_bhop_dampen_multiplier;
extern ConVar tea_overspeed_decreaseresist;
extern ConVar tea_overspeed_start;
extern ConVar tea_slide_speed;
extern ConVar tea_slide_accelerate;
extern ConVar tea_slide_jumpboost;

#endif // MOVEVARS_SHARED_H
