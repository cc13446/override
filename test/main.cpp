#include <iostream>
#include "../SafeChecker.h"

#include "TestClass.h"

int main() {
    int *a = new int[2];
    int *b = new int[2];
    int *c = new int[2];

    delete[] a;
    b[2] = 1;

    dump_all();
    return 0;
}

