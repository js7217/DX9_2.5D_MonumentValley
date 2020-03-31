#pragma once

#ifndef __COLLISION_H__
#define __COLLISION_H__

#include "Component.h"

BEGIN(ENGINE)

class ENGINE_DLL CCollision : public CComponent
{
public:
	enum COLLISION_TYPE { TERRAIN, MOUSE, SPHERE, COLL_END };

protected:
	explicit CCollision();
	explicit CCollision(COLLISION_TYPE eType);
public:
	virtual ~CCollision() PURE;

protected:
	COLLISION_TYPE m_eCollType;
};

END

#endif