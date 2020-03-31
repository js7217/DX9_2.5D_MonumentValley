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
	// ��ü����
	template <typename T>
	HRESULT SceneChange(T& functor)
	{
		if (m_pScene)
			ENGINE::SafeDelete(m_pScene);

		FAILED_CHECK_RETURN(functor(&m_pScene, m_pGraphicDev), E_FAIL);
		m_pRenderer->SetScene(m_pScene); // �������ʿ� ���� �˷��ش�.
		
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
	CScene*				m_pScene; // ���� ����� ����
	CRenderer*			m_pRenderer; // ������
};


END

#endif // !__MANAGEMENT_H__
