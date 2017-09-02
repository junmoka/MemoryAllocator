#pragma once

#include <new>
#include "MemoryPool.h"

class MemoryAllocator {

public:
	void *operator new (size_t size) {

		void *p = nullptr;

		if (size <= 8) {
			p = block8.top();
			block8.pop();
		}
		else if (size <= 16) {
			p = block16.top();
			block16.pop();
		}
		else if (size <= 32) {
			p = block32.top();
			block32.pop();
		}
		else if (size <= 64) {
			p = block64.top();
			block64.pop();
		}
		else if (size <= 128) {
			p = block128.top();
			block128.pop();
		}
		else if (size <= 256) {
			p = block256.top();
			block256.pop();
		}
		else {
			p = malloc(size);
		}

		return p ? p : throw std::bad_alloc();
	}
	void operator delete (void* p, size_t size) {

		if (size <= 8) {
			block8.push(p);
		}
		else if (size <= 16) {
			block16.push(p);
		}
		else if (size <= 32) {
			block32.push(p);
		}
		else if (size <= 64) {
			block64.push(p);
		}
		else if (size <= 128) {
			block128.push(p);
		}
		else if (size <= 256) {
			block256.push(p);
		}
	}

	static void Reset() {
		block8.Reset(defaultPoolNum);
		block16.Reset(defaultPoolNum);
		block32.Reset(defaultPoolNum);
		block64.Reset(defaultPoolNum);
		block128.Reset(defaultPoolNum);
		block256.Reset(defaultPoolNum);

	}

	static const int defaultPoolNum = 1024;
	static MemoryPool block8;
	static MemoryPool block16;
	static MemoryPool block32;
	static MemoryPool block64;
	static MemoryPool block128;
	static MemoryPool block256;
};