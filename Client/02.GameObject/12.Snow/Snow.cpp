#include "stdafx.h"
#include "Snow.h"
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
#include "Texture.h"

CSnow::CSnow(LPDIRECT3DDEVICE9 pGraphicDev)
	: ENGINE::CGameObject(pGraphicDev)
	, m_pResourceMgr(ENGINE::Get_ResourceMgr())
	, m_pTimeMgr(ENGINE::Get_TimeMgr())
	, m_pManagement(ENGINE::Get_Management())
	, m_pBuffer(nullptr), m_pTexture(nullptr), m_pTransform(nullptr)
	, m_bIsMove(false), m_bIsDestination(false)
	, m_fTimeCnt(0.f), m_fDeltaValue(0.f), m_fSpeed(0.f)
	, m_iAlphaValue(0)
{
	D3DXVec3Normalize(&m_vMousePos, &m_vMousePos);
}

CSnow::~CSnow()
{
	Release();
}

ENGINE::CTransform * CSnow::GetTransform()
{
	return m_pTransform;
}

void CSnow::Update()
{
	ENGINE::CGameObject::LateInit();
	ENGINE::CGameObject::Update();

	m_fTimeCnt += m_pTimeMgr->GetDeltaTime();
	m_fDeltaValue = m_fOscillation * m_fRandom * sinf(m_fRandom *(m_fTimeCnt - m_fRandom * 2.f));
	m_iAlphaValue = int(255 * abs(sinf(m_fTimeCnt * m_fRandom)));

	D3DXVECTOR3 vPos = 
	{
		  m_pTransform->GetPos().x 
		, m_pTransform->GetPos().y + m_fSpeed * m_pTimeMgr->GetDeltaTime()
		, m_pTransform->GetPos().z
	};

	m_pTransform->SetPos(vPos);

	if (m_pTransform->GetPos().y > WINCY + 10.f)
	{
		m_fRandom = float((rand() % 101) * (0.01f));
		m_pTransform->SetPos(D3DXVECTOR3
		(
			  WINCX * m_fRandom
			, -10.f
			, 0.f
		));
	}
}

void CSnow::LateUpdate()
{
	ENGINE::CGameObject::LateUpdate();
}

void CSnow::Render()
{
	ENGINE::CGraphicDev::GetInstance()->GetSprite()->Begin(D3DXSPRITE_ALPHABLEND);

	const TEX_INFO* pTexInfo = CTextureMgr::GetInstance()->GetTexInfo(L"SnowFlower");
	NULL_CHECK(pTexInfo);

	float fCenterX = pTexInfo->tImgInfo.Width  * 0.5f;
	float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

	D3DXMATRIX matSize, matRot, matTrans;

	D3DXMatrixScaling(&matSize
		, m_pTransform->GetSize().x
		, m_pTransform->GetSize().y
		, m_pTransform->GetSize().z
	);

	D3DXMatrixTranslation(&matTrans
		, m_pTransform->GetPos().x + m_fDeltaValue
		, m_pTransform->GetPos().y
		, m_pTransform->GetPos().z
	);

	m_pTransform->SetWorldMatrix(matSize * matTrans);

	ENGINE::CGraphicDev::GetInstance()->GetSprite()->SetTransform(&(m_pTransform->GetWorldMatrix()));
	ENGINE::CGraphicDev::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture,
		nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(m_iAlphaValue, 255, 255, 255));

	ENGINE::CGraphicDev::GetInstance()->GetSprite()->End();
}

HRESULT CSnow::Initialize()
{
	HRESULT hr = AddComponent();
	FAILED_CHECK_MSG_RETURN(hr, L"AddComponent Failed", E_FAIL);

	//srand(time(NULL));

	//¹éºÐÀ²
	m_fOscillation = 50.f;
	m_fRandom = float((rand() % 101) * (0.01f));
	m_fSpeed  = float((rand() % 50) + 10);
	
	m_pTransform->SetPos({ WINCX * m_fRandom, -WINCY * m_fRandom, 0.f });
	m_pTransform->SetDir({ 0.f, 1.f, 0.f });
	m_pTransform->SetSize({ 0.03f, 0.03f, 0.f });
	
	return S_OK;
}

HRESULT CSnow::LateInit()
{
	return S_OK;
}

void CSnow::Release()
{
}

HRESULT CSnow::AddComponent()
{
	ENGINE::CComponent* pComponent = nullptr;

	//Transform
	m_pTransform = ENGINE::CTransform::Create({ 0.f, 0.f, 1.f });
	NULL_CHECK_RETURN(m_pTransform, E_FAIL);
	m_mapComponent.insert({ L"Transform", m_pTransform });

	return S_OK;
}

float * CSnow::GetTimeCnt()
{
	return &m_fTimeCnt;
}

void CSnow::SetTransform(ENGINE::CTransform * pTransform)
{
	m_pTransform = pTransform;
}

CSnow * CSnow::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CSnow* pInstance = new CSnow(pGraphicDev);

	if (FAILED(pInstance->Initialize()))
	{
		ENGINE::SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}