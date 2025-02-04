#pragma once
#include "BMP.h"

class RLE : public BMP
{
protected: /* data */
	std::vector<uint8_t> comp;

public: /* compression */
	virtual bool decode(const std::string& _fname);
	virtual bool encode(const std::string& _fname);
};