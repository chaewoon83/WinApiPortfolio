#pragma once

enum class PlayLevelOrder
{
	BACKGROUND,
	DEBUG,
	B1FMONSTER,
	B1FBELOWPLAYER,
	B1FPLAYER,
	B1FABOVEPLAYER,
	B1FBACKGROUNDROOF,
	MONSTER,
	BELOWPLAYER,
	PLAYER,
	ABOVEPLAYER,
	BACKGROUNDROOF,
	BLACKBACKGROUND,
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
	WieldRight_1,
	WieldLeft_1,
	WieldUp_1,
	WieldDown_1,
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
	Room8,
	Room8_Trans,
	Room9,
	Room9_Trans,
	Room10,
	Room10_Trans,
	Room11,
	Room11_Trans,
	Room12,
	Room12_Trans,
	Room13,
	Room13_Trans,
	Room14,
	Room14_Trans,
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

enum class BlueStalfosState
{
	LookAroundRight,
	LookAroundLeft,
	LookAroundUp,
	LookAroundDown,
	WalkRight,
	WalkLeft,
	WalkUp,
	WalkDown,
	JumpRight,
	JumpLeft,
	JumpUp,
	JumpDown,
	Knockbacked,
	Death,
	Max,
};