#include "MemoryAllocator.h"


MemoryPool MemoryAllocator::block8(8, defaultPoolNum);
MemoryPool MemoryAllocator::block16(16, defaultPoolNum);
MemoryPool MemoryAllocator::block32(32, defaultPoolNum);
MemoryPool MemoryAllocator::block64(64, defaultPoolNum);
MemoryPool MemoryAllocator::block128(128, defaultPoolNum);
MemoryPool MemoryAllocator::block256(256, defaultPoolNum);