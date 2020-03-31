#pragma once

#ifndef __WHOLEBODY_H__
#define __WHOLEBODY_H__

#include "GameObject.h"

namespace ENGINE
{
	class CTransform;
}

class CWholeBody : public ENGINE::CGameObject
{
private:
	explicit CWholeBody(
		LPDIRECT3DDEVICE9 pGraphicDev,
		ENGINE::CTransform* pTransformTarget,
		const float* fTimeCnt);

public:
	virtual ~CWholeBody();

public:
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render();

private:
	virtual HRESULT Initialize();
	virtual HRESULT LateInit();
	virtual void Release();

private:
	HRESULT AddComponent();

public:
	static CWholeBody* Create(
		LPDIRECT3DDEVICE9 pGraphicDev,
		ENGINE::CTransform* pTransformTarget,
		const float* fTimeCnt);

private:
	ENGINE::CTransform* m_pTransform;
	ENGINE::CTransform*	m_pTransformTarget;
	const float*		m_fTimeCnt;

};

#endif