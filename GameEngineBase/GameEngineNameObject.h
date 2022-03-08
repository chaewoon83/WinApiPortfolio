#pragma once
#include <string>

// Ό³Έν :
class GameEngineNameObject
{
public:
	// constrcuter destructer
	GameEngineNameObject();
	~GameEngineNameObject();

	// delete Function
	GameEngineNameObject(const GameEngineNameObject& _Other) = delete;
	GameEngineNameObject(GameEngineNameObject&& _Other) noexcept = delete;
	GameEngineNameObject& operator=(const GameEngineNameObject& _Other) = delete;
	GameEngineNameObject& operator=(GameEngineNameObject&& _Other) noexcept = delete;

protected:
	inline void SetName(const std::string& _Name)
	{
		Name_ = _Name;
	}


	std::string GetNameCopy()
	{
		return Name_;
	}

	std::string& GetNameRef()
	{
		return Name_;
	}

	const char* GetNameConstPtr()
	{
		return Name_.c_str();
	}
private:
	std::string Name_;
};

