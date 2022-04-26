#pragma once

enum class PlayLevelOrder
{
	BACKGROUND,
	MONSTER,
	BELOWPLAYER,
	PLAYER,
	ABOVEPLAYER,
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
	Room1_Trans,
	Room2,
	Room2_Trans,
	Room3,
	Room3_Trans,
	Room4,
	Room4_Trans,
	Room5,
	Room5_Trans,
	Room6,
	Room6_Trans,
	Room7,
	Room7_Trans,
	Max
};

enum class PlayerStairsState
{
	Top,
	Bot,
	Max
};

enum class PotState
{
	Idle,
	Carried,
	InAir,
	DeathAnimation,
	Death,
	Max
};

enum class PopoState
{
	Idle,
	Knockbacked,
	Death,
	Max,
};