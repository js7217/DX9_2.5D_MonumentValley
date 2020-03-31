#pragma once

#ifndef __MONSTER_H__
#define __MONSTER_H__

namespace ENGINE
{
	class CResourceMgr;
	class CTexture;
	class CVIBuffer;
	class CTransform;
	class CManagement;
	class CBillBoard;
}

#include "GameObject.h"

class CCollTerrain;
class CMonster : public ENGINE::CGameObject
{
private:
	explicit CMonster(LPDIRECT3DDEVICE9 pGraphicDev);
public:
	~CMonster();

public:
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render();

private:
	virtual HRESULT Initialize();
	virtual HRESULT LateInit();
	virtual void Release();

private:
	HRESULT AddComponent();
	void SetPos(const float& fPosX, const float& fPosZ);
public:
	static CMonster* Create(LPDIRECT3DDEVICE9 pGraphicDev, const float& fPosX, const float& fPosZ);

private:
	ENGINE::CTransform*		m_pTransform; // ��ġ
	ENGINE::CResourceMgr*	m_pResourceMgr; // ���ҽ��Ŵ���(Ŭ�� ������)
	ENGINE::CVIBuffer*		m_pBuffer;
	ENGINE::CTexture*		m_pTexture;
	ENGINE::CManagement*	m_pManagement; // �ͷ��� ���ؽ� ����.
	ENGINE::CBillBoard*		m_pBillBoard;
	CCollTerrain*			m_pCollTerrain;
};

#endif