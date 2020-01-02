#pragma once
#include <cstdint>

namespace emu6510 {
	constexpr uint8_t byte_sign_bit = 0x80;
	constexpr uint16_t max_address = UINT16_MAX;
	constexpr size_t memory_size = max_address + 1;
}
