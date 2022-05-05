#pragma once
#include <GameEngine/GameEngineActor.h>
// Ό³Έν :
class Room3Block0 : public GameEngineActor
{
public:
	// constrcuter destructer
	Room3Block0();
	~Room3Block0();

	// delete Function
	Room3Block0(const Room3Block0& _Other) = delete;
	Room3Block0(Room3Block0&& _Other) noexcept = delete;
	Room3Block0& operator=(const Room3Block0& _Other) = delete;
	Room3Block0& operator=(Room3Block0&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	void Render() override;
private:
	static Room3Block0* Room3Block_;
public:
	static Room3Block0* GetRoom3Block0()
	{
		return Room3Block_;
	}
};

