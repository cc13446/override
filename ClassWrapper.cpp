//
// Created by cc on 2022/4/1.
//

#include "ClassWrapper.h"

#include <utility>

ClassWrapper::ClassWrapper(std::string file_name, int line, int size, void *ptr, void *head, void *tail) {
    this->file_name = std::move(file_name);
    this->line = line;
    this->size = size;
    this->ptr = ptr;
    this->head = head;
    this->tail = tail;
}

void ClassWrapper::fill_head() const {
    ASSERT(HEAD_SIZE % 16 == 0);
    auto * temp = static_cast<uint16_t *>(head);
    for(int i = 0; i < HEAD_SIZE / 16; i++) {
        temp[i] = HEAD_FILL;
    }
}

void ClassWrapper::fill_tail() const {
    ASSERT(TAIL_SIZE % 16 == 0);
    auto * temp = static_cast<uint16_t *>(tail);
    for(int i = 0; i < TAIL_SIZE / 16; i++) {
        temp[i] = TAIL_FILL;
    }
}

void ClassWrapper::fill_all() const {
    fill_head();
    fill_tail();
}

void ClassWrapper::check_head() const {
    ASSERT(HEAD_SIZE % 16 == 0);
    auto * temp = static_cast<uint16_t *>(head);
    for(int i = 0; i < HEAD_SIZE / 16; i++) {
        ASSERT_SAFE(temp[i] == HEAD_FILL, file_name.c_str(), line);
    }
}

void ClassWrapper::check_tail() const {
    ASSERT(TAIL_SIZE % 16 == 0);
    auto * temp = static_cast<uint16_t *>(tail);
    for(int i = 0; i < TAIL_SIZE / 16; i++) {
        ASSERT_SAFE(temp[i] == TAIL_FILL, file_name.c_str(), line);
    }
}

void ClassWrapper::check_all() const {
    check_head();
    check_tail();
}
