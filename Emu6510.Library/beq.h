#pragma once
#include "instruction.h"
#include "cpu.h"

namespace emu6510 {
	// BEQ
	struct beq : instruction {
		void execute(cpu& cpu, memory& memory) const noexcept override {
			const auto rel_address = static_cast<int8_t>(read_ip_byte(cpu, memory));
			if (cpu.status & status::zero) {
				const auto old_pc = cpu.pc;
				cpu.pc += rel_address;
				if (((old_pc & 0xFF00) >> 8) != ((cpu.pc & 0xFF00) >> 8))
					cpu.cycle_counter += 2; // Cross page jump
				else
					cpu.cycle_counter += 1; // Same page jump
			}
		}
	};
}