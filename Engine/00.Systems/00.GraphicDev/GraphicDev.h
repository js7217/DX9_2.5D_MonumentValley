#pragma once

#ifndef __GRAPHICDEV_H__
#define __GRAPHICDEV_H__

#include "Engine_Include.h"

BEGIN(ENGINE)

class ENGINE_DLL CGraphicDev
{
	DECLARE_SINGLETON(CGraphicDev)

public:
	enum WIN_MODE { FULL, WIN };

private:
	CGraphicDev();
	~CGraphicDev();

public:
	LPDIRECT3DDEVICE9 GetDevice();
	LPD3DXSPRITE GetSprite();
	LPD3DXFONT GetFont();

public:
	HRESULT InitDevice(HWND hWnd,
		const DWORD& dwWinCX,
		const DWORD& dwWinCY,
		WIN_MODE eMode);

private:
	void Release();

private:
	LPDIRECT3D9			m_pSDK;	// 장치를 조사할 Com객체의 포인터.
	LPDIRECT3DDEVICE9	m_pGraphicDev; // 장치를 제어할 Com객체의 포인터.

	// DirectX에서 2D 이미지를 렌더링하게 해주는 Com객체의 포인터
	LPD3DXSPRITE		m_pSprite;

	// DirectX에서 텍스트를 출력하기 위한 Com객체의 포인터. (Direct Font)
	LPD3DXFONT			m_pFont;

	// COM (Component Object Model)
};

END
#endif