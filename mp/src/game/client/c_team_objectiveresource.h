//====== Copyright � 1996-2005, Valve Corporation, All rights reserved. =======
//
// Purpose: 
//
//=============================================================================

#ifndef C_TEAM_OBJECTIVERESOURCE_H
#define C_TEAM_OBJECTIVERESOURCE_H
#ifdef _WIN32
#pragma once
#endif

#include "shareddefs.h"
#include "const.h"
#include "c_baseentity.h"
#include <igameresources.h>

#define TEAM_ARRAY( index, team )		(index + (team * MAX_CONTROL_POINTS))

//-----------------------------------------------------------------------------
// Purpose: An entity that networks the state of the game's objectives.
//			May contain data for objectives that aren't used by your mod, but
//			the extra data will never be networked as long as it's zeroed out.
//-----------------------------------------------------------------------------
class C_BaseTeamObjectiveResource : public C_BaseEntity
{
	DECLARE_CLASS( C_BaseTeamObjectiveResource, C_BaseEntity );
public:
	DECLARE_CLIENTCLASS();

					C_BaseTeamObjectiveResource();
	virtual			~C_BaseTeamObjectiveResource();

public:
	virtual void	ClientThink();
	virtual void	OnPreDataChanged( DataUpdateType_t updateType );
	virtual void	OnDataChanged( DataUpdateType_t updateType );

	void	UpdateControlPoint( const char *pszEvent, int index = -1 );
	float	GetCPCapPercentage( int index );
	int		GetNumControlPoints( void ) { return m_iNumControlPoints; }
	int		GetNumControlPointsOwned( void );
	void	SetOwningTeam( int index, int team );
	virtual void	SetCappingTeam( int index, int team );
	void	SetCapLayout( const char *pszLayout );

	// Is the point visible in the objective display
	bool	IsCPVisible( int index )
	{
		Assert( index < m_iNumControlPoints );
		return m_bCPIsVisible[index];
	}

	bool	IsCPBlocked( int index )
	{
		Assert( index < m_iNumControlPoints );
		return m_bBlocked[index];
	}

	// Get the world location of this control point
	Vector& GetCPPosition( int index )
	{
		Assert( index < m_iNumControlPoints );
		return m_vCPPositions[index];
	}

	int GetOwningTeam( int index )
	{
		if ( index >= m_iNumControlPoints )
			return TEAM_UNASSIGNED;

		return m_iOwner[index];
	}	

	int GetCappingTeam( int index )
	{
		if ( index >= m_iNumControlPoints )
			return TEAM_UNASSIGNED;

		return m_iCappingTeam[index];
	}

	int GetTeamInZone( int index )
	{
		if ( index >= m_iNumControlPoints )
			return TEAM_UNASSIGNED;

		return m_iTeamInZone[index];
	}

	// Icons
	int GetCPCurrentOwnerIcon( int index, int iOwner )
	{
		Assert( index < m_iNumControlPoints );

		return GetIconForTeam( index, iOwner );
	}

	int GetCPCappingIcon( int index )
	{
		Assert( index < m_iNumControlPoints );

		int iCapper = GetCappingTeam(index);

		Assert( iCapper != TEAM_UNASSIGNED );

		return GetIconForTeam( index, iCapper );;
	}

	// Icon for the specified team
	int GetIconForTeam( int index, int team )
	{
		Assert( index < m_iNumControlPoints );
		return m_iTeamIcons[ TEAM_ARRAY(index,team) ];
	}

	// Overlay for the specified team
	int GetOverlayForTeam( int index, int team )
	{
		Assert( index < m_iNumControlPoints );
		return m_iTeamOverlays[ TEAM_ARRAY(index,team) ];
	}

	// Number of players in the area
	int GetNumPlayersInArea( int index, int team )
	{
		Assert( index < m_iNumControlPoints );
		return m_iNumTeamMembers[ TEAM_ARRAY(index,team) ];
	}
	
	// get the required cappers for the passed team
	int GetRequiredCappers( int index, int team )
	{
		Assert( index < m_iNumControlPoints );
		return m_iTeamReqCappers[ TEAM_ARRAY(index,team) ];
	}

	// Base Icon for the specified team
	int GetBaseIconForTeam( int team )
	{
		Assert( team < MAX_TEAMS );
		return m_iTeamBaseIcons[ team ];
	}

	int GetBaseControlPointForTeam( int iTeam ) 
	{ 
		Assert( iTeam < MAX_TEAMS );
		return m_iBaseControlPoints[iTeam]; 
	}

