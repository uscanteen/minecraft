#include <stdlib.h>
#include "vgui_viewport.h"

void viewport_init(struct vgui_viewport* viewport, int width, int height) {
    viewport->width = width;
    viewport->height = height;
}

void viewport_clear(struct vgui_viewport* viewport, unsigned int color) {
    int total_pixels = viewport->width * viewport->height;
    for (int i = 0; i < total_pixels; i++) {
        viewport->pixel_buffer[i] = color;
    }

}

void viewport_shutdown(struct vgui_viewport* viewport) {
    if (viewport->pixel_buffer != NULL) {
         free(viewport->pixel_buffer);
    viewport->pixel_buffer = NULL;
}
    }
