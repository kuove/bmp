#include <stdio.h>
#include <stdint.h>
#include <math.h>

float hexToFloat(uint32_t hex) {
    float result;
    uint32_t sign = (hex >> 31) & 0x1;
    uint32_t exponent = (hex >> 23) & 0xff;
    uint32_t mantissa = hex & 0x7fffff;

    if (exponent == 0xff && mantissa != 0) {
        // NaN or infinity
        result = 0.0 / 0.0;
    } else if (exponent == 0xff && mantissa == 0) {
        // positive or negative infinity
        result = sign ? -1.0 / 0.0 : 1.0 / 0.0;
    } else if (exponent == 0 && mantissa == 0) {
        // zero
        result = 0.0;
    } else {
        // normalized or denormalized number
        exponent -= 127;
        if (exponent < -23) {
            // denormalized number
            result = mantissa * pow(2, -149);
        } else {
            // normalized number
            mantissa |= 0x800000;
            exponent += 23;
            result = mantissa * pow(2, exponent - 127 - 23);
        }
        result = sign ? -result : result;
    }

    return result;
}

int main() {
    uint32_t hex = 0x43700000;
    float result = hexToFloat(hex);
    printf("%.1f\n", result); // 输出240.0
    return 0;
}
