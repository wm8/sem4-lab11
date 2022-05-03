//Copyright 2022 wm8

#ifndef TEMPLATE_UTILS_H
#define TEMPLATE_UTILS_H
#include <exception>
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include <unistd.h>
#include <boost/program_options.hpp>
#include <boost/process/initializers.hpp>
#include <boost/process.hpp>
#include <boost/filesystem.hpp>
#include "Data.h"
using std::string;
namespace po = boost::program_options;
namespace bp = boost::process;
namespace bpi = boost::process::initializers;
using std::string;
using std::exception;
bool ParseArgs(Data* data, int argc, char **argv);
bool runCommand(std::vector<string>& args);
void run(Data* data);
#endif  // TEMPLATE_UTILS_H
