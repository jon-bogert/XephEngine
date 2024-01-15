#ifndef __XE_CORE_BLOCKALLOCATOR_H__
#define __XE_CORE_BLOCKALLOCATOR_H__

namespace xe::Core
{
	class BlockAllocator
	{
	public:
		BlockAllocator(const char* name, size_t blockSize, size_t capacity);
		virtual ~BlockAllocator();
		BlockAllocator(const BlockAllocator&) = delete;
		BlockAllocator(const BlockAllocator&&) = delete;
		BlockAllocator& operator=(const BlockAllocator&) = delete;
		BlockAllocator& operator=(const BlockAllocator&&) = delete;

		void* Allocate();
		void Free(void* ptr);

	private:
		std::string _name;
		std::vector<void*>_freeBocks;

		void* m_data = nullptr;
		size_t m_blockSize = 0;
		size_t m_capacity = 0;
		size_t m_blocksAllocatedCurrent = 0;
		size_t m_blocksAllocatedTotal = 0;
		size_t m_blocksFreed = 0;
		size_t m_blocksHighest = 0;
	};
}

#endif // !__XE_CORE_BLOCKALLOCATOR_H__