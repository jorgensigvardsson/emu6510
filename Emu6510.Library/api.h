#pragma once

#ifdef EMU6510LIBRARY_EXPORTS
#define API __declspec(dllexport)
#else
#define API __declspec(dllimport)
#endif