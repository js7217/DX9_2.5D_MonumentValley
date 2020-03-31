#include "stdafx.h"
#include "Portal.h"
#include "SphereCollider.h"
#include "Transform.h"
#include "SetTransform.h"
#include "Player.h"
#include "Mouse.h"
#include "Block.h"

CPortal::CPortal(LPDIRECT3DDEVICE9 pGraphicDev, tagType eType)
	: ENGINE::CGameObject(pGraphicDev), m_eType(eType)
	, m_pResourceMgr(ENGINE::Get_ResourceMgr())
	, m_pTimeMgr(ENGINE::Get_TimeMgr())
	, m_pManagement(ENGINE::Get_Management())
	, m_pCollisionMgr(CCollisionMgr::GetInstance())
	, m_pTarget(nullptr), m_pTarget_Transform(nullptr), m_pMouse(nullptr)
	, m_bIsActive_Src(true), m_bIsActive_Dst(true)
	, m_pOptimizationList(nullptr), m_bIsStart(false), m_fMoveAngle(0.f)
{
	ZeroMemory(&m_vSrc, sizeof(D3DXVECTOR3));
	ZeroMemory(&m_vDst, sizeof(D3DXVECTOR3));
}

CPortal::~CPortal()
{
	Release();
}

void CPortal::Update()
{
	ENGINE::CGameObject::LateInit();
	ENGINE::CGameObject::Update();

	switch (m_eStage)
	{
	case CPortal::STAGE1:
		Stage1Portal();
		break;
	case CPortal::STAGE2:
		Stage2Portal();
		break;
	case CPortal::STAGE3:
		Stage3Portal();
		break;
	case CPortal::STAGE4:
		Stage4Portal();
		break;
	case CPortal::STAGE5:
		Stage5Portal();
		break;
	default:
		break;
	}

}

void CPortal::LateUpdate()
{
	ENGINE::CGameObject::LateUpdate();
}

void CPortal::Render()
{
	ENGINE::CGameObject::Render();

}

HRESULT CPortal::Initialize()
{
	HRESULT hr = AddComponent();
	FAILED_CHECK_MSG_RETURN(hr, L"AddComponent Failed", E_FAIL);

	switch (m_eType)
	{
	case TRANS:
		break;

	case INTERACT:
		m_pTransform->SetSize({ 1.f, 0.5f, 1.f });
		m_pTransform->SetDir ({ 0.f, 1.f , 0.f });		
		break;

	default:
		break;
	}

	return S_OK;
}

HRESULT CPortal::LateInit()
{
	//Player를 타겟으로 설정
	ENGINE::CGameObject* pObj = nullptr;
	pObj = m_pManagement->GetLst(ENGINE::CLayer::LAYER_ID::OBJECT, L"Player")->front();
	NULL_CHECK_RETURN(pObj, E_FAIL);
	m_pTarget = dynamic_cast<CPlayer*>(pObj);
	//Player의 Transform 들고 있기
	m_pTarget_Transform = dynamic_cast<ENGINE::CTransform*>(m_pTarget->GetComponent(L"Transform"));
	NULL_CHECK_RETURN(m_pTarget_Transform, E_FAIL);

	switch (m_eType)
	{
	case TRANS:
	{
		break;
	}
	case INTERACT:
	{
		m_pMouse = dynamic_cast<CMouse*>(
		m_pManagement->GetLst(ENGINE::CLayer::OBJECT, L"Mouse")->front());
		NULL_CHECK_MSG_RETURN(m_pMouse, L"GetMouse is Failed", E_FAIL);

		m_pOptimizationList = m_pMouse->GetOpMzList();
		for (auto& pVec : *m_pOptimizationList)
		{
			if (m_pOptimizationList->front() == pVec)
				continue;
			for (auto& pBlock : pVec)
			{
				pBlock->Set_Size({ 0.f, 0.f, 0.f });
				pBlock->SetPos({
					  pBlock->Get_CubePos().x
					, pBlock->Get_CubePos().y// - 3.f
					, pBlock->Get_CubePos().z
				});
			}
		}

		break;
	}
	case INTERACT2:
	{
		m_pMouse = dynamic_cast<CMouse*>(
			m_pManagement->GetLst(ENGINE::CLayer::OBJECT, L"Mouse")->front());
		NULL_CHECK_MSG_RETURN(m_pMouse, L"GetMouse is Failed", E_FAIL);

		m_pOptimizationList = m_pMouse->GetOpMzList();
		m_pInteractionList = m_pMouse->GetInterActList();
		break;
	}
	default:
		break;
	}

	return S_OK;
}

