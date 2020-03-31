#include "Engine_Include.h"
#include "RcTex.h"
#include "SetTransform.h"
using namespace ENGINE;

CRcTex::CRcTex(LPDIRECT3DDEVICE9 pGraphicDev)
	:CVIBuffer(pGraphicDev)
{
}

CRcTex::~CRcTex()
{
	Release();
}

HRESULT CRcTex::CreateBuffer()
{
	m_dwVtxSize = sizeof(VTX_TEX); // 버텍스의 사이즈
	m_dwVtxFVF = VTXFVF_TEX;
	m_dwVtxCnt = 4;
	m_dwTriCnt = 2; // 정점 4개로 2개 삼각형. 인덱스 6개

	m_dwIdxSize = sizeof(INDEX32);
	m_IdxFmt = D3DFMT_INDEX32; // 인덱스 버퍼의 포맷.

	FAILED_CHECK_RETURN(CVIBuffer::CreateBuffer(), E_FAIL);

	VTX_TEX* pVtxTex = nullptr; // 버텍스 버퍼 초기화.

	m_pVB->Lock(0, 0, (void**)&pVtxTex, 0);
	pVtxTex[0].vPos = { -1.f, 1.f, 0.f };
	pVtxTex[0].vTex = { 0.f, 0.f };	// UV 좌표.

	pVtxTex[1].vPos = { 1.f, 1.f, 0.f };
	pVtxTex[1].vTex = { 1.f, 0.f };

	pVtxTex[2].vPos = { 1.f, -1.f, 0.f };
	pVtxTex[2].vTex = { 1.f, 1.f };

	pVtxTex[3].vPos = { -1.f, -1.f, 0.f };
	pVtxTex[3].vTex = { 0.f, 1.f };


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

void CRcTex::Render()
{
	CVIBuffer::Render();
}

void CRcTex::Release()
{
}

CRcTex * CRcTex::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CRcTex* pInstance = new CRcTex(pGraphicDev);

	if (FAILED(pInstance->CreateBuffer()))
	{
		ENGINE::SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}
