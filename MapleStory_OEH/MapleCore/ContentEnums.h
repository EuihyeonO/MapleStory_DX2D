#pragma once

enum class State
{
	Move = 0,
	Jump,
	Swing,
	Qskill,
	Wskill,
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
	Monster,
	Boss,
	Star,
	Weapon,
	UI,
	Mouse,
};

