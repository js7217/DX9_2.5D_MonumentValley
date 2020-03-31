#pragma once

#ifndef __HEAD_H__
#define __HEAD_H__

#include "BodyPart.h"

class CHead : public ENGINE::CBodyPart
{
private:
	explicit CHead();

public:
	virtual ~CHead();

public:
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render();

private:
	HRESULT Initialize();

public:
	static CHead* Create(
		ENGINE::CTransform*		pTransformTarget,
		const wstring&			wstrPartName,
		const float*			fTimeCnt);
};

#endif