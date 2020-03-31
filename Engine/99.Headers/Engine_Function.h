#pragma once 

#ifndef __ENGINE_FUNTION_H__
#define __ENGINE_FUNTION_H__

BEGIN(ENGINE)

template <typename T>
void SafeDelete(T& ptr)
{
	if (ptr)
	{
		delete ptr;
		ptr = nullptr;
	}
}

template <typename T>
void SafeDelete_Array(T& ptr)
{
	if (ptr)
	{
		delete[] ptr;
		ptr = nullptr;
	}
}

template <typename T>
DWORD SafeRelease(T ptr)
{
	DWORD dwRefCnt = 0;

	if (ptr)
		dwRefCnt = ptr->Release();

	return dwRefCnt;
}

END

#endif // !__ENGINE_DEFINE_H__