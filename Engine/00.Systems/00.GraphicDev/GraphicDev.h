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
	LPDIRECT3D9			m_pSDK;	// ��ġ�� ������ Com��ü�� ������.
	LPDIRECT3DDEVICE9	m_pGraphicDev; // ��ġ�� ������ Com��ü�� ������.

	// DirectX���� 2D �̹����� �������ϰ� ���ִ� Com��ü�� ������
	LPD3DXSPRITE		m_pSprite;

	// DirectX���� �ؽ�Ʈ�� ����ϱ� ���� Com��ü�� ������. (Direct Font)
	LPD3DXFONT			m_pFont;

	// COM (Component Object Model)
};

END
#endif