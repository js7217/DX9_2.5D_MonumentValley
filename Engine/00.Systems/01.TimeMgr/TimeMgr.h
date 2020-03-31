#pragma once

#ifndef __TIMEMGR_H__
#define __TIMEMGR_H__

BEGIN(ENGINE)

class ENGINE_DLL CTimeMgr
{
	DECLARE_SINGLETON(CTimeMgr)

private:
	CTimeMgr();
	~CTimeMgr();

public:
	const float& GetDeltaTime() const;

public:
	HRESULT InitTimeMgr();
	void UpdateTime();

private:
	LARGE_INTEGER m_OldTime;
	LARGE_INTEGER m_CurTime;
	LARGE_INTEGER m_CpuTick; // cpu 진동수

	float m_fDeltaTime; // 수행시간
};
END
#endif

