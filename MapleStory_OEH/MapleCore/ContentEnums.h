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
	BasicMap = 100,
	NPC,
	Player,
	Weapon,
	Monster,
	Skill,
	UI,
	Mouse,
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

