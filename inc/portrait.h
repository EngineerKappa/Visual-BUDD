#ifndef _PORTRAIT_H_
#define _PORTRAIT_H_


#include <scene.h>
///////////////////////////////
#define PORTRAIT_X_CENTER_BUDD 72
#define PORTRAIT_Y_DEFAULT 0
#define PORTRAIT_X_CENTER 64

struct Portrait
{
    Image image;
    u16 x;
    u16 y;
    u16 blink_x;
    u16 blink_y;
    u16 mouth_x;
    u16 mouth_y;
    bool has_mouth;
    bool has_eyes;
    u8 map_width;
    u8 map_height;
    u16 tileset_ind;
    enum ACTOR actor;
    enum ACTOR portrait_budd;
    Sprite* portrait_budd_sprite;
    enum POSE pose;
};

struct Portrait portrait_list[3];
u8 portrait_slot;

s16 portrait_x;
s16 portrait_y;
u16 portrait_blink_x;
u16 portrait_blink_y;
u16 portrait_blink_timer;
u16 portrait_mouth_x;
u16 portrait_mouth_y;
u16 portrait_mouth_timer;
s16 portrait_target_x;
s16 portrait_target_y;
u8 portrait_move_speed;
u8 portrait_switch_time;
enum ACTOR portrait_switch_actor;
enum POSE portrait_switch_pose;


s16 budd_x;
s16 budd_y;
u16 budd_blink_timer;
s16 budd_float_timer;

Sprite* s_portrait_blink;
Sprite* s_portrait_mouth;
Sprite* s_portrait_budd;



extern void portrait_init();
void portrait_retrieve(enum ACTOR actor, enum POSE pose);
void portrait_preload(u8 slot, enum ACTOR actor, enum POSE pose);
void portrait_load(Image image);
void portrait_free();
void animateBUDD();
void portrait_process();
void portrait_switch(enum ACTOR actor, enum POSE pose);
void portrait_switch_state();


#endif // _PORTRAIT_H_