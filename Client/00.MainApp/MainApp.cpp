#include "stdafx.h"
#include "MainApp.h"
#include "SceneSelector.h"
#include "FrameMgr.h"
#include "KeyMgr.h"
CMainApp::CMainApp()
	: m_pGraphicDev(ENGINE::Get_GraphicDev())
	, m_pManagement(ENGINE::Get_Management())
	, m_pResourceMgr(ENGINE::Get_ResourceMgr())
	, m_pTimeMgr(ENGINE::Get_TimeMgr())
	, m_pKeyMgr(ENGINE::CKeyMgr::GetInstance())
	, m_pCollisionMgr(CCollisionMgr::GetInstance())
	, m_pSoundMgr(CSoundMgr::GetInstance())
	, m_pTextureMgr(CTextureMgr::GetInstance())
	, m_pDevice(nullptr)
{
}

CMainApp::~CMainApp()
{
	Release();
}

void CMainApp::Update()
{
	m_pKeyMgr->CheckKeyInput();
	m_pTimeMgr->UpdateTime();
	m_pManagement->Update();
}

void CMainApp::LateUpdate()
{
	m_pManagement->LateUpdate();
}

void CMainApp::Render()
{
	m_pManagement->Render();
}

HRESULT CMainApp::Initialize()
{
	m_pTimeMgr->InitTimeMgr();
	m_pSoundMgr->Initialize();

	HRESULT hr = m_pGraphicDev->InitDevice(g_hWnd,
		WINCX, WINCY, ENGINE::CGraphicDev::WIN);
	FAILED_CHECK_RETURN(hr, E_FAIL);

	m_pDevice = m_pGraphicDev->GetDevice();
	m_pDevice->AddRef();

	hr = m_pManagement->InitManagement(m_pDevice);
	FAILED_CHECK_RETURN(hr, E_FAIL);

	hr = m_pManagement->SceneChange(CSceneSelector(CSceneSelector::STAGE));
	FAILED_CHECK_RETURN(hr, E_FAIL);

	return S_OK;
}

void CMainApp::Release()
{
	ENGINE::SafeRelease(m_pDevice);
	m_pKeyMgr->DestroyInstance();
	m_pSoundMgr->DestroyInstance();
	m_pCollisionMgr->DestroyInstance();
	m_pTimeMgr->DestroyInstance();
	m_pTextureMgr->DestroyInstance();
	m_pManagement->DestroyInstance();
	m_pResourceMgr->DestroyInstance();
	m_pGraphicDev->DestroyInstance();
}

CMainApp * CMainApp::Create()
{
	CMainApp* pInstance = new CMainApp;

	if (FAILED(pInstance->Initialize()))
	{
		delete pInstance;
		return nullptr;
	}

	return pInstance;
}
