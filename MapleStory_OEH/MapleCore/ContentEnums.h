#pragma once

enum class State
{
	Move = 0,
	Jump,
	Swing,
	Qskill,
	Wskill,
	Eskill,
	Up,
	Down,
};

enum class WeaponType
{
	OneHandWeapon,
	Claw,
};

enum class RenderOrder
{
	BasicMap,
	NPC,
	Player,
	Weapon,
	Monster,
	UI,
};

enum class CollisionOrder
{
	Range,
	Player,
	Monster,
	Boss,
	Star,
	Weapon,
	UI,
	Mouse,
	RopeAndLadder,

};

enum class MonsterName
{
	GreenSnail,

};

