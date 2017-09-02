#pragma once

#include <vector>

class MemoryPool {

public:
	MemoryPool(int blockSize, int blockNum) :index(0) , stack(nullptr){
		this->blockSize = blockSize;
		this->blockNum = blockNum;

		stack = new void*[blockNum];
		auto pool = new char[blockSize * blockNum];
		poolVector.emplace_back(pool);

		for (int i = 0; i < blockNum; i++) {
			stack[i] = pool + i * blockSize;
		}
	}

	~MemoryPool() {
		delete[] stack;

		for (char* pool: poolVector) {
			delete[] pool;
		}
	}

	void push(void* val) {
		if (index == 0) {
			return;
		}
		--index;
		stack[index] = val;

	}

	void* top() {
		if (blockNum <= index) {
			resize();
		}
		return stack[index];

	}
	void pop() {
		if (blockNum <= index) {
			return;
		}
		stack[index] = nullptr;
		++index;
	}

	void Reset(int blockNum) {
		if (index != 0) {
			return;
		}

		delete[] stack;

		for (char* pool : poolVector) {
			delete[] pool;
		}

		poolVector.clear();

		this->blockNum = blockNum;
		stack = new void*[blockNum];
		auto pool = new char[blockSize * blockNum];
		poolVector.emplace_back(pool);

		for (int i = 0; i < blockNum; i++) {
			stack[i] = pool + i * blockSize;
		}

	}


private:

	void resize() {
		delete[] stack;

		stack = new void*[blockNum * 2];
		auto pool = new char[blockSize * blockNum];
		poolVector.emplace_back(pool);

		for (int i = 0; i < blockNum; i++) {
			stack[blockNum + i] = pool + i * blockSize;
		}

		blockNum = blockNum * 2;

	}

	int index;
	std::vector<char*> poolVector;
	void **stack;
	int blockSize;
	int blockNum;

};
