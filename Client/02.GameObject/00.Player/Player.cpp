#include "stdafx.h"
#include "Player.h"
#include "Texture.h"
#include "VIBuffer.h"
#include "TerrainTex.h"
#include "TerrainInfo.h"
#include "RcTex.h"
#include "Transform.h"
#include "SetTransform.h"
#include "CollTerrain.h"
#include "CollMouse.h"
#include "CollCube.h"
#include "SphereCollider.h"
#include "StaticCamera.h"
#include "Block.h"
#include "KeyMgr.h"

CPlayer::CPlayer(LPDIRECT3DDEVICE9 pGraphicDev)
	: ENGINE::CGameObject(pGraphicDev)
	, m_pResourceMgr(ENGINE::Get_ResourceMgr())
	, m_pTimeMgr(ENGINE::Get_TimeMgr())
	, m_pManagement(ENGINE::Get_Management())
	, m_pCollisionMgr(CCollisionMgr::GetInstance())
	, m_pKeyMgr(ENGINE::CKeyMgr::GetInstance())
	, m_pBuffer(nullptr), m_pTexture(nullptr), m_pTransform(nullptr)
	, m_pCollTerrain(nullptr), m_pCollMouse(nullptr)
	, m_bIsMove(false), m_bIsDestination(false),m_CollYValue(0.4f)
{
	D3DXVec3Normalize(&m_vMousePos, &m_vMousePos);

	m_vRayDir = { 0.f, -1.f, 0.f };
}

CPlayer::~CPlayer()
{
	Release();
}

ENGINE::CTransform * CPlayer::GetTransform()
{
	return m_pTransform;
}

void CPlayer::Update()
{
	ENGINE::CGameObject::LateInit();
	ENGINE::CGameObject::Update();

	m_pCollisionMgr->CollisionSphere(L"Player", L"Block");
}

void CPlayer::LateUpdate()
{
	ENGINE::CGameObject::LateUpdate();
	KeyInput();
	//	MovePlayer();
	if (m_bOnOffCollCube)
	{
		CollCube();

	}
}

