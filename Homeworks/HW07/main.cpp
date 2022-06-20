#include <iostream>
#include <cassert>
#include "ringbuffer.hpp"

int add_five(int x){
    return x + 5;
}

int main(){
    assert(1 == 1);

    std::clog << "Test\n";

    RingBuffer<int> rb;
    assert(rb.is_empty());

    std::vector<int> wbuf, rbuf;
    wbuf.resize(20);
    for (int i = 0; i < 20; i++) wbuf[i] = i + 1;

    assert(rb.write_multi(20, wbuf));
    assert(rb.is_empty() == false);
    assert(rb.get_capacity() == 32);

    // check iterator 
    int tmp = 101;
    std::clog << "Testing iterator operator ++ ";
    for (__detail::__iterator<int> i = rb.begin(); i != rb.end(); i++){

        __detail::__const_iterator<int> ci(i);
        (*i) += 100;  // Testing if we can modify the numbers
        // std::clog << (*i) << ' ';
        assert((*ci) == tmp);
        tmp += 1;
        (*i) -= 100;
    }
    std::clog << '\n';

    // check operator --
    tmp = 20;
    std::clog << "Testing Operator -- ";
    for (__detail::__iterator<int> i = rb.end() - 1; i != rb.begin(); i--){
        // std::clog << (*i) << ' ';
        assert((*i) == tmp);
        tmp--;
    }
    std::clog << '\n';


    // check const iterator 
    std::clog << "Testing const iterator ";
    
    tmp = 1;
    for (__detail::__const_iterator<int> i = rb.cbegin(); i != rb.cend(); i++){
        // std::clog << (*i) << ' ';
        // (*i) += 100; // If this compiles, you are dead. This code mustn't compile.
        assert((*i) == tmp);
        tmp += 1;
    }
    std::clog << '\n';

    // read 10 elements by multi
    assert(rbuf.size() == 0);
    assert(rb.read_multi(10, rbuf));
    assert(rbuf.size() == 10);
    for (int i = 0; i < 10; i++){
        assert(rbuf[i] == i + 1);
    }

    // std::function<int(int)> fn = add_five;
    // add all elements by five
    assert(rb.map(add_five));

    // read remaining 10 elements one by one
    for (int i = 10; i < 20; i++){
        int x;
        assert(rb.read(x));
        assert(x == i+6);
    }

    // now it should be empty
    assert(rb.is_empty());

    RingBuffer<int> rb2;
    wbuf.resize(20);
    for (int i = 0; i < 20; i++) wbuf[i] = i + 1;

    assert(rb2.write_multi(20, wbuf));
    assert(rb2.is_empty() == false);
    assert(rb2.get_capacity() == 32);
    // [1, 2, ..., 20, ...(empty), 31]
    rbuf.resize(0);
    assert(rb2.read_multi(10, rbuf));
    assert(rbuf.size() == 10);
    for (int i = 0; i < 10; i++){
        assert(rbuf[i] == i + 1);
    }
    // [(empty 1~10), 11, 12, ..., 20, (empty...)]
    
    
    std::clog << "Testing iterator ++ reverse ";
    for (size_t i = 0; i < wbuf.size(); i++){
        wbuf[i] = wbuf[i] + 1000;
    }
    assert(rb2.write_multi(20, wbuf));
    assert(rb2.get_capacity() == 32);
    const int * shita, * shitb;
    tmp = 11;
    for (__detail::__const_iterator<int> ttt = rb2.cbegin(); ttt != rb2.cend(); ttt++){
        // std::clog << *ttt << ' ';
        assert(*ttt == tmp);
        // std::clog << "| Temp" << tmp << " | ";
        tmp = ((tmp == 20)? 1001 : tmp+1);
        if (*ttt == 1012){
            shita = &(*ttt);
        }
        if (*ttt == 1013){
            shitb = &(*ttt);
        }
    }
    assert(shita - shitb == 31);
    std::clog << '\n';

    std::clog << "Test passed\n";

    return 0;
}