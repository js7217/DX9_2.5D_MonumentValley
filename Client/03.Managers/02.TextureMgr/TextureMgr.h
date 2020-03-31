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
		const wstring& wstrFilePath, /* �̹��� ���. */
		const wstring& wstrObjKey, /* ������Ʈ Ű */
		const wstring& wstrStateKey = L"", /* ���� Ű�� ��Ƽ�ؽ��ĸ� ���´�. */
		const DWORD& dwCnt = 0 /* �̹��� ����, ��Ƽ �ؽ����� ��쿡�� ����� */);
	virtual void Release();

private:
	map<const wstring, CSpriteTexture*>	m_MapTexture;
};

