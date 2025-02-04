#include "ImageFile.h"

static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg) 
    {

    case WM_CLOSE:
    {
        DestroyWindow(hwnd);
        break;
    }

    case WM_DESTROY:
    {
        PostQuitMessage(0);
        break;
    }

    default: return DefWindowProc(hwnd, msg, wParam, lParam);

    }

    return 0;
}

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
    WNDCLASS wndc = { 0 };
    wndc.lpfnWndProc = WndProc;
    wndc.hInstance = hInstance;
    wndc.lpszClassName = L"DefaultWindow";
    RegisterClass(&wndc);

    ImageFile image;
    image.load("x64/test1.bmp");
    image.render(hInstance, nShowCmd);

    image.load("x64/test2.bmp");
    image.render(hInstance, nShowCmd);

    return 0;
}