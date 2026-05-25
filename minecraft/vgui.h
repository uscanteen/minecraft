#ifndef VGUI_H
#define VGUI_H

// VGUIPANEL
typedef struct VGUIPANEL {
    const char* type;
    int x, y, width, height;
} VGUIPANEL; 

// VGUISYS
typedef struct VGUISYS {
    VGUIPANEL* (*Create)(const char* type); 
} VGUISYS; 
extern const VGUISYS VGUI;

typedef struct Vertex3D {
    float x;
    float y;
    float z;
} Vertex3D;

typedef struct Edge3D {
    int start;
    int end;
} Edge3D;

typedef struct Player {
    float x;
    float y;
    float z;
    float move_speed;
} Player;
extern Player* pPlayer;
void pPlayer_Move(float move_x, float move_y, float move_z);

// Window Functions
int vgui_initialize(const char* title, int width, int height);
int vgui_runframe(void);

#endif