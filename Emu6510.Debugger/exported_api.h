#pragma once
#include "api.h"
#include <cstdint>

using debugger_t = void*;
using dbg_result = int;

constexpr dbg_result DBG_E_SUCCESS = 0;
constexpr dbg_result DBG_E_BAD_ARGUMENT = 1;
constexpr dbg_result DBG_E_BAD_INSTRUCTION = 2;
constexpr dbg_result DBG_E_NULL_ARGUMENT = 3;
constexpr dbg_result DBG_E_GEN_FAILURE = 666;

extern "C" {
	DEBUGGER_API dbg_result dbg_create(debugger_t* debugger);
	DEBUGGER_API dbg_result dbg_load_program(debugger_t debugger, uint16_t memory_offset, const uint8_t* program, uint16_t program_length);
	DEBUGGER_API dbg_result dbg_get_memory_ptr(debugger_t debugger, void** ptr);
	DEBUGGER_API dbg_result dbg_step_one_instruction(debugger_t debugger);
	DEBUGGER_API void dbg_destroy(debugger_t debugger);
}
