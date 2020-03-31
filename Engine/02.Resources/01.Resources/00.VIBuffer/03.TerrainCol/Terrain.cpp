#include "Engine_Include.h"
#include "Terrain.h"

using namespace ENGINE;

CTerrain::CTerrain(LPDIRECT3DDEVICE9 pGraphicDev, const WORD & wCntX, const WORD & wCntY, const WORD & wItv)
	:CVIBuffer(pGraphicDev)
	, m_wCntX((DWORD)wCntX), m_wCntY((DWORD)wCntY), m_wItv((DWORD)wItv)
{
}

CTerrain::~CTerrain()
{
	Release();
}

HRESULT CTerrain::CreateBuffer()
{
	// 일단 보류.
	m_dwVtxSize = sizeof(VTX_COL);
	m_dwVtxFVF = VTXFVF_COL;
	m_dwVtxCnt = (DWORD)(m_wCntX * m_wCntY); // 가로 정점 개수 * 세로 정점 개수
	m_dwTriCnt = (DWORD)(((m_wCntX - 1) * (m_wCntY - 1)) * 2); // 가로 - 1 * 세로 -1 * 2
	
	m_dwIdxSize = sizeof(INDEX32);
	m_IdxFmt = D3DFMT_INDEX32;

	FAILED_CHECK_RETURN(CVIBuffer::CreateBuffer(), E_FAIL);

	VTX_COL* pVtxCol = nullptr;

	m_pVB->Lock(0, 0, (void**)&pVtxCol, 0);

	DWORD iVtxIndex = 0;
	for (DWORD i = 0; i < m_wCntY; ++i)
	{
		for (DWORD j = 0; j < m_wCntX; ++j)
		{
			iVtxIndex = j + m_wCntX * i; // 버텍스의 인덱스
			pVtxCol[iVtxIndex].vPos = { (float)(j * m_wItv), -1.f, (float)(i * m_wItv) };
			pVtxCol[iVtxIndex].dwColor = D3DCOLOR_ARGB(255, 255, 255, 255);
		}
	}
	m_pVB->Unlock();

	INDEX32* pIndex = nullptr;

	m_pIB->Lock(0, 0, (void**)&pIndex, 0);

	int iTriIndex = 0;

	iVtxIndex = 0;

	for (WORD i = 0; i < m_wCntY - 1; ++i)
	{
		for (WORD j = 0; j < m_wCntX - 1; ++j)
		{
			iVtxIndex = j + m_wCntX * i;

			pIndex[iTriIndex] = {
				iVtxIndex + m_wCntX, iVtxIndex + m_wCntX + 1,
			iVtxIndex + 1 };

			++iTriIndex;

			pIndex[iTriIndex] = {
				iVtxIndex + m_wCntX, iVtxIndex + 1,
				iVtxIndex };

			++iTriIndex;
		}
	}

	m_pIB->Unlock();

	CVIBuffer::GetVtxInfo();

	return S_OK;
}

void CTerrain::Render()
{
	CVIBuffer::Render();
}

void CTerrain::Release()
{
}

CTerrain* CTerrain::Create(LPDIRECT3DDEVICE9 pGraphicDev, const WORD & wCntX, const WORD & wCntY, const WORD & wItv)
{
	CTerrain* pInstance = new CTerrain(pGraphicDev, wCntX, wCntY, wItv);

	if (FAILED(pInstance->CreateBuffer()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}
