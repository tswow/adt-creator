/***************************************************************
 * Name:      wxTestMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Ryan Cornwall ()
 * Created:   2010-07-15
 * Copyright: Ryan Cornwall ()
 * License:
 **************************************************************/

#include <string>

#include "list.h" //Makes my life so much easier
#include "mash.h"
#include "adtAdder.h"

#include <filesystem>

std::string usage = "Usage: adtcreator input_adt output_directory output_name min_x min_y max_x max_y\n";

int main(int argc, char** argv)
{
  if (argc < 8)
  {
    std::cout << "Invalid argument count: " << argc << "\n";
    std::cout << usage;
    exit(1);
  }

  std::string input_adt = std::string(argv[1]);

  if(!std::filesystem::exists(input_adt))
  {
    std::cout << "Missing input adt: " << input_adt << "\n";
    exit(1);
  }

  std::string output_dir = std::string(argv[2]);
  std::string output_name = std::string(argv[3]);

  int min_x;
  int min_y;
  int max_x;
  int max_y;

  try {
    min_x = std::stoi(argv[4]);
    min_y = std::stoi(argv[5]);
    max_x = std::stoi(argv[6]);
    max_y = std::stoi(argv[7]);
  }
  catch (std::exception e)
  {
    std::cout << "Invalid number format\n";
    std::cout << usage;
    exit(1);
  }

  ZoneGroup group;
  writeAdt(input_adt, output_dir, output_name, min_x, min_y, max_x, max_y);
  for (auto const& dir_entry : std::filesystem::directory_iterator{ std::filesystem::path(output_dir) })
  {
    group.append(dir_entry.path().filename().string(), dir_entry.path().string());
  }

  std::filesystem::current_path(output_dir);

  list<ZoneGroup> zoneGroupList;
  zoneGroupList.pushBack(group);

  mash(zoneGroupList, output_name, true, true, 0, 0, 0, 0);
}
