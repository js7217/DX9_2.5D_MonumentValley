#pragma once

#ifndef __RENDERER_H__
#define __RENDERER_H__

BEGIN(ENGINE)

class CScene;
class ENGINE_DLL CRenderer
{
private:
	explicit CRenderer(LPDIRECT3DDEVICE9 pGraphicDev);
public:
	~CRenderer();

public:
	void SetScene(CScene* pScene);

public:
	void Render(); // 렌더만 필요함.

private:
	HRESULT Initialize();
	void Release();

public:
	static CRenderer* Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	LPDIRECT3DDEVICE9	m_pGraphicDev;
	CScene*				m_pScene;
};



END
#endif // !__RENDERER_H__