void CPlayer::Render()
{
	m_pGraphicDev->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	m_pGraphicDev->SetRenderState(D3DRS_ALPHAREF, 1);
	m_pGraphicDev->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	ENGINE::CSetTransForm::Set_TransForm(D3DTS_WORLD, &m_pTransform->GetWorldMatrix());

	//	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pTransform->GetWorldMatrix());
	//	m_pBuffer->Set_Transform();

	//m_pTexture->Render(0);
	//m_pBuffer->Render();

	m_pGraphicDev->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

HRESULT CPlayer::Initialize()
{
	HRESULT hr = AddComponent();
	FAILED_CHECK_MSG_RETURN(hr, L"AddComponent Failed", E_FAIL);

	m_pTransform->SetPos({ 1.5f, 5.0f, 2.07f });
	m_pTransform->SetDir({ 0.f, 0.f, 1.f });
	m_pTransform->SetSize({ 1.f, 1.f, 1.f });


	return S_OK;
}

HRESULT CPlayer::LateInit()
{
	//ENGINE::CVIBuffer* pTerrainBuffer = dynamic_cast<ENGINE::CVIBuffer*>(
	//	m_pManagement->GetComponent(ENGINE::CLayer::OBJECT, L"Terrain", L"Buffer"));
	//// 터레인 버퍼를 Management의 GetComponent 함수로 가져온다.
	//NULL_CHECK_RETURN(pTerrainBuffer, E_FAIL);

	//ENGINE::CTerrainInfo* pTerrainInfo = dynamic_cast<ENGINE::CTerrainInfo*>(
	//	m_pManagement->GetComponent(ENGINE::CLayer::OBJECT, L"Terrain", L"TerrainInfo"));

	//m_pCollMouse->SetTerrainInfo(pTerrainInfo); // 터레인 정보를 가져와야 계산이 가능하다.

	//WORD wCntX = pTerrainInfo->GetCntX();
	//WORD wCntY = pTerrainInfo->GetCntZ();
	//WORD wItv = pTerrainInfo->GetItv(); // 터레인 정보.

	//m_pCollTerrain->SetTargetInfo(m_pTransform, pTerrainBuffer);
	//m_pCollTerrain->SetTerrainInfo(wCntX, wCntY, wItv);
	//// 가져온 터레인 버퍼의 주소값을 CollTerrain 컴포턴트에 Set시켜준다.

	////큐브 타기
	//list<ENGINE::CGameObject*>* pLst = m_pManagement->GetLst(ENGINE::CLayer::OBJECT, L"Block");
	//m_pCollCube->SetTargetInfo(m_pTransform, pLst);

	return S_OK;
}

void CPlayer::Release()
{
}

void CPlayer::SetState(bool bState)
{
	m_bIsDestination = bState;
}

bool CPlayer::GetState()
{
	return m_bIsDestination;
}

HRESULT CPlayer::AddComponent()
{
	ENGINE::CComponent* pComponent = nullptr;

	//Transform
	m_pTransform = ENGINE::CTransform::Create({ 0.f, 0.f, 1.f });
	NULL_CHECK_RETURN(m_pTransform, E_FAIL);
	m_mapComponent.insert({ L"Transform", m_pTransform });

	//////CollCube
	//m_pCollCube = CCollCube::Create(ENGINE::CCollision::COLL_END);
	//NULL_CHECK_RETURN(m_pCollCube, E_FAIL);
	//m_mapComponent.insert({ L"CollCube", m_pCollCube });

	////CollTerrain
	//m_pCollTerrain = CCollTerrain::Create(ENGINE::CCollision::TERRAIN);
	//NULL_CHECK_RETURN(m_pCollTerrain, E_FAIL);
	//m_mapComponent.insert({ L"CollTerrain", m_pCollTerrain });

	////SphereCollider
	//m_pSphereCollider = ENGINE::CSphereCollider::Create(m_pGraphicDev, m_pTransform, 0.2f);
	//NULL_CHECK_RETURN(m_pSphereCollider, E_FAIL);
	//m_pCollisionMgr->AddCollider(L"Player", m_pSphereCollider);
	//m_mapComponent.insert({ L"SphereCollider", m_pSphereCollider });

	//CollMouse
	m_pCollMouse = CCollMouse::Create();
	NULL_CHECK_RETURN(m_pCollMouse, E_FAIL);
	m_mapComponent.insert({ L"CollMouse", m_pCollMouse });

	return S_OK;
}

void CPlayer::KeyInput()
{
	D3DXVECTOR3 vPos, vDir, pOut;
	vPos = m_pTransform->GetPos();
	m_vPrePos = vPos;

	float fAngleY = m_pTransform->GetAngle(ENGINE::ANGLE_Y);

	if (m_pKeyMgr->KeyPressing(KEY_U))
	{
		vPos.y += 2.f * m_pTimeMgr->GetDeltaTime();
	}

	if (m_pKeyMgr->KeyPressing(KEY_J))
	{
		vPos.y -= 2.f * m_pTimeMgr->GetDeltaTime();

	}
	if (m_pKeyMgr->KeyPressing(KEY_UP))
	{
		if (m_bChangeStair == false)
		{
			vDir = { 0.f, 0.f, 1.f };
			fAngleY = 0.f;
			vPos += vDir * 2.f * m_pTimeMgr->GetDeltaTime();
			m_fTimeCnt += m_pTimeMgr->GetDeltaTime();
		}
		else
		{
			vPos.y += 2.f * m_pTimeMgr->GetDeltaTime();
			m_fTimeCnt += m_pTimeMgr->GetDeltaTime();
		}

	}

	if (m_pKeyMgr->KeyPressing(KEY_DOWN))
	{
		if (m_bChangeStair == false)
		{
			vDir = { 0.f, 0.f, -1.f };
			fAngleY = 180.f;

			vPos += vDir * 2.f * m_pTimeMgr->GetDeltaTime();
			m_fTimeCnt += m_pTimeMgr->GetDeltaTime();
		}
		else
		{
			vPos.y -= 2.f * m_pTimeMgr->GetDeltaTime();
			m_fTimeCnt += m_pTimeMgr->GetDeltaTime();
		}
	}

	if (m_pKeyMgr->KeyPressing(KEY_LEFT))
	{
		if (m_bChangeStair == false)
		{
			vDir = { -1.f, 0.f, 0.f };
			fAngleY = 270.f;

			vPos += vDir * 2.f * m_pTimeMgr->GetDeltaTime();
			m_fTimeCnt += m_pTimeMgr->GetDeltaTime();
		}
		else
		{
			vPos.y -= 2.f * m_pTimeMgr->GetDeltaTime();
			m_fTimeCnt += m_pTimeMgr->GetDeltaTime();
		}
	}

	if (m_pKeyMgr->KeyPressing(KEY_RIGHT))
	{
		if (m_bChangeStair == false)
		{
			vDir = { 1.f, 0.f, 0.f };
			fAngleY = 90.f;

			vPos += vDir * 2.f * m_pTimeMgr->GetDeltaTime();
			m_fTimeCnt += m_pTimeMgr->GetDeltaTime();
		}
		else
		{
			vPos.y += 2.f * m_pTimeMgr->GetDeltaTime();
			m_fTimeCnt += m_pTimeMgr->GetDeltaTime();
		}
	}

	if (m_pKeyMgr->KeyUp(KEY_RIGHT) || m_pKeyMgr->KeyUp(KEY_UP) ||
		m_pKeyMgr->KeyUp(KEY_DOWN) || m_pKeyMgr->KeyUp(KEY_LEFT))
	{
		m_fTimeCnt = 0.f;
	}

	if (GetAsyncKeyState('A') & 0x8000)
	{
		fAngleY += 1.f;
	}
	if (GetAsyncKeyState('D') & 0x8000)
	{
		fAngleY -= 1.f;
	}

	/*if (m_pKeyMgr->KeyDown(KEY_O))
	{
		if (m_bOnOffCollCube)
			m_bOnOffCollCube = !m_bOnOffCollCube;
		else
			m_bOnOffCollCube = !m_bOnOffCollCube;

	}*/

	//if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	//{
	//	ENGINE::CVIBuffer* pTerrainBuffer = dynamic_cast<ENGINE::CVIBuffer*>(
	//		m_pManagement->GetComponent(ENGINE::CLayer::OBJECT, L"Terrain", L"Buffer"));
	//	ENGINE::VTX_TEX* pTerrainVtx = (ENGINE::VTX_TEX*)pTerrainBuffer->GetOriginVtxInfo();

	//	m_bIsMove = m_pCollMouse->PickTerrain(&m_vMousePos, pTerrainVtx);
	//}

	//	vPos = m_pTransform->GetPos();
	m_pTransform->SetPos(vPos);
	m_pTransform->SetAngle(fAngleY, ENGINE::ANGLE_Y);
}

void CPlayer::MovePlayer()
{
	if (!m_bIsMove)
		return;

	D3DXVECTOR3 vPos = m_pTransform->GetPos();
	//D3DXVECTOR3 vDir = m_pTransform->GetDir();


	D3DXVECTOR3 vDir = m_vMousePos - vPos;

	float fDist = D3DXVec3Length(&vDir);
	D3DXVec3Normalize(&vDir, &vDir);

	if (0.1f > fDist)
	{
		m_bIsMove = false;

	}

	vPos += vDir * 10.f * m_pTimeMgr->GetDeltaTime();

	m_pTransform->SetPos(vPos);
}

float * CPlayer::GetTimeCnt()
{
	return &m_fTimeCnt;
}

list<CBlock*>& CPlayer::Get_CubeList()
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return m_CubeList;
}



