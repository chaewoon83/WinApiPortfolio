#pragma once

// Ό³Έν :
class TitileBackGround
{
public:
	// constrcuter destructer
	TitileBackGround();
	~TitileBackGround();

	// delete Function
	TitileBackGround(const TitileBackGround& _Other) = delete;
	TitileBackGround(TitileBackGround&& _Other) noexcept = delete;
	TitileBackGround& operator=(const TitileBackGround& _Other) = delete;
	TitileBackGround& operator=(TitileBackGround&& _Other) noexcept = delete;

protected:

private:

};

