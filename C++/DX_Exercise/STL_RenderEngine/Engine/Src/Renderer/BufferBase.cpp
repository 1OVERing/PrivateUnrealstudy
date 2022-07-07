#include "Core.h"
#include "BufferBase.h"

namespace Ronnie
{
	BufferBase::BufferBase()
		: buffer(nullptr), count(0), byteWidth(0)
	{
	}

	BufferBase::~BufferBase()
	{
		SafeRelease(buffer);
	}
}