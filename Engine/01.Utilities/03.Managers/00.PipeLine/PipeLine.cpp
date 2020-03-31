#include "PipeLine.h"
#include "MathMgr.h"

using namespace ENGINE;

void CPipeline::MakeWorldMatrix(
	D3DXMATRIX* pOut,
	const D3DXVECTOR3* pScale,
	const float* pRadian,
	const D3DXVECTOR3* pPosition,
	const D3DXMATRIX* pmatRotTaget,
	const D3DXMATRIX* pmatTagetWorld
)
{
	D3DXMatrixIdentity(pOut);

	D3DXVECTOR3 vRight = { 1.f, 0.f, 0.f };
	D3DXVECTOR3 vUp = { 0.f, 1.f, 0.f };
	D3DXVECTOR3 vLook = { 0.f, 0.f, 1.f };
	D3DXVECTOR3 vPos = *pPosition;

	// 크기
	vRight.x *= pScale->x;
	vUp.y *= pScale->y;
	vLook.z *= pScale->z;

	//회전 X
	CMathMgr::MyRotationX(&vRight, &vRight, pRadian[ANGLE_X]);
	CMathMgr::MyRotationX(&vUp, &vUp, pRadian[ANGLE_X]);
	CMathMgr::MyRotationX(&vLook, &vLook, pRadian[ANGLE_X]);

	// 회전 Y
	CMathMgr::MyRotationY(&vRight, &vRight, pRadian[ANGLE_Y]);
	CMathMgr::MyRotationY(&vUp, &vUp, pRadian[ANGLE_Y]);
	CMathMgr::MyRotationY(&vLook, &vLook, pRadian[ANGLE_Y]);


	// 회전 Z
	CMathMgr::MyRotationZ(&vRight, &vRight, pRadian[ANGLE_Z]);
	CMathMgr::MyRotationZ(&vUp, &vUp, pRadian[ANGLE_Z]);
	CMathMgr::MyRotationZ(&vLook, &vLook, pRadian[ANGLE_Z]);




	// 위에서 설정한 vRight, vUp, vLook, vPos를 조합하면 행렬이 완성된다.
	D3DXVECTOR3 vTargetPos = {};
	vTargetPos.x = (*pmatTagetWorld)._41;
	vTargetPos.y = (*pmatTagetWorld)._42;
	vTargetPos.z = (*pmatTagetWorld)._43;



	vPos = vPos - vTargetPos;
	MakeTransformMatrix(pOut, &vRight, &vUp, &vLook, &vPos);
	D3DXMATRIX matTargetWorld = (*pmatTagetWorld);

	/*matTargetWorld._11 = 1.f;
	matTargetWorld._22 = 1.f;
	matTargetWorld._33 = 1.f;*/





	*pOut *= (*pmatRotTaget) * matTargetWorld;
}

void CPipeline::MakeViewMatrix(
	D3DXMATRIX* pOut,
	const D3DXVECTOR3* pEye,
	const D3DXVECTOR3* pAt,
	const D3DXVECTOR3* pUp)
{
	D3DXMatrixIdentity(pOut);

	// 카메라의 월드행렬 구성.
	D3DXVECTOR3 vRight, vUp, vLook, vPos;

	vLook = (*pAt) - (*pEye);
	D3DXVec3Normalize(&vLook, &vLook);

	// 외적을 이용한 vRight 도출. 외적 순서 중요!
	D3DXVec3Cross(&vRight, pUp, &vLook);
	D3DXVec3Normalize(&vRight, &vRight);

	// 외적을 이용한 vUp 도출. 외적 순서 중요!
	D3DXVec3Cross(&vUp, &vLook, &vRight);
	D3DXVec3Normalize(&vUp, &vUp);

	vPos = *pEye;

	// 카메라의 월드행렬 완성.
	MakeTransformMatrix(pOut, &vRight, &vUp, &vLook, &vPos);

	// 카메라의 월드행렬의 역행렬이 곧 뷰행렬이 된다.
	// 역행렬 구하는 함수.
	// D3DXMatrixInverse(out, 행렬식, in)
	D3DXMatrixInverse(pOut, nullptr, pOut);
}

void CPipeline::MakeProjectionMatrix(
	D3DXMATRIX * pOut,
	const float & fFovY,
	const float & fAspect,
	const float & fNear,
	const float & fFar)
{
	D3DXMatrixIdentity(pOut);

	float fScale = 1.f / tanf(fFovY / 2.f);

	pOut->_11 = fScale / fAspect; // fAspect는 종횡비. 정사각형 상태인 뷰스페이스 상태를
								  // 직사각형인 뷰포트 상태로 종횡비에 맞게 x값을 바꿔준다. 이렇게 해야 왜곡 현상이 없어진다.
	pOut->_22 = fScale;

	pOut->_33 = fFar / (fFar - fNear);
	pOut->_43 = (-fNear * fFar) / (fFar - fNear);

	pOut->_34 = 1.f;
	pOut->_44 = 0.f;
}

void CPipeline::MakeTransformMatrix(
	D3DXMATRIX* pOut,
	const D3DXVECTOR3* pRight,
	const D3DXVECTOR3* pUp,
	const D3DXVECTOR3* pLook,
	const D3DXVECTOR3* pPosition)
{
	// 행렬 1행~4행
	memcpy(pOut->m[0], pRight, sizeof(D3DXVECTOR3));
	memcpy(pOut->m[1], pUp, sizeof(D3DXVECTOR3));
	memcpy(pOut->m[2], pLook, sizeof(D3DXVECTOR3));
	memcpy(pOut->m[3], pPosition, sizeof(D3DXVECTOR3));
}

void CPipeline::MyTransformCoord(D3DXVECTOR3 * pOut, const D3DXVECTOR3 * pIn, const D3DXMATRIX * pMatrix)
{
	D3DXVECTOR4 vVec4 = { pIn->x, pIn->y, pIn->z, 1.f }; // 벡터4짜리로 만들어야 행렬과계산이 가능.

	pOut->x = vVec4.x * pMatrix->_11
		+ vVec4.y * pMatrix->_21
		+ vVec4.z * pMatrix->_31
		+ vVec4.w * pMatrix->_41;

	pOut->y = vVec4.x * pMatrix->_12
		+ vVec4.y * pMatrix->_22
		+ vVec4.z * pMatrix->_32
		+ vVec4.w * pMatrix->_42;

	pOut->z = vVec4.x * pMatrix->_13
		+ vVec4.y * pMatrix->_23
		+ vVec4.z * pMatrix->_33
		+ vVec4.w * pMatrix->_43;

	float fZ = vVec4.x * pMatrix->_14
		+ vVec4.y * pMatrix->_24
		+ vVec4.z * pMatrix->_34
		+ vVec4.w * pMatrix->_44;

	*pOut /= fZ;
}
