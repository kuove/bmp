#define STB_IMAGE_IMPLEMENTATION
#include <stdio.h>
#include <stdint.h>
#include "stb_image.h"

int main() {
  int width, height, channels;
  uint8_t* data = stbi_load("diablo3_pose_diffuse.bmp", &width, &height, &channels, 3); // 注意这里 channels 参数必须为 4，表示使用 RGBA 模式

  if (!data) {
    printf("Could not open file\n");
    return 1;
  }

  // 计算像素偏移量
  int row = 0; // 例如，要读取第 10 行
  int col = 0; // 例如，要读取第 20 列
  int pixel_index = row * width + col;

  // 读取像素值
  uint32_t pixel_value = *(uint32_t*)(&data[pixel_index * 3]);

  // 输出像素值
  printf("Pixel at row %d, col %d: 0x%08X\n", row, col, pixel_value);

  stbi_image_free(data);

  return 0;
}
