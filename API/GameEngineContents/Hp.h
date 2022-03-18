#pragma once

// Ό³Έν :
class Hp
{
public:
	// constrcuter destructer
	Hp();
	~Hp();

	// delete Function
	Hp(const Hp& _Other) = delete;
	Hp(Hp&& _Other) noexcept = delete;
	Hp& operator=(const Hp& _Other) = delete;
	Hp& operator=(Hp&& _Other) noexcept = delete;

protected:

private:

};

