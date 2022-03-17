#pragma once

// Ό³Έν :
class Link
{
public:
	// constrcuter destructer
	Link();
	~Link();

	// delete Function
	Link(const Link& _Other) = delete;
	Link(Link&& _Other) noexcept = delete;
	Link& operator=(const Link& _Other) = delete;
	Link& operator=(Link&& _Other) noexcept = delete;

protected:

private:

};

