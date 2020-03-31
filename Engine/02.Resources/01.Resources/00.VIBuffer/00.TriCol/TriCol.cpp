#include "Engine_Include.h"
#include "TriCol.h"

using namespace ENGINE;

CTriCol::CTriCol(LPDIRECT3DDEVICE9 pGraphicDev)
	:CVIBuffer(pGraphicDev)
{
}

CTriCol::~CTriCol()
{
	Release();
}

HRESULT CTriCol::CreateBuffer()
{
	m_dwVtxSize = sizeof(VTX_COL);
	m_dwVtxFVF = VTXFVF_COL;
	m_dwVtxCnt = 3;
	m_dwTriCnt = 1; // 정점 3개당 삼각형 1개
	FAILED_CHECK_RETURN(CVIBuffer::CreateBuffer(), E_FAIL); // 부모의 CreateBuffer를 이용하여 m_pVB를 초기화한다.
	
	VTX_COL* pVtxCol = nullptr;

	m_pVB->Lock(0, 0, (void**)&pVtxCol, 0);
	//1 : 버퍼의 시작점, 2 : 0은 배열 전부를 의미, 3 : 아웃풋, 락을 건 정점을 얻어오는것, 4: 버퍼 타입

	pVtxCol[0].vPos = { 0.f, 1.f, 0.f };
	pVtxCol[0].dwColor = D3DCOLOR_ARGB(255, 255, 0, 0);

	pVtxCol[1].vPos = { 1.f, -1.f, 0.f };
	pVtxCol[1].dwColor = D3DCOLOR_ARGB(255, 0, 255, 0);

	pVtxCol[2].vPos = { -1.f, -1.f, 0.f };
	pVtxCol[2].dwColor = D3DCOLOR_ARGB(255, 0, 0, 255);

	m_pVB->Unlock();

	CVIBuffer::GetVtxInfo();
	
	return S_OK;
}

void CTriCol::Render()
{
	CVIBuffer::Render();
}

void CTriCol::Release()
{
}

CTriCol * CTriCol::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CTriCol* pInstance = new CTriCol(pGraphicDev);

	if (FAILED(pInstance->CreateBuffer()))
	{
		ENGINE::SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}
