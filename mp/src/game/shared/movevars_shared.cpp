//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
//=============================================================================//


#include "cbase.h"
#include "movevars_shared.h"

#if defined( TF_CLIENT_DLL ) || defined( TF_DLL )
#include "tf_gamerules.h"
#endif

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

// some cvars used by player movement system
#if defined( HL2_DLL ) || defined( HL2_CLIENT_DLL )
#define DEFAULT_GRAVITY_STRING	"600"
#else
#define DEFAULT_GRAVITY_STRING	"600"
#endif

float GetCurrentGravity( void )
{
#if defined( TF_CLIENT_DLL ) || defined( TF_DLL )
	if ( TFGameRules() )
	{
		return ( sv_gravity.GetFloat() * TFGameRules()->GetGravityMultiplier() );
	}
#endif 

	return sv_gravity.GetFloat();
}

ConVar	sv_gravity		( "sv_gravity", DEFAULT_GRAVITY_STRING, FCVAR_NOTIFY | FCVAR_REPLICATED, "World gravity." );

#if defined( DOD_DLL ) || defined( CSTRIKE_DLL ) || defined( HL1MP_DLL )
ConVar	sv_stopspeed	( "sv_stopspeed","100", FCVAR_NOTIFY | FCVAR_REPLICATED, "Minimum stopping speed when on ground." );
#else
ConVar	sv_stopspeed	( "sv_stopspeed","100", FCVAR_NOTIFY | FCVAR_REPLICATED, "Minimum stopping speed when on ground." );
#endif // DOD_DLL || CSTRIKE_DLL

ConVar	sv_noclipaccelerate( "sv_noclipaccelerate", "1", FCVAR_NOTIFY | FCVAR_ARCHIVE | FCVAR_REPLICATED);
ConVar	sv_noclipspeed	( "sv_noclipspeed", "10", FCVAR_ARCHIVE | FCVAR_NOTIFY | FCVAR_REPLICATED);
ConVar	sv_specaccelerate( "sv_specaccelerate", "5", FCVAR_NOTIFY | FCVAR_ARCHIVE | FCVAR_REPLICATED);
ConVar	sv_specspeed	( "sv_specspeed", "3", FCVAR_ARCHIVE | FCVAR_NOTIFY | FCVAR_REPLICATED);
ConVar	sv_specnoclip	( "sv_specnoclip", "1", FCVAR_ARCHIVE | FCVAR_NOTIFY | FCVAR_REPLICATED);

#if defined( CSTRIKE_DLL ) || defined( HL1MP_DLL )
ConVar	sv_maxspeed		( "sv_maxspeed", "320", FCVAR_NOTIFY | FCVAR_REPLICATED);
#else
ConVar	sv_maxspeed		( "sv_maxspeed", "320", FCVAR_NOTIFY | FCVAR_REPLICATED );
#endif // CSTRIKE_DLL

#ifdef _XBOX
	ConVar	sv_accelerate	( "sv_accelerate", "7", FCVAR_NOTIFY | FCVAR_REPLICATED);
#else

#if defined( CSTRIKE_DLL ) || defined( HL1MP_DLL )
	ConVar	sv_accelerate	( "sv_accelerate", "10", FCVAR_NOTIFY | FCVAR_REPLICATED);
#else
	ConVar	sv_accelerate	( "sv_accelerate", "15", FCVAR_NOTIFY | FCVAR_REPLICATED );
#endif // CSTRIKE_DLL
	
#endif//_XBOX

