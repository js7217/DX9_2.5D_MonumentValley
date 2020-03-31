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

	//���ӵ� ������ Transform
	const CTransform*		m_pTransformTarget;

	//�ڱ� �ڽ��� Transform
	CTransform*				m_pTransform;

	//Parts�� �̸�
	wstring					m_wstrPartName;

	//�ٸ� Parts(ex. ��, �ٸ� ���)�� ������ �ð���
	const float*			m_fTimeCnt;



};

END

#endif