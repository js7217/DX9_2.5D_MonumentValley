#include "Engine_Include.h"
#include "Cube.h"

using namespace ENGINE;

CCube::CCube(LPDIRECT3DDEVICE9 pGraphicDev)
	:CVIBuffer(pGraphicDev)
{
}

CCube::~CCube()
{
	Release();
}

HRESULT CCube::CreateBuffer()
{
	// 큐브 제작.
	m_dwVtxSize = sizeof(VTX_COL);
	m_dwVtxFVF = VTXFVF_COL;
	m_dwVtxCnt = 8;
	m_dwTriCnt = 12;
	
	m_dwIdxSize = sizeof(INDEX32);
	m_IdxFmt = D3DFMT_INDEX32;

	FAILED_CHECK_RETURN(CVIBuffer::CreateBuffer(), E_FAIL);

	VTX_COL* pVtxCol = nullptr;

	m_pVB->Lock(0, 0, (void**)&pVtxCol, 0);

	pVtxCol[0].vPos = { -1.f, 1.f, -1.f };
	pVtxCol[0].dwColor = D3DCOLOR_ARGB(255, 255, 255, 255);
	pVtxCol[1].vPos = { 1.f, 1.f, -1.f };
	pVtxCol[1].dwColor = D3DCOLOR_ARGB(255, 255, 255, 255);
	pVtxCol[2].vPos = { 1.f, -1.f, -1.f };
	pVtxCol[2].dwColor = D3DCOLOR_ARGB(255, 255, 255, 255);
	pVtxCol[3].vPos = { -1.f, -1.f, -1.f };
	pVtxCol[3].dwColor = D3DCOLOR_ARGB(255, 255, 255, 255);

	pVtxCol[4].vPos = { -1.f, 1.f, 1.f };
	pVtxCol[4].dwColor = D3DCOLOR_ARGB(255, 255, 255, 255);
	pVtxCol[5].vPos = { 1.f, 1.f, 1.f };
	pVtxCol[5].dwColor = D3DCOLOR_ARGB(255, 255, 255, 255);
	pVtxCol[6].vPos = { 1.f, -1.f, 1.f };
	pVtxCol[6].dwColor = D3DCOLOR_ARGB(255, 255, 255, 255);
	pVtxCol[7].vPos = { -1.f, -1.f, 1.f };
	pVtxCol[7].dwColor = D3DCOLOR_ARGB(255, 255, 255, 255);

	m_pVB->Unlock();

	INDEX32* pIndex = nullptr;

	m_pIB->Lock(0, 0, (void**)&pIndex, 0);

	// 오른쪽 면
	pIndex[0]._1 = 1;
	pIndex[0]._2 = 5;
	pIndex[0]._3 = 6;

	pIndex[1]._1 = 1;
	pIndex[1]._2 = 6;
	pIndex[1]._3 = 2;

	// 왼쪽 면
	pIndex[2]._1 = 4;
	pIndex[2]._2 = 0;
	pIndex[2]._3 = 3;

	pIndex[3]._1 = 4;
	pIndex[3]._2 = 3;
	pIndex[3]._3 = 7;

	// 위쪽 면
	pIndex[4]._1 = 4;
	pIndex[4]._2 = 5;
	pIndex[4]._3 = 1;

	pIndex[5]._1 = 4;
	pIndex[5]._2 = 1;
	pIndex[5]._3 = 0;

	// 아래쪽 면
	pIndex[6]._1 = 3;
	pIndex[6]._2 = 2;
	pIndex[6]._3 = 6;

	pIndex[7]._1 = 3;
	pIndex[7]._2 = 6;
	pIndex[7]._3 = 7;

	// 앞 면
	pIndex[8]._1 = 0;
	pIndex[8]._2 = 1;
	pIndex[8]._3 = 2;

	pIndex[9]._1 = 0;
	pIndex[9]._2 = 2;
	pIndex[9]._3 = 3;

	// 뒷 면
	pIndex[10]._1 = 5;
	pIndex[10]._2 = 4;
	pIndex[10]._3 = 7;

	pIndex[11]._1 = 5;
	pIndex[11]._2 = 7;
	pIndex[11]._3 = 6;

	m_pIB->Unlock();

	CVIBuffer::GetVtxInfo();

	return S_OK;
}

void CCube::Render()
{
	CVIBuffer::Render();
}

void CCube::Release()
{
}

CCube * CCube::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CCube* pInstance = new CCube(pGraphicDev);

	if (FAILED(pInstance->CreateBuffer()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}
