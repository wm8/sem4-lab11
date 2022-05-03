//Copyright 2022 wm8

#include "Utils.h"
int main(int argc, char** argv) {
  Data* d = new Data();
  if(!ParseArgs(d, argc, argv))
    return -1;
  run(d);
}