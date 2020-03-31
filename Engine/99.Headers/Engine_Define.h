#pragma once 

#ifndef __ENGINE_DEFINE_H__
#define __ENGINE_DEFINE_H__

#define BEGIN(NameSpace) namespace NameSpace {
#define END }

#define USING(NameSpace) using namespace NameSpace;



#ifdef ENGINE_EXPORTS
#define ENGINE_DLL _declspec(dllexport)
#else
#define ENGINE_DLL _declspec(dllimport)
#endif

#define NO_COPY(ClassName)						\
private:										\
	ClassName(const ClassName& obj);			\
	ClassName& operator=(const ClassName& obj);

#define DECLARE_SINGLETON(ClassName)		\
		NO_COPY(ClassName)					\
public:										\
	static ClassName* GetInstance()			\
	{										\
		if(nullptr == m_pInstance)			\
			m_pInstance = new ClassName;	\
											\
		return m_pInstance;					\
	}										\
											\
	void DestroyInstance()					\
	{										\
		if(m_pInstance)						\
		{									\
			delete m_pInstance;				\
			m_pInstance = nullptr;			\
		}									\
	}										\
											\
private:									\
	static ClassName* m_pInstance;

#define IMPLEMENT_SINGLETON(ClassName)		\
ClassName* ClassName::m_pInstance = nullptr;

#define MSG_BOX(message)								\
MessageBox(nullptr, message, L"System Error", MB_OK)

#define MSG_TAG_BOX(message, tag)						\
MessageBox(nullptr, message, tag, MB_OK)

#define NULL_CHECK(ptr)									\
if(nullptr == (ptr))									\
{														\
	__asm {	int 3 };									\
	return;												\
}

#define NULL_CHECK_RETURN(ptr, val)						\
if(nullptr == (ptr))									\
{														\
	__asm {	int 3 };									\
	return val;											\
}

#define NULL_CHECK_MSG(ptr, msg)						\
if(nullptr == (ptr))									\
{														\
	MSG_BOX(msg);										\
	__asm {	int 3 };									\
	return;												\
}

#define NULL_CHECK_MSG_RETURN(ptr, msg, val)			\
if(nullptr == (ptr))									\
{														\
	MSG_BOX(msg);										\
	__asm {	int 3 };									\
	return val;											\
}

#define FAILED_CHECK(hr)								\
if(FAILED(hr))											\
{														\
	MSG_BOX(L"Failed");									\
	__asm {	int 3 };									\
	return;												\
}

#define FAILED_CHECK_RETURN(hr, val)					\
if(FAILED(hr))											\
{														\
	MSG_BOX(L"Failed");									\
	__asm {	int 3 };									\
	return val;											\
}

#define FAILED_CHECK_MSG(hr, msg)						\
if(FAILED(hr))											\
{														\
	MSG_BOX(msg);										\
	__asm {	int 3 };									\
	return;												\
}

#define FAILED_CHECK_MSG_RETURN(hr, msg, val)			\
if(FAILED(hr))											\
{														\
	MSG_BOX(msg);										\
	__asm {	int 3 };									\
	return val;											\
}


#endif // !__ENGINE_DEFINE_H__
