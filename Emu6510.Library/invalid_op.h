#pragma once
#include "instruction.h"
#include "cpu.h"
#include "instrfetch.h"

namespace emu6510 {
	struct invalid_op : instruction {
		void execute(cpu& cpu, memory& /*memory*/) const override {
			throw bad_instruction(cpu.pc - 1);
		}

		std::string decode(cpu& /*cpu*/, const memory& /*memory*/) const noexcept override {
			return "???";
		}
	};
}
