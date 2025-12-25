#pragma once
extern bool running;

bool platform_create_window(int width, int height, char *title);
void platform_update_window();
void platform_swap_buffers();
void platform_destroy_window();

void *platform_load_gl_function(char *funName);
