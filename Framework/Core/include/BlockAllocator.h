#ifndef __XE_CORE_BLOCKALLOCATOR_H__
#define __XE_CORE_BLOCKALLOCATOR_H__

namespace xe::Core
{
	class BlockAllocator
	{
		std::string _name;
		std::vector<void*>_freeBocks;

		void* _data = nullptr;
		size_t _blockSize = 0;
		size_t _capacity = 0;
		size_t _blocksAllocatedCurrent = 0;
		size_t _blocksAllocatedTotal = 0;
		size_t _blocksFreed = 0;
		size_t _blocksHighest = 0;

	public:
		BlockAllocator(const char* name, size_t blockSize, size_t capacity);
		virtual ~BlockAllocator();
		BlockAllocator(const BlockAllocator&) = delete;
		BlockAllocator(const BlockAllocator&&) = delete;
		BlockAllocator& operator=(const BlockAllocator&) = delete;
		BlockAllocator& operator=(const BlockAllocator&&) = delete;

		void* Allocate();
		void Free(void* ptr);
	};
}

#endif // __XE_CORE_BLOCKALLOCATOR_H__