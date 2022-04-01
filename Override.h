//
// Created by cc on 2022/4/1.
//

#ifndef OVERRIDE_OVERRIDE_H
#define OVERRIDE_OVERRIDE_H

#include <string>

#include "ClassWrapper.h"

#define dbg(sw, format, ...) printf(format, __VA_ARGS__)

#define MAX_CLASS_NUM 10000

class Override {
public:
    static ClassWrapper* record[MAX_CLASS_NUM];
    static int class_num;

    static void check_all();
    static void dump_all();
};
void* operator new(std::size_t size, const std::string& file_name, int line) noexcept(false);
void* operator new[](std::size_t size, const std::string& file_name, int line) noexcept(false);

void operator delete(void * ptr, const std::string& file_name, int line) noexcept;
void operator delete[](void * ptr, const std::string& file_name, int line) noexcept;

void operator delete(void * ptr);
void operator delete[](void * ptr);

#endif //OVERRIDE_OVERRIDE_H
