#ifndef CFILE_H
#define CFILE_H

#include <stdio.h>
#include <SDL2/SDL.h>

class CFile
{
    public:
        CFile();
        virtual ~CFile();

        struct SFile
        {
            FILE*   file;
            char*   fileName;
        };

        SFile*      open(const char* fileName, const char* mode);
        void        close(SFile* f);
        void        seek(SFile* f, long int offset, int origin);
        long int    tell(SFile* f);

        void    read(SFile* f, void* dest, int nbBytes);
        Uint8   readU8(SFile* f);
        Sint8   readS8(SFile* f);
        Uint16  readU16(SFile* f);
        Sint16  readS16(SFile* f);
        Uint32  readU32(SFile* f);
        Sint32  readS32(SFile* f);
        Uint64  readU64(SFile* f);
        Sint64  readS64(SFile* f);
        float   readFloat(SFile* f);
        double  readDouble(SFile* f);

        void    write(SFile* f, const void* src, int nbBytes);
        void    writeU8(SFile* f, const Uint8 value);
        void    writeS8(SFile* f, const Sint8 value);
        void    writeU16(SFile* f, const Uint16 value);
        void    writeS16(SFile* f, const Sint16 value);
        void    writeU32(SFile* f, const Uint32 value);
        void    writeS32(SFile* f, const Sint32 value);
        void    writeU64(SFile* f, const Uint64 value);
        void    writeS64(SFile* f, const Sint64 value);
        void    writeFloat(SFile* f, const float value);
        void    writeDouble(SFile* f, const double value);

    protected:

    private:
        void    printError(const char* error, const char* fileName);
        void    printErrorAndClose(const char* error, SFile* f);
};

extern CFile file;

#endif // CFILE_H
