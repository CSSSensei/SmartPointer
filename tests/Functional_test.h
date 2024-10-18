//
// Created by tomin on 16.10.2024.
//

#ifndef SMARTPOINTER_FUNCTIONAL_TEST_H
#define SMARTPOINTER_FUNCTIONAL_TEST_H
#include <iostream>
#include <cassert>
#include "../pointers/ShrdPtr.h"
#include "../pointers/UnqPtr.h"

using namespace std;

// Тесты для ShrdPtr
void test_shrdPtr() {
    // Test Creation
    ShrdPtr<int> sp1(new int(5));
    assert(*sp1 == 5);
    assert(sp1.use_count() == 1);

    {    // Test Copy Constructor
        ShrdPtr<int> sp2(sp1);
        assert(*sp2 == 5);
        assert(sp1.use_count() == 2);
        assert(sp2.use_count() == 2);
        {
            // Test Assignment Operator
            ShrdPtr<int> sp3;
            sp3 = sp1;
            assert(*sp3 == 5);
            assert(sp1.use_count() == 3);
            assert(sp3.use_count() == 3);
        }
        assert(sp1.use_count() == 2);

    }
    assert(sp1.use_count() == 1);


}

void test_unqPtr() {
    // Test Creation
    UnqPtr<int> up1(new int(10));
    assert(*up1 == 10);

    // Test Move Constructor
    UnqPtr<int> up2 = move(up1);
    assert(*up2 == 10);
    assert(!up1);

    // Test Move Assignment Operator
    UnqPtr<int> up3;
    up3 = move(up2);
    assert(*up3 == 10);
    assert(!up2);

    // Test Reset
    up3.reset(new int(20));
    assert(*up3 == 20);

    // Test Release
    int* rawPtr = up3.release();
    assert(rawPtr != nullptr);
    assert(*rawPtr == 20);
    assert(!up3);
    delete rawPtr;
}

int functional_main() {
    test_shrdPtr();
    test_unqPtr();
    cout << "All tests passed!" << endl;
    return 0;
}

#endif //SMARTPOINTER_FUNCTIONAL_TEST_H
