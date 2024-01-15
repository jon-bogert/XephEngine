#ifndef __XE_CORE_TYPEDALLOCATOR_H__
#define __XE_CORE_TYPEDALLOCATOR_H__

namespace xe::Core
{
	template<typename DataType>
	class TypedAllocator : private BlockAllocator
	{
	public:
		TypedAllocator(const char* name, size_t capacity)
			: BlockAllocator(name, sizeof(DataType), capacity) { }

		template<typename...Args>
		DataType* New(Args&&... args)
		{
			DataType* instance = static_cast<DataType*>(Allocate());
			//placement new, calls constructor on designated location
			new (instance) DataType(std::forward<Args>(args)...);

			return instance;
		}

		void Delete(DataType* ptr)
		{
			if (ptr == nullptr)
			{
				return;
			}
			ptr->~DataType();
			Free(ptr);
		}
	};
}

#endif //!__XE_CORE_TYPEDALLOCATOR_H__
