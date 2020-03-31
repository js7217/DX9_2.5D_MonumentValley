#pragma once

#ifndef __ARM_H__
#define __ARM_H__

namespace ENGINE
{
	class CTexture;
}

#include "BodyPart.h"

class CArm : public ENGINE::CBodyPart
{
private:
	explicit CArm();

public:
	virtual ~CArm();

public:
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render();

private:
	HRESULT Initialize();

public:
	static CArm* Create(
		ENGINE::CTransform*		pTransformTarget,
		const wstring&			wstrPartName,
		const float*			fTimeCnt);

private:
	ENGINE::CTransform*		m_pTramsformOpposite;
	ENGINE::CTexture*		m_pTexture;
};

#endif