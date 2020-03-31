#include "Engine_Include.h"
#include "RcCol.h"

using namespace ENGINE;

CRcCol::CRcCol(LPDIRECT3DDEVICE9 pGraphicDev)
	:CVIBuffer(pGraphicDev)
{
}

CRcCol::~CRcCol()
{
	Release();
}

HRESULT CRcCol::CreateBuffer()
{
	m_dwVtxSize = sizeof(VTX_COL); // 버텍스의 사이즈
	m_dwVtxFVF = VTXFVF_COL;
	m_dwVtxCnt = 4;
	m_dwTriCnt = 2; // 정점 4개로 2개 삼각형. 인덱스 6개

	m_dwIdxSize = sizeof(INDEX32);
	m_IdxFmt = D3DFMT_INDEX32; // 인덱스 버퍼의 포맷.

	FAILED_CHECK_RETURN(CVIBuffer::CreateBuffer(), E_FAIL);

	VTX_COL* pVtxCol = nullptr; // 버텍스 버퍼 초기화.

	m_pVB->Lock(0, 0, (void**)&pVtxCol, 0);

	pVtxCol[0].vPos = { -0.5f, 0.5f, 0.f };
	pVtxCol[0].dwColor = D3DCOLOR_ARGB(255, 255, 0, 0);

	pVtxCol[1].vPos = { 0.5f, 0.5f, 0.f };
	pVtxCol[1].dwColor = D3DCOLOR_ARGB(255, 0, 255, 0);

	pVtxCol[2].vPos = { 0.5f, -0.5f, 0.f };
	pVtxCol[2].dwColor = D3DCOLOR_ARGB(255, 0, 0, 255);

	pVtxCol[3].vPos = { -0.5f, -0.5f, 0.f };
	pVtxCol[3].dwColor = D3DCOLOR_ARGB(255, 255, 0, 0);


	m_pVB->Unlock();

	INDEX32* pIndex = nullptr; // 인덱스 버퍼 초기화.

	//시계방향으로 버텍스 간 이웃관계를 형성해야한다.
	m_pIB->Lock(0, 0, (void**)&pIndex, 0);

	// 버텍스 순서
	//	0	1
	//	3	2
	pIndex[0]._1 = 0;
	pIndex[0]._2 = 1;
	pIndex[0]._3 = 2;

	pIndex[1]._1 = 0;
	pIndex[1]._2 = 2;
	pIndex[1]._3 = 3; // 인덱스 번호를 위의 버텍스와 시계방향으로 일치시켜서 삼각형을 만들어줘야함.

	m_pIB->Unlock();

	CVIBuffer::GetVtxInfo();

	return S_OK;
}

void CRcCol::Render()
{
	CVIBuffer::Render();
}

void CRcCol::Release()
{
}

CRcCol * CRcCol::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CRcCol* pInstance = new CRcCol(pGraphicDev);

	if (FAILED(pInstance->CreateBuffer()))
	{
		ENGINE::SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}