void CPortal::Release()
{

}

HRESULT CPortal::AddComponent()
{
	ENGINE::CComponent* pComponent = nullptr;

	//Transform
	m_pTransform = ENGINE::CTransform::Create({ 0.f, 0.f, 1.f });
	NULL_CHECK_RETURN(m_pTransform, E_FAIL);
	m_mapComponent.insert({ L"Transform", m_pTransform });

	//SphereCollider
	m_pSphereCollider = ENGINE::CSphereCollider::Create(m_pGraphicDev, m_pTransform, 0.2f);
	NULL_CHECK_RETURN(m_pSphereCollider, E_FAIL);
	m_pCollisionMgr->AddCollider(L"Button", m_pSphereCollider);
	m_mapComponent.insert({ L"SphereCollider", m_pSphereCollider });

	return S_OK;
}

void CPortal::Stage1Portal()
{
	switch (m_eType)
	{
	case SCENECHANGE:
		if (m_pCollisionMgr->IntersectSphere(0.15f, m_pTarget_Transform->GetPos(), 0.15f, m_vSrc))
		{
			m_pCollisionMgr->SetIsSceneChange(true);
		}
		break;
	case TRANS:
	{
		if (m_pCollisionMgr->IntersectSphere(0.15f, m_pTarget_Transform->GetPos(), 0.15f, m_vSrc))
		{
			if (m_bIsActive_Src)
			{
				m_pTarget_Transform->SetPos(m_pTarget_Transform->GetPos() + (m_vDst - m_vSrc));
				m_bIsActive_Dst = false;
			}
		}
		else
			m_bIsActive_Src = true;


		if (m_pCollisionMgr->IntersectSphere(0.15f, m_pTarget_Transform->GetPos(), 0.15f, m_vDst))
		{
			if (m_bIsActive_Dst)
			{
				m_pTarget_Transform->SetPos(m_pTarget_Transform->GetPos() + (m_vSrc - m_vDst));
				m_bIsActive_Src = false;
			}
		}
		else
			m_bIsActive_Dst = true;
		break;
	}
	default:
		break;
	}
}

