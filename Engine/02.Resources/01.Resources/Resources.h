#pragma once

#ifndef __RESOURCES_H__
#define __RESOURCES_H__

#include "Component.h"

BEGIN(ENGINE)

class ENGINE_DLL CResources : public CComponent
{
protected:
	explicit CResources(LPDIRECT3DDEVICE9 pGraphicDev);
public:
	virtual ~CResources();

public:
	virtual void Render() PURE;

	// 프로토 타입 패턴
	virtual CResources* CloneResource() PURE;
	virtual void Set_Transform() PURE;
protected:
	LPDIRECT3DDEVICE9	m_pGraphicDev;
	WORD*				m_pRefCnt;
};

END

#endif