#pragma once

#ifndef __EXPORT_UTILITY_H__
#define __EXPORT_UTILITY_H__

#include "Management.h"

BEGIN(ENGINE)

inline CManagement* Get_Management();

#include "Export_Utility.inl"

END

#endif