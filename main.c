#include <stdio.h>

#include <libavdevice/avdevice.h>
#include <libavformat/avformat.h>

#include <raylib.h>

void display_all_devices(void) {
#define MAX_WIDTH 250
  char buf[MAX_WIDTH + 1];
  const AVInputFormat *fmt = NULL;
  char *src, *dst;
  int i = 0;

  while ((fmt = av_input_audio_device_next(fmt)) != NULL) {
    dst = buf;
    for (src = fmt->name; dst - buf < sizeof buf - 1 && *src; src++, dst++) {
      *dst = *src;
    }

    if (dst - buf < sizeof buf - 4) {
      *dst++ = ' ';
      *dst++ = '-';
      *dst++ = ' ';
    }

    for (src = fmt->long_name; dst - buf < sizeof buf - 1 && *src;
         src++, dst++) {
      *dst = *src;
    }

    *dst = 0;

    DrawText(buf, 20, 20 * (i + 1), 10, BLACK);
    i++;
  }
}

int main(void) {
  avdevice_register_all();
  display_all_devices();

  InitWindow(800, 450, "ibs");
  SetTargetFPS(30);

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    display_all_devices();
    EndDrawing();
  }

  CloseWindow();

  return 0;
}
