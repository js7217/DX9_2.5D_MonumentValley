#pragma once

#ifndef __BODYPART_H__
#define __BODYPART_H__

#include "Component.h"

BEGIN(ENGINE)

class CTimeMgr;
class CVIBuffer;
class CTransform;
class CResourceMgr;
class ENGINE_DLL CBodyPart : public CComponent
{
protected:
	explicit CBodyPart();

public:
	virtual ~CBodyPart();

public:
	const wstring&		GetPartsName();
	const D3DXMATRIX*	GetWorld();
	const float*		GetTimer();

public:
	void SetTransform(const CTransform* pTransform);
	void SetTimer(const float* fTimeCnt);

protected:
	ENGINE::CVIBuffer*		m_pBuffer;
	ENGINE::CTimeMgr*		m_pTimeMgr;
	ENGINE::CResourceMgr*	m_pResourceMgr;

	//종속된 파츠의 Transform
	const CTransform*		m_pTransformTarget;

	//자기 자신의 Transform
	CTransform*				m_pTransform;

	//Parts의 이름
	wstring					m_wstrPartName;

	//다른 Parts(ex. 팔, 다리 등등)과 공유할 시간값
	const float*			m_fTimeCnt;



};

END

#endif