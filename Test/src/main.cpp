

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
	virtual size_t getSizeInByte() override {
		return TestTaskParameter::SIZE * sizeof(int);
	}
	virtual void * getData() override {
		return a;
	}


	static const size_t SIZE = 10000;
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

		// init params

		int* tmpArray = getPtrArray();
		std::fill(tmpArray, tmpArray + MAX_NDR_SIZE, 0);

		// CL ?
		//buffer = CreateBufferWithIndex(1, MAX_NDR_SIZE * sizeof(int), bufferArray);

		// KAOCC: check the location of the CL source
		program[1] = CompileExecutableWithIndex(1, "test.cl", nullptr);
		runF[1] = program[1]->createFunction("add");


		//MapBufferWithIndex(1, buffer, 0, MAX_NDR_SIZE * sizeof(int), (void**)&bufferArray);

		//set argument ?
		//runF[1]->setArg(0, buffer);


	}

	CE::Function* getRunFunction(size_t index) override {
		return runF[index];
	}

	TaskParameter* getTaskParameter(size_t index) override {
		return &param;
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
		return static_cast<int*>(param.getData());
	}

	// for testing only
	CE::Buffer* getBuffer() {
		return buffer;
	}



	// Inherited via Task
	virtual size_t getNumOfParameters() override {
		return NUM_OF_PARAMS;
	}

	~TestTask() {
		delete[] bufferArray;
	}

private:
	//CE::Function const* runF { CreateSequentialFunctionWithIndex(0, "test", std::move(fff) )};


	static const size_t MAX_NDR_SIZE = 10000;
	static const size_t NUM_OF_INSTANCE = 2;

	CE::Function* runF[NUM_OF_INSTANCE];
	CE::Executable* program[NUM_OF_INSTANCE];

	// TEST!
	TestTaskParameter param;
	static const size_t NUM_OF_PARAMS = 1;

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
	//std::cin >> tmp;

	TestTask testTask;
	testTask.setEvent(HQ::CreateEvent());

	int* ptr = testTask.getPtrArray();

	//WriteBufferWithIndex(1, testTask->getBuffer(), 0, testTask->getGlobalSize() * sizeof(int), ptr);

	// Task with Event
	std::cout << "enqueue Task One" << std::endl;
	HQ::EnqueueHeterogeneousQueue(&testTask);
	testTask.getEvent()->wait();

	// KAOCC: NOTE: the Event system here is currently broken ...

	//test
	//_sleep(5000);

	std::cout << "Task 1 complete" << std::endl;


	// KAOCC: how do you know which part of the buffer should be loaded ?
	//ReadBufferWithIndex(1, testTask->getBuffer(), 0, (testTask->getGlobalSize() * sizeof(int)) / 2, ptr + 500);

	std::cerr << "Result" << std::endl;

	std::for_each(ptr, ptr + testTask.getGlobalSize(), [](const int& n) { std::cerr << n << std::endl; });
	

	std::cerr << "Result END" << std::endl;


	std::cin >> tmp;

	// this will be non-blocking
	//TestTask testTaskB;
	//HQ::EnqueueHeterogeneousQueue(&testTaskB);

	//_sleep(5000);

	//std::cout << "Task 2 complete" << std::endl;


	const size_t ARRAY_SZ = 10;
	TestTask taskArray[ARRAY_SZ];

	for (size_t i = 0; i < ARRAY_SZ; ++i) {
		taskArray[i].setEvent(HQ::CreateEvent());
	}

	for (size_t i = 0; i < ARRAY_SZ; ++i) {
		HQ::EnqueueHeterogeneousQueue(&taskArray[i]);
	}

	for (size_t i = 0; i < ARRAY_SZ; ++i) {
		taskArray[i].getEvent()->wait();
	}

	std::cout << "Task Array complete" << std::endl;

	std::cin >> tmp;

	std::cerr << "Result" << std::endl;
	for (size_t i = 0; i < ARRAY_SZ; ++i) {
		std::cerr << "--------------- Test Array: " << i << " --------------- " << std::endl;
		//std::cin >> tmp;
		int* ptr = taskArray[i].getPtrArray();
		//std::for_each(ptr, ptr + taskArray[i].getGlobalSize(), [](const int& n) { std::cerr << n << std::endl; });
	}

	std::cerr << "Result END" << std::endl;

	HQ::DestroyEvent(testTask.getEvent());
	HQ::DestroyHeterogeneousQueue();

	//delete testTask;

	return 0;
}



