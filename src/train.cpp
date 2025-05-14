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
  Car* temp = new Car{ light, nullptr, nullptr };
  if (!first) {
    temp->next = temp;
    temp->prev = temp;
    first = temp;
  } else {
    temp->next = first;
    temp->prev = first->prev;
    first->prev->next = temp;
    first->prev = temp;
  }
}
int Train::getLength() {
  countOp = 0;
  Car* temp;
  while (true) {
    temp = first;
    uint16_t count = 1;
    if (!temp->light) {
        temp->light = true;
    }
    temp = temp->next;
    countOp += 2;
    while (!temp->light) {
      temp = temp->next;
      countOp += 2;
      count++;
    }
    temp->light = false;
    if (!first->light) {
      return count;
    }
  }
}

int Train::getOpCount() {
  return countOp;
}
