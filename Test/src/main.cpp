

#include <iostream>
#include <string>
#include <functional>
#include "HQ.hpp"


using namespace HQ;



class TestTaskParameter : public TaskParameter {

public:
	TestTaskParameter() {

	}


	std::string name {"test"};
};


void f (TaskParameter* t) {
	std::cout << " This is a test " << std::endl;
}


void ff(TaskParameter* tt) {
	TestTaskParameter* real = static_cast<TestTaskParameter*>(tt);
	std::cout << "NAME:" << real->name << std::endl;
}

void fff(int gid) {
	std::cout << gid << std::endl;
}

class TestTask : public HQ::Task {

public:


	TestTask() {
		program[0] = CreateSequentialExecutableWithIndex(0);
		runF[0] = CreateSequentialFunction(program[0], "add", std::move(fff));

		// CL ?
		program[1] = CompileExecutableWithIndex(1, "test.cl", nullptr);
		runF[1] = program[1]->createFunction("add");

		//set argument ?

	}

    CE::Function const* getRunFunction(size_t index) override {
        return runF[index];
    }

    TaskParameter* getTaskParameter() override {
        return &p;
    }

	size_t getGlobalSize() override  {
		return 1000;
	}

    Event* getEvent() override {
        return event;
    }

    void setEvent(Event* e) {
        event = e;
    }

	~TestTask() {

	}

private:
	//CE::Function const* runF { CreateSequentialFunctionWithIndex(0, "test", std::move(fff) )};


	static const size_t NUM_OF_INSTANCE = 2;

	CE::Function* runF[NUM_OF_INSTANCE];
	CE::Executable* program[NUM_OF_INSTANCE];
	TestTaskParameter p;
    Event* event {nullptr};




};


void test(int i) {
	std::cout << "test function" << std::endl;
}


int main () {


	// test




    HQ::CreateHeterogeneousQueue();


    TestTask* testTask = new TestTask();
    testTask->setEvent(HQ::CreateEvent());

	// Task with Event
    HQ::EnqueueHeterogeneousQueue(testTask);
    testTask->getEvent()->wait();

	//test
	_sleep(10000);

	std::cout << "Task 1 complete" << std::endl;

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



