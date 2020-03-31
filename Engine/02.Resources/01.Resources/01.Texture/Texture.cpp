#include "Engine_Include.h"
#include "Texture.h"

using namespace ENGINE;

CTexture::CTexture(LPDIRECT3DDEVICE9 pGraphicDev)
	:CResources(pGraphicDev)
{
}

CTexture::~CTexture()
{
	Release();
}

void CTexture::Render()
{
}

void CTexture::Render(const WORD & dwIndex)
{
	if (dwIndex >= m_dwContainerSize)
		return;

	m_pGraphicDev->SetTexture(0, m_vecTexture[dwIndex]);
}

CResources * CTexture::CloneResource()
{
	++(*m_pRefCnt);

	return new CTexture(*this);
}

void CTexture::Set_Transform()
{
}

HRESULT CTexture::LoadTexture(TEXTURE_TYPE eTexType, const wstring & wstrFilePath, const WORD & wCnt)
{
	IDirect3DBaseTexture9* pTexture = nullptr; // 가져올 텍스쳐 선언 및 초기화
	TCHAR szFullPath[MAX_PATH] = L"";
	HRESULT hr = 0;

	m_vecTexture.reserve(wCnt);

	for (WORD i = 0; i < wCnt; ++i)
	{
		swprintf_s(szFullPath, wstrFilePath.c_str(), i);

		switch (eTexType)
		{
		case TEX_NORMAL:
			hr = D3DXCreateTextureFromFile(
				m_pGraphicDev, szFullPath, (LPDIRECT3DTEXTURE9*)&pTexture);
			break;
		case TEX_CUBE:
			hr = D3DXCreateCubeTextureFromFile(
				m_pGraphicDev, szFullPath, (LPDIRECT3DCUBETEXTURE9*)&pTexture);
			break;
		}

		FAILED_CHECK_RETURN(hr, E_FAIL);
		m_vecTexture.emplace_back(pTexture);
	}

	m_dwContainerSize = m_vecTexture.size();
	return S_OK;
}

void CTexture::Release()
{
	if (0 == *m_pRefCnt)
	{
		for_each(m_vecTexture.begin(), m_vecTexture.end(),
			[](auto& pTexture)
		{
			SafeRelease(pTexture);
		});

		m_vecTexture.clear();
		m_vecTexture.shrink_to_fit();
	}
}

CTexture * CTexture::Create(LPDIRECT3DDEVICE9 pGraphicDev, TEXTURE_TYPE eTexType, const wstring & wstrFilePath, const WORD & wCnt)
{
	CTexture* pInstance = new CTexture(pGraphicDev);

	if (FAILED(pInstance->LoadTexture(eTexType, wstrFilePath, wCnt)))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}
