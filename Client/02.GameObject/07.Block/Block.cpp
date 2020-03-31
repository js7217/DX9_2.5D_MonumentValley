#include "stdafx.h"
#include "Block.h"
#include "Texture.h"
#include "VIBuffer.h"
#include "TerrainTex.h"
#include "RcTex.h"
#include "TerrainInfo.h"
#include "Transform.h"
#include "SetTransform.h"

CBlock::CBlock(LPDIRECT3DDEVICE9 pGraphicDev)
	: ENGINE::CGameObject(pGraphicDev)
	, m_pResourceMgr(ENGINE::Get_ResourceMgr())
	, m_pManagement(ENGINE::Get_Management())
	, m_pCollisionMgr(CCollisionMgr::GetInstance())
	, m_pTimeMgr(ENGINE::Get_TimeMgr())
	, m_pBuffer(nullptr), m_pTexture(nullptr), m_pTransform(nullptr), m_bIsWireFrame(false)
	, m_iSortNum(0), m_iTexNum(0), m_bIsOrtho(false), m_fMovePosValue(0.f)
	, m_bIsCalAngle(false), m_bIsReverse(false), m_bIsUseBuffer(true), m_RotSound(1)
{
	ZeroMemory(&m_PreMPos, sizeof(POINT));
	ZeroMemory(&m_CurMPos, sizeof(POINT));
	ZeroMemory(&m_MDist, sizeof(POINT));

	D3DXMatrixIdentity(&m_OriginWorld);
}

CBlock::~CBlock()
{
	Release();
}

void CBlock::Update()
{
	ENGINE::CGameObject::LateInit();
	ENGINE::CGameObject::Update();
}

void CBlock::LateUpdate()
{
	ENGINE::CGameObject::LateUpdate();
}

void CBlock::Render()
{
	UseZBuffer(); // Z버퍼를 끄고 
				  //	m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
				  //	m_pGraphicDev->SetRenderState(D3DRS_ALPHAREF, 1);
				  //	m_pGraphicDev->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	ENGINE::CSetTransForm::Set_TransForm(D3DTS_WORLD, &m_pTransform->GetWorldMatrix());
	if (m_bIsOrtho)
		m_pGraphicDev->SetRenderState(D3DRS_ZENABLE, FALSE);
	else
		m_pGraphicDev->SetRenderState(D3DRS_ZENABLE, TRUE);

	if (m_bIsWireFrame)
		m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	//	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pTransform->GetWorldMatrix());

	//	m_pBuffer->Set_TexColor(m_tARGB);
	SetTransform();


	m_pTexture->Render(m_iTexNum);
	m_pBuffer->Render();

	//	m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	m_pGraphicDev->SetRenderState(D3DRS_ZENABLE, TRUE);
	m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}

ENGINE::VTX_CUBE* CBlock::Get_CubeOriginVtx()
{
	// TODO: 여기에 반환 구문을 삽입합니다.

	return (ENGINE::VTX_CUBE*)(m_pBuffer->GetOriginVtxInfo());
}

D3DXMATRIX  CBlock::Get_CubeMatWorld()
{

	return m_pTransform->GetWorldMatrix();
}

D3DXVECTOR3 CBlock::Get_CubePos()
{
	return m_pTransform->GetPos();
}

HRESULT CBlock::Initialize()
{
	HRESULT hr = AddComponent();
	FAILED_CHECK_MSG_RETURN(hr, L"AddComponent Failed", E_FAIL);

	m_pTransform->SetPos({ 0.f, -1.f, 0.f });
	m_eCubeState = DEFAULT_STATE; // 처음엔 디폴트.

	return S_OK;
}

HRESULT CBlock::LateInit()
{
	m_OriginWorld._41 = m_pTransform->GetPos().x;
	m_OriginWorld._42 = m_pTransform->GetPos().y;
	m_OriginWorld._43 = m_pTransform->GetPos().z;

	return S_OK;
}

void CBlock::Release()
{
}

