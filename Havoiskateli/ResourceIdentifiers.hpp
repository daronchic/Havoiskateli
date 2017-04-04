#pragma once

namespace sf
{
	class Image;
	class Font;
	class Sound;
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
		test_1,
		test_2
	};
}

namespace Musics
{
	enum ID
	{
		menu,
		city
	};
}

template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Image, Images::ID> ImagesHolder;
typedef ResourceHolder<sf::Font, Fonts::ID> FontHolder;
typedef ResourceHolder<sf::Sound, Sounds::ID> SoundHolder;
typedef ResourceHolder<sf::Music, Musics::ID> MusicHolder;