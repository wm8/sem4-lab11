//
// Created by Алекс on 29.04.2022.
//

#ifndef TEMPLATE_UTILS_H
#define TEMPLATE_UTILS_H
#include <exception>
#include <iostream>
#include <string>
#include <vector>
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
void run(Data* data);
#endif  // TEMPLATE_UTILS_H
