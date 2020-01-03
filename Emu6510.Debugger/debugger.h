#pragma once

#include "../Emu6510.Library/memory.h"
#include "../Emu6510.Library/cpu.h"
#include "../Emu6510.Library/instrfetch.h"

namespace emu6510 {
	struct debugger {
		cpu cpu;
		memory memory;

		void step() {
			fetch(cpu, memory).execute(cpu, memory);
		}
	};
}