// Copyright 2021 NNTU-CS
#include "train.h"
#include "stdint.h"

Train::Train() : countOp(0), first(nullptr) {}

Train::~Train() {
  if (!first) return;
  Car* current = first;
  do {
    Car* next = current->next;
    delete current;
    current = next;
  } while (current != first);  
  first = nullptr;
}

void Train::addCar(bool light) {
  if (first == nullptr) {
    first = new Car{ light, nullptr, nullptr };
    return;
  } else if (first->next == nullptr) {
    Car* temp = new Car{ light, nullptr, nullptr };
    first->next = temp;
    first->prev = temp;
    temp->next = nullptr;
    temp->prev = nullptr;
    return;
  }
  Car* temp = new Car{ light, nullptr, nullptr };
  first->prev->next = temp;
  temp->prev = first->prev;
  first->prev = temp;
  temp->next = first;
  first = temp;
}
int Train::getLength() {
  countOp = 0;
  Car* temp;
  while (true) {
    temp = first;
    uint32_t count = 1;
    if (temp->light == false) {
      temp->light = true;
    }
    temp = temp->next;
    countOp += 2;
    while (temp->light == false) {
      temp = temp->next;
      countOp += 2;
      count++;
    }
    temp->light = false;
    if (first->light == false) {
      return count;
    }
  }
}

int Train::getOpCount() {
  return countOp;
}
