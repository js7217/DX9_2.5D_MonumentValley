#include "Engine_Include.h"
#include "Camera.h"
#include "PipeLine.h"
#include "SetTransform.h"
using namespace ENGINE;

CCamera::CCamera(LPDIRECT3DDEVICE9 pGraphicDev)
	:CGameObject(pGraphicDev)
	, m_bIsOrtho(false)
{
	ZeroMemory(&m_vEye, sizeof(D3DXVECTOR3));
	ZeroMemory(&m_vAt, sizeof(D3DXVECTOR3));

	D3DXMatrixIdentity(&m_matView);
	D3DXMatrixIdentity(&m_matProj);
}

CCamera::~CCamera()
{
}

void CCamera::MakeViewMatrix(const D3DXVECTOR3 * pEye, const D3DXVECTOR3 * pAt, const D3DXVECTOR3 * pUp)
{
	CPipeline::MakeViewMatrix(&m_matView, pEye, pAt, pUp);
	//m_pGraphicDev->SetTransform(D3DTS_VIEW, &m_matView);
	CSetTransForm::Set_TransForm(D3DTS_VIEW, &m_matView);
}

void CCamera::MakeProjectionMatrix(
	const float & fFovY, const float & fAspect, 
	const float & fNear, const float & fFar,
	const float& fRatioX, const float& fRatioY)
{
	if (m_bIsOrtho)
	{
		D3DXMatrixOrthoLH(&m_matProj, fRatioX, fRatioY, fNear, fFar);
	//	m_pGraphicDev->SetRenderState(D3DRS_ZENABLE, FALSE);
	}
	else
	{
		CPipeline::MakeProjectionMatrix(&m_matProj, fFovY, fAspect, fNear, fFar);
	//	m_pGraphicDev->SetRenderState(D3DRS_ZENABLE, TRUE);
	}

	CSetTransForm::Set_TransForm(D3DTS_PROJECTION, &m_matProj);
}
