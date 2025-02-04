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
	std::string extension(const std::string& _fname);

public: /* file */
	bool load(const std::string& _fname);
	bool save(const std::string& _fname);

public: /* viewer */
	bool render(HINSTANCE _winst, int _ncmds);

public: /* virtual */
	virtual bool load_bmp(const std::string& _fname);
	virtual bool load_png(const std::string& _fname);
	virtual bool load_webp(const std::string& _fname);

public: /* virtual */
	virtual bool save_bmp(const std::string& _fname);
	virtual bool save_png(const std::string& _fname);
	virtual bool save_webp(const std::string& _fname);
};