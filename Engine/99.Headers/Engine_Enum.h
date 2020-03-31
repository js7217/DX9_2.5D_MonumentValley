#pragma once 

#ifndef __ENGINE_ENUM_H__
#define __ENGINE_ENUM_H__

BEGIN(ENGINE)

enum RESOURCE_TYPE
{
	RESOURCE_STATIC,
	RESOURCE_DYNAMIC,
	RESOURCE_END
};

enum TEXTURE_TYPE
{
	TEX_NORMAL,
	TEX_CUBE,
	TEX_END
};

enum ANGLE_TYPE
{
	ANGLE_X,
	ANGLE_Y,
	ANGLE_Z,
	ANGLE_END
};


END

#endif // !__ENGINE_DEFINE_H__