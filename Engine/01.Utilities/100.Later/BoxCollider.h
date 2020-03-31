#pragma once

#ifndef __BOXCOLLIDER_H__
#define __BOXCOLLIDER_H__

#include "Collision.h"

BEGIN(ENGINE)

class ENGINE_DLL CBoxCollider
{
private:
	explicit CBoxCollider();

public:
	virtual ~CBoxCollider();

};

END

#endif