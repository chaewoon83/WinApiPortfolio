#pragma once
#include <GameEngine/GameEngineActor.h>
// Ό³Έν :
class Map1F : public GameEngineActor
{
public:
	// constrcuter destructer
	Map1F();
	~Map1F();

	// delete Function
	Map1F(const Map1F& _Other) = delete;
	Map1F(Map1F&& _Other) noexcept = delete;
	Map1F& operator=(const Map1F& _Other) = delete;
	Map1F& operator=(Map1F&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	void Render() override;
private:

};

