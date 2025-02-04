#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <windows.h>

#include "HeaderBMP.h"

#include <windows.h>
#include <vector>

class ImageFile
{
protected: /* data */
	std::vector<uint8_t> data;

public: /* dimension */
	uint64_t width = 0;
	uint64_t height = 0;

public: /* constructor */
	ImageFile() = default;
	~ImageFile() = default;

protected: /* extension */
	static std::string path(const std::string& _fname);
	static std::string name(const std::string& _fname);
	static std::string extension(const std::string& _fname);

public: /* bitmap display */
	bool render(HINSTANCE _winst, int _ncmds);

public: /* raw file */
	bool load(const std::string& _fname);
	bool save(const std::string& _fname);

public: /* compressed file */
	virtual bool load_comp(const std::string& _fname);
	virtual bool save_comp(const std::string& _fname);
};