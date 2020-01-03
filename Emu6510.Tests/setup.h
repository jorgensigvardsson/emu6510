#pragma once

#include "../Emu6510.Library/memory.h"
#include "../Emu6510.Library/cpu.h"
#include "../Emu6510.Library/instrfetch.h"

inline emu6510::memory make_memory() {
	return emu6510::memory();
}

inline void run_one_instruction(emu6510::cpu& cpu, emu6510::memory& memory) {
	fetch(cpu, memory).execute(cpu, memory);
}

struct execution_result {
	emu6510::cpu cpu;
	emu6510::memory memory;
};

inline execution_result run_one_instruction(const std::function<void(emu6510::cpu&, emu6510::memory&)>& setup) {
	auto memory = make_memory();
	auto cpu = emu6510::cpu();

	setup(cpu, memory);
	run_one_instruction(cpu, memory);

	return execution_result { cpu, std::move(memory) };
}