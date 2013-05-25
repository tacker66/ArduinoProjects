
#include <TVout.h>
#include <pollserial.h>
#include <fontALL.h>

TVout TV;
pollserial pserial;

void setup()  {
  TV.begin(PAL,184,72);
  TV.select_font(font6x8);
  TV.println("Serial Terminal");
  TV.set_hbi_hook(pserial.begin(57600));
}

void loop() {
  if (pserial.available()) {
    TV.print((char)pserial.read());
  }
}

