

#define BOOST_TEST_MODULE ENQUEUE_HQ_TEST
#include <boost/test/unit_test.hpp>

#include "hq/heterogeneous_queue.hpp"


BOOST_AUTO_TEST_SUITE(enqueue_test)


class test_object {
public:

    test_object() = default;
    test_object(const test_object&) = delete;
    test_object& operator=(const test_object&) = delete;

    test_object(test_object&&) = default;
    test_object& operator=(test_object&&) = default;

    int val {0};
};


class test_functor {

public:
    template<class Func, class... Args>
    int operator()(Func&& func, Args&& ... args){
        return func(args...);
    }

};

int functor_helper_func(int a, test_object& obj) {
    obj.val -= a;
    return obj.val;
}


void empty_func() {
}


char val_func(char c) {
    ++c;
    return c;
}

int ref_func(int& element) {
    ++element;
    return element;
}


int obj_func(test_object& obj) {
    obj.val++;
    return obj.val;
}

test_object obj_move_func(test_object&& rval_ref) {
    return std::forward<test_object>(rval_ref);
}


BOOST_AUTO_TEST_CASE(enqueue_empty_func) {

    hq::heterogeneous_queue hetero_queue;

    auto f = hetero_queue.enqueue<void>(empty_func);

    BOOST_TEST(f.valid());

    f.get();
}


BOOST_AUTO_TEST_CASE(enqueue_val_func) {

    hq::heterogeneous_queue hetero_queue;

    char c = 'A';
    auto f = hetero_queue.enqueue<char>(val_func, c);

    BOOST_TEST(f.valid());
    BOOST_TEST(c == 'A');
    BOOST_TEST(c == f.get() - 1);

}

BOOST_AUTO_TEST_CASE(enqueue_ref_func) {

    hq::heterogeneous_queue hetero_queue;

    int local = 100;

    auto f = hetero_queue.enqueue<int>(ref_func, std::ref(local));

    BOOST_TEST(f.valid());
    auto result = f.get();
    BOOST_TEST(local == result);

}

BOOST_AUTO_TEST_CASE(enqueue_obj_func) {

    hq::heterogeneous_queue hetero_queue;
    test_object obj;

    auto f = hetero_queue.enqueue<int>(obj_func, std::ref(obj));

    BOOST_TEST(f.valid());
    auto result = f.get();
    BOOST_TEST(obj.val == result);

}


BOOST_AUTO_TEST_CASE(enqueue_obj_move_func) {

    hq::heterogeneous_queue hetero_queue;
    test_object obj_a;
    obj_a.val = 100;

    auto f = hetero_queue.enqueue<test_object>(obj_move_func, std::move(obj_a));

    BOOST_TEST(f.valid());

    test_object obj_b = f.get();

    BOOST_TEST(obj_b.val == 100);
}

BOOST_AUTO_TEST_CASE(enqueue_functor) {

    hq::heterogeneous_queue hetero_queue;

    int a = 200;
    test_object obj;
    obj.val = 1000;

    auto f = hetero_queue.enqueue<int>(test_functor(), functor_helper_func, a, std::ref(obj));

    a += 1234;

    BOOST_TEST(f.valid());
    auto result = f.get();
    BOOST_TEST(obj.val == result);
}


BOOST_AUTO_TEST_SUITE_END()





