#ifndef VGUI_VIEWPORT_H
#define VGUI_VIEWPORT_H

struct vgui_viewport
{
    int width;
    int height;
    unsigned int *pixel_buffer;
};

// Canvas Memory
void viewport_init(struct vgui_viewport *viewport, int width, int height);

// Clear it
void viewport_clear(struct vgui_viewport *viewport, unsigned int color);

// When they closed the game, clear memory!

void viewport_shutdown(struct vgui_viewport* viewport);

#endif
