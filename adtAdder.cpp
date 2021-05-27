#include "adtAdder.h"

#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

void writeAdt(std::string sourceFile, std::string dstDir, std::string dstName, int minAdtX, int minAdtY, int maxAdtX, int maxAdtY, ZoneGroup & group)
{
	std::cout << "Reading ADT offsets\n";
	std::ifstream file(sourceFile, std::ios::out | std::ios::binary);

	uint32_t c = 12;
	file.seekg(c);

	while (true)
	{
		char hdr[5];
		hdr[4] = '\0';
		file.read(hdr, sizeof(char) * 4);
		if (std::string(hdr) == "KNCM") {
			file.seekg(c);
			break;
		}
		uint32_t size;
		file.read(reinterpret_cast<char*>(&size), sizeof(uint32_t));
		c += size+8;
		file.seekg(c);
	}

	// Collect offset offsets
	uint32_t offsets[256];
	for (unsigned i = 0; i < 256; ++i)
	{
		file.seekg(c);
		unsigned row = i / 16;
		unsigned col = i % 16;

		char hdr[5];
		hdr[4] = '\0';
		file.read(hdr, sizeof(char) * 4);
		if (std::string(hdr) != "KNCM") 
		{
			std::cout << "Invalid chunk header: " << hdr << "\n";
			exit(1);
		}
		uint32_t size;
		file.read(reinterpret_cast<char*>(&size), sizeof(uint32_t));
		offsets[i] = c + 112;
		c += size + 8;
	}
	file.close();

	std::filesystem::create_directories(dstDir);

	std::cout << "Writing ADT files\n";

	for (int x = minAdtX; x <= maxAdtX; ++x)
	{
		for (int y = minAdtY; y <= maxAdtY; ++y)
		{
			auto dstFile = dstName + "_" + std::to_string(x) + "_" + std::to_string(y) + ".adt";
			auto dstPath = (std::filesystem::path(dstDir) / dstFile).string();
			std::filesystem::copy_file(sourceFile, dstPath, std::filesystem::copy_options::overwrite_existing);
			group.append(dstFile,dstPath);

			std::ofstream out = std::ofstream(dstPath, std::ios::in | std::ios::out | std::ios::binary);
			for (unsigned i = 0; i < 256; ++i)
			{
				out.seekp(offsets[i]);
				float offX = 17066.7 - (x * 533.33333) - ((i/16)*33.33333);
				float offY = 17066.7 - (y * 533.33333) - ((i%16)*33.33333);
				out.write(reinterpret_cast<char*>(&offX), sizeof(float));
				out.write(reinterpret_cast<char*>(&offY), sizeof(float));
			}
			out.close();
		}
	}
}