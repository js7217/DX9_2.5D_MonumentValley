#pragma once

#ifndef __SNOW_H__
#define __SNOW_H__

namespace ENGINE
{
	class CResourceMgr;
	class CTexture;
	class CVIBuffer;
	class CTimeMgr;
	class CTransform;
	class CManagement;
	class CSphereCollider;
	class CKeyMgr;
}


#include "GameObject.h"

class CCollTerrain;
class CCollMouse;
class CCollCube;
class CBlock;
class CSnow : public ENGINE::CGameObject
{
private:
	explicit CSnow(LPDIRECT3DDEVICE9 pGraphicDev);
public:
	~CSnow();

public:
	ENGINE::CTransform* GetTransform();
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

public:
	float*	GetTimeCnt();

	void SetTransform(ENGINE::CTransform* pTransform);

public:
	static CSnow* Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	ENGINE::CTransform*		m_pTransform;
	ENGINE::CResourceMgr*	m_pResourceMgr;
	ENGINE::CVIBuffer*		m_pBuffer;
	ENGINE::CTexture*		m_pTexture;
	ENGINE::CTimeMgr*		m_pTimeMgr;
	ENGINE::CManagement*	m_pManagement;

	bool					m_bIsMove;
	D3DXVECTOR3				m_vMousePos;

	bool					m_bIsDestination;

	//�����ð�
	float					m_fTimeCnt;

	//�����ð��� Ȱ���� �� ����
	float					m_fDeltaValue;


	//������(�����)(0 ~ 1.00)
	float					m_fRandom;

	//����
	float					m_fOscillation;

	//���ϼӵ�
	float					m_fSpeed;

	//���� ����
	int						m_iAlphaValue;





};

#endif