void CPortal::Stage2Portal()
{
	switch (m_eType)
	{
	case SCENECHANGE:
		if (m_pCollisionMgr->IntersectSphere(0.15f, m_pTarget_Transform->GetPos(), 0.15f, m_vSrc))
		{
			m_pCollisionMgr->SetIsSceneChange(true);
		}
		break;
	case TRANS:
	{
		if (m_pCollisionMgr->IntersectSphere(0.15f, m_pTarget_Transform->GetPos(), 0.15f, m_vSrc))
		{
			if (m_bIsActive_Src)
			{
				m_pTarget_Transform->SetPos(m_pTarget_Transform->GetPos() + (m_vDst - m_vSrc));
				m_bIsActive_Dst = false;
			}
		}
		else
			m_bIsActive_Src = true;


		if (m_pCollisionMgr->IntersectSphere(0.15f, m_pTarget_Transform->GetPos(), 0.15f, m_vDst))
		{
			if (m_bIsActive_Dst)
			{
				m_pTarget_Transform->SetPos(m_pTarget_Transform->GetPos() + (m_vSrc - m_vDst));
				m_bIsActive_Src = false;
			}
		}
		else
			m_bIsActive_Dst = true;

		break;
	}
	case INTERACT:
	{
		if (m_pCollisionMgr->IntersectSphere(0.5f, m_pTarget_Transform->GetPos(), 0.5f, m_pTransform->GetPos()))
			m_bIsStart = true;

		if (m_bIsStart)
		{
			list<vector<CBlock*>>::iterator iter = m_pOptimizationList->begin();
			list<vector<CBlock*>>::iterator iter_end = m_pOptimizationList->end();
			for (iter; iter != m_pOptimizationList->end(); ++iter)
			{
				//BOOL bCheck = FALSE;
				if (m_pOptimizationList->front() == (*iter))
				{
					//++iter;
					continue;
				}

				for (auto& pBlock : *iter)
				{
					if (0.9999f <= pBlock->GetDeltaValue())
					{
						//if ((*iter)[0] == pBlock)
						//bCheck = TRUE;
						m_bIsStart = false;
						continue;
					}

					if ((*iter)[2] == pBlock)
					{
						pBlock->SetDeltaValue(1.f * fabs(sinf((0.5f) * pBlock->GetDeltaCount())));
						pBlock->SetDeltaCount(pBlock->GetDeltaCount() + m_pTimeMgr->GetDeltaTime());

						pBlock->SetPos(D3DXVECTOR3(
							pBlock->Get_CubePos().x
							, -0.5f + 0.f * pBlock->GetDeltaValue()
							, pBlock->Get_CubePos().z
						));

						pBlock->Set_Size(D3DXVECTOR3(
							1.f * ceil(pBlock->GetDeltaValue())
							, 1.f *      pBlock->GetDeltaValue()
							, 1.f * ceil(pBlock->GetDeltaValue())
						));
					}

					if ((*iter)[1] == pBlock)
					{
						pBlock->SetDeltaValue(1.f * fabs(sinf((0.5f) * pBlock->GetDeltaCount())));
						pBlock->SetDeltaCount(pBlock->GetDeltaCount() + m_pTimeMgr->GetDeltaTime());

						pBlock->SetPos(D3DXVECTOR3(
							pBlock->Get_CubePos().x
							, -0.5f + 1.0f * pBlock->GetDeltaValue()
							, pBlock->Get_CubePos().z
						));

						pBlock->Set_Size(D3DXVECTOR3(
							1.f * ceil(pBlock->GetDeltaValue())
							, 1.f *      pBlock->GetDeltaValue()
							, 1.f * ceil(pBlock->GetDeltaValue())
						));
					}

					if ((*iter)[0] == pBlock)
					{
						pBlock->SetDeltaValue(1.f * fabs(sinf((0.5f) * pBlock->GetDeltaCount())));
						pBlock->SetDeltaCount(pBlock->GetDeltaCount() + m_pTimeMgr->GetDeltaTime());

						pBlock->SetPos(D3DXVECTOR3(
							pBlock->Get_CubePos().x
							, -0.5f + 2.0f * pBlock->GetDeltaValue()
							, pBlock->Get_CubePos().z
						));

						pBlock->Set_Size(D3DXVECTOR3(
							1.f * ceil(pBlock->GetDeltaValue())
							, 1.f *      pBlock->GetDeltaValue()
							, 1.f * ceil(pBlock->GetDeltaValue())
						));
					}
				}

				//if (bCheck)
				//++iter;
			}
		}
		break;
	}
	case INTERACT2:
	{
		if (m_pCollisionMgr->IntersectSphere(0.5f, m_pTarget_Transform->GetPos(), 0.5f, m_pTransform->GetPos()))
			m_bIsStart = true;

		if (m_bIsStart)
		{
			for (auto& pVec : *m_pOptimizationList)
			{
				if (m_pOptimizationList->front() == pVec)
				{
					for (auto& pBlock : pVec)
					{
						if (3.999f <= pBlock->GetDeltaCount())
							continue;

						float fSpeed = 1.f;
						pBlock->SetDeltaCount(pBlock->GetDeltaCount() + m_pTimeMgr->GetDeltaTime());

						pBlock->SetPos(D3DXVECTOR3(
							pBlock->Get_CubePos().x
							, pBlock->Get_CubePos().y + m_pTimeMgr->GetDeltaTime() * fSpeed
							, pBlock->Get_CubePos().z));
					}
				}
			}
		}

		break;
	}

	default:
		break;
	}
}

