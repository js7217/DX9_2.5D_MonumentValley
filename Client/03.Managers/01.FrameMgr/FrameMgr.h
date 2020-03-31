#pragma once
class CFrameMgr
{
	DECLARE_SINGLETON(CFrameMgr)
public:
	CFrameMgr();
	~CFrameMgr();
public:
	HRESULT InitFrameMgr(float fCurFPS);
	bool LimitFrame();
	void RenderFrame();

private:
	LARGE_INTEGER m_OldTime;
	LARGE_INTEGER m_CurTime;
	LARGE_INTEGER m_CpuTick;

	float	m_fSPF = 0.f;
	float	m_fTimeCount = 0.f;

	TCHAR	m_szFPS[64] = L"";
	DWORD	m_dwFPS = 0;
	float	m_fTimeCount2 = 0.f;
};

