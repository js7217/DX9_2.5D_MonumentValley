#pragma once

#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "GameObject.h"

BEGIN(ENGINE)

class ENGINE_DLL CCamera : public CGameObject
{
protected:
	explicit CCamera(LPDIRECT3DDEVICE9 pGraphicDev);

public:
	virtual ~CCamera();

protected:
	void MakeViewMatrix(const D3DXVECTOR3* pEye,
		const D3DXVECTOR3* pAt, const D3DXVECTOR3* pUp);

	void MakeProjectionMatrix(const float& fFovY, const float& fAspect,
		const float& fNear, const float& fFar, const float& fRatioX, const float& fRatioY);

protected: // 카메라는 결국 뷰행렬, 투영행렬을 만든다.
	D3DXMATRIX	m_matView;
	D3DXMATRIX	m_matProj;
	D3DXVECTOR3	m_vEye;
	D3DXVECTOR3	m_vAt;
	bool		m_bIsOrtho;
};

END

#endif