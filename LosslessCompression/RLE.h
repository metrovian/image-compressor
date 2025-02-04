#pragma once
#include "ImageFile.h"

class RLE : public ImageFile
{
protected: /* data */
	std::vector<uint8_t> comp;

public: /* compressed file */
	virtual bool load_comp(const std::string& _fname);
	virtual bool save_comp(const std::string& _fname);
};