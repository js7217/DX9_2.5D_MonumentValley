#pragma once
#include "SpriteTexture.h"
class CSingleTexture :
	public CSpriteTexture
{
public:
	CSingleTexture();
	virtual ~CSingleTexture();

public:
	virtual const TEX_INFO* GetTexInfo(
		const wstring& wstrStateKey = L"",
		const DWORD& dwIndex = 0) const override;

public:
	// CTexture을(를) 통해 상속됨
	virtual HRESULT InsertTexture(
		const wstring & wstrFilePath, 
		const wstring & wstrStateKey = L"", 
		const DWORD & dwCnt = 0) override;
	virtual void Release() override;

private:
	TEX_INFO*	m_pTexInfo;
};

