#pragma once

#ifndef __MAINBODY_H__
#define __MAINBODY_H__

#include "BodyPart.h"

class CMainBody : public ENGINE::CBodyPart
{
private:
	explicit CMainBody();

public:
	virtual ~CMainBody();

public:
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render();

private:
	HRESULT Initialize();

public:
	static CMainBody* Create(
		ENGINE::CTransform*		pTransformTarget,
		const wstring&			wstrPartName,
		const float*			fTimeCnt);
};

#endif