#pragma once

#ifndef __MATHMGR_H__
#define __MATHMGR_H__

#include "Engine_Include.h"

BEGIN(ENGINE)

class ENGINE_DLL CMathMgr
{
public:
	static void MyRotationX(
		D3DXVECTOR3* pOut,
		const D3DXVECTOR3* pIn,
		float fRadianX);

	static void MyRotationY(
		D3DXVECTOR3* pOut,
		const D3DXVECTOR3* pIn,
		float fRadianY);

	static void MyRotationZ(
		D3DXVECTOR3* pOut,
		const D3DXVECTOR3* pIn,
		float fRadianZ);
};

END

#endif