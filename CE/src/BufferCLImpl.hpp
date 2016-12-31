
#ifndef _CE_BUFFERCLIMPL_HPP_
#define _CE_BUFFERCLIMPL_HPP_

#include "Buffer.hpp"
#include "CLBuffer.hpp"

namespace CE {

	class BufferCLImpl : public Buffer {
	public:
		BufferCLImpl(CLAL::CLBuffer<char> buf) : buffer(std::move(buf)) {}
		//~BufferCLImpl() override {};

		size_t getSize() const override { return buffer.getElementCount(); }

		CLAL::CLBuffer<char> getData() const { return buffer; }

	private:
		CLAL::CLBuffer<char> buffer;
	};

}


#endif
