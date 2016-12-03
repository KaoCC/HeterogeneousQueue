

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



    RunFunctionType getRunFunction() {
        return runF;
    }

    TaskParameter* getTaskParameter() {
        return &p;
    }

    Event* getEvent() {
        return nullptr;
    }

	~TestTask() {

	}

    RunFunctionType runF {ff};
	TestTaskParameter p;

};




int main () {

    HQ::hqInit();


    TestTask* testTask = new TestTask();

	// TODO: we need to implement event here
    HQ::hqEnqueue(testTask);

	//test
	_sleep(10000);

    HQ::hqDestroy();

    delete testTask;

    return 0;
}



