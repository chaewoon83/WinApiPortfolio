#pragma once
#include <GameEngine/GameEngineActor.h>
// Ό³Έν :
class Map1FRoof : public GameEngineActor
{
public:
	// constrcuter destructer
	Map1FRoof();
	~Map1FRoof();

	// delete Function
	Map1FRoof(const Map1FRoof& _Other) = delete;
	Map1FRoof(Map1FRoof&& _Other) noexcept = delete;
	Map1FRoof& operator=(const Map1FRoof& _Other) = delete;
	Map1FRoof& operator=(Map1FRoof&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	void Render() override;
private:

};

