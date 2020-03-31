#include "stdafx.h"
#include "EndingScene.h"
#include "KeyMgr.h"
#include "SceneSelector.h"
CEndingScene::CEndingScene(LPDIRECT3DDEVICE9 pGraphicDev)
	: ENGINE::CScene(pGraphicDev)
	, m_pManagement(ENGINE::Get_Management())
	, m_pKeyMgr(ENGINE::CKeyMgr::GetInstance())
{
}

CEndingScene::~CEndingScene()
{
	Release();
}

void CEndingScene::Update()
{

}

void CEndingScene::LateUpdate()
{
	if (m_pKeyMgr->KeyDown(KEY_RETURN))
	{
		DestroyWindow(g_hWnd);
	}
}

void CEndingScene::Render()
{
	ENGINE::CGraphicDev::GetInstance()->GetSprite()->Begin(D3DXSPRITE_ALPHABLEND);

	const TEX_INFO* pTexInfo = CTextureMgr::GetInstance()->GetTexInfo(L"Stage6");
	NULL_CHECK(pTexInfo);

	float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

	D3DXMATRIX matTrans;

	D3DXMatrixTranslation(&matTrans, 400.f, 300.f, 0.f);

	ENGINE::CGraphicDev::GetInstance()->GetSprite()->SetTransform(&(matTrans));
	ENGINE::CGraphicDev::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture,
		nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	ENGINE::CGraphicDev::GetInstance()->GetSprite()->End();

	RECT rc = { 280, 200, 550, 300 };
	ENGINE::CGraphicDev::GetInstance()->GetFont()->DrawText(nullptr, L"시청해주셔서 감사합니다.", lstrlen(L"시청해주셔서 감사합니다."), &rc, 0, D3DCOLOR_ARGB(255, 255, 255, 255));
}

HRESULT CEndingScene::Initialize()
{
	if (FAILED(CTextureMgr::GetInstance()->InsertTexture(
		CTextureMgr::TEX_SINGLE,
		L"../../Texture/Stage6.jpg",
		L"Stage6")))
	{
		return E_FAIL;
	}
	//m_pGraphicDev->SetRenderState(D3DRS_LIGHTING, FALSE);z

	//m_hVideo = MCIWndCreate(g_hWnd, nullptr, WS_CHILD | WS_VISIBLE | MCIWNDF_NOPLAYBAR, L"../../Video/Monument Valley Ending Happy Ending Video.wmv");
	//MoveWindow(m_hVideo, 0, 0, WINCX, WINCY, false);

	//MCIWndPlay(m_hVideo);

	return S_OK;
}

void CEndingScene::Release()
{
//	MCIWndClose(m_hVideo);
}

HRESULT CEndingScene::Add_Environment_Layer()
{
	return E_NOTIMPL;
}

HRESULT CEndingScene::Add_Object_Layer()
{
	return E_NOTIMPL;
}

HRESULT CEndingScene::Add_UI_Layer()
{
	return E_NOTIMPL;
}

CEndingScene * CEndingScene::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CEndingScene* pInstance = new CEndingScene(pGraphicDev);

	if (FAILED(pInstance->Initialize()))
	{
		ENGINE::SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}
