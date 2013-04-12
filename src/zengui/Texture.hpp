#ifndef ZENGUI_TEXTURE_HPP
#define ZENGUI_TEXTURE_HPP

namespace zn
{
namespace ui
{
	/*
		This is all what the GUI knows about textures.
		how to draw them is up to you.
	*/
	struct Texture
	{
		void * userdata = nullptr;
		int width = 0;
		int height = 0;
		std::string ID;
		std::string src; // filename
	};

} // namespace ui
} // namespace zn

#endif // ZENGUI_TEXTURE_HPP

