#pragma once

#ifndef __TERRAININFO_H__
#define __TERRAININFO_H__

#include "Component.h"

BEGIN(ENGINE)

class ENGINE_DLL CTerrainInfo : public CComponent
{
private:
	explicit CTerrainInfo();

public:
	virtual ~CTerrainInfo();

public:
	void SetTerrainInfo(const WORD& wCntX, const WORD& wCntZ, const WORD& wItv);

public:
	const WORD& GetCntX();
	const WORD& GetCntZ();
	const WORD& GetItv();
public:
	static CTerrainInfo* Create();
private:
	WORD m_wCntX; // 가로 방향 정점 개수
	WORD m_wCntZ; // 세로 방향 정점 개수
	WORD m_wItv; // 정점간의 간격
};

END


#endif