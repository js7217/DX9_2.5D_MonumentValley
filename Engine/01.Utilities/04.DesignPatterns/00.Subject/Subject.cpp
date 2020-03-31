#include "Engine_Include.h"
#include "Subject.h"
#include "Observer.h"
using namespace ENGINE;

CSubject::CSubject()
{
}

CSubject::~CSubject()
{
	Release();
}

void CSubject::Subscribe(CObserver * pObserver)
{ // 옵저버 추가.
	NULL_CHECK(pObserver);

	m_ObserverLst.emplace_back(pObserver);
}

void CSubject::UnSubscribe(CObserver * pObserver)
{ // 옵저버 삭제.
	NULL_CHECK(pObserver);

	auto iter_find = find(m_ObserverLst.begin(), 
		m_ObserverLst.end(), pObserver);

	if (m_ObserverLst.end() == iter_find)
		return;

	m_ObserverLst.erase(iter_find);
}

void CSubject::Notify(int iMessage)
{ // 업데이트
	for (auto& pObserver : m_ObserverLst)
		pObserver->Update(iMessage);
}

void CSubject::Release()
{
	m_ObserverLst.clear();
}
