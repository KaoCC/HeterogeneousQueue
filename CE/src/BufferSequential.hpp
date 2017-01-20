#ifndef _CE_BUFFERSEQUENTIAL_HPP_
#define _CE_BUFFERSEQUENTIAL_HPP_


#include "Buffer.hpp"

#include <vector>

namespace CE {

	class BufferSequential : public Buffer {


	public:

		BufferSequential(void* data, size_t size);

		virtual size_t getSize() const override;


	private:
		std::vector<char> buffer;

	};
}







#endif
