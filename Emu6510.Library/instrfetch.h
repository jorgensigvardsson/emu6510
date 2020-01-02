#pragma once
#include "instruction.h"
#include <memory>
#include "api.h"

namespace emu6510 {
	class memory;
	API instruction& fetch(cpu& cpu, memory& memory);

	class bad_instruction : public std::exception {
	public:
		const int ptr;

		bad_instruction(int ptr) : ptr{ ptr } {  }

	};
}
