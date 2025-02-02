//====== Copyright � 1996-2005, Valve Corporation, All rights reserved. =======
//
// Purpose: 
//
//=============================================================================

#ifndef TF_WEAPON_BRITISH_GRENADE_H
#define TF_WEAPON_BRITISH_GRENADE_H
#endif
#ifdef _WIN32
#pragma once
#endif

#include "tf_weapon_grenadelauncher.h"

#if defined( CLIENT_DLL )
#define CTFBritishGrenade C_TFBritishGrenade
#endif

// Reload Modes
enum
{
	TF_WEAPON_SHOTGUN_RELOAD_START = 0,
	TF_WEAPON_SHOTGUN_RELOAD_SHELL,
	TF_WEAPON_SHOTGUN_RELOAD_CONTINUE,
	TF_WEAPON_SHOTGUN_RELOAD_FINISH
};

//=============================================================================
//
// Shotgun class.
//
class CTFBritishGrenade : public CTFGrenadeLauncher
{
public:

	DECLARE_CLASS(CTFBritishGrenade, CTFGrenadeLauncher);
	DECLARE_NETWORKCLASS();
	DECLARE_PREDICTABLE();

	CTFBritishGrenade();

	virtual int		GetWeaponID(void) const			{ return TF_WEAPON_BRITISH_GRENADE; }
	virtual void	PrimaryAttack();
	virtual void SecondaryAttack();
	void LaunchGrenade(void);

protected:

	void		Fire(CTFPlayer *pPlayer);
	void		UpdatePunchAngles(CTFPlayer *pPlayer);

private:

	CTFBritishGrenade(const CTFBritishGrenade &) {}
};