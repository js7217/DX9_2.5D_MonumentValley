#include "Engine_Include.h"
#include "TerrainInfo.h"

using namespace ENGINE;

CTerrainInfo::CTerrainInfo()
	: m_wCntX(0), m_wCntZ(0), m_wItv(0)
{
}

CTerrainInfo::~CTerrainInfo()
{
}

void CTerrainInfo::SetTerrainInfo(const WORD & wCntX, const WORD & wCntZ, const WORD & wItv)
{
	m_wCntX = wCntX;
	m_wCntZ = wCntZ;
	m_wItv = wItv;
}

const WORD & CTerrainInfo::GetCntX()
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return m_wCntX;
}

const WORD & CTerrainInfo::GetCntZ()
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return m_wCntZ;
}

const WORD & CTerrainInfo::GetItv()
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return m_wItv;
}

CTerrainInfo * CTerrainInfo::Create()
{
	return new CTerrainInfo();
}
