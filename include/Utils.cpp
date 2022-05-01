//
// Created by Алекс on 29.04.2022.
//
#include <vector>
#include "Utils.h"
bool ParseArgs(Data* data, int argc, char **argv) {
  po::options_description desc("Allowed options:");
  desc.add_options()
      ("config", po::value<std::string>(),
                     "указать конфигурацию сборки (по умолчанию Debug)")
      ("install", "добавить этап установки (в директорию _install)")
      ("pack", "добавить этап упаковки (в архив формата tar.gz)")
      ("timeout", po::value<unsigned int>(),"указывать время ожидания (в секундах)")
      ("help", "this message");
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
    if (map.count("help"))
    {
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
  } catch (std::exception& ex)
  {
    std::cerr << ex.what() << std::endl;
  }
  return false;
}

void run([[maybe_unused]]  Data * data) {
  setlocale(LC_CTYPE,"");
  //boost::iostreams::file_descriptor_sink sink("stdout.txt");
  boost::system::error_code ec;
  bp::child c = bp::execute(
      bpi::run_exe("test.exe")
      /*bpi::bind_stdout(sink),
      bpi::close_stdin(),
      bpi::close_stderr()*/

  );
  bp::wait_for_exit(c);
  std::cout << ec.message() << std::endl;
}