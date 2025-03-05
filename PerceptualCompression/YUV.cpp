#include "YUV.h"

std::vector<uint8_t> YUV::transform(const std::vector<uint8_t>& _bmp)
{
    std::vector<uint8_t> ret = _bmp;

    uint64_t pwidth = (width * 3 + 3) & ~3;

    for (uint64_t i = 0; i < width; ++i)
    {
        for (uint64_t j = 0; j < height; ++j)
        {
            uint64_t bmpi = (height - j - 1) * pwidth + i * 3;
            uint64_t yuvi = (j * width + i) * 3;

            uint8_t scb = _bmp[bmpi + 0];
            uint8_t scg = _bmp[bmpi + 1];
            uint8_t scr = _bmp[bmpi + 2];
            
            ret[yuvi + 0] = static_cast<uint8_t>(16 + (0.257 * scr) + (0.504 * scg) + (0.098 * scb));
            ret[yuvi + 1] = static_cast<uint8_t>(128 - (0.148 * scr) - (0.291 * scg) + (0.439 * scb));
            ret[yuvi + 2] = static_cast<uint8_t>(128 + (0.439 * scr) - (0.368 * scg) - (0.071 * scb));
        }
    }

    return ret;
}

std::vector<uint8_t> YUV::inverse(const std::vector<uint8_t>& _yuv)
{
    return std::vector<uint8_t>();
}

bool YUV::decode(const std::string& _fname)
{
    return false;
}

bool YUV::encode(const std::string& _fname)
{
    return false;
}
