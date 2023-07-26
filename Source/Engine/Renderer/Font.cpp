#include "Font.h"
#include "SDL2-2.28.1/include/SDL_ttf.h"
#include <iostream>

namespace kiko
{
	Font::Font(const std::string& filename, int fontSize)
	{
		Load(filename, fontSize);
	}

	Font::~Font()
	{
		if (m_ttfFont != nullptr)
		{
			TTF_CloseFont(m_ttfFont);
		}
	}

	void Font::Load(const std::string& filename, int fontSize)
	{
		// Use filename.c_str() to get the C-style string.
		const char* cFilename = filename.c_str();

		// Load the font using TTF_OpenFont and assign the result to m_ttfFont.
		m_ttfFont = TTF_OpenFont(cFilename, fontSize);

		if (m_ttfFont == nullptr)
		{
			std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
		}
	}
}