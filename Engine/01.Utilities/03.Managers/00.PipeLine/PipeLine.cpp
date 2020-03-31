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

	// ũ��
	vRight.x *= pScale->x;
	vUp.y *= pScale->y;
	vLook.z *= pScale->z;

	//ȸ�� X
	CMathMgr::MyRotationX(&vRight, &vRight, pRadian[ANGLE_X]);
	CMathMgr::MyRotationX(&vUp, &vUp, pRadian[ANGLE_X]);
	CMathMgr::MyRotationX(&vLook, &vLook, pRadian[ANGLE_X]);

	// ȸ�� Y
	CMathMgr::MyRotationY(&vRight, &vRight, pRadian[ANGLE_Y]);
	CMathMgr::MyRotationY(&vUp, &vUp, pRadian[ANGLE_Y]);
	CMathMgr::MyRotationY(&vLook, &vLook, pRadian[ANGLE_Y]);


	// ȸ�� Z
	CMathMgr::MyRotationZ(&vRight, &vRight, pRadian[ANGLE_Z]);
	CMathMgr::MyRotationZ(&vUp, &vUp, pRadian[ANGLE_Z]);
	CMathMgr::MyRotationZ(&vLook, &vLook, pRadian[ANGLE_Z]);




	// ������ ������ vRight, vUp, vLook, vPos�� �����ϸ� ����� �ϼ��ȴ�.
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

	// ī�޶��� ������� ����.
	D3DXVECTOR3 vRight, vUp, vLook, vPos;

	vLook = (*pAt) - (*pEye);
	D3DXVec3Normalize(&vLook, &vLook);

	// ������ �̿��� vRight ����. ���� ���� �߿�!
	D3DXVec3Cross(&vRight, pUp, &vLook);
	D3DXVec3Normalize(&vRight, &vRight);

	// ������ �̿��� vUp ����. ���� ���� �߿�!
	D3DXVec3Cross(&vUp, &vLook, &vRight);
	D3DXVec3Normalize(&vUp, &vUp);

	vPos = *pEye;

	// ī�޶��� ������� �ϼ�.
	MakeTransformMatrix(pOut, &vRight, &vUp, &vLook, &vPos);

	// ī�޶��� ��������� ������� �� ������� �ȴ�.
	// ����� ���ϴ� �Լ�.
	// D3DXMatrixInverse(out, ��Ľ�, in)
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

	pOut->_11 = fScale / fAspect; // fAspect�� ��Ⱦ��. ���簢�� ������ �佺���̽� ���¸�
								  // ���簢���� ����Ʈ ���·� ��Ⱦ�� �°� x���� �ٲ��ش�. �̷��� �ؾ� �ְ� ������ ��������.
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
	// ��� 1��~4��
	memcpy(pOut->m[0], pRight, sizeof(D3DXVECTOR3));
	memcpy(pOut->m[1], pUp, sizeof(D3DXVECTOR3));
	memcpy(pOut->m[2], pLook, sizeof(D3DXVECTOR3));
	memcpy(pOut->m[3], pPosition, sizeof(D3DXVECTOR3));
}

void CPipeline::MyTransformCoord(D3DXVECTOR3 * pOut, const D3DXVECTOR3 * pIn, const D3DXMATRIX * pMatrix)
{
	D3DXVECTOR4 vVec4 = { pIn->x, pIn->y, pIn->z, 1.f }; // ����4¥���� ������ ��İ������ ����.

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
