#include "stdafx.h"
#include "Stage.h"
#include "Layer.h"
#include "Player.h"
#include "Building.h"
#include "Monster.h"
#include "StaticCamera.h"
#include "Transform.h"
#include "MyTerrain.h"
#include "SetTransform.h"
#include "TimeMgr.h"
#include "Block.h"
#include "Mouse.h"
#include "WholeBody.h"
#include "KeyMgr.h"
#include "SceneSelector.h"
#include "BackGround.h"
#include "Portal.h"

CStage::CStage(LPDIRECT3DDEVICE9 pGraphicDev)
	: CScene(pGraphicDev)
	, m_pManagement(ENGINE::Get_Management())
	, m_pResourceMgr(ENGINE::Get_ResourceMgr())
	, m_pCollisionMgr(CCollisionMgr::GetInstance())
	, m_pKeyMgr(ENGINE::CKeyMgr::GetInstance())
	, m_pSoundMgr(CSoundMgr::GetInstance())
	, m_bIsCreateBox(false), m_fTime(10.f)
	, m_pPlayer(nullptr), m_bIsLogoDone(false)
{
}

CStage::~CStage()
{
	Release();
}

void CStage::Update()
{
	ENGINE::CScene::Update();

	ENGINE::CGameObject* pObj = m_pManagement->GetLst(ENGINE::CLayer::OBJECT, L"Player")->front();
	ENGINE::CTransform* pTransform = dynamic_cast<ENGINE::CTransform*>(pObj->GetComponent(L"Transform"));

	//포탈 to Logo
	if (m_pCollisionMgr->IntersectSphere(0.2f, pTransform->GetPos(),
		0.5f, D3DXVECTOR3(4.5f, 10.5f, 7.5f)))
	{
		dynamic_cast<CPlayer*>(pObj)->SetState(true);

		list<ENGINE::CGameObject*>* pLst = m_pManagement->GetLst(ENGINE::CLayer::ENVIROMENT, L"StaticCamera");

		if (pLst->empty())
			return;

		ENGINE::CGameObject* pObj = pLst->front();
		NULL_CHECK_MSG(pObj, L"Camera is nullptr");
		CStaticCamera* pCamera = dynamic_cast<CStaticCamera*>(pObj);

		if (*pCamera->GetHeight() <= 0.125f
			&& !m_bIsLogoDone)
			pCamera->SetHeight(*pCamera->GetHeight() + 0.0005f);
		else
		{
			pCamera->SetHeight(0.f);
			m_bIsLogoDone = true;
		}
	}
	////큐브 좌우 충돌 끄기
	//if (m_pCollisionMgr->IntersectSphere(0.2f, m_pPlayer->GetTransform()->GetPos(),
	//	0.5f, D3DXVECTOR3(-2.0f, 7.5f, 1.5f)))
	//		m_pPlayer->Set_bIsPrePos(true);
}

void CStage::LateUpdate()
{
	ENGINE::CScene::LateUpdate();
	if (m_pKeyMgr->KeyDown(KEY_RESET))
	{
		m_pPlayer->GetTransform()->SetPos(D3DXVECTOR3(0.6f, 0.2f, 2.07f));
		return;
	}
	if (m_pKeyMgr->KeyDown(KEY_RETURN))
	{
		m_pCollisionMgr->SetIsSceneChange(true);
		return;
	}
}

