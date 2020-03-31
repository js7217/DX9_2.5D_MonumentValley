#pragma once
#ifndef __SCENE_H__
#define __SCENE_H__
#include "Layer.h"

BEGIN(ENGINE)


class ENGINE_DLL CScene
{
protected:
	explicit CScene(LPDIRECT3DDEVICE9 pGraphicDev);
public:
	virtual ~CScene();

public:
	CComponent* GetComponent(CLayer::LAYER_ID eLayerID,
		const wstring& wstrObjectKey, const wstring& wstrComponentKey);

	list<CGameObject*>* GetLst(CLayer::LAYER_ID eLayerID,
		const wstring& wstrObjectKey);

public:
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render();

protected:
	virtual HRESULT Initialize();
	virtual void Release();

protected:
	virtual HRESULT Add_Environment_Layer() PURE;
	virtual HRESULT Add_Object_Layer()		PURE;
	virtual HRESULT Add_UI_Layer()			PURE;

protected:
	LPDIRECT3DDEVICE9 m_pGraphicDev;

public: // Àç¼º
	void SetIsEnding(const bool& bIsEnding);
	const bool& GetIsEnding();

	typedef map<WORD, CLayer*>	MAP_LAYER;
	MAP_LAYER					m_mapLayer;
	bool						m_bIsEnding;
};

END

#endif // !__SCENE_H__
