#include <Windows.h>

#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineDebug.h>

void GameInit()
{
    //�ؽ�ó�� �ε��ϰ� �غ� �ϰ�
    // ������Ʈ�� �̸� ��������
}
void GameLoop()
{
    Rectangle(GameEngineWindow::GetInst().GETHDC(), 100, 100, 200, 200);
    // �׸� �׸���
}
int __stdcall WinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ char*   lpCmdLine,
    _In_ int       nCmdShow)
{
    GameEngineDebug::LeakCheckOn();
    GameEngineWindow::GetInst().CreateGameWindow(hInstance, "GameWindow");
    GameEngineWindow::GetInst().ShowGameWindow();
    GameEngineWindow::GetInst().MessageLoop(GameInit, GameLoop);
    GameEngineWindow::Destroy();

}