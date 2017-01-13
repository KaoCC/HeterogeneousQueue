

#include <iostream>
#include <string>
#include <functional>
#include "HQ.hpp"


#include <algorithm>

using namespace HQ;



class TestTaskParameter : public TaskParameter {

public:
	TestTaskParameter() {

	}

	// Inherited via TaskParameter
	virtual size_t getSize() override {
		return TestTaskParameter::SIZE * sizeof(int);
	}
	virtual void * getData() override {
		return nullptr;
	}


	static const size_t SIZE = 500;
	int a[SIZE];

	std::string name{ "test" };
	
};


void f(TaskParameter* t) {
	std::cout << " This is a test " << std::endl;
}


void ff(TaskParameter* tt) {
	TestTaskParameter* real = static_cast<TestTaskParameter*>(tt);
	std::cout << "NAME:" << real->name << std::endl;
}

void fff(int gid) {
	std::cout << gid << std::endl;
}



void ffff(int gid, int* buffer) {

	std::cerr << gid << ":" << buffer[gid] << std::endl;
	buffer[gid] += gid;
}


class TestTask : public HQ::Task {

public:


	TestTask() {


		// init buffer array
		bufferArray = new int[MAX_NDR_SIZE];

		std::fill(bufferArray, bufferArray + MAX_NDR_SIZE, 0);

		// bind it !
		std::function<void(int)> testFunc = std::bind(ffff, std::placeholders::_1, bufferArray);

		program[0] = CreateSequentialExecutableWithIndex(0);
		runF[0] = CreateSequentialFunction(program[0], "add", std::move(testFunc));


		// CL ?
		buffer = CreateBufferWithIndex(1, MAX_NDR_SIZE * sizeof(int), bufferArray);

		// KAOCC: check the location of the CL source
		program[1] = CompileExecutableWithIndex(1, "test.cl", nullptr);
		runF[1] = program[1]->createFunction("add");


		//MapBufferWithIndex(1, buffer, 0, MAX_NDR_SIZE * sizeof(int), (void**)&bufferArray);

		//set argument ?
		runF[1]->setArg(0, buffer);


	}

	CE::Function* getRunFunction(size_t index) override {
		return runF[index];
	}

	TaskParameter* getTaskParameter(size_t index) override {
		return &param[index];
	}

	size_t getGlobalSize() override {
		return MAX_NDR_SIZE;
	}

	Event* getEvent() override {
		return event;
	}

	void setEvent(Event* e) {
		event = e;
	}

	// for testing only
	int* getPtrArray() {
		return bufferArray;
	}

	// for testing only
	CE::Buffer* getBuffer() {
		return buffer;
	}



	// Inherited via Task
	virtual size_t getNumOfParameters() override {
		return numberOfParams;
	}

	~TestTask() {
		delete[] bufferArray;
	}

private:
	//CE::Function const* runF { CreateSequentialFunctionWithIndex(0, "test", std::move(fff) )};


	static const size_t MAX_NDR_SIZE = 1000;
	static const size_t NUM_OF_INSTANCE = 2;

	CE::Function* runF[NUM_OF_INSTANCE];
	CE::Executable* program[NUM_OF_INSTANCE];

	// TEST!
	TestTaskParameter param[2];
	size_t numberOfParams = 2;

	Event* event {nullptr};


	CE::Buffer* buffer;
	int* bufferArray = nullptr;



};


void test(int i) {
	std::cout << "test function" << std::endl;
}


int main() {


	// test




	HQ::CreateHeterogeneousQueue();

	int tmp;
	std::cin >> tmp;

	TestTask* testTask = new TestTask();
	testTask->setEvent(HQ::CreateEvent());

	int* ptr = testTask->getPtrArray();

	//WriteBufferWithIndex(1, testTask->getBuffer(), 0, testTask->getGlobalSize() * sizeof(int), ptr);

	// Task with Event
	HQ::EnqueueHeterogeneousQueue(testTask);
	testTask->getEvent()->wait();

	// KAOCC: NOTE: the Event system here is currently broken ...

	//test
	_sleep(10000);

	std::cout << "Task 1 complete" << std::endl;


	// KAOCC: how do you know which part of the buffer should be loaded ?
	//ReadBufferWithIndex(1, testTask->getBuffer(), 0, (testTask->getGlobalSize() * sizeof(int)) / 2, ptr + 500);

	std::cerr << "Result" << std::endl;

	std::for_each(ptr, ptr + testTask->getGlobalSize(), [](const int& n) { std::cerr << n << std::endl; });
	

	std::cerr << "Result END" << std::endl;


	std::cin >> tmp;

	// this will be non-blocking
	TestTask testTaskB;
	HQ::EnqueueHeterogeneousQueue(&testTaskB);

	_sleep(10000);

	std::cout << "Task 2 complete" << std::endl;

	HQ::DestroyEvent(testTask->getEvent());
	HQ::DestroyHeterogeneousQueue();

	delete testTask;

	return 0;
}



