#include "Zelda.h"
#include "PlayLevel.h"
#include "EndLevel.h"
#include "TitleLevel.h"

Zelda::Zelda()
{
}

Zelda::~Zelda()
{
}

void Zelda::GameInit()
{
	CreateLevel<TitleLevel>("Title");
	CreateLevel<PlayLevel>("Play");
	CreateLevel<EndLevel>("End");
}
void Zelda::GameLoop()
{

}
void Zelda::GameEnd()
{

}