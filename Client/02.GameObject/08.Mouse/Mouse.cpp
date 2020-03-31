#include "stdafx.h"
#include "Mouse.h"
#include "KeyMgr.h"
#include "CollMouse.h"
#include "Transform.h"
#include "Block.h"
#include "Player.h"
CMouse::CMouse(LPDIRECT3DDEVICE9 pGraphicDev)
	: CGameObject(pGraphicDev)
	, m_pKeyMgr(ENGINE::CKeyMgr::GetInstance())
	, m_pCollisionMgr(CCollisionMgr::GetInstance())
	, m_pCollMouse(nullptr)
	, m_bIsOrtho(true)
	, m_pPlayer(nullptr)
	, m_fValue(0.9f)
{
	ZeroMemory(&m_tPt, sizeof(POINT));
}

CMouse::~CMouse()
{
	Release();
}

void CMouse::Update()
{
//	ENGINE::CGameObject::LateInit();
	ENGINE::CGameObject::Update();
	GetMousePos(); // 마우스 좌표 얻기.
	KeyInput();
}

void CMouse::LateUpdate()
{
	ENGINE::CGameObject::LateUpdate();

	for (auto& pCube : m_CubeList) // 일반 큐브들
	{
		int iRenderNum = pCube->Get_SortNum();

		m_mapRenderCube.insert({ iRenderNum, pCube });
	}
	for (auto& CubeList : m_OptimizationList) // 합쳐진 애들 리스트
	{
		for (auto& pCube : CubeList)
		{
			int iRenderNum = pCube->Get_SortNum();

			m_mapRenderCube.insert({ iRenderNum, pCube });
		}
	}

	for (auto& vecCubeList : m_InteractionList)
	{
		for (auto& vecCube : vecCubeList)
		{
			for (auto& pCube : vecCube)
			{
				int iRenderNum = pCube->Get_SortNum();

				m_mapRenderCube.insert({ iRenderNum, pCube });
			}
		}
	}
}

void CMouse::Render()
{
	for (auto& pCube : m_mapRenderCube) // 렌더는 하나의 합쳐진 리스트에서 렌더가 이뤄줘야함.
	{
		pCube.second->Render();
	}

	m_mapRenderCube.clear();

	POINT pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	ENGINE::CGraphicDev::GetInstance()->GetSprite()->Begin(D3DXSPRITE_ALPHABLEND);

	const TEX_INFO* pTexInfo = CTextureMgr::GetInstance()->GetTexInfo(L"2");
	NULL_CHECK(pTexInfo);

	float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

	D3DXMATRIX matTrans;

	D3DXMatrixTranslation(&matTrans, pt.x + 15.f, pt.y + 10.f, 0.f);

	ENGINE::CGraphicDev::GetInstance()->GetSprite()->SetTransform(&(matTrans));
	ENGINE::CGraphicDev::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture,
		nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	ENGINE::CGraphicDev::GetInstance()->GetSprite()->End();

}

HRESULT CMouse::AddComponent()
{
	//CollMouse
	m_pCollMouse = CCollMouse::Create();
	NULL_CHECK_RETURN(m_pCollMouse, E_FAIL);

	m_mapComponent.insert({ L"CollMouse", m_pCollMouse });

	return S_OK;
}

HRESULT CMouse::Initialize()
{
	HRESULT hr = AddComponent();
	FAILED_CHECK_MSG_RETURN(hr, L"AddComponent Failed", E_FAIL);

	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(
		CTextureMgr::TEX_SINGLE,
		L"../../Texture/2.png",
		L"2")))
	{
		return E_FAIL;
	}

	return S_OK;
}

HRESULT CMouse::LateInit()
{

	return S_OK;
}

void CMouse::Release()
{
	m_CubeList.clear();
	m_OptimizationList.clear();
}