void CBlock::SetTransform()
{
	if (m_bIsSelected == true)
	{

		D3DXMATRIX matAxis, matTrans;
		D3DXMatrixIdentity(&matAxis);
		D3DXMatrixIdentity(&matTrans);

		CalAngle();
		switch (m_eCubeState)
		{
		case CBlock::ROT_X:
			D3DXMatrixRotationX(&matAxis, D3DXToRadian(m_fAxisAngle));
			break;
		case CBlock::ROT_Y:
			D3DXMatrixRotationY(&matAxis, D3DXToRadian(m_fAxisAngle));
			break;
		case CBlock::ROT_Z:
			D3DXMatrixRotationZ(&matAxis, D3DXToRadian(m_fAxisAngle));
			break;
		case CBlock::MOVE_X:
			m_pTransform->SetPos(m_pTransform->GetPos() + D3DXVECTOR3(m_fMovePosValue / 500.f, 0.f, 0.f));
			break;
		case CBlock::MOVE_Y:
			m_pTransform->SetPos(m_pTransform->GetPos() + D3DXVECTOR3(0.f, m_fMovePosValue / 500.f, 0.f));
			break;
		case CBlock::MOVE_Z:
			m_pTransform->SetPos(m_pTransform->GetPos() + D3DXVECTOR3(0.f, 0.f, m_fMovePosValue / 500.f));
			break;
		case CBlock::DEFAULT_STATE:
			break;
		}
		m_pTransform->Set_TargetRot(matAxis);
	}

}

void CBlock::UseZBuffer()
{
	if (!m_bIsUseBuffer) // 애초에 사용안하겠다 하면 Z버퍼는 무조건 사용하게끔함.
		return;
	switch (m_eCubeState)
	{
	case CBlock::ROT_X:
		if ((45.f <= m_fAxisAngle && 225.f >= m_fAxisAngle))
			m_bIsOrtho = true;
		else
			m_bIsOrtho = false;
		break;
	case CBlock::ROT_Y:
		if ((45.f <= m_fAxisAngle && 135.f >= m_fAxisAngle))
			m_bIsOrtho = true;
		else
			m_bIsOrtho = false;
		break;
	case CBlock::ROT_Z:
		if ((135.f <= m_fAxisAngle && 315.f >= m_fAxisAngle))
			m_bIsOrtho = true;
		else
			m_bIsOrtho = false;
		break;
	case CBlock::MOVE_X:
		break;
	case CBlock::MOVE_Y:
		break;
	case CBlock::MOVE_Z:
		break;
	default:
		break;
	}
}

HRESULT CBlock::AddComponent()
{
	ENGINE::CComponent* pComponent = nullptr;

	// 사각형 버텍스 정보
	pComponent = m_pResourceMgr->CloneResource(ENGINE::RESOURCE_STATIC, L"Buffer_CubeTex");
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent.insert({ L"Buffer", pComponent });
	m_pBuffer = dynamic_cast<ENGINE::CVIBuffer*>(pComponent);

	// 사각형 텍스쳐 정보
	pComponent = m_pResourceMgr->CloneResource(ENGINE::RESOURCE_STATIC, L"Texture_Cube");
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent.insert({ L"Texture", pComponent });
	m_pTexture = dynamic_cast<ENGINE::CTexture*>(pComponent);

	// 위치정보
	m_pTransform = ENGINE::CTransform::Create({ 0.f, 0.f, 1.f });
	NULL_CHECK_RETURN(m_pTransform, E_FAIL);
	m_mapComponent.insert({ L"Transform", m_pTransform });

	////SphereCollider
	//m_pSphereCollider = ENGINE::CSphereCollider::Create(m_pGraphicDev, m_pTransform, 0.5f);
	//NULL_CHECK_RETURN(m_pSphereCollider, E_FAIL);
	//m_pCollisionMgr->AddCollider(L"Block", m_pSphereCollider);
	//m_mapComponent.insert({ L"SphereCollider", m_pSphereCollider });

	return S_OK;
}

void CBlock::SetPos(const float & fPosX, const float & fPosZ)
{
	m_pTransform->SetPos({ fPosX, -0.5f, fPosZ });
}

void CBlock::SetPos(D3DXVECTOR3 vCenterPos)
{
	m_pTransform->SetPos(vCenterPos);

}

void CBlock::SetSortNum(const int & iNum)
{
	m_iSortNum = iNum;
}

void CBlock::SetTexNum(const int & iTexNum)
{
	m_iTexNum = iTexNum;
}

void CBlock::SetCubeState(CUBE_STATE eCubeState)
{
	m_eCubeState = eCubeState;
}

