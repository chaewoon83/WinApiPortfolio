#pragma once
#include <GameEngine/GameEngineActor.h>
// Ό³Έν :
class ItemMagicJar_Small_ : public GameEngineActor
{
public:
	// constrcuter destructer
	ItemMagicJar_Small_();
	~ItemMagicJar_Small_();

	// delete Function
	ItemMagicJar_Small_(const ItemMagicJar_Small_& _Other) = delete;
	ItemMagicJar_Small_(ItemMagicJar_Small_&& _Other) noexcept = delete;
	ItemMagicJar_Small_& operator=(const ItemMagicJar_Small_& _Other) = delete;
	ItemMagicJar_Small_& operator=(ItemMagicJar_Small_&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	void Render() override;
private:

};

