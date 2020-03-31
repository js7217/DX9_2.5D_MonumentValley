#pragma once

#ifndef __CLIENT_STRUCT_H__
#define __CLIENT_STRUCT_H__

typedef struct tagTexInfo
{
	// 이미지 한장을 제어하기 위한 Com객체의 포인터
	LPDIRECT3DTEXTURE9	pTexture;

	// 이미지 한장의 정보를 저장할 구조체
	D3DXIMAGE_INFO		tImgInfo;
}TEX_INFO;

#endif