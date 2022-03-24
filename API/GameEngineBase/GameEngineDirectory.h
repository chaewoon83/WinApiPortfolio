#pragma once
#include "GameEnginePath.h"

// ���� : ���ϰ� ���丮�� ���� �����ϱ� ���� Ŭ����
class GameEngineFile;
class GameEngineDirectory : public GameEnginePath
{
public:
	// constrcuter destructer
	GameEngineDirectory();
	~GameEngineDirectory();

	// delete Function
	GameEngineDirectory(const GameEngineDirectory& _Other) = delete;
	GameEngineDirectory(GameEngineDirectory&& _Other) noexcept = delete;
	GameEngineDirectory& operator=(const GameEngineDirectory& _Other) = delete;
	GameEngineDirectory& operator=(GameEngineDirectory&& _Other) noexcept = delete;

	void MoveParent();

	void MoveParent(const std::string& _Name);
	
	bool IsRoot();

	void Move(const std::string& _Name);

	std::vector<GameEngineFile> GetAllFile(const std::string& _Ext = "");

protected:

private:

};