	int GetPreviousPointForPoint( int index, int team, int iPrevIndex )
	{
		Assert( index < m_iNumControlPoints );
		Assert( iPrevIndex >= 0 && iPrevIndex < MAX_PREVIOUS_POINTS );
		int iIntIndex = iPrevIndex + (index * MAX_PREVIOUS_POINTS) + (team * MAX_CONTROL_POINTS * MAX_PREVIOUS_POINTS);
		return m_iPreviousPoints[ iIntIndex ];
	}

	bool TeamCanCapPoint( int index, int team )
	{
		Assert( index < m_iNumControlPoints );
		return m_bTeamCanCap[ TEAM_ARRAY( index, team ) ];
	}

	const char *GetCapLayoutInHUD( void ) { return m_pszCapLayoutInHUD; }

	bool PlayingMiniRounds( void ){ return m_bPlayingMiniRounds; }
	bool IsInMiniRound( int index ) { return m_bInMiniRound[index]; }

	bool ShouldWarnOnCap( int index )
	{
		Assert( index < m_iNumControlPoints );
		return m_bWarnOnCap[index];
	}

	const char *GetWarnSound( int index )
	{
		Assert( index < m_iNumControlPoints );
		return m_iszWarnSound[index];
	}

	virtual const char *GetGameSpecificCPCappingSwipe( int index, int iCappingTeam )
	{
		// You need to implement this in your game's objective resource.
		Assert(0);
		return NULL;
	}
	virtual const char *GetGameSpecificCPBarFG( int index, int iOwningTeam )
	{
		// You need to implement this in your game's objective resource.
		Assert(0);
		return NULL;
	}
	virtual const char *GetGameSpecificCPBarBG( int index, int iCappingTeam )
	{
		// You need to implement this in your game's objective resource.
		Assert(0);
		return NULL;
	}

	bool CapIsBlocked( int index );

	int		GetTimerToShowInHUD( void ) { return m_iTimerToShowInHUD; }

protected:
	int		m_iTimerToShowInHUD;

	int		m_iNumControlPoints;
	int		m_iPrevNumControlPoints;
	bool	m_bPlayingMiniRounds;
	bool	m_bControlPointsReset;
	bool	m_bOldControlPointsReset;
	int		m_iUpdateCapHudParity;
	int		m_iOldUpdateCapHudParity;

	// data variables
	Vector		m_vCPPositions[MAX_CONTROL_POINTS];
	bool		m_bCPIsVisible[MAX_CONTROL_POINTS];
	float		m_flLazyCapPerc[MAX_CONTROL_POINTS];
	float		m_flOldLazyCapPerc[MAX_CONTROL_POINTS];
	int			m_iTeamIcons[MAX_CONTROL_POINTS * MAX_CONTROL_POINT_TEAMS];
	int			m_iTeamOverlays[MAX_CONTROL_POINTS * MAX_CONTROL_POINT_TEAMS];
	int			m_iTeamReqCappers[MAX_CONTROL_POINTS * MAX_CONTROL_POINT_TEAMS];
	float		m_flTeamCapTime[MAX_CONTROL_POINTS * MAX_CONTROL_POINT_TEAMS];
	int			m_iPreviousPoints[ MAX_CONTROL_POINTS * MAX_CONTROL_POINT_TEAMS * MAX_PREVIOUS_POINTS ];
	bool		m_bTeamCanCap[ MAX_CONTROL_POINTS * MAX_CONTROL_POINT_TEAMS ];
	int			m_iTeamBaseIcons[MAX_TEAMS];
	int			m_iBaseControlPoints[MAX_TEAMS];
	bool		m_bInMiniRound[MAX_CONTROL_POINTS];
	bool		m_bWarnOnCap[MAX_CONTROL_POINTS];
	char		m_iszWarnSound[MAX_CONTROL_POINTS][255];

	// state variables
	int		m_iNumTeamMembers[MAX_CONTROL_POINTS * MAX_CONTROL_POINT_TEAMS];
	int		m_iCappingTeam[MAX_CONTROL_POINTS];
	int		m_iTeamInZone[MAX_CONTROL_POINTS];
	bool	m_bBlocked[MAX_CONTROL_POINTS];
	int		m_iOwner[MAX_CONTROL_POINTS];

	// client calculated state
	float	m_flCapTimeLeft[MAX_CONTROL_POINTS];
	float	m_flCapLastThinkTime[MAX_CONTROL_POINTS];

	bool	m_bWarnedOnFinalCap[MAX_CONTROL_POINTS];
	float	m_flLastCapWarningTime[MAX_CONTROL_POINTS];
	char	m_pszCapLayoutInHUD[MAX_CAPLAYOUT_LENGTH];
};

extern C_BaseTeamObjectiveResource *g_pObjectiveResource;

inline C_BaseTeamObjectiveResource *ObjectiveResource()
{
	return g_pObjectiveResource;
}

#endif // C_TEAM_OBJECTIVERESOURCE_H
