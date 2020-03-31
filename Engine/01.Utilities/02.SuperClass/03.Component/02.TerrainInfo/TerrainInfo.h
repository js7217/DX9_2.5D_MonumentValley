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
	WORD m_wCntX; // ���� ���� ���� ����
	WORD m_wCntZ; // ���� ���� ���� ����
	WORD m_wItv; // �������� ����
};

END


#endif