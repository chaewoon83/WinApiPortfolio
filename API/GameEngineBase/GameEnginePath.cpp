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

//현재 폴더 찾기
void GameEnginePath::SetCurrentPath()
{
	Path_ = std::filesystem::current_path();
}

//이 경로가 존재하는 경로인지 확인
bool GameEnginePath::IsExits()
{
	return std::filesystem::exists(Path_);
}

//확장자 떼오기 (확장자가 없을 가능성도 있다. 확장자가 없어도 디렉토리일 수 있따)
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