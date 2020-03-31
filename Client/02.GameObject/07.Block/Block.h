#pragma once

#ifndef __BLOCK_H__
#define __BLOCK_H__

namespace ENGINE
{
	class CResourceMgr;
	class CTexture;
	class CVIBuffer;
	class CTransform;
	class CManagement;
	class CSphereCollider;
}

#include "GameObject.h"

class CCollTerrain;
class CBlock : public ENGINE::CGameObject
{
private:
	explicit CBlock(LPDIRECT3DDEVICE9 pGraphicDev);
public:
	~CBlock();

public:
	enum CUBE_STATE
	{
		ROT_X,
		ROT_Y,
		ROT_Z,
		MOVE_X,
		MOVE_Y,
		MOVE_Z,
		DEFAULT_STATE
	};

public:
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render();
public:
	ENGINE::VTX_CUBE* Get_CubeOriginVtx();
	D3DXMATRIX Get_CubeMatWorld();
	D3DXVECTOR3 Get_CubePos();
	const int& Get_SortNum();
	const int& Get_TexNum();

public:
	void Set_IsWireFrame(const bool& bIsWireFrame);
	void SetSortNum(const int& iNum);
	void SetTexNum(const int& iTexNum);
	void SetCubeState(CUBE_STATE eCubeState);
	void SetOrtho(const bool& bIsOrtho);
	void Set_bIsSelected(bool bCheck);
	void Set_AxisAngle(float fAngle);
	void Set_MoveValue(float fMoveValue);
	void Set_Size(const D3DXVECTOR3& vSize);
public:

	bool Get_bIsSelected();
	ENGINE::CTransform* Get_Transform();
	ENGINE::CVIBuffer*	Get_Buffer();
	const CBlock::CUBE_STATE& Get_CubeState();
	const D3DXVECTOR3& Get_CubeSize();
	const D3DXMATRIX& Get_OriginWorld() const;
public:
	void MouseLButtonDown(POINT pt);
	void MouseLPressing(POINT pt);
	void MouseLButtonUp(POINT pt);
	void CalAngle();
private:
	virtual HRESULT Initialize();
	virtual HRESULT LateInit();
	virtual void Release();
private:
	void SetTransform();
	void UseZBuffer();
private:
	HRESULT AddComponent();
public:
	void SetPos(const float& fPosX, const float& fPosZ);
	void SetPos(D3DXVECTOR3 vCenterPos);
public:
	static CBlock* Create(LPDIRECT3DDEVICE9 pGraphicDev,
		const float& fPosX, const float& fPosZ,
		const int& iSortNum, const int& iTexNum,
		const D3DXVECTOR3& vSize = { 1.f, 1.f, 1.f }, CUBE_STATE eState = CUBE_STATE::DEFAULT_STATE);
	static CBlock* Create(
		LPDIRECT3DDEVICE9 pGraphicDev, D3DXVECTOR3 vCenterPos,
		const int& iSortNum, const int& iTexNum,
		const D3DXVECTOR3& vSize = { 1.f, 1.f, 1.f }, CUBE_STATE eState = CUBE_STATE::DEFAULT_STATE);

public: // 재성
	void SetTargetAngle(float fAngle);
	void Set_IsReverse(const bool& bIsReverse);
	const bool& Get_IsReverse();
	void Set_IsUseZBuffer(const bool& bIsUseZBuffer);
public:
	void SetDeltaValue(float fValue);
	void SetDeltaCount(float fValue);

	float GetDeltaValue();
	float GetDeltaCount();

	int& Get_RotSound();

private:
	CCollisionMgr*				m_pCollisionMgr;
	ENGINE::CSphereCollider*	m_pSphereCollider;
	ENGINE::CTransform*		m_pTransform; // 위치
	ENGINE::CResourceMgr*	m_pResourceMgr; // 리소스매니저(클론 가져옴)
	ENGINE::CVIBuffer*		m_pBuffer;
	ENGINE::CTexture*		m_pTexture;
	ENGINE::CTimeMgr*		m_pTimeMgr;
	ENGINE::CManagement*	m_pManagement; // 터레인 버텍스 정보.
	CCollTerrain*			m_pCollTerrain;

	bool					m_bIsWireFrame;
	bool					bCheckMouseMove = false;
	bool					m_bIsSelected; // 움직이는거 혹은 회전할 애들 선택되었나 안되었나 확인하는거
	bool					m_bIsOrtho;
	bool					m_bIsCalAngle;
	bool					m_bIsReverse; //  CubeState가 반대값인지 아닌지.
	bool					m_bIsUseBuffer; // Z버퍼를 사용할지말지


	int						m_iSortNum; // 직교때 소팅하기 위한 넘버링.
	int						m_iTexNum; // 입힐 텍스쳐 번호.


	float					m_fAxisAngle;
	float					m_fMovePosValue;
	int						m_RotSound;
	D3DXVECTOR3				m_vAxisPos;

	CUBE_STATE				m_eCubeState;
	//마우스로 각도및 위치 변경하기 위한 값
	POINT					m_PreMPos;
	POINT					m_CurMPos;
	POINT					m_MDist;

	D3DXMATRIX				m_OriginWorld;


	//큐브를 움직이게 하기 위한 시간값
	float					m_fDeltaValue;
	float					m_fDeltaCount;

};

#endif