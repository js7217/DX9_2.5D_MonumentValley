#include "stdafx.h"
#include "Stage3.h"
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

CStage3::CStage3(LPDIRECT3DDEVICE9 pGraphicDev)
	: CScene(pGraphicDev)
	, m_pManagement(ENGINE::Get_Management())
	, m_pResourceMgr(ENGINE::Get_ResourceMgr())
	, m_pCollisionMgr(CCollisionMgr::GetInstance())
	, m_pKeyMgr(ENGINE::CKeyMgr::GetInstance())
	, m_pSoundMgr(CSoundMgr::GetInstance())
	, m_bIsCreateBox(false), m_fTime(10.f)
	, m_pPlayer(nullptr), m_iSpriteAlpha(255), m_fSpriteRenderTimer(2.f)
{
}

CStage3::~CStage3()
{
	Release();
}

void CStage3::Update()
{
	ENGINE::CScene::Update();
	if (m_pCollisionMgr->IntersectSphere(0.2f, m_pPlayer->GetTransform()->GetPos(),
		0.4f, D3DXVECTOR3(1.5f, 5.5f, 8.5f)))
	{
		m_pPlayer->Set_bIsPrePos(true);
	}
	if (m_pCollisionMgr->IntersectSphere(0.2f, m_pPlayer->GetTransform()->GetPos(),
		0.4f, D3DXVECTOR3(10.5f, 7.5f, 4.5f)))
	{
		m_pPlayer->Set_bIsPrePos(false);
	}
	if (m_pCollisionMgr->IntersectSphere(0.2f, m_pPlayer->GetTransform()->GetPos(),
		0.4f, D3DXVECTOR3(4.5f, 13.5f, 7.5f)))
	{
		m_pPlayer->Set_bIsPrePos(true);
	}
}

void CStage3::LateUpdate()
{
	ENGINE::CScene::LateUpdate();
	if (m_pKeyMgr->KeyDown(KEY_RESET))
	{
		m_pPlayer->GetTransform()->SetPos(D3DXVECTOR3(1.5f, 1.5f, 1.5f));
		return;
	}
}

void CStage3::Render()
{
	CFrameMgr::GetInstance()->RenderFrame();

	ENGINE::CScene::Render();

	if (m_iSpriteAlpha > 0)
		SpriteRender();

	if (m_pKeyMgr->KeyDown(KEY_RETURN))
	{
		m_pManagement->SceneChange(CSceneSelector(CSceneSelector::STAGE4));
		return;
	}

	if (m_pCollisionMgr->GetIsSceneChange()) // 부딪혔을 경우.
	{
		m_pManagement->SceneChange(CSceneSelector(CSceneSelector::STAGE4));
		return;
	}

}

HRESULT CStage3::Initialize()
{
	HRESULT hr = m_pResourceMgr->AddTexture(m_pGraphicDev,
		ENGINE::RESOURCE_STATIC, ENGINE::TEX_NORMAL,
		L"Texture_Stage3", L"../Bin/Resources/Texture/BackGround3.png", 1);

	hr = Add_Environment_Layer();
	FAILED_CHECK_MSG_RETURN(hr , L"Add_Environment_Layer Failed", E_FAIL);

	hr = Add_Object_Layer();
	FAILED_CHECK_MSG_RETURN(hr, L"Add_Object_Layer Failed", E_FAIL);

	hr = Add_UI_Layer();
	FAILED_CHECK_MSG_RETURN(hr, L"Add_UI_Layer Failed", E_FAIL);


	AddSpriteTexture();
	//사운드 매니저!
	m_pSoundMgr->PlayBGM(L"BGM3.mp3");
//	m_pSoundMgr->PlayBGM(L"MainMenu.mp3");

	return S_OK;
}

void CStage3::Release()
{
	m_pSoundMgr->AllStop();
	m_pCollisionMgr->DestroyInstance();
	m_pResourceMgr->ResetDynamaicResource();
}

CStage3 * CStage3::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CStage3* pInstance = new CStage3(pGraphicDev);

	if (FAILED(pInstance->Initialize()))
	{
		ENGINE::SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}

HRESULT CStage3::Add_Environment_Layer()
{
	ENGINE::CLayer* pEnvironment_Layer = ENGINE::CLayer::Create(m_pGraphicDev);
	NULL_CHECK_MSG_RETURN(pEnvironment_Layer, L"Environment Layer Create Failed", E_FAIL);

	HRESULT hr = 0;
	ENGINE::CGameObject* pGameObject = nullptr;

	pGameObject = CStaticCamera::Create(m_pGraphicDev,
		D3DXVECTOR3(14.14f, 0.f, 14.14f), 0.f, 45.f, 31.3f, 34.f, 28.f, 21.f);
	NULL_CHECK_MSG_RETURN(pGameObject, L"StaticCamera Create Failed", E_FAIL);

	hr = pEnvironment_Layer->AddObject(L"StaticCamera", pGameObject);
	FAILED_CHECK_MSG_RETURN(hr, L"Environment Layer AddObject Failed", E_FAIL);

	m_mapLayer.insert({ ENGINE::CLayer::ENVIROMENT, pEnvironment_Layer });
	return S_OK;
}

