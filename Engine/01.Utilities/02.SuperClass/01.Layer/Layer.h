#pragma once

#ifndef __LAYER_H__
#define __LAYER_H__

BEGIN(ENGINE)

class CComponent;
class CGameObject;
class ENGINE_DLL CLayer // '��' �̶�� �ǹ�. �� ����� �Ӽ��� ������Ʈ���� ���� �����ϴ� ��.
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
	// Ű ���� ���� ������Ʈ�� �ټ��� �� ������ ����Ʈ�� �ѹ��� ����.
	MAP_OBJLST m_mapObjList;
};

END
#endif