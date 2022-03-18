#include "GameEngineWindow.h"
#include "GameEngineDebug.h"

GameEngineWindow* GameEngineWindow::Inst_ = new GameEngineWindow();

LRESULT CALLBACK MessageProcess(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case(WM_DESTROY):
        //â�� ������(���α׷��� �ƴ� â)
        GameEngineWindow::GetInst().Off();
        return DefWindowProc(hWnd, message, wParam, lParam);
    case WM_PAINT:
    {
        //������ ȭ�鿡 ������ �׷�����
        //HDC ȭ�鿡 ���� �׸� �� �ִ� ����
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
    wcex.lpfnWndProc = MessageProcess;
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
        MsgBoxAssert("�����츦 �ι� ������ �߽��ϴ�");
        return;
    }
    hInst_ = _hInst;
    Title_ = _Title;
    RegClass(_hInst);

    hWnd_ = CreateWindowA("GameEngineWindowClass", Title_.c_str() , WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, _hInst, nullptr);
    //WS_OVERLAPPEDWINDOW => �������� ����(�޴��� ���µ�
    //CW_USEDEFAULT â�� ũ�����ϱ�

    //ȭ�鿡 ���� �׸��� ���� �ڵ�
    //ȭ�鿡 �����찡 �ѹ� ������� �׸� �� �ִ�
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
        MsgBoxAssert("���� �����찡 ��������� �ʾҽ��ϴ�. ȭ�鿡 ����� �� �����ϴ�");
        return;
    }
    ShowWindow(hWnd_, SW_SHOW);
    //hWnd�� �ԷµǴ� ���� => Ư�� �����츦 ��󳻱� ���Ͽ�
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
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        if (nullptr == _LoopFunction)
        {
            continue;
        }

        _LoopFunction();
        
    }
}

void GameEngineWindow::SetWindowScaleAndPosition(float4 _Pos, float4 _Scale)
{
    //�޴��ٸ� ������ ������ ũ�⸦ ����ش�
    RECT Rc = {0, 0, _Scale.ix(), _Scale.iy() };
    // �׸��� ũ��, ��Ÿ��, �޴��� ����
    // WS_OVERLAPPEDWINDOW �̰��� �޴����� ��Ÿ���ε� �̰��� �����Ͽ� �˷��ش�
    AdjustWindowRect(&Rc, WS_OVERLAPPEDWINDOW, FALSE);
    Scale_ = _Scale;
    //�׸� ���鶧 ��������, �������� + ũ��� �����
    SetWindowPos(hWnd_, nullptr, _Pos.ix(), _Pos.iy(), Rc.right - Rc.left, Rc.bottom - Rc.top, SWP_NOZORDER);
}