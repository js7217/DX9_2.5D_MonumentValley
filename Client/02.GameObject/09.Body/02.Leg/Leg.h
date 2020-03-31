#pragma once

#ifndef __LEG_H__
#define __LEG_H__

#include "BodyPart.h"

class CLeg : public ENGINE::CBodyPart
{
private:
	explicit CLeg();

public:
	virtual ~CLeg();

public:
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render();

private:
	HRESULT Initialize();

public:
	static CLeg* Create(
		ENGINE::CTransform*		pTransformTarget,
		const wstring&			wstrPartName,
		const float*			fTimeCnt);

private:
	ENGINE::CTransform*			m_pTramsformOpposite;
};

#endif