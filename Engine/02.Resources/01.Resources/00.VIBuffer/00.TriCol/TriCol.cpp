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
	m_dwTriCnt = 1; // ���� 3���� �ﰢ�� 1��
	FAILED_CHECK_RETURN(CVIBuffer::CreateBuffer(), E_FAIL); // �θ��� CreateBuffer�� �̿��Ͽ� m_pVB�� �ʱ�ȭ�Ѵ�.
	
	VTX_COL* pVtxCol = nullptr;

	m_pVB->Lock(0, 0, (void**)&pVtxCol, 0);
	//1 : ������ ������, 2 : 0�� �迭 ���θ� �ǹ�, 3 : �ƿ�ǲ, ���� �� ������ �����°�, 4: ���� Ÿ��

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
