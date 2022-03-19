#pragma once
#include <GameEngine/GameEngineActor.h>
// Ό³Έν :
class ItemMagicJar_Large_ : public GameEngineActor
{
public:
	// constrcuter destructer
	ItemMagicJar_Large_();
	~ItemMagicJar_Large_();

	// delete Function
	ItemMagicJar_Large_(const ItemMagicJar_Large_& _Other) = delete;
	ItemMagicJar_Large_(ItemMagicJar_Large_&& _Other) noexcept = delete;
	ItemMagicJar_Large_& operator=(const ItemMagicJar_Large_& _Other) = delete;
	ItemMagicJar_Large_& operator=(ItemMagicJar_Large_&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	void Render() override;
private:

};

