#pragma once
#include "api.h"
#include "opcodes.h"

namespace emu6510 {
	class memory;
	struct cpu;

	struct API instruction {
		virtual ~instruction() = default;
		virtual void execute(cpu& cpu, memory& memory) const noexcept = 0;
	};
}