#if defined( CSTRIKE_DLL ) || defined( HL1MP_DLL )
ConVar	sv_airaccelerate(  "sv_airaccelerate", "10", FCVAR_NOTIFY | FCVAR_REPLICATED);    
ConVar	sv_wateraccelerate(  "sv_wateraccelerate", "10", FCVAR_NOTIFY | FCVAR_REPLICATED);     
ConVar	sv_waterfriction(  "sv_waterfriction", "1", FCVAR_NOTIFY | FCVAR_REPLICATED);      
ConVar	sv_footsteps	( "sv_footsteps", "1", FCVAR_NOTIFY | FCVAR_REPLICATED, "Play footstep sound for players" );
ConVar	sv_rollspeed	( "sv_rollspeed", "200", FCVAR_NOTIFY | FCVAR_REPLICATED);
ConVar	sv_rollangle	( "sv_rollangle", "0", FCVAR_NOTIFY | FCVAR_REPLICATED, "Max view roll angle");
#else
ConVar	sv_airaccelerate("sv_airaccelerate", "35", FCVAR_NOTIFY | FCVAR_REPLICATED);
ConVar	tea_q3accelerate("tea_q3accelerate", "2.25", FCVAR_NOTIFY | FCVAR_REPLICATED);
ConVar	tea_movementmode("tea_movementmode", "2", FCVAR_NOTIFY | FCVAR_REPLICATED, "0 - default source engine. (sv_airaccelerate) 1 - quake 3. (tea_q3accelerate) 2 - cpma (what we use in this mod) (and also btw cpma is just tf2 and q3 at once) (also we stole the idea of this cvar from of)" );
ConVar	sv_wateraccelerate(  "sv_wateraccelerate", "10", FCVAR_NOTIFY | FCVAR_REPLICATED  );     
ConVar	sv_waterfriction(  "sv_waterfriction", "1", FCVAR_NOTIFY | FCVAR_REPLICATED  );      
ConVar	sv_footsteps	( "sv_footsteps", "1", FCVAR_NOTIFY | FCVAR_REPLICATED, "Play footstep sound for players" );
ConVar	sv_rollspeed	( "sv_rollspeed", "200", FCVAR_ARCHIVE );
ConVar	sv_rollangle	( "sv_rollangle", "1", FCVAR_ARCHIVE, "Max view roll angle");
#endif // CSTRIKE_DLL

#if defined( DOD_DLL ) || defined( CSTRIKE_DLL ) || defined( HL1MP_DLL )
ConVar	sv_friction		( "sv_friction","4", FCVAR_NOTIFY | FCVAR_REPLICATED, "World friction." );
#else
ConVar	sv_friction		( "sv_friction","6", FCVAR_NOTIFY | FCVAR_REPLICATED, "World friction." );
#endif // DOD_DLL || CSTRIKE_DLL

#if defined( CSTRIKE_DLL ) || defined( HL1MP_DLL )
ConVar	sv_bounce		( "sv_bounce","0", FCVAR_NOTIFY | FCVAR_REPLICATED, "Bounce multiplier for when physically simulated objects collide with other objects." );
ConVar	sv_maxvelocity	( "sv_maxvelocity","3500", FCVAR_REPLICATED, "Maximum speed any ballistically moving object is allowed to attain per axis." );
ConVar	sv_stepsize		( "sv_stepsize","18", FCVAR_NOTIFY | FCVAR_REPLICATED );
ConVar	sv_backspeed	( "sv_backspeed", "0.6", FCVAR_ARCHIVE | FCVAR_REPLICATED, "How much to slow down backwards motion" );
ConVar  sv_waterdist	( "sv_waterdist","12", FCVAR_REPLICATED, "Vertical view fixup when eyes are near water plane." );
#else
ConVar	sv_bounce		( "sv_bounce","0", FCVAR_NOTIFY | FCVAR_REPLICATED, "Bounce multiplier for when physically simulated objects collide with other objects." );
ConVar	sv_maxvelocity	( "sv_maxvelocity","10000", FCVAR_REPLICATED, "Maximum speed any ballistically moving object is allowed to attain per axis." );
ConVar	sv_stepsize		( "sv_stepsize","18", FCVAR_NOTIFY | FCVAR_REPLICATED  );
ConVar	sv_backspeed	( "sv_backspeed", "0.6", FCVAR_ARCHIVE | FCVAR_REPLICATED, "How much to slow down backwards motion" );
ConVar  sv_waterdist	( "sv_waterdist","12", FCVAR_REPLICATED, "Vertical view fixup when eyes are near water plane." );
#endif // CSTRIKE_DLL

ConVar	sv_skyname		( "sv_skyname", "sky_urb01", FCVAR_ARCHIVE | FCVAR_REPLICATED, "Current name of the skybox texture" );

// Vehicle convars
ConVar r_VehicleViewDampen( "r_VehicleViewDampen", "1", FCVAR_CHEAT | FCVAR_NOTIFY | FCVAR_REPLICATED );

// Jeep convars
ConVar r_JeepViewDampenFreq( "r_JeepViewDampenFreq", "7.0", FCVAR_CHEAT | FCVAR_NOTIFY | FCVAR_REPLICATED );
ConVar r_JeepViewDampenDamp( "r_JeepViewDampenDamp", "1.0", FCVAR_CHEAT | FCVAR_NOTIFY | FCVAR_REPLICATED);
ConVar r_JeepViewZHeight( "r_JeepViewZHeight", "10.0", FCVAR_CHEAT | FCVAR_NOTIFY | FCVAR_REPLICATED );

