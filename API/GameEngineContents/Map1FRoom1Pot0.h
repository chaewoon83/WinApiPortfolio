#pragma once
#include <GameEngine/GameEngineActor.h>
// ���� :
class Map1FRoom1Pot0 : public GameEngineActor
{
public:
	// constrcuter destructer
	Map1FRoom1Pot0();
	~Map1FRoom1Pot0();

	// delete Function
	Map1FRoom1Pot0(const Map1FRoom1Pot0& _Other) = delete;
	Map1FRoom1Pot0(Map1FRoom1Pot0&& _Other) noexcept = delete;
	Map1FRoom1Pot0& operator=(const Map1FRoom1Pot0& _Other) = delete;
	Map1FRoom1Pot0& operator=(Map1FRoom1Pot0&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	void Render() override;
private:

};

