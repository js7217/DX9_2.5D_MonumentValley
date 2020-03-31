#pragma once

#ifndef __STATICCAMERA_H__
#define __STATICCAMERA_H__

#include "Camera.h"

namespace ENGINE
{
	class CTimeMgr;
	class CManagement;
	class CTransform;
	class CKeyMgr;
}

class CStaticCamera : public ENGINE::CCamera
{
private:
	explicit CStaticCamera(LPDIRECT3DDEVICE9 pGraphicDev);

public:
	virtual ~CStaticCamera();

public:
	virtual void Update();
	virtual void LateUpdate();

private:
	virtual HRESULT Initialize();
	virtual HRESULT LateInit();
	virtual void Release();

private:
	void KeyInput();
	void TargetRenewal();
	void OrthoTarget();

public:
	float*	GetHeight();
	D3DXVECTOR3& GetCamPos();
	D3DXVECTOR3& GetCamDir();
	void	SetHeight(float fHeight);

public:
	void SetTargetPos(const D3DXVECTOR3& vPos);
	void SetAngleX(const float& fAngleX);
	void SetAngleY(const float& fAngleY);
	void SetCamAngle(const float& fCamAngle);
	void SetTargetDist(const float& fTargetDist);
	void SetRatio(const float& fRatioX, const float& fRatioY);
	void Set_Stage5ZoomIn(bool Check);
public:
	void Stage5ZoomIn();

public:
	static CStaticCamera* Create(LPDIRECT3DDEVICE9 pGraphicDev, const D3DXVECTOR3& vTargetPos,
		const float& fAngleX, const float& fAngleY,
		const float& fCamAngle, const float& fTargetDist,
		const float& fRatioX, const float& fRatioY);

private:
	ENGINE::CTimeMgr*			m_pTimeMgr;
	ENGINE::CManagement*		m_pManagement;
	ENGINE::CTransform*			m_pCamTarget;
	ENGINE::CKeyMgr*			m_pKeyMgr;
	float						m_fTargetDist; // Ÿ�ٰ��� �Ÿ�
	float						m_fCamAngle; // ī�޶� ����
	float						m_fCamSpeed; // ī�޶� ���ǵ�

	D3DXVECTOR3					m_vCamPos;
	D3DXVECTOR3					m_vCamDir;
	D3DXVECTOR3					m_vTargetPos;

	float						m_fRatioX;		//�������� ����
	float						m_fRatioY;		//�������� ����


	float						m_fHeight;
	float						m_fAngleX;
	float						m_fAngleY;
	bool						m_Stage5ZoomIn;
	float						m_fStage5Angle;
};
#endif