// Airboat convars
ConVar r_AirboatViewDampenFreq( "r_AirboatViewDampenFreq", "7.0", FCVAR_CHEAT | FCVAR_NOTIFY | FCVAR_REPLICATED );
ConVar r_AirboatViewDampenDamp( "r_AirboatViewDampenDamp", "1.0", FCVAR_CHEAT | FCVAR_NOTIFY | FCVAR_REPLICATED);
ConVar r_AirboatViewZHeight( "r_AirboatViewZHeight", "0.0", FCVAR_CHEAT | FCVAR_NOTIFY | FCVAR_REPLICATED );

// tea for two convars

ConVar tea_bhop_dampen_start("tea_bhop_dampen_start", "1.0", FCVAR_CHEAT | FCVAR_NOTIFY | FCVAR_REPLICATED, "when you jump off the ground and your horizontal velocity is over (this number * your class's movespeed), limits your horizontal velocity based on the value of tea_bhop_dampen_severity.");
ConVar tea_bhop_dampen_severity("tea_bhop_dampen_severity", "0.1", FCVAR_CHEAT | FCVAR_NOTIFY | FCVAR_REPLICATED, "changes the amount of limiting when going over tea_bhop_dampen_start. 0 is no limiting, 1 is full limiting, going outside of 0 and 1 can be catastrophic and is not reccomended.");
ConVar tea_airdash_zvel_influence("tea_airdash_zvel_influence", "1", FCVAR_CHEAT | FCVAR_NOTIFY | FCVAR_REPLICATED, "when you double jump, there is a calculation that checks how fast you're moving, including vertically. this convar multiplies that vertical velocity influence. also see tea_airdash_zvel_influence_horizontal_dampening" );
ConVar tea_overspeed_friction("tea_overspeed_friction", "2", FCVAR_CHEAT | FCVAR_NOTIFY | FCVAR_REPLICATED, "if a player is overspeeding (see tea_overspeed_start), this value is used instead of sv_friction.");
ConVar tea_airdash_zvel_influence_horizontal_dampening("tea_airdash_zvel_influence_horizontal_dampening", "0.5", FCVAR_CHEAT | FCVAR_NOTIFY | FCVAR_REPLICATED, "when you double jump, there is a calculation that checks how fast you're moving, including vertically. however, the way this is calculated causes higher horizontal velocities to cause vertical velocities to have less effect during double jumps. this changes how much we ignore that dampening. 0 is full ignorance, 1 is no ignorance, you can set it anywhere in between, or even anywhere outside of that area.");
ConVar tea_flagcarrier_universal_accelerate_multiplier("tea_flagcarrier_universal_accelerate_multiplier", "0.75", FCVAR_CHEAT | FCVAR_NOTIFY | FCVAR_REPLICATED, "when you have the flag, your sv_accelerate, sv_airaccelerate, and tea_q3accelerate are multiplied by this amount.");
ConVar tea_flagcarrier_bhop_dampen_multiplier("tea_flagcarrier_bhop_dampen_multiplier", "1.5", FCVAR_CHEAT | FCVAR_NOTIFY | FCVAR_REPLICATED, "when you have the flag, your tea_bhop_dampen_severity is multiplied by this amount.");
ConVar tea_overspeed_decreaseresist("tea_overspeed_decreaseresist", "0.5", FCVAR_CHEAT | FCVAR_NOTIFY | FCVAR_REPLICATED, "if a player is overspeeding (see tea_overspeed_start), any decreases in velocity are reduced in severity, according to this amount. 1 is full resistance, 0 is no resistance.");
ConVar tea_overspeed_start("tea_overspeed_start", "1.35", FCVAR_CHEAT | FCVAR_NOTIFY | FCVAR_REPLICATED, "if a player is on the ground and over their movement speed, the player is considered to be overspeeding. the velocity required to be overspeeding is this times the player's movement speed.");
ConVar tea_slide_speed("tea_slide_speed", "2", FCVAR_CHEAT | FCVAR_NOTIFY | FCVAR_REPLICATED, "slide speed is a multiple of the player's ordinary move speed. default 2");
ConVar tea_slide_accelerate("tea_slide_accelerate", "15", FCVAR_CHEAT | FCVAR_NOTIFY | FCVAR_REPLICATED, "how much acceleration is applied to a slide. default 15");
ConVar tea_slide_jumpboost("tea_slide_jumpboost", "1.5", FCVAR_CHEAT | FCVAR_NOTIFY | FCVAR_REPLICATED, "multiplier on jump height when sliding. default 1.5");