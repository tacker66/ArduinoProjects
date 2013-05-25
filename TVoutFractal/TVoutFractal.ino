
#include <TVout.h>
#include <fontALL.h>

TVout TV;

void setup() {
  TV.begin(PAL, 136, 104);
  TV.clear_screen();
  TV.select_font(font8x8);
  TV.print(4, 44, "Mandelbrot-Demo");
  delay(3000);
  TV.clear_screen();
  
  const unsigned int width = TV.hres();
  const unsigned int height = TV.vres();
  const float min_re = -2.2;
  const float max_re = 0.8;
  const float min_im = -1.1;
  const float max_im = 1.1;

  unsigned int x, y, depth;
  float im, re, tr, ti, temp;
  
  for (y = 0; y < height; y++) {
    im = min_im + y * (max_im - min_im) / height;
    for (x = 0; x < width; x++) {
      re = min_re + x * (max_re - min_re) / width;
      tr = re;
      ti = im;

      depth = 0;
      while (depth++ < 20) {
        temp = tr * tr - ti * ti + re;
        ti = 2 * tr * ti + im;
        tr = temp;
        if (tr * tr + ti * ti > 4)
          break;
      }
      if (depth < 16 && !(depth%2))
        TV.set_pixel(x, y, WHITE);
    }
  }
}

void loop() {}

