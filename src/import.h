/**
 *
 * @file import.cpp
 *
 * @brief for importing images to the database
 *
 * @ingroup image-store
 *
 * @author Euan Williams
 *
*/
#pragma once

#include <iostream>

#include "database.h"

class ImageImporter {
  DatabaseInterface database;
  
  public:
    ImageImporter(const std::string& database_file)
        : database(database_file) // Correctly initialize 'database'
    {
        // Other initialization code, if needed
    }
};

