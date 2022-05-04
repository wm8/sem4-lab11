//Copyright 2022 wm8
#include <vector>
#include "Utils.h"
bool ParseArgs(Data* data, int argc, char **argv) {
  po::options_description desc("Allowed options:");
  desc.add_options()("config", po::value<std::string>(),
                     "указать конфигурацию сборки (по умолчанию Debug)")(
      "install", "добавить этап установки (в директорию _install)")(
      "pack", "добавить этап упаковки (в архив формата tar.gz)")(
      "timeout", po::value<unsigned int>(),
      "указывать время ожидания (в секундах)")
      ("help", "Показать описание");
  po::positional_options_description positionalDescription;
  positionalDescription.add("input", -1);
  po::variables_map map;
  try {
    po::store(po::command_line_parser(argc, argv)
                  .options(desc)
                  .positional(positionalDescription)
                  .run(),
              map);
    po::store(po::parse_command_line(argc, argv, desc), map);
    po::notify(map);
    if (map.count("help")) {
      std::cout << "Usage: options_description [options]\n";
      std::cout << desc;
      return false;
    }
    if (map.count("install")) data->install = true;
    if (map.count("pack")) data->pack = true;
    if (map.count("config")) {
      auto config = map["config"].as<std::string>();
      if (config == "Release")
        config = "Release";
      else
        config = "Debug";
    }
    return true;
  } catch (std::exception& ex) {
    std::cerr << ex.what() << std::endl;
  }
  return false;
}
bool runCommand(std::vector<string>& args) {
  boost::system::error_code ec;
  bp::child c = bp::execute(
      bpi::set_on_error(ec),
      bpi::set_args(args));
  auto ex_code = bp::wait_for_exit(c);
  /*if(ex_code) {
    //std::cout << ec.message() << std::endl;
    return false;
  }*/
  return ex_code == 0;
}
void run([[maybe_unused]]  Data * data) {
  data->cmake_path = bp::search_path("cmake");
  if (!data->timeout)
    std::this_thread::sleep_for(std::chrono::seconds(data->timeout));
  std::vector<string> args = {data->cmake_path, "-H.", "-B_builds",
                              "-DCMAKE_INSTALL_PREFIX=_install",
                              "-DCMAKE_BUILD_TYPE=" + data->config};
  if (!runCommand(args)) return;
  args.clear();
  args = {data->cmake_path, "-build", "_builds"};
  if (!runCommand(args)) return;
  if (data->install) {
    args.clear();
    args = {data->cmake_path, "-build", "_builds", "--target", "install"};
    if (!runCommand(args)) return;
  }
  if (data->pack) {
    args.clear();
    args = {data->cmake_path, "-build", "_builds", "--target", "package"};
    if (!runCommand(args)) return;
  }
}

