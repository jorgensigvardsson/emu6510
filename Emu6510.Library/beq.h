#pragma once
#include "instruction.h"
#include "cpu.h"
#include "decode_internal.h"
#include <sstream>

namespace emu6510 {
	// BEQ
	constexpr const char* beq_mnemonic = "BEQ";

	struct beq : instruction {
		void execute(cpu& cpu, memory& memory) const noexcept override {
			const auto rel_address = first_arg(cpu, memory);
			if (cpu.status & status::zero) {
				const auto old_pc = cpu.pc;
				cpu.pc += rel_address;
				if (((old_pc & 0xFF00) >> 8) != ((cpu.pc & 0xFF00) >> 8))
					cpu.cycle_counter += 2; // Cross page jump
				else
					cpu.cycle_counter += 1; // Same page jump
			}
		}

		int8_t first_arg(cpu& cpu, const memory& memory) const noexcept {
			return static_cast<int8_t>(read_ip_byte(cpu, memory));
		}

		std::string decode(cpu& cpu, const memory& memory) const noexcept override {
			std::stringstream ss;
			ss << beq_mnemonic << " ";
			internal::hex_number(ss, first_arg(cpu, memory));
			return ss.str();
		}
	};
}