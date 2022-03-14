#include <color/color.h>
#include <stdio.h>
#include <stdlib.h>
#include <vec3/vec3.h>
#define PROJECT_NAME "teeet"
const int image_width = 256;
const int image_height = 256;
int main() {
  printf("P3\n%d %d\n255\n", image_width, image_height);
  for (int j = image_height - 1; j >= 0; --j) {
    fprintf(stderr, "\rScanLines Remaining: %d ", j);
    fflush(stderr);
    for (int i = 0; i < image_width; ++i) {
      color pixel_color = {(double)i / (image_width - 1),

                           (double)j / (image_height - 1), 0.25};
      write_color(pixel_color);
    }
  }

  fprintf(stderr, "\nDone.\n");
  return EXIT_SUCCESS;
}
