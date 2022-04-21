#pragma once

// Ό³Έν :
class EnemyManager
{
public:
	// constrcuter destructer
	EnemyManager();
	~EnemyManager();

	// delete Function
	EnemyManager(const EnemyManager& _Other) = delete;
	EnemyManager(EnemyManager&& _Other) noexcept = delete;
	EnemyManager& operator=(const EnemyManager& _Other) = delete;
	EnemyManager& operator=(EnemyManager&& _Other) noexcept = delete;

protected:

private:

};

