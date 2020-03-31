#pragma once 

#ifndef __ENGINE_STRUCT_H__
#define __ENGINE_STRUCT_H__

BEGIN(ENGINE)

typedef struct tagVertexColor
{
	D3DXVECTOR3 vPos; // ������ ��ġ
	DWORD		dwColor; // ������ ����
}VTX_COL;

const DWORD VTXFVF_COL = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX0;
// FVF �Ӽ��� ��������!!! x,y,z ���� ������ �÷��� ������ �ؽ��� ������ ���� ��.
// ���ǻ��� : ����ü�� ������ FVF �Ӽ��� �����ִ� ������ ��ġ�ؾ� �۵��Ѵ�.
typedef struct tagVertexTexture
{
	D3DXVECTOR3 vPos; // ������ ��ġ
	D3DXVECTOR2	vTex; // �ؽ��� UV ��ǥ
}VTX_TEX;

const DWORD VTXFVF_TEX = D3DFVF_XYZ | D3DFVF_TEX1;
// x,y,z �� ��ǥ�� ������ �ؽ��� ���� 1���� �ϰڴ�.

typedef struct tagVertexCube
{
	D3DXVECTOR3 vPos;		// ���� ��ġ
	D3DXVECTOR3 vTex;		// ť�� �ؽ�ó ��ǥ 3D
}VTX_CUBE;

const DWORD VTXFVF_CUBE = D3DFVF_XYZ | D3DFVF_TEX1 | D3DFVF_TEXCOORDSIZE3(0);

typedef struct tagVertexSphere
{
	D3DXVECTOR3 vPos;		// ���� ��ġ
	DWORD dwDiff;			// ť�� �ؽ�ó ��ǥ 3D
}VTX_SPHERE;

const DWORD VTXFVF_SPHERE = D3DFVF_XYZ | D3DFVF_DIFFUSE;

typedef struct tagIndex16
{
	WORD _1, _2, _3; // ���� 2����Ʈ
}INDEX16;

typedef struct tagIndex32
{
	DWORD _1, _2, _3; // ���� 4����Ʈ
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