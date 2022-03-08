#include "GameEngineWindow.h"
#include "GameEngineDebug.h"

GameEngineWindow* GameEngineWindow::Inst_ = new GameEngineWindow();

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case(WM_DESTROY):
        //창이 꺼질때(프로그램이 아닌 창)
        GameEngineWindow::GetInst().Off();
        return DefWindowProc(hWnd, message, wParam, lParam);
    case WM_PAINT:
    {
        //윈도우 화면에 뭔가가 그려질때
        //HDC 화면에 뭔갈 그릴 수 있는 권한
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        EndPaint(hWnd, &ps);
        return DefWindowProc(hWnd, message, wParam, lParam);
        break;
    }
    default:
        break;
    }
    return DefWindowProc(hWnd, message, wParam, lParam);
}

GameEngineWindow::GameEngineWindow()
    :hInst_(nullptr)
    , hWnd_(nullptr)
    , WindowOn_(true)
    , HDC_(nullptr)
{
}

GameEngineWindow::~GameEngineWindow() 
{
}

void GameEngineWindow::Off()
{
    WindowOn_ = false;
}

void GameEngineWindow::RegClass(HINSTANCE _hInst)
{
    WNDCLASSEXA wcex;

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
    wcex.lpszClassName = "GameEngineWindowClass";
    wcex.hIconSm = nullptr;

    RegisterClassExA(&wcex);
}

void GameEngineWindow::CreateGameWindow(HINSTANCE _hInst, const std::string _Title)
{
    if (nullptr != hInst_)
    {
        MsgBoxAssert("윈도우를 두번 띄우려고 했습니다");
        return;
    }
    hInst_ = _hInst;
    Title_ = _Title;
    RegClass(_hInst);

    hWnd_ = CreateWindowA("GameEngineWindowClass", Title_.c_str() , WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, _hInst, nullptr);
    //WS_OVERLAPPEDWINDOW => 윈도우의 형식(메뉴의 유뮤등
    //CW_USEDEFAULT 창의 크기정하기

    //화면에 뭔갈 그리기 위한 핸들
    //화면에 윈도우가 한번 띄워져야 그릴 수 있다
    HDC_ = GetDC(hWnd_);

    if (!hWnd_)
    {
        return;
    }
    
}

void GameEngineWindow::ShowGameWindow()
{
    if (nullptr == hWnd_)
    {
        MsgBoxAssert("메인 윈도우가 만들어지지 않았습니다. 화면에 출력할 수 없습니다");
        return;
    }
    ShowWindow(hWnd_, SW_SHOW);
    //hWnd가 입력되는 이유 => 특정 윈도우를 골라내기 위하여
    UpdateWindow(hWnd_);
}

void GameEngineWindow::MessageLoop(void(*_InitFunction)(), void(*_LoopFunction)())
{

    if (nullptr != _InitFunction)
    {
        _InitFunction();
    }
    MSG msg;

    while (WindowOn_)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            DispatchMessageA(&msg);
        }
        if (nullptr == _LoopFunction)
        {
            continue;
        }

        _LoopFunction();
        
    }
}