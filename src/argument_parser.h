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
#include <optional>
#include <assert.h>

class Arguments {
  public:
    std::string mode;

    // Required for import mode
    std::optional<std::string> directory;
};

// Parses a single arg
std::optional<std::string> parse_arg(std::vector<std::string> raw_args, std::string key, bool allow_null) {
    auto index = find(raw_args.begin(), raw_args.end(), key);

    // Get the value associated with the key
    int arg_position = std::distance(raw_args.begin(), index);
    if (arg_position + 1 >= raw_args.size()) {
        if (allow_null) {
          return std::nullopt;
        }
        throw std::out_of_range("No value provided for key: " + key);  // Prevent out-of-bounds access
    }

    std::string value = raw_args[arg_position + 1];
    std::cout << " - Found argument '" << key << "' value: '" << value << "'" << std::endl;
    return value;
};

// Parses cli arguments, returns them as an argument object.
Arguments parse_args(int argc, char* argv[]) {
    std::cout << "\nParsing args..." << std::endl;

    // Convert argv to a vector of strings for easier handling
    std::vector<std::string> args(argv, argv + argc);

    Arguments parsed_args;
    parsed_args.mode = parse_arg(args, "--mode", false).value();
    parsed_args.directory = parse_arg(args, "--directory", true);

    std::cout << "\n" << std::endl;
    return parsed_args;
};

