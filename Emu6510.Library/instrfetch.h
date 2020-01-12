#pragma once
#include "instruction.h"
#include <memory>
#include "api.h"

namespace emu6510 {
	class memory;
	LIBRARY_API instruction& fetch(cpu& cpu, memory& memory, uint16_t* addr_start, uint16_t* addr_len) noexcept;
	LIBRARY_API instruction& fetch(cpu& cpu, memory& memory) noexcept;
	LIBRARY_API bool is_valid(const instruction& instruction) noexcept;

	class bad_instruction : public std::exception {
	public:
		const int ptr;

		bad_instruction(int ptr) : ptr{ ptr } {  }

	};
}
