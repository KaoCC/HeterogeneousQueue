

#include "HQ/ThreadPool.h"




void f() {

}



int main () {

    HQ::ThreadPool<void> pool;

    pool.enqueue( f );


    return 0;
}



