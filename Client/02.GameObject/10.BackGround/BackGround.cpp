#include "stdafx.h"
#include "BackGround.h"
#include "Texture.h"
#include "VIBuffer.h"
#include "Component.h"
#include "SetTransform.h"
#include "Transform.h"
#include "BillBoard.h"
#include "StaticCamera.h"
#include "Player.h"

CBackGround::CBackGround(LPDIRECT3DDEVICE9 pGraphicDev)
	: ENGINE::CGameObject(pGraphicDev)
	, m_pManagement(ENGINE::Get_Management())
	, m_pResourceMgr(ENGINE::Get_ResourceMgr())
	, m_pTimeMgr(ENGINE::Get_TimeMgr())
	, m_pTransform(nullptr), m_pStaticCamera(nullptr)
{

}

CBackGround::~CBackGround()
{
	Release();
}

void CBackGround::Update()
{
	ENGINE::CGameObject::LateInit();
	ENGINE::CGameObject::Update();

	ENGINE::CGameObject* pObj = m_pManagement->GetLst(ENGINE::CLayer::LAYER_ID::OBJECT, L"Player")->front();

	CPlayer* pPlayer = dynamic_cast<CPlayer*>(pObj);
	NULL_CHECK(pPlayer);

	if (pPlayer->GetState() &&
		m_fRatio > -1.99f)
		m_fRatio -= 0.008f;

}

void CBackGround::LateUpdate()
{
	ENGINE::CGameObject::LateUpdate();
}

void CBackGround::Render()
{
	ENGINE::CGameObject::Render();

	//현재 월드, 뷰, 투영을 저장//////////////////////////////////////////
	D3DXMATRIX matWorld_Ref, MatView_Ref, matProj_Ref;
	matWorld_Ref = ENGINE::CSetTransForm::GetMatWorld();
	MatView_Ref = ENGINE::CSetTransForm::GetMatView();
	matProj_Ref = ENGINE::CSetTransForm::GetMatProj();
	///////////////////////////////////////////////////////////////////////

	//직교투영 계산////////////////////////////////////////////////////////
	D3DXMATRIX matWorld, matView, matProj;
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixIdentity(&matView);
	D3DXMatrixIdentity(&matProj);
	D3DXMatrixOrthoLH(&matProj, WINCX, WINCY, 0.f, 1.f);

	float fScale[AX_MAX];
	fScale[AX_X] = 1.0f;
	fScale[AX_Y] = 1.0f;
	fScale[AX_Z] = 1.f;
	for (int i = 0; i < AX_MAX; ++i)
			matView(i, i) *= fScale[i];

	//matView._41 = 1.f * m_pStaticCamera->GetCamDir().x;
	matView._42 = m_fRatio;// (m_fRatio + m_pStaticCamera->GetCamDir().y);
	matView._43 = 1.f * m_pStaticCamera->GetCamDir().z;

	ENGINE::CSetTransForm::Set_TransForm(D3DTS_WORLD, &matWorld);
	ENGINE::CSetTransForm::Set_TransForm(D3DTS_VIEW, &matView);
	ENGINE::CSetTransForm::Set_TransForm(D3DTS_PROJECTION, &matProj);
	////////////////////////////////////////////////////////////////////////

	//그림2 직교투영 반영
	m__pTexture->Render(0);
	m__pBuffer->Render();

	//그림1과 그림2의 간격
	matView._42 += 2.f;
	ENGINE::CSetTransForm::Set_TransForm(D3DTS_VIEW, &matView);

	//그림1 직교투영 반영
	m_pTexture->Render(0);
	m_pBuffer->Render();

	//직교투영 이전 월드, 뷰, 투영 전달/////////////////////////////////////
	ENGINE::CSetTransForm::Set_TransForm(D3DTS_WORLD, &matWorld_Ref);
	ENGINE::CSetTransForm::Set_TransForm(D3DTS_VIEW, &MatView_Ref);
	ENGINE::CSetTransForm::Set_TransForm(D3DTS_PROJECTION, &matProj_Ref);
	////////////////////////////////////////////////////////////////////////
}

