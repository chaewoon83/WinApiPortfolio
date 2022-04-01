#pragma once
#include <GameEngine/GameEngineActor.h>
// Ό³Έν :
class EXMap : public GameEngineActor
{
public:
	// constrcuter destructer
	EXMap();
	~EXMap();

	// delete Function
	EXMap(const EXMap& _Other) = delete;
	EXMap(EXMap&& _Other) noexcept = delete;
	EXMap& operator=(const EXMap& _Other) = delete;
	EXMap& operator=(EXMap&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	void Render() override;
private:

};

