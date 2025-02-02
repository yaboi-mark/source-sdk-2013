//====== Copyright � 1996-2005, Valve Corporation, All rights reserved. =======
//
// Purpose: 
//
//=============================================================================

#include "cbase.h"
#include "tf_weapon_garand.h"
#include "in_buttons.h"
#include "decals.h"
#include "tf_fx_shared.h"

// Client specific.
#if defined( CLIENT_DLL )
#include "c_tf_player.h"
// Server specific.
#else
#include "tf_player.h"
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

CREATE_SIMPLE_WEAPON_TABLE(TFGarand, tf_weapon_garand)


//=============================================================================
//
// Weapon Shotgun functions.
//

//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
CTFGarand::CTFGarand()
{
	m_bReloadsSingly = true;
}

//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
void CTFGarand::PrimaryAttack()
{
	if (!CanAttack())
		return;

	// Set the weapon mode.
	m_iWeaponMode = TF_WEAPON_PRIMARY_MODE;

	BaseClass::PrimaryAttack();
}


void CTFGarand::SecondaryAttack(void)
{
	return; // we dont need any of the shit after this
	if (!CanAttack())
		return;

	// Set the weapon mode.
	m_iWeaponMode = TF_WEAPON_SECONDARY_MODE;

	BaseClass::SecondaryAttack();
}

void CTFGarand::ItemPostFrame( void )
{
	// If we're lowered, we're not allowed to fire
	if (m_bLowered)
		return;

	// Get the owning player.
	CTFPlayer *pPlayer = GetTFPlayerOwner();
	if ( !pPlayer )
		return;

	if ( pPlayer->m_nButtons & IN_ATTACK2 )
	{
		if ( !IsZoomed() ) {
			ZoomIn();
		}
	}
	else if ( IsZoomed() ) {
		ZoomOut();
	}

	BaseClass::ItemPostFrame();
}

bool CTFGarand::IsZoomed(void)
{
	CTFPlayer *pPlayer = GetTFPlayerOwner();

	if (pPlayer)
	{
		return pPlayer->m_Shared.InCond(TF_COND_ZOOMED);
	}

	return false;
}