#pragma once
#include "BMP.h"

class PNG : public BMP
{
public: /* compression */
	virtual bool decode(const std::string& _fname);
	virtual bool encode(const std::string& _fname);
};