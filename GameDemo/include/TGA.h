#ifndef TGA_H
#define TGA_H

//#include "Graphics.h"
#include "CFile.h"

class TGA
{
    public:
        TGA();
        virtual ~TGA();
        //Color*  load(const char* filename, int* width, int* height);

    protected:

    private:
        enum EHDir
        {
            eLeftToRight,
            eRightToLeft
        };

        enum EVDir
        {
            eTopToBottom,
            eBottomToTop
        };

        enum EImageType
        {
            eNoImage = 0,
            eIndexed = 1,
            eTrueColor = 2,
            eGray = 3,
            eIndexedRLE = 9,
            eTrueColorRLE = 10,
            eGrayRLE = 11
        };

        // header datas
        struct SHeader
        {
            Uint8   IDLength;
            Uint8   colorMapType;
            Uint8   imageType;
            Uint16  colorMap_firstEntryIndex;
            Uint16  colorMap_length;
            Uint8   colorMap_entrySize;
            Uint16  xOrigin;
            Uint16  yOrigin;
            Uint16  imageWidth;
            Uint16  imageHeight;
            Uint8   pixelDepth;
            Uint8   alphaBits;
            EHDir   hDirection;
            EVDir   vDirection;
        };

        void    printError(const char* error, CFile::SFile* f);

        void    readHeader(CFile::SFile* f, SHeader* h);
        void    printHeader(SHeader* h);
};

extern TGA tga;

#endif // TGA_H
