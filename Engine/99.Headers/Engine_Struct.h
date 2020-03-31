#pragma once 

#ifndef __ENGINE_STRUCT_H__
#define __ENGINE_STRUCT_H__

BEGIN(ENGINE)

typedef struct tagVertexColor
{
	D3DXVECTOR3 vPos; // 정점의 위치
	DWORD		dwColor; // 정점의 색상
}VTX_COL;

const DWORD VTXFVF_COL = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX0;
// FVF 속성을 정해주자!!! x,y,z 축을 가지며 컬러를 가지고 텍스쳐 매핑을 안할 것.
// 주의사항 : 구조체의 순번과 FVF 속성을 정해주는 순서가 일치해야 작동한다.
typedef struct tagVertexTexture
{
	D3DXVECTOR3 vPos; // 정점의 위치
	D3DXVECTOR2	vTex; // 텍스쳐 UV 좌표
}VTX_TEX;

const DWORD VTXFVF_TEX = D3DFVF_XYZ | D3DFVF_TEX1;
// x,y,z 축 좌표를 가지고 텍스쳐 매핑 1장을 하겠다.

typedef struct tagVertexCube
{
	D3DXVECTOR3 vPos;		// 정점 위치
	D3DXVECTOR3 vTex;		// 큐브 텍스처 좌표 3D
}VTX_CUBE;

const DWORD VTXFVF_CUBE = D3DFVF_XYZ | D3DFVF_TEX1 | D3DFVF_TEXCOORDSIZE3(0);

typedef struct tagVertexSphere
{
	D3DXVECTOR3 vPos;		// 정점 위치
	DWORD dwDiff;			// 큐브 텍스처 좌표 3D
}VTX_SPHERE;

const DWORD VTXFVF_SPHERE = D3DFVF_XYZ | D3DFVF_DIFFUSE;

typedef struct tagIndex16
{
	WORD _1, _2, _3; // 개당 2바이트
}INDEX16;

typedef struct tagIndex32
{
	DWORD _1, _2, _3; // 개당 4바이트
}INDEX32;

typedef struct tagInfo
{
	D3DXVECTOR3 vPos;
	D3DXVECTOR3 vDir;
	D3DXVECTOR3 vLook;
	D3DXVECTOR3 vSize;
	D3DXMATRIX	matWorld;
}INFO;

typedef struct tagARGB
{
	int iAlpha = 255;
	int iRed = 255;
	int iGreen = 255;
	int iBlue = 255;
}MYARGB;



END

#endif // !__ENGINE_DEFINE_H__