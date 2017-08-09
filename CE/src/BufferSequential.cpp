#include "BufferSequential.hpp"


namespace CE {

	BufferSequential::BufferSequential(void * data, size_t size) {

		buffer.resize(size);
		char* tmp = reinterpret_cast<char*>(data);
		std::copy(tmp, tmp + size, buffer.begin());
	}

	size_t BufferSequential::getSize() const {

		return buffer.size();
	}

}
