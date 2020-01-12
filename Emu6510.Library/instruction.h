#pragma once
#include <string>
#include "api.h"

namespace emu6510 {
	class memory;
	struct cpu;

	struct LIBRARY_API instruction {
		virtual ~instruction() = default;
		virtual void execute(cpu& cpu, memory& memory) const = 0;
		virtual std::string decode(cpu& cpu, const memory& memory) const noexcept = 0;
	};
}