void CBlock::SetOrtho(const bool & bIsOrtho)
{
	m_bIsOrtho = bIsOrtho;
}

void CBlock::Set_bIsSelected(bool bCheck)
{
	m_bIsSelected = bCheck;
}

bool CBlock::Get_bIsSelected()
{
	return m_bIsSelected;
}

ENGINE::CTransform * CBlock::Get_Transform()
{
	return m_pTransform;
}

ENGINE::CVIBuffer * CBlock::Get_Buffer()
{
	return m_pBuffer;
}

const CBlock::CUBE_STATE& CBlock::Get_CubeState()
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return m_eCubeState;
}

const D3DXVECTOR3 & CBlock::Get_CubeSize()
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return m_pTransform->GetSize();
}

const D3DXMATRIX & CBlock::Get_OriginWorld() const
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return m_OriginWorld;
}

void CBlock::Set_AxisAngle(float fAngle)
{
	if (360.f <= m_fAxisAngle)
		m_fAxisAngle = 0;
	if (0 > m_fAxisAngle)
		m_fAxisAngle += 360.f;
	m_fAxisAngle += fAngle;
}

void CBlock::Set_MoveValue(float fMoveValue)
{
	m_fMovePosValue += fMoveValue;
}

void CBlock::Set_Size(const D3DXVECTOR3 & vSize)
{
	m_pTransform->SetSize(vSize);
}



void CBlock::MouseLButtonDown(POINT pt)
{
	m_PreMPos.x = pt.x;
	m_PreMPos.y = pt.y;
	m_CurMPos.x = pt.x;
	m_CurMPos.y = pt.y;
}

void CBlock::MouseLPressing(POINT pt)
{
	if (!bCheckMouseMove)
	{
		m_PreMPos.x = pt.x;
		m_PreMPos.y = pt.y;
	}
	m_CurMPos.x = pt.x;
	m_CurMPos.y = pt.y;

	m_MDist.x = (m_CurMPos.x - m_PreMPos.x);
	m_MDist.y = (m_CurMPos.y - m_PreMPos.y);
	m_PreMPos = m_CurMPos;

	if (m_fAxisAngle >= 360.f)
		m_fAxisAngle -= 360.f;
	if (m_fAxisAngle < 0.f)
		m_fAxisAngle += 360.f;

	if (ROT_X <= m_eCubeState && m_eCubeState <= ROT_Z)
		m_fAxisAngle += float((m_MDist.x + m_MDist.y) / 3.f);

	if (m_bIsReverse)
	{
		if (MOVE_X <= m_eCubeState && m_eCubeState <= MOVE_Z)
			m_fMovePosValue -= float((m_MDist.x + m_MDist.y) / 5);
	}
	else
	{
		if (MOVE_X <= m_eCubeState && m_eCubeState <= MOVE_Z)
			m_fMovePosValue += float((m_MDist.x + m_MDist.y) / 5);

	}

	m_RotSound = (int)m_fAxisAngle % 90;

}

void CBlock::MouseLButtonUp(POINT pt)
{
	bCheckMouseMove = true;
	m_bIsCalAngle = true;

	m_fMovePosValue = 0.f;

	ZeroMemory(&m_CurMPos, sizeof(POINT));

}