CMouse * CMouse::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CMouse* pInstance = new CMouse(pGraphicDev);

	if (FAILED(pInstance->Initialize()))
	{
		ENGINE::SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CMouse::AddCube_List(CBlock* pBlock)
{
	NULL_CHECK(pBlock);

	m_CubeList.emplace_back(pBlock);
}

void CMouse::AddCube_OptimizationList(vector<CBlock*>* pVecBlock)
{
	if (pVecBlock->empty())
		return;

	m_OptimizationList.emplace_back(*pVecBlock);
}

void CMouse::AddCube_InteractionList(list<vector<CBlock*>>* pvecBlockList)
{
	if (pvecBlockList->empty())
		return;

	m_InteractionList.emplace_back(*pvecBlockList);
}

void CMouse::GetMousePos()
{
	GetCursorPos(&m_tPt);
	ScreenToClient(g_hWnd, &m_tPt);
}

void CMouse::KeyInput()
{

	if (m_pKeyMgr->KeyDown(KEY_LBUTTON))
	{
		m_pCollisionMgr->SetSphereColl(false);
	//	m_pCollisionMgr->SetVailedState(true);

		for (auto& vecCube : m_OptimizationList)
		{
			for (auto& pCube : vecCube)
			{
				if (!pCube->Get_bIsSelected())
					break;
				if (m_pCollMouse->PickSphere(&pCube->Get_CubeMatWorld()))
				{
					m_vecPickCubeList.clear();
					for (auto& pCube : vecCube)
					{
						m_vecPickCubeList.emplace_back(pCube); // 픽된 큐브 리스트.

						pCube->MouseLButtonDown(m_tPt);
					}
					break;
				}
			}
			if (!m_vecPickCubeList.empty())
				break;
		}

		for (auto& vecCubeList : m_InteractionList)
		{
			if (!m_vecPickCubeList.empty())
				break;
			for (auto& vecCube : vecCubeList)
			{
				for (auto& pCube : vecCube)
				{
					if (!pCube->Get_bIsSelected()) // 선택되지 않는 큐브들이면 클릭할수없게 만든다.
						break;
					if (m_pCollMouse->PickSphere(&pCube->Get_CubeMatWorld()))
					{
						m_vecPickCubeList.clear();
						for (auto& vecCube : vecCubeList)
						{
							for (auto& pCube : vecCube)
							{
								m_vecPickCubeList.emplace_back(pCube); // 픽된 큐브 리스트.

								pCube->MouseLButtonDown(m_tPt);
							}
						}
						break;
					}
				}
			}
		}
	}
	if (m_pKeyMgr->KeyUp(KEY_LBUTTON))
	{
		m_pCollisionMgr->SetSphereColl(true);
		for (auto& pCube : m_vecPickCubeList)
		{
			pCube->MouseLButtonUp(m_tPt);
		}

		m_vecPickCubeList.clear(); // 업 버튼을 누르면 초기화.
	}
	if (m_pKeyMgr->KeyPressing(KEY_LBUTTON))
	{
		for (auto& pCube : m_vecPickCubeList)
		{
			pCube->MouseLPressing(m_tPt);
		}

		if (!m_vecPickCubeList.empty())
		{
			switch ((*m_vecPickCubeList.begin())->Get_CubeState())
			{
			case CBlock::ROT_X:
			case CBlock::ROT_Y:
			case CBlock::ROT_Z:
				if ((*m_vecPickCubeList.begin())->Get_RotSound() == 0)
					CSoundMgr::GetInstance()->MyPlaySound(L"Rot1.wav", CSoundMgr::ROT1);
				if ((*m_vecPickCubeList.begin())->Get_RotSound() == 18)
					CSoundMgr::GetInstance()->MyPlaySound(L"Rot2.wav", CSoundMgr::ROT2);
				if ((*m_vecPickCubeList.begin())->Get_RotSound() == 36)
					CSoundMgr::GetInstance()->MyPlaySound(L"Rot3.wav", CSoundMgr::ROT3);
				if ((*m_vecPickCubeList.begin())->Get_RotSound() == 54)
					CSoundMgr::GetInstance()->MyPlaySound(L"Rot4.wav", CSoundMgr::ROT4);
				if ((*m_vecPickCubeList.begin())->Get_RotSound() == 72)
					CSoundMgr::GetInstance()->MyPlaySound(L"Rot5.wav", CSoundMgr::ROT5);
				break;
			default:
				break;
			}
		}
		CollMovingCube();

	}
	// M버튼( 직교때 다른 각도 표현)

	if (m_pKeyMgr->KeyUp(KEY_SPACE)) // 여기 다시봐보기.
	{
		m_bIsOrtho = !m_bIsOrtho;
		m_pCollMouse->Set_bIsOrtho(m_bIsOrtho);
	}
}

list<CBlock*>* CMouse::GetCubeList()
{
	return &m_CubeList;
}

list<vector<CBlock*>>* CMouse::GetOpMzList()
{
	return &m_OptimizationList;
}

list<list<vector<CBlock*>>>* CMouse::GetInterActList()
{
	return &m_InteractionList;
}

list<CBlock*>& CMouse::Get_MovingCubeList()
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return m_MovingCubeList;
}

