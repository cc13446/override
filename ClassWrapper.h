//
// Created by cc on 2022/4/1.
//

#ifndef OVERRIDE_CLASSWRAPPER_H
#define OVERRIDE_CLASSWRAPPER_H

#include <string>


#define ASSERT(C) do {                              \
    if (!(C)) {                                     \
        printf("**** FATAL: ASSERT(%s): FAILED!\n"  \
            "\tFile %s, Line %d\n",                 \
            #C, __FILE__, __LINE__);                \
        exit(1);                                    \
    }                                               \
} while(0)


#define ASSERT_SAFE(C, file_name, line) do {                    \
    if (!(C)) {                                                 \
        printf("**** FATAL: CLASS_NOT_SAFE_WHICH_CREATE_AT:\n"  \
            "\tFile %s, Line %d\n",                             \
            file_name, line);                                   \
        exit(1);                                                \
    }                                                           \
} while(0)



const char HEAD_FILL = (char)0xc8;
const char TAIL_FILL = (char)0x8c;

#define HEAD_SIZE 128
#define TAIL_SIZE 128

class ClassWrapper {

public:
    std::string file_name;
    int line;
    int size;
    void* ptr;
    void* head;
    void* tail;

    ClassWrapper(std::string file_name, int line, int size, void* ptr, void* head, void* tail);

    void fill_head() const;
    void fill_tail() const;

    void fill_all() const;

    void check_head() const;
    void check_tail() const;

    void check_all() const;

};


#endif //OVERRIDE_CLASSWRAPPER_H
