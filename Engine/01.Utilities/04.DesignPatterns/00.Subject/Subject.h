#pragma once

#ifndef __SUBJECT_H__
#define __SUBJECT_H__

BEGIN(ENGINE)

class CObserver;
class ENGINE_DLL CSubject
{
protected:
	explicit CSubject();

public:
	virtual ~CSubject();

public:
	virtual void Subscribe(CObserver* pObserver);
	virtual void UnSubscribe(CObserver* pObserver);
	virtual void Notify(int iMessage);

private:
	void Release();

protected:
	typedef list<CObserver*>	OBSERVER_LST;
	OBSERVER_LST				m_ObserverLst;
};

END
#endif