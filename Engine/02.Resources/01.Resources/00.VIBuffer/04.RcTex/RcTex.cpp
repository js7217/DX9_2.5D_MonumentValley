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
	m_dwVtxSize = sizeof(VTX_TEX); // ���ؽ��� ������
	m_dwVtxFVF = VTXFVF_TEX;
	m_dwVtxCnt = 4;
	m_dwTriCnt = 2; // ���� 4���� 2�� �ﰢ��. �ε��� 6��

	m_dwIdxSize = sizeof(INDEX32);
	m_IdxFmt = D3DFMT_INDEX32; // �ε��� ������ ����.

	FAILED_CHECK_RETURN(CVIBuffer::CreateBuffer(), E_FAIL);

	VTX_TEX* pVtxTex = nullptr; // ���ؽ� ���� �ʱ�ȭ.

	m_pVB->Lock(0, 0, (void**)&pVtxTex, 0);
	pVtxTex[0].vPos = { -1.f, 1.f, 0.f };
	pVtxTex[0].vTex = { 0.f, 0.f };	// UV ��ǥ.

	pVtxTex[1].vPos = { 1.f, 1.f, 0.f };
	pVtxTex[1].vTex = { 1.f, 0.f };

	pVtxTex[2].vPos = { 1.f, -1.f, 0.f };
	pVtxTex[2].vTex = { 1.f, 1.f };

	pVtxTex[3].vPos = { -1.f, -1.f, 0.f };
	pVtxTex[3].vTex = { 0.f, 1.f };


	m_pVB->Unlock();

	INDEX32* pIndex = nullptr; // �ε��� ���� �ʱ�ȭ.

	//�ð�������� ���ؽ� �� �̿����踦 �����ؾ��Ѵ�.
	m_pIB->Lock(0, 0, (void**)&pIndex, 0);

	// ���ؽ� ����
	//	0	1
	//	3	2
	pIndex[0]._1 = 0;
	pIndex[0]._2 = 1;
	pIndex[0]._3 = 2;

	pIndex[1]._1 = 0;
	pIndex[1]._2 = 2;
	pIndex[1]._3 = 3; // �ε��� ��ȣ�� ���� ���ؽ��� �ð�������� ��ġ���Ѽ� �ﰢ���� ����������.

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
