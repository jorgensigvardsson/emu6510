#pragma once
#include "instruction.h"
#include "cpu.h"

namespace emu6510 {

	// NOP
	struct nop : instruction {
		void execute(cpu& cpu, memory& /*memory*/) const noexcept override {
			/* do nothing */
			++cpu.cycle_counter;
		}
	};
}
