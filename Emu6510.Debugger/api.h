#pragma once

#ifdef EMU6510DEBUGGER_EXPORTS
#define DEBUGGER_API __declspec(dllexport)
#else
#define DEBUGGER_API __declspec(dllimport)
#endif