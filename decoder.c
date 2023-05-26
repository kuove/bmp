#include <stdio.h>
#include <stdlib.h>
#include <sys/malloc.h>
#include <assert.h>
#include <stdio.h>

typedef unsigned int uint32;
typedef unsigned short uint16;
typedef unsigned char uint8;



void decode_dxt1_rgba(FILE* file, uint32 data0, uint32 data1)
{
    // data0 = 0x18812061;
    // data1 = 0x8E0AEFAF;

    uint32 color0 = (data1 & 0xffff0000) >> 16;
    uint32 color1 = data1 & 0x0000ffff;

    uint32 r0 = color0 & 0x1f;
    uint32 g0 = (color0 & 0x7e0) >> 5;
    uint32 b0 = (color0 & 0xf800) >> 11;
    uint32 r1 = color1 & 0x1f;
    uint32 g1 = (color1 & 0x7e0) >> 5;
    uint32 b1 = (color1 & 0xf800) >> 11;

    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            uint32 bits = (data0 >> (x * 2 + y * 8)) & 0x3;
            uint32 code = bits & 0x3;
            uint32 a = 255;

            uint32 r, g, b;

            if (code == 0) {
                r = r0;
                g = g0;
                b = b0;
            }
            else if (code == 1) {
                r = r1;
                g = g1;
                b = b1;
            }
            else if (code == 3 && color0 <= color1) {
                r = g = b = a = 0;
            }
            else {
                if (code == 2 && color0 > color1) {
                    r = (2 * r0 + r1) / 3;
                    g = (2 * g0 + g1) / 3;
                    b = (2 * b0 + b1) / 3;
                }
                else if (code == 3 && color0 > color1) {
                    r = (r0 + 2 * r1) / 3;
                    g = (g0 + 2 * g1) / 3;
                    b = (b0 + 2 * b1) / 3;
                }
                else {
                    assert(code == 2 && color0 <= color1);
                    r = (r0 + r1) / 2;
                    g = (g0 + g1) / 2;
                    b = (b0 + b1) / 2;
                }
            }
            fprintf(file, "%x%x%x\n", b << 3, g << 2, r << 3);
            // printf("%#04x %#04x %#04x\n", b << 3, g << 2, r << 3);
        }
    }
}


int main() {
    FILE* file = fopen("压缩后.dds", "rb"); 
    int offfset = 128;
    int w = 256;
    FILE* output = fopen("data.txt", "w");
    uint32 temp[w * w];
    // uint8 *temp = (uint8*) malloc(w * w);
    fseek(file, offfset, SEEK_SET);
    size_t si = fread(temp, sizeof(uint32), w * w, file);

    for(size_t i = 0; i < si; i = i + 2)
    {
        uint32 c0 = temp[i];
        uint32 c1 = temp[i + 1];

        decode_dxt1_rgba(output,c0, c1);
    }
    // decode_dxt1_rgba(output,1, 1);
    fclose(file);
    fclose(output);

    return 0;
}

