#pragma once

enum class PlayLevelOrder
{
	BACKGROUND,
	MONSTER,
	PLAYER,
	MAPOBJECT,
	BACKGROUNDROOF,
	UILAYOUT,
	UI,
	MAX,
};

enum class TitleOrder
{
	BACKGROUND,
	OBJECTS,
	LOGO,
	TRIANGLES,
	SWORD,
	ZeldaZ,
	TWINKLE,
	MAX,
};

enum class PlayerState
{
	IdleRight,
	IdleLeft,
	IdleUp,
	IdleDown,
	MoveRight,
	MoveLeft,
	MoveUp,
	MoveDown,
	WieldRight,
	WieldLeft,
	WieldUp,
	WieldDown,
	DamagedRight,
	DamagedLeft,
	DamagedUp,
	DamagedDown,
	CarryStartRight,
	CarryStartLeft,
	CarryStartUp,
	CarryStartDown,
	CarryIdleRight,
	CarryIdleLeft,
	CarryIdleUp,
	CarryIdleDown,
	CarryMoveRight,
	CarryMoveLeft,
	CarryMoveUp,
	CarryMoveDown,
	Max
};

enum class CameraState
{
	Room1,
	Room2,
	Room3,
	Room4,
	Room5,
	Room6,
	Room7,
	Max
};

enum class StairsState
{
	Top,
	Bot,
	Max
};
