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

constexpr int MAX_DECODED_OP_LEN = 16;

#pragma pack(push, 4)
struct decoded_instruction {
	bool is_valid_op;
	char decoded_op[MAX_DECODED_OP_LEN];
	uint16_t op_start_addr;
	uint32_t op_len;
};
#pragma pack(pop)

extern "C" {
	DEBUGGER_API dbg_result dbg_create(debugger_t* debugger);
	DEBUGGER_API dbg_result dbg_load_program(debugger_t debugger, uint16_t memory_offset, const uint8_t* program, uint16_t program_length);
	DEBUGGER_API dbg_result dbg_get_memory_ptr(debugger_t debugger, void** ptr);
	DEBUGGER_API dbg_result dbg_step_one_instruction(debugger_t debugger);
	DEBUGGER_API dbg_result dbg_get_registers(debugger_t debugger, uint8_t* a, uint8_t* x, uint8_t* y, uint16_t* pc, uint8_t* s, uint8_t* p);
	DEBUGGER_API dbg_result dbg_decode(debugger_t debugger, /* in/out */ uint16_t* pc, /* out */ decoded_instruction* di);
	DEBUGGER_API void dbg_destroy(debugger_t debugger);
}
