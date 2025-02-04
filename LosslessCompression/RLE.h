#pragma once
#include "ImageFile.h"

class RLE : public ImageFile
{
protected: /* data */
	std::vector<uint8_t> comp;

public: /* compression */
	virtual bool decode(const std::string& _fname);
	virtual bool encode(const std::string& _fname);
};