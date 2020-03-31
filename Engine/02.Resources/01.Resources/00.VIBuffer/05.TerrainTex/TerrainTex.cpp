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
	// 일단 보류.
	m_dwVtxSize = sizeof(VTX_TEX);
	m_dwVtxFVF = VTXFVF_TEX;
	m_dwVtxCnt = (DWORD)(m_wCntX * m_wCntY); // 가로 정점 개수 * 세로 정점 개수
	m_dwTriCnt = (DWORD)(((m_wCntX - 1) * (m_wCntY - 1)) * 2); // 가로 - 1 * 세로 -1 * 2
	
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
			iVtxIndex = j + m_wCntX * i; // 버텍스의 인덱스
			pVtxTex[iVtxIndex].vPos = { (float)(j * m_wItv), 
				-1.f + (pPixel[iVtxIndex] & 0x000000ff) * 0.01f * m_wItv, 
				(float)(i * m_wItv) };

			pVtxTex[iVtxIndex].vTex = {
				pVtxTex[iVtxIndex].vPos.x / float((m_wCntX - 1) * m_wItv), // UV 좌표 x축
				1.f - pVtxTex[iVtxIndex].vPos.z / float((m_wCntY - 1) * m_wItv) //UV 좌표 y축
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
	// TODO: 여기에 반환 구문을 삽입합니다.
	return m_wCntX;
}

WORD CTerrainTex::GetCntY()
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	return m_wCntY;
}

WORD CTerrainTex::GetItv()
{
	// TODO: 여기에 반환 구문을 삽입합니다.
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
	BITMAPINFOHEADER tBmpInfoHeader; // 비트맵 파일, 정보 헤더를 가져옴
	// 이는 직접 사용보단 다음 픽셀 정보를 얻어오기 위한 일련의 과정.
	// 파일을 Read 할때는 순서대로 Read 해야함을 잊지말자.

	ReadFile(hFile, &tBmpFileHeader, sizeof(BITMAPFILEHEADER), &dwByte, nullptr);
	ReadFile(hFile, &tBmpInfoHeader, sizeof(BITMAPINFOHEADER), &dwByte, nullptr);

	DWORD* pPixel = new DWORD[tBmpInfoHeader.biWidth * tBmpInfoHeader.biHeight];
	// 사진 전체에 대한 픽셀 정보를 동적생성.

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
