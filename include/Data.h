//Copyright 2022 wm8

#ifndef TEMPLATE_DATA_H
#define TEMPLATE_DATA_H
#include <string>
struct Data {
  bool install;
  bool pack;
  std::string config;
  unsigned int timeout;
  std::string cmake_path;
};
#endif  // TEMPLATE_DATA_H
