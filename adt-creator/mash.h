#ifndef __MASH
#define __MASH

#include <string>

#include "list.h"
#include "zoneGroup.h"

int mash(list<ZoneGroup> zoneGroupList, std::string outputName, bool, bool, int zOffset=0, int wdtXOffset=0, int wdtYOffset=0, int wdtZOffset=0);

#endif
