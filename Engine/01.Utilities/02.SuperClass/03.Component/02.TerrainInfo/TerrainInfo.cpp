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
	// TODO: ���⿡ ��ȯ ������ �����մϴ�.
	return m_wCntX;
}

const WORD & CTerrainInfo::GetCntZ()
{
	// TODO: ���⿡ ��ȯ ������ �����մϴ�.
	return m_wCntZ;
}

const WORD & CTerrainInfo::GetItv()
{
	// TODO: ���⿡ ��ȯ ������ �����մϴ�.
	return m_wItv;
}

CTerrainInfo * CTerrainInfo::Create()
{
	return new CTerrainInfo();
}
