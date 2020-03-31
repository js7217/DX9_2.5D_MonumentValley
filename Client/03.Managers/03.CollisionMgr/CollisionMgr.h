#pragma once

namespace ENGINE
{
	class CSphereCollider;
	class CBoxCollider;
}

class CBlock;
class CCollisionMgr
{
	DECLARE_SINGLETON(CCollisionMgr)

private:
	explicit CCollisionMgr();

public:
	~CCollisionMgr();

public:
	void OBB(const wstring& wstrSrcLst, const wstring& wstrDstLst);
	void AABB(const wstring& wstrSrcLst, const wstring& wstrDstLst);
	void CollisionSphere(const wstring& wstrSrcLst, const wstring& wstrDstLst);

public:
	void Collision_OpMz_Nor();

public:
	void AddCollider(
		const wstring& wstrColliderName, 
		ENGINE::CSphereCollider* pCollider);

	void AddCollider(
		const wstring& wstrColliderName, 
		ENGINE::CBoxCollider* pCollider);

public:
	bool IntersectSphere(
		const float& fRadiousSrc,
		const D3DXVECTOR3& vCenterSrc,
		const float& fRadiousDst,
		const D3DXVECTOR3& vCenterDst,
		float* vDist = nullptr);

	bool IntersectBox(
		const D3DXVECTOR3& vMinSrc,
		const D3DXVECTOR3& vMaxSrc,
		const D3DXVECTOR3& vMinDst,
		const D3DXVECTOR3& vMaxDst);

public:
	void SetCubeList(list<CBlock*>* pList);
	void SetOpMzList(list<vector<CBlock*>>* pList);
	void SetInterActList(list<list<vector<CBlock*>>>* pList);

	bool GetVailedState();
	void SetVailedState(bool bState);

public: // 재성
	void SetIsSceneChange(const bool& bIsSceneChange);
	const bool& GetIsSceneChange();
	void SetIsStair3(const bool& bIsStair3);
	const bool& GetIsStair3();
	void SetSphereColl(const bool& bIsSphereColl);
public:
	typedef list<ENGINE::CSphereCollider*>			SPHERELST;
	typedef list<ENGINE::CBoxCollider*>				BOXLST;
	
	typedef map<wstring, SPHERELST>  	MAP_SPHERE_COLLIDER;
	typedef map<wstring, BOXLST>		MAP_BOX_COLLIDER;

private:
	MAP_SPHERE_COLLIDER		m_mapSphere;
	MAP_BOX_COLLIDER		m_mapBox;

	list<CBlock*>*				 m_CubeList; // 큐브리스트
	list<vector<CBlock*>>*		 m_OptimizationList; // 합쳐진 큐브 리스트.
	list<list<vector<CBlock*>>>* m_InteractionList; // InteractionList


	bool					m_bIsValid;

	// 재성
	bool					m_bIsSceneChange;
	bool					m_bIsStair3;
	bool					m_bIsSphereColl;
};

