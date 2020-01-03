#include "pch.h"
#include "exported_api.h"
#include "../Emu6510.Library/memory.h"
#include "../Emu6510.Library/cpu.h"
#include "../Emu6510.Library/instrfetch.h"
#include "debugger.h"

#define CHECK_NULL_ARG(x) do { if(!(x)) return DBG_E_NULL_ARGUMENT; } while(false)

dbg_result dbg_create(debugger_t* debugger) {
	CHECK_NULL_ARG(debugger);
	
	*debugger = nullptr;

	try {
		*debugger = new emu6510::debugger();
		return DBG_E_SUCCESS;
	} catch(...) {
		return DBG_E_GEN_FAILURE;
	}
}

dbg_result dbg_load_program(debugger_t debugger, uint16_t memory_offset, const uint8_t* program, uint16_t program_length) {
	CHECK_NULL_ARG(debugger);
	CHECK_NULL_ARG(program);

	auto dbg = static_cast<emu6510::debugger*>(debugger);

	const auto memory_iterator = std::begin(dbg->memory) + memory_offset;
	if(memory_iterator + program_length > std::end(dbg->memory))
		return DBG_E_BAD_ARGUMENT;

	std::copy(program, program + program_length, memory_iterator);

	// Setup CPU for running the program
	dbg->cpu = emu6510::cpu {};
	dbg->cpu.sp = 0xFF;
	dbg->cpu.pc = memory_offset;

	return DBG_E_SUCCESS;
}

dbg_result dbg_get_memory_ptr(debugger_t debugger, void** ptr) {
	CHECK_NULL_ARG(debugger);
	CHECK_NULL_ARG(ptr);

	auto dbg = static_cast<emu6510::debugger*>(debugger);
	*ptr = &dbg->memory[0];
	return DBG_E_SUCCESS;
}

dbg_result dbg_step_one_instruction(debugger_t debugger) {
	CHECK_NULL_ARG(debugger);

	auto dbg = static_cast<emu6510::debugger*>(debugger);

	try {
		dbg->step();
		return DBG_E_SUCCESS;
	} catch (emu6510::bad_instruction&) {
		return DBG_E_BAD_INSTRUCTION;
	} catch (...) {
		return DBG_E_GEN_FAILURE;
	}
}

void dbg_destroy(debugger_t debugger) {
	if (debugger == nullptr)
		return;

	delete static_cast<emu6510::debugger*>(debugger);
}
