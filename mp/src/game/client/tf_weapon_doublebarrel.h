//====== Copyright © 1996-2005, Valve Corporation, All rights reserved. =======
//
// Purpose: 
//
//=============================================================================

#ifndef TF_WEAPON_DOUBLEBARREL_H
#define TF_WEAPON_DOUBLEBARREL_H
#endif
#ifdef _WIN32
#pragma once
#endif

#include "tf_weaponbase_gun.h"

#if defined( CLIENT_DLL )
#define CTFDoublebarrel C_TFDoublebarrel
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
class CTFDoublebarrel : public CTFWeaponBaseGun
{
public:

	DECLARE_CLASS(CTFDoublebarrel, CTFWeaponBaseGun);
	DECLARE_NETWORKCLASS();
	DECLARE_PREDICTABLE();

	CTFDoublebarrel();

	virtual int		GetWeaponID(void) const			{ return TF_WEAPON_DOUBLEBARREL; }
	virtual void	PrimaryAttack();
	virtual void SecondaryAttack();

protected:

	void		Fire(CTFPlayer *pPlayer);
	void		UpdatePunchAngles(CTFPlayer *pPlayer);

private:

	CTFDoublebarrel(const CTFDoublebarrel &) {}
};