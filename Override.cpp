//
// Created by cc on 2022/4/1.
//
#include <cstdio>
#include <cstdlib>

#include "Override.h"

int Override::class_num = 0;
ClassWrapper* Override::record[MAX_CLASS_NUM] = {};

void Override::check_all() {
    ASSERT(Override::class_num >= 0 && Override::class_num < MAX_CLASS_NUM);
    for(int i = 0; i < Override::class_num; i++) {
        if(Override::record[i] != nullptr) {
            Override::record[i]->check_all();
        }
    }
}

void Override::dump_all() {
    ASSERT(Override::class_num >= 0 && Override::class_num < MAX_CLASS_NUM);
    for(int i = 0; i < Override::class_num; i++) {
        if(Override::record[i] != nullptr) {
            dbg(0, "第%d个对象\n", i);
            Override::record[i]->check_all();
        }
    }
}


void* operator new(std::size_t size, const std::string& file_name, int line) noexcept(false){
    ASSERT(Override::class_num >= 0 && Override::class_num < MAX_CLASS_NUM);
    auto * ptr = (char *)malloc(size + HEAD_SIZE + TAIL_SIZE);
    if (!ptr) {
        throw std::bad_alloc();
    }
    auto* classWrapper = new ClassWrapper(file_name, line, size, ptr + HEAD_SIZE, ptr, ptr + HEAD_SIZE + size);
    classWrapper->fill_all();
    for (int i = 0; i < Override::class_num; i++) {
        if (Override::record[i] == nullptr) {
            Override::record[i] = classWrapper;
            return ptr + HEAD_SIZE;
        }
    }
    ASSERT(Override::class_num >= 0 && Override::class_num + 1 < MAX_CLASS_NUM);
    Override::record[Override::class_num++] = classWrapper;
    return ptr + HEAD_SIZE;
}

void* operator new[](std::size_t size, const std::string& file_name, int line) noexcept(false){
    ASSERT(Override::class_num >= 0 && Override::class_num < MAX_CLASS_NUM);
    auto * ptr = (char *)malloc(size + HEAD_SIZE + TAIL_SIZE);
    if (!ptr) {
        throw std::bad_alloc();
    }
    auto* classWrapper = new ClassWrapper(file_name, line, size, ptr + HEAD_SIZE, ptr, ptr + HEAD_SIZE + size);
    classWrapper->fill_all();
    for (int i = 0; i < Override::class_num; i++) {
        if (Override::record[i] == nullptr) {
            Override::record[i] = classWrapper;
            return ptr + HEAD_SIZE;
        }
    }
    ASSERT(Override::class_num >= 0 && Override::class_num + 1 < MAX_CLASS_NUM);
    Override::record[Override::class_num++] = classWrapper;
    return ptr + HEAD_SIZE;
}

void operator delete(void * ptr, const std::string& file_name, int line) noexcept {
    ASSERT(Override::class_num >= 0 && Override::class_num < MAX_CLASS_NUM);
    for (int i = 0; i < Override::class_num; i++) {
        if (Override::record[i]->ptr == ptr) {
            dbg(0, "DELETE OPERATOR AT %s, %d\n", file_name.c_str(), line);
            Override::record[i]->check_all();
            free(Override::record[i] -> head);
            Override::record[i] = nullptr;
            break;
        }
    }
    free(ptr);
}
void operator delete[](void * ptr, const std::string& file_name, int line) noexcept {
    ASSERT(Override::class_num >= 0 && Override::class_num < MAX_CLASS_NUM);
    for (int i = 0; i < Override::class_num; i++) {
        if (Override::record[i]->ptr == ptr) {
            dbg(0, "DELETE OPERATOR AT %s, %d\n", file_name.c_str(), line);
            Override::record[i]->check_all();
            free(Override::record[i] -> head);
            Override::record[i] = nullptr;
            break;
        }
    }
    free(ptr);
}

void operator delete(void * ptr) {
    ASSERT(Override::class_num >= 0 && Override::class_num < MAX_CLASS_NUM);
    for (int i = 0; i < Override::class_num; i++) {
        if (Override::record[i]->ptr == ptr) {
            dbg(0, "DELETE CLASS CREATE AT %s, %d \n", Override::record[i] -> file_name.c_str(), Override::record[i] -> line);
            Override::record[i]->check_all();
            free(Override::record[i] -> head);
            Override::record[i] = nullptr;
            break;
        }
    }
    free(ptr);
}
void operator delete[](void * ptr) {
    ASSERT(Override::class_num >= 0 && Override::class_num < MAX_CLASS_NUM);
    for (int i = 0; i < Override::class_num; i++) {
        if (Override::record[i]->ptr == ptr) {
            dbg(0, "DELETE CLASS CREATE AT %s, %d\n", Override::record[i] -> file_name.c_str(), Override::record[i] -> line);
            Override::record[i]->check_all();
            free(Override::record[i] -> head);
            Override::record[i] = nullptr;
            break;
        }
    }
    free(ptr);
}
