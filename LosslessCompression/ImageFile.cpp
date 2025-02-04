#include "ImageFile.h"

std::string ImageFile::extension(const std::string& _fname)
{
    return std::string(std::find(_fname.begin(), _fname.end(), '.') + 1, _fname.end());
}

bool ImageFile::load(const std::string& _fname)
{
    std::string ext = extension(_fname);

    if (ext == "bmp") return load_bmp(_fname);
    if (ext == "png") return load_png(_fname);
    if (ext == "webp") return load_webp(_fname);

    return false;
}

bool ImageFile::save(const std::string& _fname)
{
    std::string ext = extension(_fname);

    if (ext == "bmp") return save_bmp(_fname);
    if (ext == "png") return save_png(_fname);
    if (ext == "webp") return save_webp(_fname);

    return false;
}

bool ImageFile::render(HINSTANCE _winst, int _ncmds)
{
    if (data.empty()) return false;

    HWND hwnd = CreateWindow
    (
        L"DefaultWindow", 
        L"Image Compressor", 
        WS_CAPTION | WS_SYSMENU,
        CW_USEDEFAULT, 
        CW_USEDEFAULT, 
        width, 
        height, 
        NULL, 
        NULL, 
        _winst, 
        NULL
    );

    ShowWindow(hwnd, _ncmds);
    UpdateWindow(hwnd);
    InvalidateRect(hwnd, NULL, TRUE);

    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hwnd, &ps);

    BITMAPINFO bmi = { 0 };
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = width;
    bmi.bmiHeader.biHeight = height;
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 24;
    bmi.bmiHeader.biCompression = BI_RGB;

    SetDIBitsToDevice(hdc, 0, 0, width, height, 0, 0, 0, height, data.data(), &bmi, DIB_RGB_COLORS);
    EndPaint(hwnd, &ps);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return true;
}

bool ImageFile::load_bmp(const std::string& _fname)
{
    HeaderBMP header;
    std::ifstream ifs(_fname, std::ios::binary);

    if (!ifs.is_open()) 
    {
        std::cerr << "Open Error : " << _fname << std::endl;
        return false;
    }

    ifs.read(reinterpret_cast<char*>(&header), sizeof(HeaderBMP));

    if (header.type != 0x4D42)
    {
        std::cerr << "Header Error : " << header.type << std::endl;
        return false;
    }

    if (header.depth != 0x0018)
    {
        std::cerr << "Header Error : " << header.depth << std::endl;
        return false;
    }

    width = header.width;
    height = header.height;

    data.resize(header.dsi);

    ifs.read(reinterpret_cast<char*>(data.data()), header.dsi);
    ifs.close();

    return true;
}

bool ImageFile::load_png(const std::string& _fname)
{
    return false;
}

bool ImageFile::load_webp(const std::string& _fname)
{
    return false;
}

bool ImageFile::save_bmp(const std::string& _fname)
{
    HeaderBMP header;
    std::ofstream ofs(_fname, std::ios::binary);

    if (!ofs.is_open()) 
    {
        std::cerr << "Open Error : " << _fname << std::endl;
        return false;
    }

    header.width = width;
    header.height = height;

    header.fsi = data.size() + 0x0036;
    header.dsi = data.size();

    ofs.write(reinterpret_cast<const char*>(&header), sizeof(header));
    ofs.write(reinterpret_cast<const char*>(data.data()), data.size());
    ofs.close();

    return true;
}

bool ImageFile::save_png(const std::string& _fname)
{
    return false;
}

bool ImageFile::save_webp(const std::string& _fname)
{
    return false;
}
