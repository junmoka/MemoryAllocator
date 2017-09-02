//#define MEMORY_LEAK_CHECK

#ifdef MEMORY_LEAK_CHECK
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>  
#endif

#include <iostream>
#include <chrono>

#include "Allocator\MemoryAllocator.h"

class Test1{
	int val1;
	int val2;
	char val3;
};


class Test2 : public MemoryAllocator{
	int val1;
	int val2;
	char val3;
};

int main(){

#ifdef MEMORY_LEAK_CHECK
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

#ifdef _DEBUG
	std::cout << "DebugBuild" << std::endl;
#else
	std::cout << "ReleaseBuild" << std::endl;
#endif

	const int loop = 1000000;

	std::cout << "AllocatorTest" << std::endl;
	std::cout << "AllocatorSize:" << sizeof(Test1) << std::endl;
	std::cout << "AllocatorNum:" << loop << std::endl << std::endl;

	double avgDefaultNew = 0;
	double avgCustomNew = 0;

	double avgDefaultDelete = 0;
	double avgCustomDelete = 0;

	double avgDefaultNewDelete = 0;
	double avgCustomNewDelete = 0;


	int testNum = 10;
	for (int i = 0; i < testNum; ++i) {
		
		//2週目以降メモリプールのサイズがloop数分に拡張されているので正確な計測のためリセット
		MemoryAllocator::Reset();

		{
			std::cout << "DefaultAllocator" << std::endl;

			auto test = new Test1*[loop];

			std::chrono::system_clock::time_point  start, end;
			start = std::chrono::system_clock::now();

			for (int j = 0; j < loop; j++) {
				test[j] = new Test1();
			}
			end = std::chrono::system_clock::now();
			auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

			std::cout << "newTime:" << elapsed << "us" << std::endl;
			avgDefaultNew += elapsed;

			start = std::chrono::system_clock::now();
			for (int j = 0; j < loop; j++) {
				delete test[j];
			}
			end = std::chrono::system_clock::now();
			elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

			std::cout << "deleteTime:" << elapsed << "us" << std::endl;
			avgDefaultDelete += elapsed;

			start = std::chrono::system_clock::now();

			for (int j = 0; j < loop; j++) {
				test[j] = new Test1();
				delete test[j];
			}
			end = std::chrono::system_clock::now();
			elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

			std::cout << "new/deleteTime:" << elapsed << "us" << std::endl << std::endl;
			avgDefaultNewDelete += elapsed;

			delete[] test;

		}

		{
			std::cout << "CustomAllocator" << std::endl;
			auto test = new Test2*[loop];

			std::chrono::system_clock::time_point  start, end;
			start = std::chrono::system_clock::now();

			for (int j = 0; j < loop; j++) {
				test[j] = new Test2();
			}
			end = std::chrono::system_clock::now();
			auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

			std::cout << "newTime:" << elapsed << "us" << std::endl;
			avgCustomNew += elapsed;

			start = std::chrono::system_clock::now();
			for (int j = 0; j < loop; j++) {
				delete test[j];
			}
			end = std::chrono::system_clock::now();
			elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

			std::cout << "deleteTime:" << elapsed << "us" << std::endl;
			avgCustomDelete += elapsed;


			start = std::chrono::system_clock::now();

			for (int j = 0; j < loop; j++) {
				test[j] = new Test2();
				delete test[j];
			}
			end = std::chrono::system_clock::now();
			elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

			std::cout << "new/deleteTime:" << elapsed << "us" << std::endl << std::endl;
			avgCustomNewDelete += elapsed;

			delete[] test;

		}
	}

	std::cout << "DefaultAllocatorAverage" << std::endl;
	std::cout << "newTime:" << avgDefaultNew / testNum << "us" << std::endl;
	std::cout << "deleteTime:" << avgDefaultDelete / testNum << "us" << std::endl;
	std::cout << "new/deleteTime:" << avgDefaultNewDelete / testNum << "us" << std::endl << std::endl;

	std::cout << "CustomAllocatorAverage" << std::endl;
	std::cout << "newTime:" << avgCustomNew / testNum << "us" << std::endl;
	std::cout << "deleteTime:" << avgCustomDelete / testNum << "us" << std::endl;
	std::cout << "new/deleteTime:" << avgCustomNewDelete / testNum << "us" << std::endl << std::endl;


	std::cout << "CustomAllocatorRate" << std::endl;
	std::cout << "newTimeRate:" << avgCustomNew / avgDefaultNew << "%" << std::endl;
	std::cout << "deleteTimeRate:" << avgCustomDelete / avgDefaultDelete << "%" << std::endl;
	std::cout << "new/deleteTimeRate:" << avgCustomNewDelete / avgDefaultNewDelete << "%" << std::endl << std::endl;

	getchar();
    return 0;
}