void CPortal::Stage3Portal()
{
	if (m_pCollisionMgr->IntersectSphere(0.15f, m_pTarget_Transform->GetPos(), 0.3f, D3DXVECTOR3(11.5f, 7.5f, 7.5)))
	{
		m_pTarget->Set_bIsCollCube(false);
	}

	if (m_pCollisionMgr->IntersectSphere(0.15f, m_pTarget_Transform->GetPos(), 0.13f, D3DXVECTOR3(4.5f, 13.5f, 1.5)))
	{
		m_pTarget->Set_bIsCollCube(true);

	}


	switch (m_eType)
	{
	case CPortal::SCENECHANGE:
		if (m_pCollisionMgr->IntersectSphere(0.5f, m_pTarget_Transform->GetPos(), 0.5f, m_vSrc))
		{
			m_pCollisionMgr->SetIsSceneChange(true);
		}
		break;
	case CPortal::TRANS:
		if (m_pCollisionMgr->IntersectSphere(0.15f, m_pTarget_Transform->GetPos(), 0.15f, m_vSrc))
		{
			if (m_bIsActive_Src)
			{
				m_pTarget_Transform->SetPos(m_pTarget_Transform->GetPos() + (m_vDst - m_vSrc));
				m_bIsActive_Dst = false;
			}
		}
		else
			m_bIsActive_Src = true;


		if (m_pCollisionMgr->IntersectSphere(0.15f, m_pTarget_Transform->GetPos(), 0.15f, m_vDst))
		{
			if (m_bIsActive_Dst)
			{
				m_pTarget_Transform->SetPos(m_pTarget_Transform->GetPos() + (m_vSrc - m_vDst));
				m_bIsActive_Src = false;
			}
		}
		else
			m_bIsActive_Dst = true;
		break;
	case CPortal::INTERACT:
		break;
	case CPortal::INTERACT2:
		if (m_pCollisionMgr->IntersectSphere(0.5f, m_pTarget_Transform->GetPos(), 0.5f, m_pTransform->GetPos()))
			m_bIsStart = true;

		if (m_bIsStart && m_fMoveAngle <= 90.f)
		{
			for (auto& vecCube : *m_pOptimizationList)
			{
				for (auto& pCube : vecCube)
				{
					pCube->Set_bIsSelected(true);
					m_fMoveAngle += 10.f * m_pTimeMgr->GetDeltaTime();
					pCube->SetTargetAngle(m_fMoveAngle);
				}
			}
		}
		else
			for (auto& vecCube : *m_pOptimizationList)
			{
				for (auto& pCube : vecCube)
					pCube->Set_bIsSelected(false); // 마우스로 움직이지 못하게 막아버린다.
			}
		break;
	default:
		break;
	}
}

void CPortal::Stage4Portal()
{
	switch (m_eType)
	{
	case CPortal::SCENECHANGE:
		if (m_pCollisionMgr->IntersectSphere(0.3f, m_pTarget_Transform->GetPos(), 0.3f, m_vSrc))
		{
			m_pCollisionMgr->SetIsSceneChange(true);
		}
		break;
	case CPortal::TRANS:
		if (m_pCollisionMgr->IntersectSphere(0.15f, m_pTarget_Transform->GetPos(), 0.15f, m_vSrc))
		{
			if (m_bIsActive_Src)
			{
				m_pTarget_Transform->SetPos(m_pTarget_Transform->GetPos() + (m_vDst - m_vSrc));
				m_bIsActive_Dst = false;
			}
		}
		else
			m_bIsActive_Src = true;


		if (m_pCollisionMgr->IntersectSphere(0.15f, m_pTarget_Transform->GetPos(), 0.15f, m_vDst))
		{
			if (m_bIsActive_Dst)
			{
				m_pTarget_Transform->SetPos(m_pTarget_Transform->GetPos() + (m_vSrc - m_vDst));
				m_bIsActive_Src = false;
			}
		}
		else
			m_bIsActive_Dst = true;
		break;
	case CPortal::INTERACT:
		break;
	case CPortal::INTERACT2:
		if (m_pCollisionMgr->IntersectSphere(0.5f, m_pTarget_Transform->GetPos(), 0.5f, m_pTransform->GetPos()))
		{
			m_bIsStart = true;
			m_pCollisionMgr->SetIsStair3(true);
		}

		if (m_bIsStart && m_fMoveAngle < 90.f)
		{
			for (auto& vecCubeList : *m_pInteractionList)
			{
				m_fMoveAngle += 10.f * m_pTimeMgr->GetDeltaTime();
				if (vecCubeList == m_pInteractionList->front())
				{
					for (auto& vecCube : vecCubeList)
					{
						for (auto& pCube : vecCube)
						{
							pCube->Set_bIsSelected(true);
							
							pCube->SetTargetAngle(m_fMoveAngle);
						}
					}
				}
				else
				{
					for (auto& vecCube : vecCubeList)
					{
						for (auto& pCube : vecCube)
						{
							pCube->Set_bIsSelected(true);
							pCube->SetTargetAngle(-m_fMoveAngle);
						}
					}
				}
			}
		}
		else
		{
			for (auto& vecCubeList : *m_pInteractionList)
			{
				for (auto& vecCube : vecCubeList)
				{
					for (auto& pCube : vecCube)
						pCube->Set_bIsSelected(false);
				}
			}
		}
		break;
	default:
		break;
	}
}

