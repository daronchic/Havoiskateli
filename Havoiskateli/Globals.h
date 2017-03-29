#pragma once

struct Vector2 {
	int x, y;
	Vector2() : x(0), y(0) {}
	Vector2(int _x, int _y) : x(_x), y(_y) {}
};

namespace globalData {
	static const int screenWidth{ 1366 };
	static const int screenHeight{ 768 };
	static int levelWidth = 1600;
	static int levelHeight = 1600;
}

enum Direction {
	LEFT,
	RIGHT,
	UP,
	DOWN
};

enum PlayerState {
	STAY,
	WALK,
	SLEEP
};

namespace sides {
	enum Side {
		TOP,
		BOTTOM,
		LEFT,
		RIGHT,
		NONE
	};
	const inline Side getOppositeSide(Side side) {
		return
			side == TOP ? BOTTOM :
			side == BOTTOM ? TOP :
			side == LEFT ? RIGHT :
			side == RIGHT ? LEFT :
			NONE;
	}
}

namespace States {
	enum ID {
		TitleScreen,
		MainMenuScreen,
		GameScreen,
		PauseScreen
	};
}