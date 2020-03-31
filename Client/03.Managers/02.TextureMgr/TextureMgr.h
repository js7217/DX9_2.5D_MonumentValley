#pragma once

class CSpriteTexture;
class CTextureMgr
{
	DECLARE_SINGLETON(CTextureMgr)

public:
	enum TEX_TYPE { TEX_SINGLE, TEX_MULTI };

private:
	CTextureMgr();
	~CTextureMgr();

public:
	virtual const TEX_INFO* GetTexInfo(
		const wstring& wstrObjKey,
		const wstring& wstrStateKey = L"",
		const DWORD& dwIndex = 0) const;

public:
	virtual HRESULT InsertTexture(
		TEX_TYPE eTextureType,
		const wstring& wstrFilePath, /* 이미지 경로. */
		const wstring& wstrObjKey, /* 오브젝트 키 */
		const wstring& wstrStateKey = L"", /* 상태 키는 멀티텍스쳐만 갖는다. */
		const DWORD& dwCnt = 0 /* 이미지 개수, 멀티 텍스쳐일 경우에만 사용함 */);
	virtual void Release();

private:
	map<const wstring, CSpriteTexture*>	m_MapTexture;
};

