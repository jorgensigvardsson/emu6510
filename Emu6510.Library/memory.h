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

		using iterator = std::vector<uint8_t>::iterator;
		using const_iterator = std::vector<uint8_t>::const_iterator;

		iterator begin() { return m_buffer.begin(); }
		iterator end() { return m_buffer.end(); }
		const_iterator begin() const { return m_buffer.begin(); }
		const_iterator end() const { return m_buffer.end(); }
	};
}
