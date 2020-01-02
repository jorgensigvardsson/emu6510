#pragma once
#include <vector>

namespace emu6510 {
	class memory {
		std::vector<uint8_t> m_buffer;
		
	public:
		memory(int size) {
			m_buffer.resize(size);
		}

		uint8_t& operator[](int index) {
			return m_buffer[index];
		}

		const uint8_t& operator[](int index) const {
			return m_buffer[index];
		}

		uint16_t read_word(uint16_t location) const {
			const auto lobyte = m_buffer[location];
			const auto hibyte = m_buffer[1 + location];

			return hibyte << 8 | lobyte;
		}
	};
}
