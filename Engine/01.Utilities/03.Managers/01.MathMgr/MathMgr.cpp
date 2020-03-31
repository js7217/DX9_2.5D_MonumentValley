#include "MathMgr.h"

using namespace ENGINE;

void CMathMgr::MyRotationX(
	D3DXVECTOR3* pOut, 
	const D3DXVECTOR3* pIn, 
	float fRadianX)
{
	/* X축 회전
	1	0	0	0
	0	c	s	0
	0	-s	c	0
	0	0	0	1	
	*/

	D3DXVECTOR3 vTemp = *pIn;

	pOut->x = vTemp.x;
	pOut->y = vTemp.y * cosf(fRadianX) + vTemp.z * -sinf(fRadianX);
	pOut->z = vTemp.y * sinf(fRadianX) + vTemp.z * cosf(fRadianX);
}

void CMathMgr::MyRotationY(
	D3DXVECTOR3* pOut, 
	const D3DXVECTOR3* pIn, 
	float fRadianY)
{
	/* Y축 회전
	c	0	-s	0
	0	1	0	0
	s	0	c	0
	0	0	0	1
	*/

	D3DXVECTOR3 vTemp = *pIn;

	pOut->x = vTemp.x * cosf(fRadianY) + vTemp.z * sinf(fRadianY);
	pOut->y = vTemp.y;
	pOut->z = vTemp.x * -sinf(fRadianY) + vTemp.z * cosf(fRadianY);
}

void CMathMgr::MyRotationZ(
	D3DXVECTOR3* pOut, 
	const D3DXVECTOR3* pIn, 
	float fRadianZ)
{
	/* Z축 회전
	c	s	0	0
	-s	c	0	0
	0	0	1	0
	0	0	0	1
	*/

	D3DXVECTOR3 vTemp = *pIn;

	pOut->x = vTemp.x * cosf(fRadianZ) + vTemp.y * -sinf(fRadianZ);
	pOut->y = vTemp.x * sinf(fRadianZ) + vTemp.y * cosf(fRadianZ);
	pOut->z = vTemp.z;
}