void CBlock::CalAngle()
{
	if (m_bIsCalAngle == true)
	{
		if (0.f < m_fAxisAngle && m_fAxisAngle <= 45.f)
			m_fAxisAngle -= 90.f * m_pTimeMgr->GetDeltaTime();
		if (45.f < m_fAxisAngle && m_fAxisAngle < 90.f)
			m_fAxisAngle += 90.f * m_pTimeMgr->GetDeltaTime();


		if (90.f < m_fAxisAngle && m_fAxisAngle <= 135.f)
			m_fAxisAngle -= 90.f * m_pTimeMgr->GetDeltaTime();

		if (135.f < m_fAxisAngle && m_fAxisAngle < 180.f)
			m_fAxisAngle += 90.f * m_pTimeMgr->GetDeltaTime();

		if (180.f < m_fAxisAngle && m_fAxisAngle <= 225.f)
			m_fAxisAngle -= 90.f * m_pTimeMgr->GetDeltaTime();
		if (225.f < m_fAxisAngle && m_fAxisAngle < 270.f)
			m_fAxisAngle += 90.f * m_pTimeMgr->GetDeltaTime();

		if (270.f < m_fAxisAngle && m_fAxisAngle <= 315.f)
			m_fAxisAngle -= 90.f * m_pTimeMgr->GetDeltaTime();
		if (315.f < m_fAxisAngle && m_fAxisAngle < 360.f)
			m_fAxisAngle += 90.f * m_pTimeMgr->GetDeltaTime();

		if (m_fAxisAngle < 1.f)
		{
			m_fAxisAngle = 0.f;
			m_bIsCalAngle = false;
		}

		if ((89.f <= m_fAxisAngle && m_fAxisAngle < 90.f) || (90.f < m_fAxisAngle && m_fAxisAngle <= 91.f))
		{
			m_fAxisAngle = 90.f;
			m_bIsCalAngle = false;
		}

		if ((179.f <= m_fAxisAngle && m_fAxisAngle < 180.f) || (180.f < m_fAxisAngle && m_fAxisAngle <= 181.f))
		{
			m_fAxisAngle = 180.f;
			m_bIsCalAngle = false;
		}

		if ((269.f <= m_fAxisAngle && m_fAxisAngle < 270.f) || (270.f < m_fAxisAngle && m_fAxisAngle <= 271.f))
		{
			m_fAxisAngle = 270.f;
			m_bIsCalAngle = false;
		}
		if (m_fAxisAngle >= 359.f)
		{
			m_fAxisAngle = 360.f;
			m_bIsCalAngle = false;
		}

	}
}


void CBlock::Set_IsWireFrame(const bool & bIsWireFrame)
{
	m_bIsWireFrame = bIsWireFrame;
}

const int& CBlock::Get_SortNum()
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return m_iSortNum;
}

const int& CBlock::Get_TexNum()
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return m_iTexNum;
}

CBlock * CBlock::Create(LPDIRECT3DDEVICE9 pGraphicDev,
	const float& fPosX, const float& fPosZ,
	const int& iSortNum, const int& iTexNum,
	const D3DXVECTOR3& vSize, CUBE_STATE eState)
{
	CBlock* pInstance = new CBlock(pGraphicDev);

	if (FAILED(pInstance->Initialize()))
	{
		ENGINE::SafeDelete(pInstance);
		return nullptr;
	}
	// 위치, 사이즈, 소팅 번호, 텍스쳐번호, 큐브상태
	pInstance->SetPos(fPosX, fPosZ);
	pInstance->Set_Size(vSize);
	pInstance->SetSortNum(iSortNum);
	pInstance->SetTexNum(iTexNum);
	pInstance->SetCubeState(eState);

	return pInstance;
}

CBlock * CBlock::Create(LPDIRECT3DDEVICE9 pGraphicDev,
	D3DXVECTOR3 vCenterPos, const int& iSortNum,
	const int& iTexNum, const D3DXVECTOR3& vSize, CUBE_STATE eState)
{
	CBlock* pInstance = new CBlock(pGraphicDev);

	if (FAILED(pInstance->Initialize()))
	{
		ENGINE::SafeDelete(pInstance);
		return nullptr;
	}
	// 위치, 사이즈, 소팅 번호, 텍스쳐번호, 큐브상태
	pInstance->SetPos(vCenterPos);
	pInstance->Set_Size(vSize);
	pInstance->SetSortNum(iSortNum);
	pInstance->SetTexNum(iTexNum);
	pInstance->SetCubeState(eState);

	return pInstance;
}

void CBlock::SetTargetAngle(float fAngle)
{
	m_fAxisAngle = fAngle;
}

void CBlock::Set_IsReverse(const bool & bIsReverse)
{
	m_bIsReverse = bIsReverse;
}

const bool & CBlock::Get_IsReverse()
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return m_bIsReverse;
}

void CBlock::Set_IsUseZBuffer(const bool & bIsUseZBuffer)
{
	m_bIsUseBuffer = bIsUseZBuffer;
}


void CBlock::SetDeltaValue(float fValue)
{
	m_fDeltaValue = fValue;
}

void CBlock::SetDeltaCount(float fValue)
{
	m_fDeltaCount = fValue;
}

float CBlock::GetDeltaValue()
{
	return m_fDeltaValue;
}

float CBlock::GetDeltaCount()
{
	return m_fDeltaCount;
}

int & CBlock::Get_RotSound()
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return m_RotSound;
}
