#include "Pch.h"
#include "BlockAllocator.h"
#include "DebugUtil.h"

xe::Core::BlockAllocator::BlockAllocator(const char* name, size_t blockSize, size_t capacity)
	: _name(name)
	, _blockSize(blockSize)
	, _capacity(capacity)
	, _freeBocks(capacity)
{
	ASSERT(blockSize > 0, "BlockAllocator: invalid block size");
	ASSERT(capacity > 0, "BlockAllocator: invalid capacity");

	_data = std::malloc(blockSize * capacity);
	for (size_t i = 0; i < capacity; ++i)
	{
		_freeBocks[i] = static_cast<uint8_t*>(_data) + (i * _blockSize);
	}

	LOG("%s allocated %zu blocks, block size: %zu", _name.c_str(), capacity, blockSize);
}

xe::Core::BlockAllocator::~BlockAllocator()
{
	ASSERT(_blocksAllocatedTotal == _blocksFreed, "BlockAllocator: not all blocks are freed");
	std::free(_data);

	LOG("%s destructed, Allocated: %zu, Freed: %zu, Highest: %zu",
		_name.c_str(), _blocksAllocatedCurrent, _blocksFreed, _blocksHighest);
}

void* xe::Core::BlockAllocator::Allocate()
{
	if (_freeBocks.empty())
	{
		LOG("%s no free blocks available", _name.c_str());
		return nullptr;
	}

	void* freeBlock = _freeBocks.back();
	_freeBocks.pop_back();

	++_blocksAllocatedTotal;
	++_blocksAllocatedCurrent;
	_blocksHighest = std::max(_blocksHighest, _blocksAllocatedCurrent);

	LOG("%s allocatd at %p, Allocated: %zu, HighestCount: %zu",
		_name.c_str(),
		freeBlock,
		_blocksAllocatedCurrent,
		_blocksHighest);

	return freeBlock;
}

void xe::Core::BlockAllocator::Free(void* ptr)
{
	if (ptr == nullptr)
		return;

	const uint8_t* start = static_cast<uint8_t*>(_data);
	const uint8_t* end = static_cast<uint8_t*>(_data) + (_blockSize * _capacity);
	const uint8_t* current = static_cast<uint8_t*>(ptr);
	const auto diff = current - start;
	ASSERT(current >= start && current < end && static_cast<size_t>(diff) % _blockSize == 0,
		"BlockAllocator: invalid address being freed");
	LOG("%s free %p", _name.c_str(), ptr);
	--_blocksAllocatedCurrent;
	++_blocksFreed;
	_freeBocks.emplace_back(ptr);
}
