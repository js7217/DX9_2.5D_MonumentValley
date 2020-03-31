#include "stdafx.h"
#include "CollMouse.h"
#include "Transform.h"
#include "TerrainInfo.h"
#include "SetTransform.h"
CCollMouse::CCollMouse()
	: m_pTerrainInfo(nullptr)
	, m_bIsOrtho(true)
{
}

CCollMouse::~CCollMouse()
{
	Release();
}

bool CCollMouse::PickTerrain(D3DXVECTOR3 * pOut, const ENGINE::VTX_TEX * pTerrainVtx)
{
	Translation_ViewSpace();

	// ���� ������ ��������� �׵�����̴�.
	D3DXMATRIX matWorld;
	D3DXMatrixIdentity(&matWorld);
	Translation_LocalSpace(&matWorld);

	float fU = 0.f, fV = 0.f, fDist = 0.f;
	WORD wCntVtxX = m_pTerrainInfo->GetCntX();
	WORD wCntVtxZ = m_pTerrainInfo->GetCntZ();

	for (int i = 0; i < wCntVtxZ - 1; ++i)
	{
		for (int j = 0; j < wCntVtxX - 1; ++j)
		{
			int iIndex = j + wCntVtxX * i;

			// ������ ��
			if (D3DXIntersectTri(
				&pTerrainVtx[iIndex + wCntVtxX].vPos,		/* �ﰢ�� ������ 1 */
				&pTerrainVtx[iIndex + wCntVtxX + 1].vPos,	/* �ﰢ�� ������ 2 */
				&pTerrainVtx[iIndex + 1].vPos, /* �ﰢ�� ������ 3 */
				&m_vPivotPos,	/* ������ ����� */
				&m_vRayDir,		/* ������ ���� */
				&fU,			/* ���� ���� ��ǥ ���� �� U */
				&fV,			/* ���� ���� ��ǥ ���� �� V */
				&fDist))		/* ���� ������� ���� �������� �Ÿ� */
			{
				// *pOut = V1 + U(V2 - V1) + V(V3 - V1)
				*pOut = pTerrainVtx[iIndex + wCntVtxX].vPos +
					fU * (pTerrainVtx[iIndex + wCntVtxX + 1].vPos - pTerrainVtx[iIndex + wCntVtxX].vPos)
					+ fV * (pTerrainVtx[iIndex + 1].vPos - pTerrainVtx[iIndex + wCntVtxX].vPos);

				// D3DXVec3TransformCoord(pOut, pOut, �������)
				return true;
			}

			// ���� �Ʒ�		
			if (D3DXIntersectTri(
				&pTerrainVtx[iIndex + wCntVtxX].vPos,		/* �ﰢ�� ������ 1 */
				&pTerrainVtx[iIndex + 1].vPos,	/* �ﰢ�� ������ 2 */
				&pTerrainVtx[iIndex].vPos, /* �ﰢ�� ������ 3 */
				&m_vPivotPos,	/* ������ ����� */
				&m_vRayDir,		/* ������ ���� */
				&fU,			/* ���� ���� ��ǥ ���� �� U */
				&fV,			/* ���� ���� ��ǥ ���� �� V */
				&fDist))		/* ���� ������� ���� �������� �Ÿ� */
			{
				// *pOut = V1 + U(V2 - V1) + V(V3 - V1)
				*pOut = pTerrainVtx[iIndex + wCntVtxX].vPos +
					fU * (pTerrainVtx[iIndex + 1].vPos - pTerrainVtx[iIndex + wCntVtxX].vPos)
					+ fV * (pTerrainVtx[iIndex].vPos - pTerrainVtx[iIndex + wCntVtxX].vPos);

				// D3DXVec3TransformCoord(pOut, pOut, �������)
				return true;
			}
		}
	}
	return false;
}

