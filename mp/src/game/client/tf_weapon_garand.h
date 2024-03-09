//====== Copyright © 1996-2005, Valve Corporation, All rights reserved. =======
//
// Purpose: 
//
//=============================================================================

#ifndef TF_WEAPON_GARAND_H
#define TF_WEAPON_GARAND_H
#endif
#ifdef _WIN32
#pragma once
#endif

#include "tf_weaponbase_gun.h"

#if defined( CLIENT_DLL )
#define CTFGarand C_TFGarand
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
class CTFGarand : public CTFWeaponBaseGun
{
public:

	DECLARE_CLASS(CTFGarand, CTFWeaponBaseGun);
	DECLARE_NETWORKCLASS();
	DECLARE_PREDICTABLE();

	CTFGarand();

	virtual int		GetWeaponID(void) const			{ return TF_WEAPON_GARAND; }
	virtual void	PrimaryAttack();
	virtual void SecondaryAttack();
	virtual void ItemPostFrame(void);

	bool IsZoomed(void);

protected:

	void		Fire(CTFPlayer *pPlayer);
	void		UpdatePunchAngles(CTFPlayer *pPlayer);

private:

	CTFGarand(const CTFGarand &) {}
};