#include "Engine_Include.h"
#include "InfoSubject.h"

using namespace ENGINE;

IMPLEMENT_SINGLETON(CInfoSubject)

CInfoSubject::CInfoSubject()
{

}

CInfoSubject::~CInfoSubject()
{
	Release();
}

DATA_LST * CInfoSubject::GetDataLst(int iMessage)
{// 데이터리스트의 주소를 준다.
	auto iter_find = m_mapDataLst.find(iMessage);

	if (m_mapDataLst.end() == iter_find)
		return nullptr;

	return &(iter_find->second);
}

void CInfoSubject::AddData(int iMessage, void * pData)
{
	NULL_CHECK(pData);

	m_mapDataLst[iMessage].push_back(pData);
	CSubject::Notify(iMessage);
}

void CInfoSubject::RemoveData(int iMessage, void * pData)
{
	NULL_CHECK(pData);

	auto iter_find = m_mapDataLst.find(iMessage);

	if (m_mapDataLst.end() == iter_find)
		return;

	DATA_LST::iterator iter_lst = find(iter_find->second.begin(),
		iter_find->second.end(), pData); // pData가 어디있는지 찾아야함.

	iter_find->second.erase(iter_lst);
}

void CInfoSubject::Release()
{
	for_each(m_mapDataLst.begin(), m_mapDataLst.end(),
		[](auto& MyPair)
	{
		MyPair.second.clear();
	});

	m_mapDataLst.clear();
}
