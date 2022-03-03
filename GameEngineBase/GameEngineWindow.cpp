#include "GameEngineWindow.h"

GameEngineWindow* GameEngineWindow::Inst_ = new GameEngineWindow();

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    return DefWindowProc(hWnd, message, wParam, lParam);
}

GameEngineWindow::GameEngineWindow() 
{
}

GameEngineWindow::~GameEngineWindow() 
{
}

void GameEngineWindow::CreateGameWindow(HINSTANCE _hInst)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = _hInst;
    wcex.hIcon = nullptr;
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = L"GameEngineWindowClass";
    wcex.hIconSm = nullptr;

    RegisterClassExW(&wcex);

    hWnd_ = CreateWindowW(L"GameEngineWindowClass", L"packman", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, _hInst, nullptr);
    //WS_OVERLAPPEDWINDOW => �������� ����(�޴��� ���µ�
    //CW_USEDEFAULT â�� ũ�����ϱ�
    if (!hWnd_)
    {
        return;
    }
}

void GameEngineWindow::ShowGameWindow()
{
    ShowWindow(hWnd_, SW_SHOW);
    //hWnd�� �ԷµǴ� ���� => Ư�� �����츦 ��󳻱� ���Ͽ�
    UpdateWindow(hWnd_);
}