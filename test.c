#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

typedef struct {
  unsigned char b;
  unsigned char g;
  unsigned char r;
} Pixel;

int main() {
  FILE* file = fopen("diablo3_pose_diffuse.bmp", "rb");
  if (!file) {
    printf("Could not open file\n");
    return 1;
  }

  // 读取文件头
  unsigned char header[54];
  fread(header, sizeof(unsigned char), 54, file);

  // 获取像素偏移量
  int pixel_offset = header[10] + (header[11] << 8) + (header[12] << 16) + (header[13] << 24);

  // 读取图像数据
  int width = header[18] + (header[19] << 8) + (header[20] << 16) + (header[21] << 24);
  int height = header[22] + (header[23] << 8) + (header[24] << 16) + (header[25] << 24);
  int row_size = width * 3;
  if (row_size % 4 != 0) {
    row_size += 4 - (row_size % 4);
  }
  int data_size = row_size * height;
  unsigned char* data = (unsigned char*) malloc(data_size);
  fseek(file, pixel_offset, SEEK_SET);
  fread(data, sizeof(unsigned char), data_size, file);

  // 计算像素偏移量
  int row = 0; // 例如，要读取第 10 行
  int col = 0; // 例如，要读取第 20 列
  int pixel_index = row * width + col;
  int pixel_offset_in_data = pixel_index * 3;

  // 读取像素值
  unsigned char b = data[pixel_offset_in_data];
  unsigned char g = data[pixel_offset_in_data + 1];
  unsigned char r = data[pixel_offset_in_data + 2];

  unsigned int c = (r << 16) | (g << 8) | b;

  printf("Pixel at row %d, col %d: R=%d, G=%d, B=%d, C=%x\n", row, col, r, g, b, c);

  fclose(file);
  free(data);

  return 0;
}

