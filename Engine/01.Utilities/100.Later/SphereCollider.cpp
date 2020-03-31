#include "SphereCollider.h"
#include "Transform.h"

using namespace ENGINE;

CSphereCollider::CSphereCollider()
	: m_pTransform(nullptr)
	, m_pMatWorld(nullptr)
	, m_pSphereMesh(nullptr)
	, m_bIsColl(true)
{
	
}

CSphereCollider::~CSphereCollider()
{
	//SafeRelease(m_pSphereMesh);
}

void CSphereCollider::SetGraphicDev(LPDIRECT3DDEVICE9 pGraphicDev)
{
	m_pGraphicDev = pGraphicDev;
}

void CSphereCollider::SetCollisionState(bool bState)
{
	m_bIsColl = bState;
}

void CSphereCollider::SetWorld(const D3DXMATRIX* pMatWorld)
{
	m_pMatWorld = pMatWorld;
}

void CSphereCollider::SetTransform(CTransform* pTransform)
{
	m_pTransform = pTransform;
}

void CSphereCollider::SetPos(const D3DXVECTOR3& vPos)
{
	m_pTransform->SetPos(vPos);
}

void CSphereCollider::SetRadius(float fRadius)
{
	m_fRadius = fRadius;
}

float CSphereCollider::GetRadius()
{
	return m_fRadius;
}

D3DXVECTOR3 CSphereCollider::GetPos()
{
	D3DXMATRIX pMatWorld = m_pTransform->GetWorldMatrix();
	D3DXVECTOR3 vPos = { pMatWorld._41, pMatWorld._42, pMatWorld._43 };

	return vPos;
}

void CSphereCollider::Update()
{
	/*VTX_SPHERE* pVtxSphere;
	m_pSphereMesh->LockVertexBuffer(0, (void**)&pVtxSphere);

	D3DXVECTOR3 vPos = m_pTransform->GetPos();

	for (DWORD i = 0; i < m_pSphereMesh->GetNumVertices(); i++)
	{
		D3DXComputeBoundingSphere(&pVtxSphere[i].vPos,
			m_pSphereMesh->GetNumVertices(),
			sizeof(VTX_SPHERE),
			&GetPos(),
			&m_fRadius);

	}
	m_pSphereMesh->UnlockVertexBuffer();*/
}

void CSphereCollider::LateUpdate()
{

}

void CSphereCollider::Render()
{
	/*m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	m_pSphereMesh->DrawSubset(0);

	m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);*/
}

HRESULT CSphereCollider::CreateSphere()
{
	LPD3DXMESH pMeshTmp;

	D3DXCreateSphere(m_pGraphicDev, m_fRadius, 10, 10, &pMeshTmp, nullptr);

	pMeshTmp->CloneMeshFVF(0, VTXFVF_SPHERE, m_pGraphicDev, &m_pSphereMesh);

	VTX_SPHERE* pVtxSphere;
	m_pSphereMesh->LockVertexBuffer(0, (void**)&pVtxSphere);

	for (DWORD i = 0; i < pMeshTmp->GetNumVertices(); i++)
	{

	}

	m_pSphereMesh->UnlockVertexBuffer();

	SafeRelease(pMeshTmp);

	return S_OK;
}

CSphereCollider * CSphereCollider::Create(
	LPDIRECT3DDEVICE9 pGraphicDev,
	CTransform*		  pTransform,
	float			  fRadius)
{
	CSphereCollider* pInstance = new CSphereCollider;

	pInstance->SetGraphicDev(pGraphicDev);
	pInstance->SetTransform(pTransform);
	pInstance->SetRadius(fRadius);

	return pInstance;
}

