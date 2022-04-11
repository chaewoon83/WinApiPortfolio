#include "GameEnginePath.h"

GameEnginePath::GameEnginePath() 
{
}

GameEnginePath::GameEnginePath(const std::filesystem::path& _Path)
	:Path_(_Path)
{

}

GameEnginePath::~GameEnginePath() 
{
}

//���� ���� ã��
void GameEnginePath::SetCurrentPath()
{
	Path_ = std::filesystem::current_path();
}

//�� ��ΰ� �����ϴ� ������� Ȯ��
bool GameEnginePath::IsExits()
{
	return std::filesystem::exists(Path_);
}

//Ȯ���� ������ (Ȯ���ڰ� ���� ���ɼ��� �ִ�. Ȯ���ڰ� ��� ���丮�� �� �ֵ�)
std::string GameEnginePath::GetExtension()
{
	return Path_.extension().string();
}

std::string GameEnginePath::GetFileName()
{
	return Path_.filename().string();
} 

std::string GameEnginePath::GetFullPath()
{
	return Path_.string();
}