HRESULT CStage3::Add_Object_Layer()
{
	ENGINE::CLayer* pObjLayer = ENGINE::CLayer::Create(m_pGraphicDev);
	NULL_CHECK_MSG_RETURN(pObjLayer, L"Add_Object_Layer Failed", E_FAIL);

	ENGINE::CGameObject* pObject = nullptr;
	ENGINE::CGameObject* pPlayer = nullptr;
	// BackGround Create
	pObject = CBackGround::Create(m_pGraphicDev, CBackGround::STAGE3);
	NULL_CHECK_RETURN(pObject, E_FAIL);
	HRESULT hr = pObjLayer->AddObject(L"BackGround", pObject);
	FAILED_CHECK_MSG_RETURN(hr, L"Object Layer AddObject Failed", E_FAIL);

	// Player Create
	pPlayer = CPlayer::Create(m_pGraphicDev);
	NULL_CHECK_MSG_RETURN(pPlayer, L"Player Create Failed", E_FAIL);
	m_pPlayer = dynamic_cast<CPlayer*>(pPlayer);
	m_pPlayer->GetTransform()->SetPos(D3DXVECTOR3(1.5f, 1.5f, 1.5f));
	//m_pPlayer->Set_CollYValue(0.5f);

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

	//Portal
	pObject = CPortal::Create(m_pGraphicDev,
		CPortal::tagType::TRANS, CPortal::STAGE3,
		D3DXVECTOR3(11.5f, 7.5f, 7.98f),
		D3DXVECTOR3(4.5f, 13.5f, 1.02f));
	NULL_CHECK_MSG_RETURN(pObject, L"Portal Create FAiled", E_FAIL);
	hr = pObjLayer->AddObject(L"Portal", pObject);
	FAILED_CHECK_MSG_RETURN(hr, L"Object Layer AddObject Failed", E_FAIL);

	//Button2
	pObject = CPortal::Create(m_pGraphicDev, CPortal::tagType::INTERACT2, CPortal::STAGE3);
	NULL_CHECK_MSG_RETURN(pObject, L"Button Create FAiled", E_FAIL);
	dynamic_cast<CPortal*>(pObject)->SetPos({ 4.5f, 7.5f, 0.5f });
	hr = pObjLayer->AddObject(L"Button", pObject);
	FAILED_CHECK_MSG_RETURN(hr, L"Object Layer AddObject Failed", E_FAIL);

	// SceneChange Portal
	pObject = CPortal::Create(m_pGraphicDev,
		CPortal::tagType::SCENECHANGE, CPortal::STAGE3,
		D3DXVECTOR3(4.5, 13.5f, 9.22f));
	NULL_CHECK_MSG_RETURN(pObject, L"SceneChange Portal Create FAiled", E_FAIL);
	hr = pObjLayer->AddObject(L"SceneChangePortal", pObject);
	FAILED_CHECK_MSG_RETURN(hr, L"Object Layer AddObject Failed", E_FAIL);
	
	// Map Load
	hr = LoadMap(pObjLayer, dynamic_cast<CPlayer*>(pPlayer));
	FAILED_CHECK_MSG_RETURN(hr, L"Block Load Failed", E_FAIL);

	// Layer Insert
	m_mapLayer.insert({ ENGINE::CLayer::OBJECT, pObjLayer });

	return S_OK;
}

HRESULT CStage3::Add_UI_Layer()
{
	return S_OK;
}

void CStage3::AddSpriteTexture()
{
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(
		CTextureMgr::TEX_SINGLE,
		L"../../Texture/Stage3.png",
		L"Stage3")))
	{
		return;
	}
}

void CStage3::SpriteRender()
{
	ENGINE::CGraphicDev::GetInstance()->GetSprite()->Begin(D3DXSPRITE_ALPHABLEND);

	const TEX_INFO* pTexInfo = CTextureMgr::GetInstance()->GetTexInfo(L"Stage3");
	NULL_CHECK(pTexInfo);

	float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

	D3DXMATRIX matTrans;

	D3DXMatrixTranslation(&matTrans, 400.f, 300.f, 0.f);

	ENGINE::CGraphicDev::GetInstance()->GetSprite()->SetTransform(&(matTrans));
	ENGINE::CGraphicDev::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture,
		nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(m_iSpriteAlpha, 255, 255, 255));

	ENGINE::CGraphicDev::GetInstance()->GetSprite()->End();

	if (m_fSpriteRenderTimer >= 0.f)
	{
		m_fSpriteRenderTimer -= ENGINE::CTimeMgr::GetInstance()->GetDeltaTime();
	}
	else
		m_iSpriteAlpha -= ENGINE::CTimeMgr::GetInstance()->GetDeltaTime();

}


HRESULT CStage3::LoadMap(ENGINE::CLayer* pObjLayer, CPlayer* pPlayer)
{
	ENGINE::CGameObject* pObject = CMouse::Create(m_pGraphicDev);
	NULL_CHECK_MSG_RETURN(pObject, L"Mouse Create Failed", E_FAIL);
	dynamic_cast<CMouse*>(pObject)->Set_Player(pPlayer);
	//dynamic_cast<CMouse*>(pObject)->Set_Value(0.73f);

	HRESULT hr = pObjLayer->AddObject(L"Mouse", pObject);
	FAILED_CHECK_MSG_RETURN(hr, L"Object Layer AddObject Failed", E_FAIL);

	HANDLE hFile = CreateFile(L"../../Data/Stage3_New.dat", GENERIC_READ, 0, 0,
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
			pPlayer->Get_CubeList().push_back(pCube);
			dynamic_cast<CMouse*>(pObject)->AddCube_List(pCube);
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
			//	pCube->Set_bIsSelected(true);
				pCube->Get_Transform()->Set_TagetWorld(matTargetWorld);
				pCube->Set_IsReverse(bIsReverse);

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
					pCube->Set_IsUseZBuffer(false); // Z버퍼의 사용 변화를 허용하지 않겠다.

					vecCube.emplace_back(pCube);
					pPlayer->Get_CubeList().push_back(pCube);
					dynamic_cast<CMouse*>(pObject)->Get_MovingCubeList().push_back(pCube);


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
