//====== Copyright © 1996-2005, Valve Corporation, All rights reserved. =======
//
// Purpose: 
//
//=============================================================================

#ifndef TF_WEAPON_SPAZ_H
#define TF_WEAPON_SPAZ_H
#endif
#ifdef _WIN32
#pragma once
#endif

#include "tf_weaponbase_gun.h"

#if defined( CLIENT_DLL )
#define CTFSpaz C_TFSpaz
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
class CTFSpaz : public CTFWeaponBaseGun
{
public:

	DECLARE_CLASS(CTFSpaz, CTFWeaponBaseGun);
	DECLARE_NETWORKCLASS();
	DECLARE_PREDICTABLE();

	CTFSpaz();

	virtual int		GetWeaponID(void) const			{ return TF_WEAPON_SPAZ; }
	virtual void	PrimaryAttack();
	virtual void SecondaryAttack();

protected:

	void		Fire(CTFPlayer *pPlayer);
	void		UpdatePunchAngles(CTFPlayer *pPlayer);

private:

	CTFSpaz(const CTFSpaz &) {}
};