#pragma once

#ifndef __PIPELINE_H__
#define __PIPELINE_H__

#include "Engine_Include.h"

BEGIN(ENGINE)

class ENGINE_DLL CPipeline
{
public:
	static void MakeWorldMatrix(
		D3DXMATRIX* pOut,
		const D3DXVECTOR3* pScale,
		const float* pRadian,
		const D3DXVECTOR3* pPosition,
		const D3DXMATRIX* pmatRotTaget,
		const D3DXMATRIX* pmatTagetWorld);

	static void MakeViewMatrix(
		D3DXMATRIX* pOut,
		const D3DXVECTOR3* pEye,
		const D3DXVECTOR3* pAt,
		const D3DXVECTOR3* pUp);

	static void MakeProjectionMatrix(
		D3DXMATRIX* pOut,
		const float& fFovY,
		const float& fAspect,
		const float& fNear,
		const float& fFar);

	static void MakeTransformMatrix(
		D3DXMATRIX* pOut,
		const D3DXVECTOR3* pRight,
		const D3DXVECTOR3* pUp,
		const D3DXVECTOR3* pLook,
		const D3DXVECTOR3* pPosition);

	static void MyTransformCoord(
		D3DXVECTOR3* pOut,
		const D3DXVECTOR3* pIn,
		const D3DXMATRIX* pMatrix);
};

END

#endif