CPlayer * CPlayer::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CPlayer* pInstance = new CPlayer(pGraphicDev);

	if (FAILED(pInstance->Initialize()))
	{
		ENGINE::SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CPlayer::Translation_ViewSpace()
{
	m_vOriginRay = m_pTransform->GetPos();
}


bool CPlayer::CollCube()
{
	if (m_CubeList.empty())
		return false;
	Translation_ViewSpace();
	map<float, D3DXVECTOR3> mapTemp;
	int i = 0;

	for (auto& pCube : m_CubeList)
	{
		i++;
		ENGINE::VTX_CUBE* pCubeVtx = (ENGINE::VTX_CUBE*)pCube->Get_Buffer()->GetOriginVtxInfo();
		D3DXMATRIX WorldMatrix = pCube->Get_Transform()->GetWorldMatrix();
		ENGINE::VTX_CUBE CompareVtx[8] = {};

		for (int i = 0; i < 8; i++)
		{
			D3DXVec3TransformCoord(&CompareVtx[i].vPos, &pCubeVtx[i].vPos, &WorldMatrix);
		}



		float fU = 0.f, fV = 0.f, fDist = 0.f;

		//ex) 위에서 포인트를 찍었을떄 위면 아랫면이 동시에 통과되니까
		// 맵에 넣어서 자동 솔팅 후 제일 가까운거 뽑을라고 만든 맵

		// 로컬 좌표 {0.f 0.f, 0.f} 기준으로
		// 상, 하, 좌, 우, 앞, 뒤 로 이동 할 중심 좌표
		D3DXVECTOR3 vCenterTemp = {};
		//오른쪽면 검사
		if (D3DXIntersectTri(
			&CompareVtx[1].vPos,
			&CompareVtx[5].vPos,
			&CompareVtx[6].vPos,
			&m_vOriginRay,
			&m_vRayDir,
			&fU, &fV, &fDist) ||
			D3DXIntersectTri(
				&CompareVtx[1].vPos,
				&CompareVtx[6].vPos,
				&CompareVtx[2].vPos,
				&m_vOriginRay,
				&m_vRayDir,
				&fU, &fV, &fDist))
		{
			//오른쪽일경우 우로 ITV * 1.f
			vCenterTemp =
			{ pCube->Get_Transform()->GetWorldMatrix()._41,
				pCube->Get_Transform()->GetWorldMatrix()._42,
				pCube->Get_Transform()->GetWorldMatrix()._43 };
			vCenterTemp += D3DXVECTOR3(0.f, 1.f, 0.f);

			mapTemp.insert({ fDist, vCenterTemp });

		}


		//왼쪽 검사
		if (D3DXIntersectTri(
			&CompareVtx[4].vPos,
			&CompareVtx[0].vPos,
			&CompareVtx[3].vPos,
			&m_vOriginRay,
			&m_vRayDir,
			&fU, &fV, &fDist) ||
			D3DXIntersectTri(
				&CompareVtx[4].vPos,
				&CompareVtx[3].vPos,
				&CompareVtx[7].vPos,
				&m_vOriginRay,
				&m_vRayDir,
				&fU, &fV, &fDist))
		{
			vCenterTemp =
			{ pCube->Get_Transform()->GetWorldMatrix()._41,
				pCube->Get_Transform()->GetWorldMatrix()._42,
				pCube->Get_Transform()->GetWorldMatrix()._43 };
			vCenterTemp += D3DXVECTOR3(0.f, 1.f, 0.f);

			mapTemp.insert({ fDist, vCenterTemp });


		}


		//위쪽 검사
		if (D3DXIntersectTri(
			&CompareVtx[4].vPos,
			&CompareVtx[5].vPos,
			&CompareVtx[1].vPos,
			&m_vOriginRay,
			&m_vRayDir,
			&fU, &fV, &fDist) ||
			D3DXIntersectTri(
				&CompareVtx[4].vPos,
				&CompareVtx[1].vPos,
				&CompareVtx[0].vPos,
				&m_vOriginRay,
				&m_vRayDir,
				&fU, &fV, &fDist))
		{
			vCenterTemp =
			{ pCube->Get_Transform()->GetWorldMatrix()._41,
				pCube->Get_Transform()->GetWorldMatrix()._42,
				pCube->Get_Transform()->GetWorldMatrix()._43 };
			vCenterTemp += D3DXVECTOR3(0.f, 1.f, 0.f);

			mapTemp.insert({ fDist, vCenterTemp });


		}


		//아래쪽 검사
		if (D3DXIntersectTri(
			&CompareVtx[3].vPos,
			&CompareVtx[2].vPos,
			&CompareVtx[6].vPos,
			&m_vOriginRay,
			&m_vRayDir,
			&fU, &fV, &fDist) ||
			D3DXIntersectTri(
				&CompareVtx[3].vPos,
				&CompareVtx[6].vPos,
				&CompareVtx[7].vPos,
				&m_vOriginRay,
				&m_vRayDir,
				&fU, &fV, &fDist))
		{
			vCenterTemp =
			{ pCube->Get_Transform()->GetWorldMatrix()._41,
				pCube->Get_Transform()->GetWorldMatrix()._42,
				pCube->Get_Transform()->GetWorldMatrix()._43 };
			vCenterTemp += D3DXVECTOR3(0.f, 1.f, 0.f);

			mapTemp.insert({ fDist, vCenterTemp });


		}


		//앞쪽 검사
		if (D3DXIntersectTri(
			&CompareVtx[0].vPos,
			&CompareVtx[1].vPos,
			&CompareVtx[2].vPos,
			&m_vOriginRay,
			&m_vRayDir,
			&fU, &fV, &fDist) ||
			D3DXIntersectTri(
				&CompareVtx[0].vPos,
				&CompareVtx[2].vPos,
				&CompareVtx[3].vPos,
				&m_vOriginRay,
				&m_vRayDir,
				&fU, &fV, &fDist))
		{
			vCenterTemp =
			{ pCube->Get_Transform()->GetWorldMatrix()._41,
				pCube->Get_Transform()->GetWorldMatrix()._42,
				pCube->Get_Transform()->GetWorldMatrix()._43 };
			vCenterTemp += D3DXVECTOR3(0.f, 1.f, 0.f);

			mapTemp.insert({ fDist, vCenterTemp });

		}


		//뒤쪽 검사
		if (D3DXIntersectTri(
			&CompareVtx[5].vPos,
			&CompareVtx[4].vPos,
			&CompareVtx[7].vPos,
			&m_vOriginRay,
			&m_vRayDir,
			&fU, &fV, &fDist) ||
			D3DXIntersectTri(
				&CompareVtx[5].vPos,
				&CompareVtx[7].vPos,
				&CompareVtx[6].vPos,
				&m_vOriginRay,
				&m_vRayDir,
				&fU, &fV, &fDist))
		{
			vCenterTemp =
			{ pCube->Get_Transform()->GetWorldMatrix()._41,
				pCube->Get_Transform()->GetWorldMatrix()._42,
				pCube->Get_Transform()->GetWorldMatrix()._43 };
			vCenterTemp += D3DXVECTOR3(0.f, 1.f, 0.f);

			mapTemp.insert({ fDist, vCenterTemp });

		}

	}
	if (!mapTemp.empty())
	{
		// 하나라도 레이 캐스트가 면을 통과한 경우의 값들을
		// 순회하면서 TerrainTool에 있는 mapCube에다가 채워줌
		D3DXVECTOR3 vPos = m_pTransform->GetPos();

		vPos.y = vPos.y - mapTemp.begin()->first + m_CollYValue;
		m_pTransform->SetPos(vPos);

		return true;
	}
	if (m_bIsOnPrePos)
		m_pTransform->SetPos(m_vPrePos);
	return false;
}

//bool CPlayer::CollMovingCube()
//{
//	if (m_CubeList.empty())
//		return false;
//	Translation_ViewSpace();
//	map<float, D3DXMATRIX> mapTemp;
//	int i = 0;
//
//	for (auto& pCube : m_CubeList)
//	{
//		i++;
//		ENGINE::VTX_CUBE* pCubeVtx = (ENGINE::VTX_CUBE*)pCube->Get_Buffer()->GetOriginVtxInfo();
//		D3DXMATRIX WorldMatrix = pCube->Get_Transform()->GetWorldMatrix();
//		ENGINE::VTX_CUBE CompareVtx[8] = {};
//
//		for (int i = 0; i < 8; i++)
//		{
//			D3DXVec3TransformCoord(&CompareVtx[i].vPos, &pCubeVtx[i].vPos, &WorldMatrix);
//		}
//
//
//
//		float fU = 0.f, fV = 0.f, fDist = 0.f;
//
//
//		D3DXVECTOR3 vCenterTemp = {};
//
//		//위쪽 검사
//		if (D3DXIntersectTri(
//			&CompareVtx[4].vPos,
//			&CompareVtx[5].vPos,
//			&CompareVtx[1].vPos,
//			&m_vOriginRay,
//			&m_vRayDir,
//			&fU, &fV, &fDist) ||
//			D3DXIntersectTri(
//				&CompareVtx[4].vPos,
//				&CompareVtx[1].vPos,
//				&CompareVtx[0].vPos,
//				&m_vOriginRay,
//				&m_vRayDir,
//				&fU, &fV, &fDist))
//		{
//			vCenterTemp =
//			{ pCube->Get_Transform()->GetWorldMatrix()._41,
//				pCube->Get_Transform()->GetWorldMatrix()._42,
//				pCube->Get_Transform()->GetWorldMatrix()._43 };
//			vCenterTemp += D3DXVECTOR3(0.f, 1.f, 0.f);
//
//			mapTemp.insert({ fDist, WorldMatrix });
//
//
//		}
//
//
//	}
//	if (!mapTemp.empty())
//	{
//		// 하나라도 레이 캐스트가 면을 통과한 경우의 값들을
//		// 순회하면서 TerrainTool에 있는 mapCube에다가 채워줌
//		m_pTransform->Set_TagetWorld(mapTemp.begin()->second);
//
//		return true;
//	}
//	if (m_bIsOnPrePos)
//		m_pTransform->SetPos(m_vPrePos);
//	return false;
//}

void CPlayer::Set_bIsCollCube(bool Check)
{
	m_bOnOffCollCube = Check;
}

void CPlayer::Set_bChangeStair(bool Check)
{
	m_bChangeStair = Check;
}

void CPlayer::Set_bIsPrePos(bool Check)
{
	m_bIsOnPrePos = Check;
}

void CPlayer::Set_CollYValue(float fValue)
{
	m_CollYValue = fValue;
}

bool CPlayer::Get_bIsCollCube()
{
	return m_bOnOffCollCube;
}

bool CPlayer::Get_bChangeStair()
{
	return m_bChangeStair;
}
