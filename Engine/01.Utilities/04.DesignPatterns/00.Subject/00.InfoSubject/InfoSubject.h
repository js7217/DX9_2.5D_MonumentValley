#pragma once

#ifndef __INFOSUBJECT_H__
#define __INFOSUBJECT_H__

#include "Subject.h"

BEGIN(ENGINE)

typedef list<void*>			DATA_LST;
typedef map<int, DATA_LST>	MAP_DATALST;

class ENGINE_DLL CInfoSubject : public CSubject
{
	DECLARE_SINGLETON(CInfoSubject)

private:
	explicit CInfoSubject();
	virtual ~CInfoSubject();

public:
	DATA_LST* GetDataLst(int iMessage);

public:
	void AddData(int iMessage, void* pData);
	void RemoveData(int iMessage, void* pData);

private:
	void Release();

private:
	MAP_DATALST m_mapDataLst;
};

END
#endif