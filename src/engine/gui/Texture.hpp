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
		void * userdata;
		int width;
		int height;
		std::string ID;
		std::string src; // filename

		Texture()
		:   userdata(nullptr),
            width(0), height(0)
        {}
	};

} // namespace ui
} // namespace zn

#endif // ZENGUI_TEXTURE_HPP

