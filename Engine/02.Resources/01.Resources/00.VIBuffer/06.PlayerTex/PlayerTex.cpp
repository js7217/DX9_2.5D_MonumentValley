#include "Engine_Include.h"
#include "PlayerTex.h"

using namespace ENGINE;

CPlayerTex::CPlayerTex(LPDIRECT3DDEVICE9 pGraphicDev)
	:CVIBuffer(pGraphicDev)
{
}

CPlayerTex::~CPlayerTex()
{
	Release();
}

HRESULT CPlayerTex::CreateBuffer()
{
	// 큐브 제작.
	m_dwVtxSize = sizeof(VTX_CUBE);
	m_dwVtxFVF = VTXFVF_CUBE;
	m_dwVtxCnt = 8;
	m_dwTriCnt = 12;
	
	m_dwIdxSize = sizeof(INDEX32);
	m_IdxFmt = D3DFMT_INDEX32;

	FAILED_CHECK_RETURN(CVIBuffer::CreateBuffer(), E_FAIL);

	VTX_CUBE* pVtxCube = nullptr;

	m_pVB->Lock(0, 0, (void**)&pVtxCube, 0);

	pVtxCube[0].vPos = { -1.f, 1.f, -1.f };
	pVtxCube[0].vTex = pVtxCube[0].vPos;

	pVtxCube[1].vPos = { 1.f, 1.f, -1.f };
	pVtxCube[1].vTex = pVtxCube[1].vPos;

	pVtxCube[2].vPos = { 1.f, -1.f, -1.f };
	pVtxCube[2].vTex = pVtxCube[2].vPos;

	pVtxCube[3].vPos = { -1.f, -1.f, -1.f };
	pVtxCube[3].vTex = pVtxCube[3].vPos;

	pVtxCube[4].vPos = { -1.f, 1.f, 1.f };
	pVtxCube[4].vTex = pVtxCube[4].vPos;

	pVtxCube[5].vPos = { 1.f, 1.f, 1.f };
	pVtxCube[5].vTex = pVtxCube[5].vPos;

	pVtxCube[6].vPos = { 1.f, -1.f, 1.f };
	pVtxCube[6].vTex = pVtxCube[6].vPos;

	pVtxCube[7].vPos = { -1.f, -1.f, 1.f };
	pVtxCube[7].vTex = pVtxCube[7].vPos;

	m_pVB->Unlock();

	// 인덱스 버퍼 조작
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

void CPlayerTex::Render()
{
	CVIBuffer::Render();
}

void CPlayerTex::Release()
{
}

CPlayerTex * CPlayerTex::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CPlayerTex* pInstance = new CPlayerTex(pGraphicDev);

	if (FAILED(pInstance->CreateBuffer()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}
