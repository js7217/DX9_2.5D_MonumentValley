#include "Engine_Include.h"
#include "Collision.h"

using namespace ENGINE;

CCollision::CCollision()
{
}

CCollision::CCollision(COLLISION_TYPE eType)
	: m_eCollType(eType)
{
}

CCollision::~CCollision()
{
}
