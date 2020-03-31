#pragma once

#ifndef __SETTRANSFORM_H__
#define __SETTRANSFORM_H__

#include "Engine_Include.h"

BEGIN(ENGINE)

class ENGINE_DLL CSetTransForm
{
public:
	static const D3DXMATRIX& GetMatWorld();
	static const D3DXMATRIX& GetMatView();
	static const D3DXMATRIX& GetMatProj();
public:
	static void Set_TransForm(D3DTRANSFORMSTATETYPE eTransformStateType, const D3DXMATRIX* matTrans);
private:
	static D3DXMATRIX m_matWorld;
	static D3DXMATRIX m_matView;
	static D3DXMATRIX m_matProj;
};

END

#endif