void CPortal::Stage5Portal()
{
	switch (m_eType)
	{
	case CPortal::SCENECHANGE:
		if (m_pCollisionMgr->IntersectSphere(0.15f, m_pTarget_Transform->GetPos(), 0.15f, m_vSrc))
		{

			m_pCollisionMgr->SetIsSceneChange(true);
		}
		break;
	case CPortal::TRANS:
		/////////////////////////////////////////////////////////////////////////////
		if (m_pCollisionMgr->IntersectSphere(0.15f, m_pTarget_Transform->GetPos(), 0.3f, D3DXVECTOR3(2.5f, 8.5f, 9.5f)))
		{
			m_pTarget->Set_bIsCollCube(false);
		}

		if (m_pCollisionMgr->IntersectSphere(0.15f, m_pTarget_Transform->GetPos(), 0.3f, D3DXVECTOR3(5.5f, 6.5f, 11.5f)))
		{
			m_pTarget->Set_bIsCollCube(true);
		}
		/////////////////////////////////////////////////////////////////////////////


		/////////////////////////////////////////////////////////////////////////////
		if (m_pCollisionMgr->IntersectSphere(0.15f, m_pTarget_Transform->GetPos(), 0.3f, D3DXVECTOR3(11.5f, 4.5f, 6.5f)))
		{
			m_pTarget->Set_bIsCollCube(false);
		}

		if (m_pCollisionMgr->IntersectSphere(0.15f, m_pTarget_Transform->GetPos(), 0.3f, D3DXVECTOR3(6.5f, 8.5f, 2.5f)))
		{
			m_pTarget->Set_bIsCollCube(true);
		}
		/////////////////////////////////////////////////////////////////////////////


		/////////////////////////////////////////////////////////////////////////////
		if (m_pCollisionMgr->IntersectSphere(0.15f, m_pTarget_Transform->GetPos(), 0.3f, D3DXVECTOR3(2.5f, 6.5f, 12.5f)))
		{
			m_pTarget->Set_bIsCollCube(false);
		}

		if (m_pCollisionMgr->IntersectSphere(0.15f, m_pTarget_Transform->GetPos(), 0.3f, D3DXVECTOR3(4.5f, 5.5f, 13.5f)))
		{
			m_pTarget->Set_bIsCollCube(true);
		}
		/////////////////////////////////////////////////////////////////////////////


		if (m_pCollisionMgr->IntersectSphere(0.15f, m_pTarget_Transform->GetPos(), 0.15f, m_vSrc))
		{

			if (m_bIsActive_Src)
			{
				m_pTarget_Transform->SetPos(m_pTarget_Transform->GetPos() + (m_vDst - m_vSrc));
				m_bIsActive_Dst = false;

			}
		}
		else
		{
			m_bIsActive_Src = true;

		}


		if (m_pCollisionMgr->IntersectSphere(0.15f, m_pTarget_Transform->GetPos(), 0.15f, m_vDst))
		{

			if (m_bIsActive_Dst)
			{
				m_pTarget_Transform->SetPos(m_pTarget_Transform->GetPos() + (m_vSrc - m_vDst));
				m_bIsActive_Src = false;

			}
		}
		else
		{
			m_bIsActive_Dst = true;
			//m_pTarget->Set_bIsCollCube(true);
		}
		break;
	}
}

void CPortal::SetStage(tagStage eStage)
{
	m_eStage = eStage;
}

void CPortal::SetEntrance(D3DXVECTOR3 pSrc, D3DXVECTOR3 pDst)
{
	m_vSrc = pSrc;
	m_vDst = pDst;
}

void CPortal::SetPos(D3DXVECTOR3 vPos)
{
	m_pTransform->SetPos(vPos);
}

CPortal * CPortal::Create(LPDIRECT3DDEVICE9 pGraphicDev, tagType eType, tagStage eStage,
	D3DXVECTOR3 pSrc, D3DXVECTOR3 pDst)
{
	CPortal* pInstance = new CPortal(pGraphicDev, eType);

	if (FAILED(pInstance->Initialize()))
	{
		ENGINE::SafeDelete(pInstance);
		return nullptr;
	}

	pInstance->SetEntrance(pSrc, pDst);
	pInstance->SetStage(eStage);

	return pInstance;
}

CPortal * CPortal::Create(LPDIRECT3DDEVICE9 pGraphicDev, tagType eType, tagStage eStage)
{
	CPortal* pInstance = new CPortal(pGraphicDev, eType);

	if (FAILED(pInstance->Initialize()))
	{
		ENGINE::SafeDelete(pInstance);
		return nullptr;
	}

	pInstance->SetStage(eStage);

	return pInstance;
}

