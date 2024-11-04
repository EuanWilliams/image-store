// 
// Euan Williams: 01/11/2024
//
// Encapsulates data about an image
//
#pragma once

#include <iostream>

class Image {
  public:
    int id;
    std::string filepath;
    int import_date;
    std::string import_source;
    std::string import_metadata;
};

easyexif::EXIFInfo parse_jpeg_exif(unsigned char *buffer, unsigned long fsize) {
  // Parse EXIF
  easyexif::EXIFInfo result;
  int code = result.parseFrom(buffer, fsize);
  delete[] buffer;
  if (code) {
    printf("Error parsing EXIF: code %d\n", code);
  }
  return result;
};

void output_exif_results(easyexif::EXIFInfo result) {
  // Dump EXIF information
  printf("Camera make          : %s\n", result.Make.c_str());
  printf("Camera model         : %s\n", result.Model.c_str());
  printf("Software             : %s\n", result.Software.c_str());
  printf("Bits per sample      : %d\n", result.BitsPerSample);
  printf("Image width          : %d\n", result.ImageWidth);
  printf("Image height         : %d\n", result.ImageHeight);
  printf("Image description    : %s\n", result.ImageDescription.c_str());
  printf("Image orientation    : %d\n", result.Orientation);
  printf("Image copyright      : %s\n", result.Copyright.c_str());
  printf("Image date/time      : %s\n", result.DateTime.c_str());
  printf("Original date/time   : %s\n", result.DateTimeOriginal.c_str());
  printf("Digitize date/time   : %s\n", result.DateTimeDigitized.c_str());
  printf("Subsecond time       : %s\n", result.SubSecTimeOriginal.c_str());
  printf("Exposure time        : 1/%d s\n",
        (unsigned)(1.0 / result.ExposureTime));
  printf("F-stop               : f/%.1f\n", result.FNumber);
  printf("Exposure program     : %d\n", result.ExposureProgram);
  printf("ISO speed            : %d\n", result.ISOSpeedRatings);
  printf("Subject distance     : %f m\n", result.SubjectDistance);
  printf("Exposure bias        : %f EV\n", result.ExposureBiasValue);
  printf("Flash used?          : %d\n", result.Flash);
  printf("Flash returned light : %d\n", result.FlashReturnedLight);
  printf("Flash mode           : %d\n", result.FlashMode);
  printf("Metering mode        : %d\n", result.MeteringMode);
  printf("Lens focal length    : %f mm\n", result.FocalLength);
  printf("35mm focal length    : %u mm\n", result.FocalLengthIn35mm);
  printf("GPS Latitude         : %f deg (%f deg, %f min, %f sec %c)\n",
        result.GeoLocation.Latitude, result.GeoLocation.LatComponents.degrees,
        result.GeoLocation.LatComponents.minutes,
        result.GeoLocation.LatComponents.seconds,
        result.GeoLocation.LatComponents.direction);
  printf("GPS Longitude        : %f deg (%f deg, %f min, %f sec %c)\n",
        result.GeoLocation.Longitude, result.GeoLocation.LonComponents.degrees,
        result.GeoLocation.LonComponents.minutes,
        result.GeoLocation.LonComponents.seconds,
        result.GeoLocation.LonComponents.direction);
  printf("GPS Altitude         : %f m\n", result.GeoLocation.Altitude);
  printf("GPS Precision (DOP)  : %f\n", result.GeoLocation.DOP);
  printf("Lens min focal length: %f mm\n", result.LensInfo.FocalLengthMin);
  printf("Lens max focal length: %f mm\n", result.LensInfo.FocalLengthMax);
  printf("Lens f-stop min      : f/%.1f\n", result.LensInfo.FStopMin);
  printf("Lens f-stop max      : f/%.1f\n", result.LensInfo.FStopMax);
  printf("Lens make            : %s\n", result.LensInfo.Make.c_str());
  printf("Lens model           : %s\n", result.LensInfo.Model.c_str());
  printf("Focal plane XRes     : %f\n", result.LensInfo.FocalPlaneXResolution);
  printf("Focal plane YRes     : %f\n", result.LensInfo.FocalPlaneYResolution);
};

// Reads a JPEG into a buffer
// TODO: This return type is wrong
int read_image(std::string image_path) {
  // Open file to file pointer "*fp"
  FILE *fp = std::fopen(image_path.c_str(), "rb");
  if (!fp) {
    printf("Can't open file.\n");
    return -1;
  }
 
  // Check size of open file by moving pointer to end of file, and using ftell to find the location of the pointer. Finally move the pointer back to the start
  // of the file.
  fseek(fp, 0, SEEK_END);
  unsigned long fsize = ftell(fp);
  rewind(fp);
 
  // Create a new buffer, *buf, using the size we just found, use fread to read the image into the buffer.
  unsigned char *buf = new unsigned char[fsize];
  if (fread(buf, 1, fsize, fp) != fsize) {
    printf("Can't read file.\n");
    delete[] buf;
    return -2;
  }
  fclose(fp);
};
