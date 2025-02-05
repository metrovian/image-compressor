#include "RLE.h"

static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg) 
    {

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

    RLE ori;
    ori.load("x64/test3.bmp");
    if (!ori.encode("x64/test3.rle"))
    {
        MessageBox(NULL, L"Encode Failed : Increased Result", L"RLE Compression", FALSE);
    }

    RLE rle;
    rle.decode("x64/test3.rle");
    rle.save("x64/test3_decode.bmp");
    rle.render(hInstance, nShowCmd);

    return 0;
}