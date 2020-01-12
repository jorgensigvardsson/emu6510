#pragma once
#include "instruction.h"
#include "cpu.h"

namespace emu6510 {
	// NOP
	constexpr const char* nop_mnemonic = "NOP";
	
	struct nop : instruction {
		void execute(cpu& cpu, memory& /*memory*/) const noexcept override {
			/* do nothing */
			++cpu.cycle_counter;
		}

		std::string decode(cpu& /*cpu*/, const memory& /*memory*/) const noexcept override {
			return nop_mnemonic;
		}
	};
}
