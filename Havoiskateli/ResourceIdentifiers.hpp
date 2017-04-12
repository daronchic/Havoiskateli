#pragma once

namespace sf
{
	class Image;
	class Font;
	class SoundBuffer;
	class Music;
}

namespace Images
{
	enum ID
	{
		menu_background_1,
		menu_background_2,
		menu_background_3,
		menu_background_4,
		menu_StartingWindow,
		menu_stand,

		player_1,
		player_2,
		player_3,
		player_4
	};
}

namespace Fonts
{
	enum ID
	{
		titleFont,
		menuFont
	};
}

namespace Sounds
{
	enum ID
	{
		button_switched,
		button_pressed,
		player_changed,
		player_switched
	};
}

namespace Musics
{
	enum ID
	{
		none,
		menu,
		city
	};
}

template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Image, Images::ID> ImagesHolder;
typedef ResourceHolder<sf::Font, Fonts::ID> FontHolder;
typedef ResourceHolder<sf::SoundBuffer, Sounds::ID> SoundHolder;