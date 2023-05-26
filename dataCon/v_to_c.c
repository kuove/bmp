#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
typedef struct 
{
    unsigned char r,g,b,a;
}Color;


Color vector_from_color(unsigned int rgba) {
	Color result;
    result.r = (rgba >> 16) & 0xFF;
    result.g = (rgba >> 8) & 0xFF;
    result.b = rgba & 0xFF;
    result.g = (rgba >> 24) & 0xFF;
    return result;
}

int main(){
    unsigned int c = 3839873040;
    Color cc = vector_from_color(c);

    return 0;
}

// #include <stdio.h>

// typedef struct {
//     unsigned char r;
//     unsigned char g;
//     unsigned char b;
// } Color;

// Color intToColor(unsigned int color) {
//     Color result;
//     result.r = (color >> 16) & 0xFF;
//     result.g = (color >> 8) & 0xFF;
//     result.b = color & 0xFF;
//     return result;
// }

// int main() {
//     unsigned int colorInt = 4284950802; 
//     Color colorVec = intToColor(colorInt);
//     printf("r=%d, g=%d, b=%d\n", colorVec.r, colorVec.g, colorVec.b);
//     return 0;
// }
