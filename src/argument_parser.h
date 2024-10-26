/**
 *
 * @file argument_paraser.cpp
 *
 * @brief for parsing command line arguments
 *
 * @ingroup image-store
 *
 * @author Euan Williams
 *
*/
#pragma once

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

class Arguments {
  public:
    std::string mode;
};

// Parses a single arg
std::string parse_arg(std::vector<std::string> raw_args, std::string key) {
    auto index = find(raw_args.begin(), raw_args.end(), key);
    int arg_position = std::distance(raw_args.begin(), index);

    std::string value = raw_args[arg_position + 1];

    if (index == raw_args.end()) {
      std::cout << "Not found." << std::endl;
    }
    else {
      std::cout << " - Found argument '" << key << "' value: '" << value << "'" << std::endl;
    }
    return value;
}

Arguments parse_args(int argc, char* argv[]) {
    std::cout << "Parsing args..." << std::endl;

    // Convert argv to a vector of strings for easier handling
    std::vector<std::string> args(argv, argv + argc);

    Arguments parsed_args;

    parsed_args.mode = parse_arg(args, "--mode");
    return parsed_args;
};

