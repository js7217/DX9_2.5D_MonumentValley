#include "Engine_Include.h"
#include "Resources.h"

using namespace ENGINE;


CResources::CResources(LPDIRECT3DDEVICE9 pGraphicDev)
	: m_pGraphicDev(pGraphicDev)
	, m_pRefCnt(new WORD(0))
{
	m_pGraphicDev->AddRef();
}

CResources::~CResources()
{
	if (0 == *m_pRefCnt)
	{
		ENGINE::SafeDelete(m_pRefCnt);
		ENGINE::SafeRelease(m_pGraphicDev);
	}
	else
		--(*m_pRefCnt);
}
