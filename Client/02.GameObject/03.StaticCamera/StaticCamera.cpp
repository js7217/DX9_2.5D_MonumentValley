#include "stdafx.h"
#include "StaticCamera.h"
#include "Transform.h"
#include "Layer.h"
#include "SetTransform.h"
#include "KeyMgr.h"


CStaticCamera::CStaticCamera(LPDIRECT3DDEVICE9 pGraphicDev)
	: ENGINE::CCamera(pGraphicDev)
	, m_pTimeMgr(ENGINE::Get_TimeMgr())
	, m_pManagement(ENGINE::Get_Management())
	, m_pKeyMgr(ENGINE::CKeyMgr::GetInstance())
	, m_pCamTarget(nullptr), m_fTargetDist(0.f)
	, m_fCamAngle(0.f), m_fCamSpeed(0.f), m_Stage5ZoomIn(false), m_fStage5Angle(0.f)
{
	ZeroMemory(&m_vCamPos, sizeof(D3DXVECTOR3));
	ZeroMemory(&m_vCamDir, sizeof(D3DXVECTOR3));
}

CStaticCamera::~CStaticCamera()
{
	Release();
}

void CStaticCamera::Update()
{
	ENGINE::CGameObject::LateInit();
	KeyInput();
	Stage5ZoomIn();
}

void CStaticCamera::LateUpdate()
{
	if(m_bIsOrtho)
		OrthoTarget();
	else
		TargetRenewal();
}

HRESULT CStaticCamera::Initialize()
{
	/*m_fTargetDist = 10.f;
	m_fCamAngle = 45.f;
	m_fCamSpeed = 10.f;*/

	//m_fCamAngle = 35.25f;
	//m_fTargetDist = 17.f;
	//m_fRatioX = 20.8f;
	//m_fRatioY = 15.6f;

//	m_fCamAngle = 40.f;
//	m_fTargetDist = 34.f;
//	m_fRatioX = 30.39f;
//	m_fRatioY = 22.8f;

//	m_fCamAngle = 25.3f;
//	m_fTargetDist = 25.f;
//	m_fRatioX = 21.6f;
//	m_fRatioY = 16.2f;

	m_bIsOrtho = true;

	m_fHeight = 0;

	return S_OK;
}

HRESULT CStaticCamera::LateInit()
{
	m_pCamTarget = dynamic_cast<ENGINE::CTransform*>(m_pManagement->
		GetComponent(ENGINE::CLayer::OBJECT,L"Player", L"Transform"));
	NULL_CHECK_RETURN(m_pCamTarget, E_FAIL);
	return S_OK;
}

void CStaticCamera::Release()
{
}

void CStaticCamera::KeyInput()
{
	//D3DXVECTOR3 vPos = m_pCamTarget->GetPos();


	if (GetAsyncKeyState(VK_ADD) & 0x8000)
		m_fTargetDist -= m_fCamSpeed * m_pTimeMgr->GetDeltaTime();
	if (GetAsyncKeyState(VK_SUBTRACT) & 0x8000)
		m_fTargetDist += m_fCamSpeed * m_pTimeMgr->GetDeltaTime();

	if (m_pKeyMgr->KeyDown(KEY_SPACE))
	{
		m_bIsOrtho = !m_bIsOrtho;
	//	m_fCamAngle = 35.25f;
	//	m_fTargetDist = 17.f;
	//	m_fCamAngle = 25.3f;
	//	m_fTargetDist = 25.f;

	//	m_fCamAngle = 40.f;
	//	m_fTargetDist = 34.f;
	}
	if (m_pKeyMgr->KeyDown(KEY_P))
	{
		m_Stage5ZoomIn = true;
	}
}

void CStaticCamera::TargetRenewal() 
{
	// 1. ī�޶� ��ġ ��� 2. Ÿ���� Right���͸� �̿��� ȸ�� 3.����� �����.
	D3DXVECTOR3 vEye = m_pCamTarget->GetDir() * -1.f;
	D3DXVec3Normalize(&vEye, &vEye); // ī�޶��� ��ġ�� Ÿ���� �����̴�. �� �ݴ���� -> ���� -1�� ����

	vEye *= m_fTargetDist; // Ÿ�ٰ� ī�޶��� �Ÿ��� ��Ÿ��.

	D3DXVECTOR3 vRight = {}; // ���� Ÿ���� x�� -> Right���͸� �����´�.
	memcpy(&vRight, m_pCamTarget->GetWorldMatrix().m[0], sizeof(D3DXVECTOR3));

	D3DXMATRIX matRotAxis; // ������ Right���͸� �̿��Ͽ� ȸ�������� ����.

	D3DXMatrixRotationAxis(&matRotAxis, &vRight, D3DXToRadian(m_fCamAngle));
	D3DXVec3TransformNormal(&vEye, &vEye, &matRotAxis); // ȸ���� �ѵ�
	// ������ �����ͼ� Eye�� �����Ų��.


	vEye += m_pCamTarget->GetPos(); // ���ʹ� ��� 0,0 ���� ����.
	// ��Ȯ�� ��ġ�ľ��� ����.

	ENGINE::CCamera::MakeViewMatrix(&vEye, &m_pCamTarget->GetPos(),
		&D3DXVECTOR3(0.f, 1.f, 0.f));
}

