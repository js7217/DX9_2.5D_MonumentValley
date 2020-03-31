#pragma once

#ifndef __MANAGEMENT_H__
#define __MANAGEMENT_H__
#include "Renderer.h"
#include "Layer.h"

class CFrameMgr;
BEGIN(ENGINE)

class ENGINE_DLL CManagement
{
	DECLARE_SINGLETON(CManagement)

private:
	explicit CManagement();
public:
	~CManagement();

public:
	CComponent* GetComponent(CLayer::LAYER_ID eLayerID,
		const wstring& wstrObjectKey, const wstring& wstrComponentKey);

	list<CGameObject*>* GetLst(CLayer::LAYER_ID eLayerID,
		const wstring& wstrObjectKey);

public:
	// 씬체인지
	template <typename T>
	HRESULT SceneChange(T& functor)
	{
		if (m_pScene)
			ENGINE::SafeDelete(m_pScene);

		FAILED_CHECK_RETURN(functor(&m_pScene, m_pGraphicDev), E_FAIL);
		m_pRenderer->SetScene(m_pScene); // 렌더러쪽에 씬을 알려준다.
		
		return S_OK;
	}

public:
	HRESULT InitManagement(LPDIRECT3DDEVICE9 pGraphicDev);
	void Update();
	void LateUpdate();
	void Render();

private:
	void Release();

private:
	LPDIRECT3DDEVICE9	m_pGraphicDev;
	CScene*				m_pScene; // 내가 사용할 씬과
	CRenderer*			m_pRenderer; // 렌더러
};


END

#endif // !__MANAGEMENT_H__
