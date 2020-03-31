#pragma once

#ifndef __LAYER_H__
#define __LAYER_H__

BEGIN(ENGINE)

class CComponent;
class CGameObject;
class ENGINE_DLL CLayer // '층' 이라는 의미. 즉 비슷한 속성의 오브젝트끼리 묶어 관리하는 층.
{
public:
	enum LAYER_ID { ENVIROMENT, OBJECT, UI };

protected:
	explicit CLayer(LPDIRECT3DDEVICE9 pGraphicDev);
public:
	virtual ~CLayer();

public:
	CComponent* GetComponent(const wstring& wstrObjectKey, const wstring& wstrComponentKey);

	list<CGameObject*>* GetLst(const wstring& wstrObjectKey);

public:
	HRESULT AddObject(const wstring& wstrObjectKey, CGameObject* pObject);
	void Update();
	void LateUpdate();
	void Render();

private:
	void Release();

public:
	static CLayer* Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	LPDIRECT3DDEVICE9 m_pGraphicDev;

	typedef list<CGameObject*> OBJLST;
	typedef map<wstring, OBJLST> MAP_OBJLST;
	// 키 값이 같은 오브젝트가 다수일 수 있으니 리스트로 한번더 관리.
	MAP_OBJLST m_mapObjList;
};

END
#endif