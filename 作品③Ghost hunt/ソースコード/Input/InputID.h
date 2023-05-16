#pragma once
#include <type_traits>

// ƒ{ƒ^ƒ“‚ÌŽí—Þ
enum class InputID
{
	Non,
	Up,
	Down,
	Left,
	Right,
	Btn1,
	Btn2,
	Max
};

static InputID begin(InputID) { return InputID::Up; };
static InputID end(InputID) { return InputID::Max; };
static InputID operator++(InputID& state)
{
	return (state = static_cast<InputID>(std::underlying_type<InputID>::type(state) + 1));
};
static InputID operator*(const InputID& state) { return state; };