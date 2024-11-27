#include "TGA.h"

TGA::TGA()
{
    //ctor
}

TGA::~TGA()
{
    //dtor
}

// Color* TGA::load(const char* filename, int* width, int* height)
// {
//     CFile::SFile*   f = file.open(filename, "rb");

//     SHeader header;
//     readHeader(f, &header);
//     printHeader(&header);

//     Color* image = NULL;
//     *width  = header.imageWidth;
//     *height = header.imageHeight;

//     file.close(f);
//     return image;
// }

// void TGA::printError(const char* error, CFile::SFile* f)
// {
//     printf("TGA %s : %s\n", f->fileName, error);
//     //file.close(f);
//     exit(EXIT_FAILURE);
// }

// void TGA::readHeader(CFile::SFile* f, SHeader* h)
// {
//     h->IDLength = file.readU8(f);

//     h->colorMapType = file.readU8(f);
//     if (h->colorMapType > 1)
//         printError("Wrong format", f);

//     h->imageType = file.readU8(f);

//     if (h->imageType != eIndexed &&
//         h->imageType != eTrueColor &&
//         h->imageType != eGray &&
//         h->imageType != eIndexedRLE &&
//         h->imageType != eTrueColorRLE &&
//         h->imageType != eGrayRLE)
//     {
//         printError("Wrong format", f);
//     }

//     h->colorMap_firstEntryIndex = file.readU16(f);
//     h->colorMap_length = file.readU16(f);
//     h->colorMap_entrySize = file.readU8(f);

//     if (h->colorMapType == 1 && h->colorMap_length != 0)
//     {
//         if (h->colorMap_entrySize != 15 &&
//             h->colorMap_entrySize != 16 &&
//             h->colorMap_entrySize != 24 &&
//             h->colorMap_entrySize != 32)
//         {
//             printError("Wrong format", f);
//         }
//     }

//     h->xOrigin = file.readU16(f);
//     h->yOrigin = file.readU16(f);
//     h->imageWidth  = file.readU16(f);
//     h->imageHeight = file.readU16(f);
//     h->pixelDepth = file.readU8(f);

//     if (h->pixelDepth != 8 &&
//         h->pixelDepth != 16 &&
//         h->pixelDepth != 24 &&
//         h->pixelDepth != 32)
//     {
//         printError("Wrong format", f);
//     }

//     Uint8 flags = file.readU8(f);

//     if ((flags & 0xC0) != 0)
//         printError("Wrong format", f);

//     h->alphaBits = flags & 0xF;

//     if (h->alphaBits != 0 &&
//         h->alphaBits != 1 &&
//         h->alphaBits != 8)
//     {
//         printError("Wrong format", f);
//     }

//     if ((flags & 0x10) == 0)
//         h->hDirection = eLeftToRight;
//     else
//         h->hDirection = eRightToLeft;

//     if ((flags & 0x20) == 0)
//         h->vDirection = eBottomToTop;
//     else
//         h->vDirection = eTopToBottom;

//     if (h->imageType == eIndexed && h->colorMap_length == 0)
//         printError("Wrong format", f);

//     if (h->imageType == eIndexedRLE && h->colorMap_length == 0)
//         printError("Wrong format", f);
// }

// void TGA::printHeader(SHeader* h)
// {
//     printf("IDLength: %d\n", h->IDLength);
//     printf("colorMapType: %d\n", h->colorMapType);
//     printf("imageType: %d\n", h->imageType);
//     printf("colorMap_firstEntryIndex: %d\n", h->colorMap_firstEntryIndex);
//     printf("colorMap_length: %d\n", h->colorMap_length);
//     printf("colorMap_entrySize: %d\n", h->colorMap_entrySize);
//     printf("xOrigin: %d\n", h->xOrigin);
//     printf("yOrigin: %d\n", h->yOrigin);
//     printf("imageWidth: %d\n", h->imageWidth);
//     printf("imageHeight: %d\n", h->imageHeight);
//     printf("pixelDepth: %d\n", h->pixelDepth);
//     printf("alphaBits: %d\n", h->alphaBits);
//     printf("hDirection: %s\n", (h->hDirection == eLeftToRight ? "left to right" : "right to left"));
//     printf("vDirection: %s\n", (h->vDirection == eTopToBottom ? "top to bottom" : "bottom to top"));
// }
