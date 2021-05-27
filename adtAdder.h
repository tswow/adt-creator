#ifndef _ADTADDER
#define _ADTADDER

#include <string>

#include "zoneGroup.h"

void writeAdt(std::string sourceFile, std::string outDir, std::string outName, int minAdtX, int minAdtY, int maxAdtX, int maxAdtY, ZoneGroup & group);
#endif
