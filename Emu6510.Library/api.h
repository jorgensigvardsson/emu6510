#pragma once

#ifdef DLL_IMPORT
#define API __declspec(dllimport)
#else
#define API __declspec(dllexport)
#endif