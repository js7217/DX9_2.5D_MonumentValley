#pragma once

#ifndef __BACKGROUND_H__
#define __BACKGROUND_H__

namespace ENGINE
{
	class CResourceMgr;
	class CVIBuffer;
	class CTexture;
	class CTimeMgr;
	class CTransform;
	class CBillBoard;
	class CManagement;
}

#include "GameObject.h"

class CStaticCamera;
class CBackGround : public ENGINE::CGameObject
{
public:
	enum TEX_SCALE { AX_X,AX_Y,AX_Z,AX_MAX };
	enum STAGE
	{
		STAGE1,
		STAGE2, 
		STAGE3,
		STAGE4,
		STAGE5
	};

private:
	explicit CBackGround(LPDIRECT3DDEVICE9 pGraphicDev);
public:
	virtual ~CBackGround();

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
	static CBackGround* Create(LPDIRECT3DDEVICE9 pGraphicDev, STAGE eStage);
public:
	void Set_Stage(STAGE eStage);
private:
	ENGINE::CResourceMgr*	m_pResourceMgr;
	ENGINE::CTimeMgr*		m_pTimeMgr;
	ENGINE::CTransform*		m_pTransform;
	ENGINE::CBillBoard*		m_pBillBoard;
	ENGINE::CManagement*	m_pManagement;

	//그림1
	ENGINE::CVIBuffer*		m_pBuffer;
	ENGINE::CTexture*		m_pTexture;

	//그림2
	ENGINE::CVIBuffer*		m__pBuffer;
	ENGINE::CTexture*		m__pTexture;


	CStaticCamera*			m_pStaticCamera;

	float m_fRatio = 0.f;
	STAGE					m_eStage;

	

};

#endif