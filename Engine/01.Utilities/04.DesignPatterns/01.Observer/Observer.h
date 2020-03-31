#pragma once

#ifndef __OBSERVER_H__
#define __OBSERVER_H__

BEGIN(ENGINE)

class ENGINE_DLL CObserver
{
protected:
	explicit CObserver();
public:
	virtual ~CObserver();

public:
	virtual void Update(int iMessage) PURE;
};

END

#endif // !1
