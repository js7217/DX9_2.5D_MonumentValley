#pragma once

#ifndef __CLIENT_STRUCT_H__
#define __CLIENT_STRUCT_H__

typedef struct tagTexInfo
{
	// �̹��� ������ �����ϱ� ���� Com��ü�� ������
	LPDIRECT3DTEXTURE9	pTexture;

	// �̹��� ������ ������ ������ ����ü
	D3DXIMAGE_INFO		tImgInfo;
}TEX_INFO;

#endif