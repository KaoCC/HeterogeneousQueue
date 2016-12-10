

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


class TestTask : public HQ::Task {

public:



    RunFunctionType getRunFunction() override {
        return runF;
    }

    TaskParameter* getTaskParameter() override {
        return &p;
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
    RunFunctionType runF {ff};
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
	//_sleep(10000);

	// this will be non-blocking
	TestTask testTaskB;
	HQ::EnqueueHeterogeneousQueue(&testTaskB);


    HQ::DestroyEvent(testTask->getEvent());
    HQ::DestroyHeterogeneousQueue();

    delete testTask;

    return 0;
}