bool CCollMouse::PickObject(D3DXVECTOR3 * pOut, const ENGINE::VTX_TEX * pObjectVtx, const D3DXMATRIX * pMatWorld)
{
	Translation_ViewSpace();
	Translation_LocalSpace(pMatWorld);

	float fU = 0.f, fV = 0.f, fDist = 0.f;

	// ������ ��
	if (D3DXIntersectTri(
		&pObjectVtx[0].vPos,		/* �ﰢ�� ������ 1 */
		&pObjectVtx[1].vPos,	/* �ﰢ�� ������ 2 */
		&pObjectVtx[2].vPos, /* �ﰢ�� ������ 3 */
		&m_vPivotPos,	/* ������ ����� */
		&m_vRayDir,		/* ������ ���� */
		&fU,			/* ���� ���� ��ǥ ���� �� U */
		&fV,			/* ���� ���� ��ǥ ���� �� V */
		&fDist))		/* ���� ������� ���� �������� �Ÿ� */
	{
		// *pOut = V1 + U(V2 - V1) + V(V3 - V1)
		*pOut = pObjectVtx[0].vPos +
			fU * (pObjectVtx[1].vPos - pObjectVtx[0].vPos)
			+ fV * (pObjectVtx[2].vPos - pObjectVtx[0].vPos);

		D3DXVec3TransformCoord(pOut, pOut, pMatWorld);
		return true;
	}

	// ���� �Ʒ�		
	if (D3DXIntersectTri(
		&pObjectVtx[0].vPos,		/* �ﰢ�� ������ 1 */
		&pObjectVtx[2].vPos,	/* �ﰢ�� ������ 2 */
		&pObjectVtx[3].vPos, /* �ﰢ�� ������ 3 */
		&m_vPivotPos,	/* ������ ����� */
		&m_vRayDir,		/* ������ ���� */
		&fU,			/* ���� ���� ��ǥ ���� �� U */
		&fV,			/* ���� ���� ��ǥ ���� �� V */
		&fDist))		/* ���� ������� ���� �������� �Ÿ� */
	{
		// *pOut = V1 + U(V2 - V1) + V(V3 - V1)
		*pOut = pObjectVtx[0].vPos +
			fU * (pObjectVtx[2].vPos - pObjectVtx[0].vPos)
			+ fV * (pObjectVtx[3].vPos - pObjectVtx[0].vPos);

		D3DXVec3TransformCoord(pOut, pOut, pMatWorld);
		return true;
	}

	return false;
}

bool CCollMouse::PickSphere(D3DXMATRIX * pMatWorld)
{
	Translation_ViewSpace();
	Translation_LocalSpace(pMatWorld);

	float b = D3DXVec3Dot(&m_vPivotPos, &m_vRayDir);
	float a = D3DXVec3Dot(&m_vRayDir, &m_vRayDir);
	float c = (m_vPivotPos.x * m_vPivotPos.x
		+ m_vPivotPos.y * m_vPivotPos.y
		+ m_vPivotPos.z * m_vPivotPos.z) - (1.f);
	float fresult = b*b - a * c;

	if (fresult >= 0.f)
		return true;

	return false;
}

void CCollMouse::SetTerrainInfo(ENGINE::CTerrainInfo * pTerrainInfo)
{
	m_pTerrainInfo = pTerrainInfo;
}

void CCollMouse::Set_bIsOrtho(bool bIsOrtho)
{
	m_bIsOrtho = bIsOrtho;
}

HRESULT CCollMouse::Initialize()
{
	return S_OK;
}

void CCollMouse::Release()
{
}

void CCollMouse::Translation_ViewSpace()
{
	POINT pt = GetMousePos();
	D3DXVECTOR3 vMouse = {};

	// ����Ʈ -> ����
	vMouse.x = float(pt.x) / (WINCX >> 1) - 1.f;
	vMouse.y = float(-pt.y) / (WINCY >> 1) + 1.f;
	vMouse.z = 1.f;

	// ���� -> �� ( ù��° ��� )
	/*D3DXMATRIX matProj = *(m_pCamObserver->GetProj());
	D3DXMatrixInverse(&matProj, nullptr, &matProj);
	D3DXVec3TransformCoord(&vMouse, &vMouse, &matProj);*/

	// ���� -> �� ( �ι�° ��� )
	D3DXMATRIX matProj = ENGINE::CSetTransForm::GetMatProj();
	vMouse.x /= matProj._11;
	vMouse.y /= matProj._22;

	// �� �����̽������� ���� ������� ����.
	if (m_bIsOrtho)
		m_vPivotPos = { vMouse.x, vMouse.y, 0.f };
	else
		m_vPivotPos = { 0.f, 0.f, 0.f };

	m_vRayDir = vMouse - m_vPivotPos;
	D3DXVec3Normalize(&m_vRayDir, &m_vRayDir);
}

void CCollMouse::Translation_LocalSpace(const D3DXMATRIX* pMatWorld)
{
	// �� -> ����
	D3DXMATRIX matView = ENGINE::CSetTransForm::GetMatView();
	D3DXMatrixInverse(&matView, nullptr, &matView);

	D3DXVec3TransformCoord(&m_vPivotPos, &m_vPivotPos, &matView);
	D3DXVec3TransformNormal(&m_vRayDir, &m_vRayDir, &matView);
	D3DXVec3Normalize(&m_vRayDir, &m_vRayDir);

	// ���� -> ����
	D3DXMATRIX matWorld = *pMatWorld;
	D3DXMatrixInverse(&matWorld, nullptr, &matWorld);

	D3DXVec3TransformCoord(&m_vPivotPos, &m_vPivotPos, &matWorld);
	D3DXVec3TransformNormal(&m_vRayDir, &m_vRayDir, &matWorld);
	D3DXVec3Normalize(&m_vRayDir, &m_vRayDir);
}

POINT CCollMouse::GetMousePos()
{
	POINT pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	return pt;
}

CCollMouse * CCollMouse::Create()
{
	CCollMouse* pInstance = new CCollMouse;

	if (FAILED(pInstance->Initialize()))
	{
		ENGINE::SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}
