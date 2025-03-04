#pragma once
#pragma pack(push, 1)
struct HeaderYUV
{
    uint16_t type = 0x5559;
    uint32_t fsi;
    uint32_t ofs = 0x001B;
    int32_t width;
    int32_t height;
    uint16_t depth = 0x0018;
    uint32_t dsi;
    uint8_t qdy = 0x04;
    uint8_t qdb = 0x02;
    uint8_t qdr = 0x02;
};
#pragma pack(pop)