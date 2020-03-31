#include "Engine_Include.h"
#include "KeyMgr.h"

IMPLEMENT_SINGLETON(ENGINE::CKeyMgr)

ENGINE::CKeyMgr::CKeyMgr()
	: m_dwCurKey(0), m_dwKeyDowned(0), m_dwKeyPressed(0)
{

}

ENGINE::CKeyMgr::~CKeyMgr()
{

}


void ENGINE::CKeyMgr::CheckKeyInput()
{
	m_dwCurKey = 0;

	if (GetAsyncKeyState(VK_UP) & 0x8000)
		m_dwCurKey |= KEY_UP;
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		m_dwCurKey |= KEY_DOWN;
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		m_dwCurKey |= KEY_LEFT;
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		m_dwCurKey |= KEY_RIGHT;
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
		m_dwCurKey |= KEY_RETURN;
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		m_dwCurKey |= KEY_SPACE;
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		m_dwCurKey |= KEY_LBUTTON;
	if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
		m_dwCurKey |= KEY_RBUTTON;
	if (GetAsyncKeyState(VK_MBUTTON) & 0x8000)
		m_dwCurKey |= KEY_MBUTTON;
	if (GetAsyncKeyState('U') & 0x8000)
		m_dwCurKey |= KEY_U;
	if (GetAsyncKeyState('J') & 0x8000)
		m_dwCurKey |= KEY_J;
	if (GetAsyncKeyState('R') & 0x8000)
		m_dwCurKey |= KEY_RESET;
	if (GetAsyncKeyState('P') & 0x8000)
		m_dwCurKey |= KEY_P;
}

bool ENGINE::CKeyMgr::KeyDown(DWORD dwKey)
{
	// ���� ������ ���� ���� ������ �� true
	if (!(m_dwKeyDowned & dwKey) && (m_dwCurKey & dwKey))
	{
		m_dwKeyDowned |= dwKey;
		return true;
	}
	// ���� ������ �ְ� ���� ������ �ʾ��� �� false
	else if ((m_dwKeyDowned & dwKey) && !(m_dwCurKey & dwKey))
	{
		m_dwKeyDowned ^= dwKey;
		return false;
	}

	return false;
}

bool ENGINE::CKeyMgr::KeyUp(DWORD dwKey)
{
	// ���� ������ �ְ� ���� �� ������ �� true
	if ((m_dwKeyPressed & dwKey) && !(m_dwCurKey & dwKey))
	{
		m_dwKeyPressed ^= dwKey;
		return true;
	}
	// ���� ������ ���� ���� ������ �� false
	else if (!(m_dwKeyPressed & dwKey) && (m_dwCurKey & dwKey))
	{
		m_dwKeyPressed |= dwKey;
		return false;
	}

	return false;
}

bool ENGINE::CKeyMgr::KeyPressing(DWORD dwKey)
{
	if (m_dwCurKey & dwKey)
		return true;

	return false;
}

// Ctrl + C �Ǵ� Ctrl + V�� ���� ���.
bool ENGINE::CKeyMgr::KeyCombine(DWORD dwFirstKey, DWORD dwSecondKey)
{
	if (KeyDown(dwSecondKey) && KeyPressing(dwFirstKey))
		return true;

	return false;
}