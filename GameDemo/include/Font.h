#ifndef FONT_H
#define FONT_H

#include "Vector3.h"

class Font
{
    public:
        Font();
        virtual ~Font();

        // load/unload from a file
        //bool Load(const std::string& fileName);
        // bool Load(const char& fileName);
        // void Unload();
        // Given string and this font, draw string to a texture
        //class Texture* RenderText(const std::string& text,
                                  //const Vector3& color = Color::White,
                                  //int pointSize = 30);

    protected:

    private:
        // Map of point sizes to font data
        //std::unordered_map<int, TTF_Font*> mFontData;
};

#endif // FONT_H
