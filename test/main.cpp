

#include <iostream>
#include <string>
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




int main () {

    HQ::hqInit();


    TestTask* testTask = new TestTask();
    testTask->setEvent(HQ::hqCreateEvent());

	// Task with Event
    HQ::hqEnqueue(testTask);
    testTask->getEvent()->wait();

	//test
	//_sleep(10000);

	// this will be non-blocking
	TestTask testTaskB;
	HQ::hqEnqueue(&testTaskB);


    HQ::hqDestroyEvent(testTask->getEvent());
    HQ::hqDestroy();

    delete testTask;

    return 0;
}



