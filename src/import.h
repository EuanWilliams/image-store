//
// Euan Williams: 03/11/2024
//
// For importing images into the dataset
//
#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <chrono>
#include <ctime> 
#include <vector>

#include "exif.h"
#include "database.h"
#include "image.h"


class ImageToImport {
  public:
    std::string original_filepath;
    std::chrono::time_point<std::chrono::system_clock> import_date = std::chrono::system_clock::now();
    std::string source;

    ImageToImport(std::string filepath, std::string source) {
      this->original_filepath = filepath;
      this->source = source;
    }
};


class ImageImporter {
  public:
    DatabaseInterface database;

    // Constructor that uses the setup_db function
    ImageImporter(const std::string& database_file)
      : database(setup_db(database_file))  // Call setup_db to construct and assign the database
    {
        // Any additional setup logic can go here if needed
    }

    bool import_images(std::vector<ImageToImport> images) {
      for (const ImageToImport image_to_import : images) {
        std::cout << "Importing image: " << image_to_import.original_filepath << std::endl;
        // TODO: Fix this return type
        // this doesnt work!
        
        // std::optional<unsigned char> = read_image(image_to_import.original_filepath);
        // easyexif::EXIFInfo result = parse_jpeg_exif(image, fsize);
        //output_exif_results(result);
      };
    };
};

