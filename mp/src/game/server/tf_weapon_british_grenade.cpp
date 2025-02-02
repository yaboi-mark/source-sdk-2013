//====== Copyright � 1996-2005, Valve Corporation, All rights reserved. =======
//
// Purpose: 
//
//=============================================================================

#include "cbase.h"
#include "tf_weapon_british_grenade.h"
#include "decals.h"
#include "tf_fx_shared.h"

// Client specific.
#if defined( CLIENT_DLL )
#include "c_tf_player.h"
// Server specific.
#else
#include "tf_player.h"
#include "tf_gamestats.h"
#endif

#define CREATE_SIMPLE_WEAPON_TABLE( WpnName, entityname )			\
																	\
	IMPLEMENT_NETWORKCLASS_ALIASED( WpnName, DT_##WpnName )	\
															\
	BEGIN_NETWORK_TABLE( C##WpnName, DT_##WpnName )			\
	END_NETWORK_TABLE()										\
															\
	BEGIN_PREDICTION_DATA( C##WpnName )						\
	END_PREDICTION_DATA()									\
															\
	LINK_ENTITY_TO_CLASS( entityname, C##WpnName );			\
	PRECACHE_WEAPON_REGISTER( entityname );
#define CREATE_SIMPLE_WEAPON_TABLE_OLD(WpnName, entityname)			    \
																	\
	IMPLEMENT_NETWORKCLASS_ALIASED( ##WpnName##, DT_##WpnName## )	\
																	\
	BEGIN_NETWORK_TABLE( C##WpnName##, DT_##WpnName## )				\
	END_NETWORK_TABLE()												\
																	\
	BEGIN_PREDICTION_DATA( C##WpnName## )							\
	END_PREDICTION_DATA()											\
																	\
	LINK_ENTITY_TO_CLASS( ##entityname##, C##WpnName## );			\
	PRECACHE_WEAPON_REGISTER( ##entityname## );


//=============================================================================
//
// Weapon Shotgun tables.
//

CREATE_SIMPLE_WEAPON_TABLE(TFBritishGrenade, tf_weapon_british_grenade)


//=============================================================================
//
// Weapon Shotgun functions.
//

//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
CTFBritishGrenade::CTFBritishGrenade()
{
	m_bReloadsSingly = false;
}

//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
void CTFBritishGrenade::PrimaryAttack()
{
	if (!CanAttack())
		return;

	// Set the weapon mode.
	m_iWeaponMode = TF_WEAPON_PRIMARY_MODE;

	BaseClass::PrimaryAttack();
}


void CTFBritishGrenade::SecondaryAttack(void)
{
	if (!CanAttack())
		return;

	// Set the weapon mode.
	m_iWeaponMode = TF_WEAPON_SECONDARY_MODE;

	BaseClass::SecondaryAttack();
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CTFBritishGrenade::LaunchGrenade(void)
{
	// Get the player owning the weapon.
	CTFPlayer *pPlayer = ToTFPlayer(GetPlayerOwner());
	if (!pPlayer)
		return;

	CalcIsAttackCritical();

	SendWeaponAnim(ACT_VM_PRIMARYATTACK);

	pPlayer->SetAnimation(PLAYER_ATTACK1);
	pPlayer->DoAnimationEvent(PLAYERANIMEVENT_ATTACK_PRIMARY);

	FireProjectile(pPlayer);

#if !defined( CLIENT_DLL ) 
	pPlayer->SpeakWeaponFire();
	CTF_GameStats.Event_PlayerFiredWeapon(pPlayer, IsCurrentAttackACrit());
#endif

	// Set next attack times.
	m_flNextPrimaryAttack = gpGlobals->curtime + m_pWeaponInfo->GetWeaponData(m_iWeaponMode).m_flTimeFireDelay;

	SetWeaponIdleTime(gpGlobals->curtime + SequenceDuration());

	// Check the reload mode and behave appropriately.
	if (m_bReloadsSingly)
	{
		m_iReloadMode.Set(TF_RELOAD_START);
	}
}