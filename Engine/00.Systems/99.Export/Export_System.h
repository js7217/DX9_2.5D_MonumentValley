#pragma once

#ifndef __EXPORT_SYSTEM_H__
#define __EXPORT_SYSTEM_H__

#include "GraphicDev.h"
#include "TimeMgr.h"

BEGIN(ENGINE)

inline CGraphicDev* Get_GraphicDev();
inline CTimeMgr*	Get_TimeMgr();
#include "Export_System.inl"
END

#endif