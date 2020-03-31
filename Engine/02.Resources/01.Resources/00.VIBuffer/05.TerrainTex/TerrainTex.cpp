#include "Engine_Include.h"
#include "TerrainTex.h"

using namespace ENGINE;

CTerrainTex::CTerrainTex(LPDIRECT3DDEVICE9 pGraphicDev, const WORD & wCntX, const WORD & wCntY, const WORD & wItv)
	:CVIBuffer(pGraphicDev)
	, m_wCntX((DWORD)wCntX), m_wCntY((DWORD)wCntY), m_wItv((DWORD)wItv)
{
}

CTerrainTex::~CTerrainTex()
{
	Release();
}

HRESULT CTerrainTex::CreateBuffer()
{
	// �ϴ� ����.
	m_dwVtxSize = sizeof(VTX_TEX);
	m_dwVtxFVF = VTXFVF_TEX;
	m_dwVtxCnt = (DWORD)(m_wCntX * m_wCntY); // ���� ���� ���� * ���� ���� ����
	m_dwTriCnt = (DWORD)(((m_wCntX - 1) * (m_wCntY - 1)) * 2); // ���� - 1 * ���� -1 * 2
	
	m_dwIdxSize = sizeof(INDEX32);
	m_IdxFmt = D3DFMT_INDEX32;

	FAILED_CHECK_RETURN(CVIBuffer::CreateBuffer(), E_FAIL);

	VTX_TEX* pVtxTex = nullptr;

	DWORD* pPixel = LoadHeightMap();

	m_pVB->Lock(0, 0, (void**)&pVtxTex, 0);

	DWORD iVtxIndex = 0;

	for (DWORD i = 0; i < m_wCntY; ++i)
	{
		for (DWORD j = 0; j < m_wCntX; ++j)
		{
			iVtxIndex = j + m_wCntX * i; // ���ؽ��� �ε���
			pVtxTex[iVtxIndex].vPos = { (float)(j * m_wItv), 
				-1.f + (pPixel[iVtxIndex] & 0x000000ff) * 0.01f * m_wItv, 
				(float)(i * m_wItv) };

			pVtxTex[iVtxIndex].vTex = {
				pVtxTex[iVtxIndex].vPos.x / float((m_wCntX - 1) * m_wItv), // UV ��ǥ x��
				1.f - pVtxTex[iVtxIndex].vPos.z / float((m_wCntY - 1) * m_wItv) //UV ��ǥ y��
			};
		}
	}

	m_pVB->Unlock();

	SafeDelete_Array(pPixel);

	INDEX32* pIndex = nullptr;

	m_pIB->Lock(0, 0, (void**)&pIndex, 0);

	int iTriIndex = 0;

	iVtxIndex = 0;

	for (WORD i = 0; i < m_wCntY - 1; ++i)
	{
		for (WORD j = 0; j < m_wCntX - 1; ++j)
		{
			iVtxIndex = j + m_wCntX * i;

			pIndex[iTriIndex] = {
				iVtxIndex + m_wCntX, iVtxIndex + m_wCntX + 1,
			iVtxIndex + 1 };

			++iTriIndex;

			pIndex[iTriIndex] = {
				iVtxIndex + m_wCntX, iVtxIndex + 1,
				iVtxIndex };

			++iTriIndex;
		}
	}

	m_pIB->Unlock();

	CVIBuffer::GetVtxInfo();

	return S_OK;
}

void CTerrainTex::Render()
{
	CVIBuffer::Render();
}

WORD CTerrainTex::GetCntX()
{
	// TODO: ���⿡ ��ȯ ������ �����մϴ�.
	return m_wCntX;
}

WORD CTerrainTex::GetCntY()
{
	// TODO: ���⿡ ��ȯ ������ �����մϴ�.
	return m_wCntY;
}

WORD CTerrainTex::GetItv()
{
	// TODO: ���⿡ ��ȯ ������ �����մϴ�.
	return m_wItv;
}

void CTerrainTex::Release()
{
}

DWORD * CTerrainTex::LoadHeightMap()
{
	HANDLE hFile = nullptr;
	DWORD dwByte = 0;

	hFile = CreateFile(L"../Bin/Resources/Texture/Terrain/Height.bmp",
		GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

	if (INVALID_HANDLE_VALUE == hFile)
		return nullptr;

	BITMAPFILEHEADER tBmpFileHeader;
	BITMAPINFOHEADER tBmpInfoHeader; // ��Ʈ�� ����, ���� ����� ������
	// �̴� ���� ��뺸�� ���� �ȼ� ������ ������ ���� �Ϸ��� ����.
	// ������ Read �Ҷ��� ������� Read �ؾ����� ��������.

	ReadFile(hFile, &tBmpFileHeader, sizeof(BITMAPFILEHEADER), &dwByte, nullptr);
	ReadFile(hFile, &tBmpInfoHeader, sizeof(BITMAPINFOHEADER), &dwByte, nullptr);

	DWORD* pPixel = new DWORD[tBmpInfoHeader.biWidth * tBmpInfoHeader.biHeight];
	// ���� ��ü�� ���� �ȼ� ������ ��������.

	ReadFile(hFile, pPixel, sizeof(DWORD) * tBmpInfoHeader.biWidth * tBmpInfoHeader.biHeight,
		&dwByte, nullptr);

	CloseHandle(hFile);

	return pPixel;
}

CTerrainTex* CTerrainTex::Create(LPDIRECT3DDEVICE9 pGraphicDev, const WORD & wCntX, const WORD & wCntY, const WORD & wItv)
{
	CTerrainTex* pInstance = new CTerrainTex(pGraphicDev, wCntX, wCntY, wItv);

	if (FAILED(pInstance->CreateBuffer()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}
