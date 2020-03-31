#pragma once

#ifndef __EXPORT_RESOURCE_H__
#define __EXPORT_RESOURCE_H__

#include "ResourceMgr.h"

BEGIN(ENGINE)

inline CResourceMgr* Get_ResourceMgr();

#include "Export_Resource.inl"

END

#endif