void CStage::Render()
{
	if (!m_pCollisionMgr->IntersectSphere(0.2f, m_pPlayer->GetTransform()->GetPos(),
		0.5f, D3DXVECTOR3(4.5f, 10.5f, 7.5f)))
	{
		RECT rc = { 520, 300, 920, 400 };

		ENGINE::CGraphicDev::GetInstance()->GetFont()->DrawText(nullptr, L"길게 눌러 회전하시오.", lstrlen(L"길게 눌러 회전하시오."), &rc, 0, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
	CFrameMgr::GetInstance()->RenderFrame();
	ENGINE::CScene::Render();

	if (m_pCollisionMgr->GetIsSceneChange())
	{
		m_pManagement->SceneChange(CSceneSelector(CSceneSelector::STAGE2));
		return;
	}

}

HRESULT CStage::Initialize()
{
	m_pGraphicDev->SetRenderState(D3DRS_LIGHTING, FALSE);

	HRESULT hr = m_pResourceMgr->AddBuffer(m_pGraphicDev, ENGINE::RESOURCE_STATIC,
		ENGINE::CVIBuffer::BUFFER_RCTEX, L"Buffer_RcTex");
	FAILED_CHECK_MSG_RETURN(hr, L"Buffer_RcTex Add Failed", E_FAIL);

	//Cube Buffer
	hr = m_pResourceMgr->AddBuffer(m_pGraphicDev, ENGINE::RESOURCE_STATIC,
		ENGINE::CVIBuffer::BUFFER_CUBETEX, L"Buffer_CubeTex");
	FAILED_CHECK_MSG_RETURN(hr, L"Buffer_Cube Add Failed", E_FAIL);

	//CubeCol Buffer
	hr = m_pResourceMgr->AddBuffer(m_pGraphicDev, ENGINE::RESOURCE_STATIC,
		ENGINE::CVIBuffer::BUFFER_CUBE, L"Buffer_CubeCol");
	FAILED_CHECK_MSG_RETURN(hr, L"Buffer_CubeCol Add Failed", E_FAIL);

	//Player Cube Buffer
	hr = m_pResourceMgr->AddBuffer(m_pGraphicDev, ENGINE::RESOURCE_STATIC,
		ENGINE::CVIBuffer::BUFFER_PLAYER_CUBE, L"Buffer_PlayerCube");
	FAILED_CHECK_MSG_RETURN(hr, L"Buffer_PlayerCube Add Failed", E_FAIL);

	//Cube Texture
	hr = m_pResourceMgr->AddTexture(m_pGraphicDev, ENGINE::RESOURCE_STATIC,
		ENGINE::TEX_CUBE, L"Texture_Cube", L"../Bin/Resources/Texture/CubeTex/CubeTex%d.dds", 10);
	FAILED_CHECK_MSG_RETURN(hr, L"Texture_Cube Add Failed", E_FAIL);

	//BackGround Img
	hr = m_pResourceMgr->AddTexture(m_pGraphicDev, 
		ENGINE::RESOURCE_STATIC, ENGINE::TEX_NORMAL, 
		L"Texture_Title", L"../Bin/Resources/Texture/MonumentMentValley.jpg", 1);
	FAILED_CHECK_MSG_RETURN(hr, L"Texture_Title Add Failed", E_FAIL);

	hr = m_pResourceMgr->AddTexture(m_pGraphicDev, 
		ENGINE::RESOURCE_STATIC, ENGINE::TEX_NORMAL, 
		L"Texture_Stage1", L"../Bin/Resources/Texture/BackGround.jpg", 1);
	FAILED_CHECK_MSG_RETURN(hr, L"Texture_Stage1 Add Failed", E_FAIL);

	//hr = m_pResourceMgr->AddBuffer(m_pGraphicDev, ENGINE::RESOURCE_STATIC, ENGINE::CVIBuffer::BUFFER_RCTEX, L"Buffer_RcTex");


	hr = Add_Environment_Layer();
	FAILED_CHECK_MSG_RETURN(hr , L"Add_Environment_Layer Failed", E_FAIL);

	hr = Add_Object_Layer();
	FAILED_CHECK_MSG_RETURN(hr, L"Add_Object_Layer Failed", E_FAIL);

	hr = Add_UI_Layer();
	FAILED_CHECK_MSG_RETURN(hr, L"Add_UI_Layer Failed", E_FAIL);

	AddSpriteTexture(); // 스프라이트 이미지 로드.
	//사운드 매니저!
	m_pSoundMgr->PlayBGM(L"BGM1.mp3");

	return S_OK;
}

void CStage::Release()
{
	m_pSoundMgr->AllStop();
	m_pCollisionMgr->DestroyInstance();
	m_pResourceMgr->ResetDynamaicResource();
}

CStage * CStage::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CStage* pInstance = new CStage(pGraphicDev);

	if (FAILED(pInstance->Initialize()))
	{
		ENGINE::SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}

HRESULT CStage::Add_Environment_Layer()
{
	ENGINE::CLayer* pEnvironment_Layer = ENGINE::CLayer::Create(m_pGraphicDev);
	NULL_CHECK_MSG_RETURN(pEnvironment_Layer, L"Environment Layer Create Failed", E_FAIL);

	HRESULT hr = 0;
	ENGINE::CGameObject* pGameObject = nullptr;

	pGameObject = CStaticCamera::Create(m_pGraphicDev, D3DXVECTOR3(8.f, 0.f, 8.f),
		0.f, 45.f, 35.25f, 17.f, 20.8f, 15.6f);
	//pGameObject = CStaticCamera::Create(m_pGraphicDev, D3DXVECTOR3(12.02f, 0.f, 12.02f),
	//	0.f, 45.f, 35.25f, 38.f, 40.8f, 30.6f);
	NULL_CHECK_MSG_RETURN(pGameObject, L"StaticCamera Create Failed", E_FAIL);

	hr = pEnvironment_Layer->AddObject(L"StaticCamera", pGameObject);
	FAILED_CHECK_MSG_RETURN(hr, L"Environment Layer AddObject Failed", E_FAIL);

	m_mapLayer.insert({ ENGINE::CLayer::ENVIROMENT, pEnvironment_Layer });
	return S_OK;
}

HRESULT CStage::Add_Object_Layer()
{
	ENGINE::CLayer* pObjLayer = ENGINE::CLayer::Create(m_pGraphicDev);
	NULL_CHECK_MSG_RETURN(pObjLayer, L"Add_Object_Layer Failed", E_FAIL);

	ENGINE::CGameObject* pObject = nullptr;
	ENGINE::CGameObject* pPlayer = nullptr;
	// BackGround Create
	pObject = CBackGround::Create(m_pGraphicDev, CBackGround::STAGE1);
	NULL_CHECK_RETURN(pObject, E_FAIL);
	HRESULT hr = pObjLayer->AddObject(L"BackGround", pObject);
	FAILED_CHECK_MSG_RETURN(hr, L"Object Layer AddObject Failed", E_FAIL);

	// Player Create
	pPlayer = CPlayer::Create(m_pGraphicDev);
	NULL_CHECK_MSG_RETURN(pPlayer, L"Player Create Failed", E_FAIL);
	m_pPlayer = dynamic_cast<CPlayer*>(pPlayer);
	m_pPlayer->GetTransform()->SetPos(D3DXVECTOR3(0.6f, 0.2f, 2.07f));
	m_pPlayer->Set_bIsPrePos(false);


	 hr = pObjLayer->AddObject(L"Player", pPlayer);
	FAILED_CHECK_MSG_RETURN(hr, L"Object Layer AddObject Failed", E_FAIL);

	// Player's Body
	pObject = CWholeBody::Create(m_pGraphicDev,
		dynamic_cast<ENGINE::CTransform*>(pPlayer->GetComponent(L"Transform")),
		dynamic_cast<CPlayer*>(pPlayer)->GetTimeCnt());
	NULL_CHECK_MSG_RETURN(pObject, L"Player's Body Failed", E_FAIL);

	hr = pObjLayer->AddObject(L"WholeBody", pObject);
	FAILED_CHECK_MSG_RETURN(hr, L"Object Layer AddObject Failed", E_FAIL);

	hr = LoadMap(pObjLayer, dynamic_cast<CPlayer*>(pPlayer));
	FAILED_CHECK_MSG_RETURN(hr, L"Block Load Failed", E_FAIL);

	/*pObject = CPortal::Create(m_pGraphicDev,
		CPortal::SCENECHANGE, CPortal::STAGE1,
		D3DXVECTOR3(4.5f, 0.5f, 7.5f));*/

	//Portal
	pObject = CPortal::Create(m_pGraphicDev,
		CPortal::tagType::TRANS, CPortal::STAGE1,
		D3DXVECTOR3(4.5f, 0.5f, 7.5f),
		D3DXVECTOR3(-2.5f, 7.5f, 0.5f));
	NULL_CHECK_MSG_RETURN(pObject, L"Portal Create FAiled", E_FAIL);
	hr = pObjLayer->AddObject(L"Portal", pObject);
	FAILED_CHECK_MSG_RETURN(hr, L"Object Layer AddObject Failed", E_FAIL);

	// Layer Insert
	m_mapLayer.insert({ ENGINE::CLayer::OBJECT, pObjLayer });

	return S_OK;
}

HRESULT CStage::Add_UI_Layer()
{
	return S_OK;
}

void CStage::AddSpriteTexture()
{
}


HRESULT CStage::LoadMap(ENGINE::CLayer* pObjLayer, CPlayer* pPlayer)
{
	ENGINE::CGameObject* pObject = CMouse::Create(m_pGraphicDev);
	NULL_CHECK_MSG_RETURN(pObject, L"Mouse Create Failed", E_FAIL);
	HRESULT hr = pObjLayer->AddObject(L"Mouse", pObject);
	FAILED_CHECK_MSG_RETURN(hr, L"Object Layer AddObject Failed", E_FAIL);

	HANDLE hFile = CreateFile(L"../../Data/Stage1_New.dat", GENERIC_READ, 0, 0,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

	if (INVALID_HANDLE_VALUE == hFile)
	{
		MessageBox(g_hWnd, L"Load Failed", nullptr, MB_OK);
		return E_FAIL;
	}

	DWORD dwByte = 0;

	int iCubeListSize = 0;
	int iOptiListSize = 0;
	int iInterListSize = 0;

	int ivecCubeList = 0; // vecCubeList size
	int ivecCube = 0; // InterList vecCube size

	int iVecSize = 0;
	int iTexNum = 0;
	int iSortNum = 0;
	bool bIsReverse = false;

	CBlock::CUBE_STATE eCubeState = CBlock::DEFAULT_STATE;
	D3DXVECTOR3 vSize = { 0.5f, 0.5f, 0.5f };
	D3DXVECTOR3 vCubePos = {};
	ENGINE::MYARGB tARGB = {};

	vector<CBlock*> vecCube;
	list<vector<CBlock*>> vecCubeList;

	D3DXMATRIX matTargetWorld;

	ReadFile(hFile, &iCubeListSize, sizeof(int), &dwByte, nullptr); // 1. 큐브 리스트 사이즈 읽어오기.
	ReadFile(hFile, &iOptiListSize, sizeof(int), &dwByte, nullptr);
	ReadFile(hFile, &iInterListSize, sizeof(int), &dwByte, nullptr);

	while (true)
	{
		for (; iCubeListSize > 0; --iCubeListSize) // m_CubeList
		{
			ReadFile(hFile, &vCubePos, sizeof(D3DXVECTOR3), &dwByte, nullptr);
			ReadFile(hFile, &iTexNum, sizeof(int), &dwByte, nullptr);
			ReadFile(hFile, &iSortNum, sizeof(int), &dwByte, nullptr);
			ReadFile(hFile, &(eCubeState), sizeof(CBlock::CUBE_STATE), &dwByte, nullptr);
			ReadFile(hFile, &vSize, sizeof(D3DXVECTOR3), &dwByte, nullptr);

			CBlock* pCube =
				CBlock::Create(m_pGraphicDev, vCubePos, iSortNum, iTexNum, vSize, eCubeState);

			HRESULT hr = pObjLayer->AddObject(L"Block", pCube);
			pPlayer->Get_CubeList().push_back(pCube); // 플레이어가 사용할 큐브 리스트
			dynamic_cast<CMouse*>(pObject)->AddCube_List(pCube); // 마우스꺼.

		}

		for (; iOptiListSize > 0; --iOptiListSize) // m_OptimizationList
		{
			ReadFile(hFile, &iVecSize, sizeof(int), &dwByte, nullptr); // 3. 합쳐진 큐브들의 각각의 사이즈.

			for (; iVecSize > 0; --iVecSize)
			{
				ReadFile(hFile, &vCubePos, sizeof(D3DXVECTOR3), &dwByte, nullptr);
				ReadFile(hFile, &iTexNum, sizeof(int), &dwByte, nullptr);
				ReadFile(hFile, &iSortNum, sizeof(int), &dwByte, nullptr);
				ReadFile(hFile, &(eCubeState), sizeof(CBlock::CUBE_STATE), &dwByte, nullptr);
				ReadFile(hFile, &vSize, sizeof(D3DXVECTOR3), &dwByte, nullptr);
				ReadFile(hFile, &matTargetWorld, sizeof(D3DXMATRIX), &dwByte, nullptr);
				ReadFile(hFile, &bIsReverse, sizeof(bool), &dwByte, nullptr);


				CBlock* pCube = CBlock::Create(m_pGraphicDev, vCubePos, iSortNum, iTexNum, vSize, eCubeState);
				pCube->Set_bIsSelected(true);
				pCube->Get_Transform()->Set_TagetWorld(matTargetWorld);
				pCube->Set_IsReverse(bIsReverse);

		//		pCube->Set_IsUseZBuffer(false);

				pPlayer->Get_CubeList().push_back(pCube);

				vecCube.emplace_back(pCube);

				HRESULT hr = pObjLayer->AddObject(L"OptimizationBlock", pCube);
			}

			if (!vecCube.empty())
			{
				dynamic_cast<CMouse*>(pObject)->AddCube_OptimizationList(&vecCube);

				vecCube.clear();
				vecCube.shrink_to_fit();
			}
		}

		for (; iInterListSize > 0; --iInterListSize) // m_InteractionList
		{
			ReadFile(hFile, &ivecCubeList, sizeof(int), &dwByte, nullptr);

			for (; ivecCubeList > 0; --ivecCubeList)
			{
				ReadFile(hFile, &ivecCube, sizeof(int), &dwByte, nullptr);

				for (; ivecCube > 0; --ivecCube)
				{
					ReadFile(hFile, &vCubePos, sizeof(D3DXVECTOR3), &dwByte, nullptr);
					ReadFile(hFile, &iTexNum, sizeof(int), &dwByte, nullptr);
					ReadFile(hFile, &iSortNum, sizeof(int), &dwByte, nullptr);
					ReadFile(hFile, &(eCubeState), sizeof(CBlock::CUBE_STATE), &dwByte, nullptr);
					ReadFile(hFile, &vSize, sizeof(D3DXVECTOR3), &dwByte, nullptr);
					ReadFile(hFile, &matTargetWorld, sizeof(D3DXMATRIX), &dwByte, nullptr);
					ReadFile(hFile, &bIsReverse, sizeof(bool), &dwByte, nullptr);


					CBlock* pCube = CBlock::Create(m_pGraphicDev, vCubePos, iSortNum, iTexNum, vSize, eCubeState);
					pCube->Set_bIsSelected(true);
					pCube->Get_Transform()->Set_TagetWorld(matTargetWorld);
					pCube->Set_IsReverse(bIsReverse);


					vecCube.emplace_back(pCube);
					HRESULT hr = pObjLayer->AddObject(L"InteractionBlock", pCube);
				}

				if (!vecCube.empty())
				{
					vecCubeList.emplace_back(vecCube);

					vecCube.clear();
					vecCube.shrink_to_fit();
				}
			}

			if (!vecCubeList.empty())
			{
				dynamic_cast<CMouse*>(pObject)->AddCube_InteractionList(&vecCubeList);

				vecCubeList.clear();
			}
		}
		ReadFile(hFile, &ivecCube, sizeof(int), &dwByte, nullptr);

		if (0 == dwByte)
		{
			//	m_iSortNum++; // 렌더할 소팅 넘버를 다 채웠으니 다음 번호부터 채워나가면 된다.
			break;
		}
	}

	CloseHandle(hFile);

	return S_OK;
}
