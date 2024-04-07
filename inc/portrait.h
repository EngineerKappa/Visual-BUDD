#ifndef _PORTRAIT_H_
#define _PORTRAIT_H_


#include <scene.h>
///////////////////////////////
#define PORTRAIT_X_CENTER_BUDD 72
#define PORTRAIT_Y_DEFAULT 0
#define PORTRAIT_X_CENTER 64

struct AnimRegion
{
    u16 destination_x;
    u16 destination_y ;
    u16 source_x;
    u16 source_y;
    u8 width;
    u8 height;
    u8 frames;
    u8 frame_delay;
    u8 current_frame;
    u8 frame_wait;
};

struct Portrait
{
    Image image;
    u16 x;
    u16 y;
    struct AnimRegion blink_anim;
    struct AnimRegion talk_anim;
    struct AnimRegion passive_anim;

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
struct AnimRegion portrait_anim_init(u8 width, u8 height,u8 frames, u16 source_x, u16 source_y, u16 destination_x, u16 destination_y,u8 frame_delay);
void portrait_anim_set_frame(u8 slot, struct AnimRegion *region, u8 frame);


#endif // _PORTRAIT_H_