void CStaticCamera::OrthoTarget()
{
	D3DXVECTOR3 vDir;
	D3DXVECTOR3 vLook = { 0.f, 0.f, 1.f };
//	D3DXVECTOR3 vPos = { 13.35f, 0.f, 9.f };
//	D3DXVECTOR3 vPos = { 8.f, 0.f, 8.f };
//	D3DXVECTOR3 vPos  = { 22.31f, 0.f, 13.81f };
	D3DXMATRIX matRotX, matRotY;
	D3DXMatrixRotationX(&matRotX, D3DXToRadian(m_fAngleX));
	D3DXMatrixRotationY(&matRotY, D3DXToRadian(m_fAngleY));
	//D3DXMatrixRotationY(&matRotY, D3DXToRadian(50.f));

	D3DXVec3TransformNormal(&vDir, &vLook, &(matRotY));
	D3DXVec3Normalize(&vDir, &vDir);

	// 1. ī�޶� ��ġ ��� 2. Ÿ���� Right���͸� �̿��� ȸ�� 3.����� �����.
	m_vCamPos = vDir * -1.f;
	D3DXVec3Normalize(&m_vCamPos, &m_vCamPos); // ī�޶��� ��ġ�� Ÿ���� �����̴�. �� �ݴ���� -> ���� -1�� ����

	m_vCamPos *= m_fTargetDist; // Ÿ�ٰ� ī�޶��� �Ÿ��� ��Ÿ��.

	D3DXVECTOR3 vRight = {}; // ���� Ÿ���� x�� -> Right���͸� �����´�.
	memcpy(&vRight, matRotY.m[0], sizeof(D3DXVECTOR3));

	D3DXMATRIX matRotAxis; // ������ Right���͸� �̿��Ͽ� ȸ�������� ����.

	D3DXMatrixRotationAxis(&matRotAxis, &vRight, D3DXToRadian(m_fCamAngle));
	D3DXVec3TransformNormal(&m_vCamPos, &m_vCamPos, &matRotAxis); // ȸ���� �ѵ�
																  // ������ �����ͼ� Eye�� �����Ų��.

	m_vCamPos += m_vTargetPos; // ���ʹ� ��� 0,0 ���� ����.
							
			 // ��Ȯ�� ��ġ�ľ��� ����.

	//Eye�� At�� y��ǥ�� ����
	m_vCamPos.y += m_fHeight;
	m_vTargetPos.y += m_fHeight;
	m_vCamDir = m_vTargetPos - m_vCamPos;
	D3DXVec3Normalize(&m_vCamDir, &m_vCamDir);

	ENGINE::CCamera::MakeViewMatrix(&m_vCamPos, &m_vTargetPos,
		&D3DXVECTOR3(0.f, 1.f, 0.f));

	ENGINE::CCamera::MakeProjectionMatrix(D3DXToRadian(45.f), WINCX / (float)WINCY, 1.f, 1000.f, m_fRatioX, m_fRatioY);
}

float * CStaticCamera::GetHeight()
{
	return &m_fHeight;
}

D3DXVECTOR3 & CStaticCamera::GetCamPos()
{
	// TODO: ���⿡ ��ȯ ������ �����մϴ�.
	return m_vCamPos;
}

D3DXVECTOR3 & CStaticCamera::GetCamDir()
{
	return m_vCamDir;
}

void CStaticCamera::SetHeight(float fHeight)
{
	m_fHeight = fHeight;
}

void CStaticCamera::SetTargetPos(const D3DXVECTOR3 & vPos)
{
	m_vTargetPos = vPos;
}

void CStaticCamera::SetAngleX(const float & fAngleX)
{
	m_fAngleX = fAngleX;
}

void CStaticCamera::SetAngleY(const float & fAngleY)
{
	m_fAngleY = fAngleY;
}

void CStaticCamera::SetCamAngle(const float & fCamAngle)
{
	m_fCamAngle = fCamAngle;
}

void CStaticCamera::SetTargetDist(const float & fTargetDist)
{
	m_fTargetDist = fTargetDist;
}

void CStaticCamera::SetRatio(const float & fRatioX, const float & fRatioY)
{
	m_fRatioX = fRatioX;
	m_fRatioY = fRatioY;
}

void CStaticCamera::Set_Stage5ZoomIn(bool Check)
{
	m_Stage5ZoomIn = Check;
}

void CStaticCamera::Stage5ZoomIn()
{
	if (m_Stage5ZoomIn == true)
	{
		m_fStage5Angle += m_pTimeMgr->GetDeltaTime();

		m_fRatioX = m_fRatioX - (160.f * tanf(D3DXToRadian(m_fStage5Angle)));
		m_fRatioY = m_fRatioY - (120.f * tanf(D3DXToRadian(m_fStage5Angle)));

		if (m_fRatioX <= 28.f || m_fRatioY <= 21.f)
		{
			m_fRatioX = 28.f;
			m_fRatioY = 21.f;
			m_Stage5ZoomIn = false;
		}
	}
}

CStaticCamera * CStaticCamera::Create(LPDIRECT3DDEVICE9 pGraphicDev, const D3DXVECTOR3& vTargetPos,
	const float& fAngleX, const float& fAngleY,
	const float& fCamAngle, const float& fTargetDist,
	const float& fRatioX, const float& fRatioY)
{
	CStaticCamera* pInstance = new CStaticCamera(pGraphicDev);

	if (FAILED(pInstance->Initialize()))
	{
		ENGINE::SafeDelete(pInstance);
		return nullptr;
	}

	pInstance->SetTargetPos(vTargetPos);
	pInstance->SetAngleX(fAngleX);
	pInstance->SetAngleY(fAngleY);
	pInstance->SetCamAngle(fCamAngle);
	pInstance->SetTargetDist(fTargetDist);
	pInstance->SetRatio(fRatioX, fRatioY);

	pInstance->MakeProjectionMatrix(D3DXToRadian(45.f), WINCX / (float)WINCY, 1.f, 1000.f, fRatioX, fRatioY);

	return pInstance;
}