HRESULT CBackGround::Initialize()
{
	HRESULT hr = AddComponent();
	FAILED_CHECK_MSG_RETURN(hr, L"Component Add Failed", E_FAIL);

	m_pTransform->SetSize({ 3.f, 3.f, 3.f });
	m_pTransform->SetPos({0.f, 0.f, 0.f});


	return S_OK;
}

HRESULT CBackGround::LateInit()
{
	list<ENGINE::CGameObject*>* pLst = m_pManagement->GetLst(ENGINE::CLayer::ENVIROMENT, L"StaticCamera");

	if (pLst->empty())
		return E_FAIL;

	ENGINE::CGameObject* pObj = pLst->front();

	NULL_CHECK_MSG_RETURN(pObj, L"Camera is nullptr",E_FAIL);

	m_pStaticCamera = dynamic_cast<CStaticCamera*>(pObj);

	return S_OK;
}

void CBackGround::Release()
{
}

HRESULT CBackGround::AddComponent()
{
	ENGINE::CComponent* pComponent = nullptr;

	//그림1////////////////////////////////////////////////////////////////////////////
	pComponent = m_pResourceMgr->CloneResource(ENGINE::RESOURCE_STATIC, L"Texture_Title");
	NULL_CHECK_MSG_RETURN(pComponent, L"Texture_Title is nullptr", E_FAIL);
	m_mapComponent.insert({ L"Texture1", pComponent });
	m_pTexture = dynamic_cast<ENGINE::CTexture*>(pComponent);

	pComponent = m_pResourceMgr->CloneResource(ENGINE::RESOURCE_STATIC, L"Buffer_RcTex");
	NULL_CHECK_MSG_RETURN(pComponent, L"Buffer_RcTex is nullptr", E_FAIL);
	m_mapComponent.insert({ L"Buffer1", pComponent });
	m_pBuffer = dynamic_cast<ENGINE::CVIBuffer*>(pComponent);
	///////////////////////////////////////////////////////////////////////////////////


	//Transform////////////////////////////////////////////////////////////////////////
	m_pTransform = ENGINE::CTransform::Create({ 0.f, 0.f, 1.f });
	NULL_CHECK_RETURN(m_pTransform, E_FAIL);
	m_mapComponent.insert({ L"Transform", m_pTransform });
	///////////////////////////////////////////////////////////////////////////////////

	wstring wstrTextureName;
	switch (m_eStage)
	{
	case CBackGround::STAGE1:
		wstrTextureName = L"Texture_Stage1";
		break;
	case CBackGround::STAGE2:
		wstrTextureName = L"Texture_Stage2";
		break;
	case CBackGround::STAGE3:
		wstrTextureName = L"Texture_Stage3";
		break;
	case CBackGround::STAGE4:
		wstrTextureName = L"Texture_Stage4";
		break;
	case CBackGround::STAGE5:
		wstrTextureName = L"Texture_Stage5";
		break;
	default:
		break;
	}


	//그림2////////////////////////////////////////////////////////////////////////////
	pComponent = m_pResourceMgr->CloneResource(ENGINE::RESOURCE_STATIC, wstrTextureName);
	NULL_CHECK_MSG_RETURN(pComponent, L"Texture_Title is nullptr", E_FAIL);
	m_mapComponent.insert({ L"Texture2", pComponent });
	m__pTexture = dynamic_cast<ENGINE::CTexture*>(pComponent);

	pComponent = m_pResourceMgr->CloneResource(ENGINE::RESOURCE_STATIC, L"Buffer_RcTex");
	NULL_CHECK_MSG_RETURN(pComponent, L"Buffer_RcTex is nullptr", E_FAIL);
	m_mapComponent.insert({ L"Buffer2", pComponent });
	m__pBuffer = dynamic_cast<ENGINE::CVIBuffer*>(pComponent);
	///////////////////////////////////////////////////////////////////////////////////

	return S_OK;
}

CBackGround * CBackGround::Create(LPDIRECT3DDEVICE9 pGraphicDev, STAGE eStage)
{
	CBackGround* pInstance = new CBackGround(pGraphicDev);

	pInstance->Set_Stage(eStage);

	if (FAILED(pInstance->Initialize()))
	{
		ENGINE::SafeDelete(pInstance);
		return nullptr;
	}


	return pInstance;
}

void CBackGround::Set_Stage(STAGE eStage)
{
	m_eStage = eStage;
}