void CMouse::Set_Player(CPlayer * pPlayer)
{
	m_pPlayer = pPlayer;
}

bool CMouse::CollMovingCube()
{
	if (m_MovingCubeList.empty())
		return false;

	map<float, D3DXVECTOR3> mapTemp;
	//map<float, D3DXVECTOR3> mapTemp2;

	int i = 0;

	for (auto& pCube : m_MovingCubeList)
	{
		i++;
		ENGINE::VTX_CUBE* pCubeVtx = (ENGINE::VTX_CUBE*)pCube->Get_Buffer()->GetOriginVtxInfo();
		D3DXMATRIX WorldMatrix = pCube->Get_Transform()->GetWorldMatrix();
		/*D3DXMATRIX	TargetWorld = pCube->Get_Transform()->GetTargetWorld();
		D3DXMATRIX TargetRot = pCube->Get_Transform()->GetTargetRot();*/

		ENGINE::VTX_CUBE CompareVtx[8] = {};

		for (int i = 0; i < 8; i++)
		{
			D3DXVec3TransformCoord(&CompareVtx[i].vPos, &pCubeVtx[i].vPos, &WorldMatrix);
		}



		float fU = 0.f, fV = 0.f, fDist = 0.f;


		D3DXVECTOR3 vCenterTemp = {};

		//위쪽 검사
		if (D3DXIntersectTri(
			&CompareVtx[4].vPos,
			&CompareVtx[5].vPos,
			&CompareVtx[1].vPos,
			&m_pPlayer->GetTransform()->GetPos(),
			&D3DXVECTOR3(0.f, -1.f, 0.f),
			&fU, &fV, &fDist) ||
			D3DXIntersectTri(
				&CompareVtx[4].vPos,
				&CompareVtx[1].vPos,
				&CompareVtx[0].vPos,
				&m_pPlayer->GetTransform()->GetPos(),
				&D3DXVECTOR3(0.f, -1.f, 0.f),
				&fU, &fV, &fDist))
		{
			vCenterTemp =
			{ pCube->Get_Transform()->GetWorldMatrix()._41,
				pCube->Get_Transform()->GetWorldMatrix()._42,
				pCube->Get_Transform()->GetWorldMatrix()._43 };
			vCenterTemp += D3DXVECTOR3(0.f, m_fValue, 0.f);

			mapTemp.insert({ fDist, vCenterTemp });

		}


	}
	if (!mapTemp.empty())
	{
		// 하나라도 레이 캐스트가 면을 통과한 경우의 값들을
		// 순회하면서 TerrainTool에 있는 mapCube에다가 채워줌
		m_pPlayer->GetTransform()->SetPos(mapTemp.begin()->second);
		//m_pPlayer->GetTransform()->Set_TargetRot(mapTemp2.begin()->second);


		return true;
	}


	return false;
}

void CMouse::Set_Value(const float & fValue)
{
	m_fValue = fValue;
}
