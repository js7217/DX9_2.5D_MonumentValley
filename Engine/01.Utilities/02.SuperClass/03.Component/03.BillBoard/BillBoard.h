#pragma once

#ifndef __BILLBOARD_H__
#define __BILLBOARD_H__

#include "Component.h"

BEGIN(ENGINE)

class CTransform;
class ENGINE_DLL CBillBoard : public CComponent
{
private:
	explicit CBillBoard();
	explicit CBillBoard(ENGINE::CTransform* pTransform);
public:
	virtual ~CBillBoard();

public:
	virtual void LateUpdate();

public:
	static CBillBoard* Create(ENGINE::CTransform* pTransform);
private:
	ENGINE::CTransform* m_pTransform;
};

END
#endif