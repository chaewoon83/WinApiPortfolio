#include "GameEngineLevel.h"
//delete (*StartActor)�� �ϱ����� (�ҿ����� ���� ������ ���ֱ� ���Ͽ�)
#include "GameEngineActor.h"

GameEngineLevel::GameEngineLevel() 
{
}  



GameEngineLevel::~GameEngineLevel() 
{
	std::map<int, std::list<GameEngineActor*>>::iterator GroupStart = AllActor_.begin();
	std::map<int, std::list<GameEngineActor*>>::iterator GroupEnd = AllActor_.end();
	std::list<GameEngineActor*>::iterator StartActor;
	std::list<GameEngineActor*>::iterator EndActor;

	for (; GroupStart != GroupEnd; ++GroupStart)
	{
		std::list<GameEngineActor*>& Group = GroupStart->second;

		StartActor = Group.begin();
		EndActor = Group.end();

		for (; StartActor != EndActor; ++StartActor)
		{
			if ((*StartActor) == nullptr)
			{
				continue;
			}
			delete (*StartActor);
			(*StartActor) = nullptr;
		}
	}
}

void GameEngineLevel::ActorUpdate()
{
	std::map<int, std::list<GameEngineActor*>>::iterator GroupStart = AllActor_.begin();
	std::map<int, std::list<GameEngineActor*>>::iterator GroupEnd = AllActor_.end();
	std::list<GameEngineActor*>::iterator StartActor;
	std::list<GameEngineActor*>::iterator EndActor;


	for (; GroupStart != GroupEnd; ++GroupStart)
	{
		std::list<GameEngineActor*>& Group = GroupStart->second;

		StartActor = Group.begin();
		EndActor = Group.end();

		for (; StartActor != EndActor; ++StartActor)
		{
			(*StartActor)->ReleaseUpdate();
			if (false == (*StartActor)->IsUpdate())
			{
				continue;
			}
			(*StartActor)->Update();
		}
	}
}
void GameEngineLevel::ActorRender()
{
	std::map<int, std::list<GameEngineActor*>>::iterator GroupStart = AllActor_.begin();
	std::map<int, std::list<GameEngineActor*>>::iterator GroupEnd = AllActor_.end();
	std::list<GameEngineActor*>::iterator StartActor;
	std::list<GameEngineActor*>::iterator EndActor;


	for (; GroupStart != GroupEnd; ++GroupStart)
	{
		std::list<GameEngineActor*>& Group = GroupStart->second;

		//Renderer�� ȣ��ȴ�
		StartActor = Group.begin();
		EndActor = Group.end();

		for (; StartActor != EndActor; ++StartActor)
		{
			if (false == (*StartActor)->IsUpdate())
			{
				continue;
			}
			(*StartActor)->Rendering();
		}
		//Actor �������� Render()�Լ��� ȣ��ȴ�
		StartActor = Group.begin();
		EndActor = Group.end();

		for (; StartActor != EndActor; ++StartActor)
		{
			(*StartActor)->Render();
		}
	}
}
void GameEngineLevel::ActorRelease()
{
	std::map<int, std::list<GameEngineActor*>>::iterator GroupStart = AllActor_.begin();
	std::map<int, std::list<GameEngineActor*>>::iterator GroupEnd = AllActor_.end();
	std::list<GameEngineActor*>::iterator StartActor;
	std::list<GameEngineActor*>::iterator EndActor;


	for (; GroupStart != GroupEnd; ++GroupStart)
	{
		std::list<GameEngineActor*>& Group = GroupStart->second;

		//IsDeath�� Ȯ���� true�� delete�Ѵ�
		StartActor = Group.begin();
		EndActor = Group.end();

		for (; StartActor != EndActor;)
		{
			if (true == (*StartActor)->IsDeath())
			{
				delete (* StartActor);
				StartActor = Group.erase(StartActor);
				continue;
			}
			// ���� List.erase(iteratorValue)�� �ϰ� �ȴٸ� �ڵ������� ++StartActor���� �������ֱ⶧����
			// StartActor = Group.erase(StartActor); �϶� ++StartActor�� �ϸ�ȵȴ�
			// ���� �ۿ� ���� ++StartActor�� ���ش�
			++StartActor;
		}
	}
}

