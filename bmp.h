#ifndef BMP_H
#define BMP_H
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define uint unsigned int
#define ushort unsigned short

typedef struct bmpFileHeader
{
    ushort bfType;
    uint bfSize;
    uint bfReserved;
    uint bfOffBits;
}bmpHeader;

typedef struct bmpInfoHeader
{
    uint biSize;
    int biWidth;
    int biHeight;
    ushort biPlanes;
    ushort biBitCount;
    uint biCompression;
    uint biSizeImage;
    int biXPelsPerMeter;
    int biYPelsperMeter;
    uint biClrUsed;
    uint biCLrImportant;
}infoHeader;

#endif