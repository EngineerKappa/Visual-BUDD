#ifndef _SCENE_H_
#define _SCENE_H_

//////////////////
enum ACTOR {
	NONE,
	UNKNOWN,
	RHEA,
	ERIS,
	STELLA,
	CERES,
    BOXER,
    RAY,
    DOT,
    SEEKER,
    STRATOS,
    MAYA
};

enum POSE {
	NORMAL,
	HAPPY,
    ANGRY,
    SAD,
    DETERMINED
};

enum ACTOR actor_current;
enum ACTOR portrait_actor;
enum ACTOR portrait_budd;

enum SCENE_STATE {
	FADEIN,
  	TEXTBOX,
	PORTRAIT_MOVE,
	PORTRAIT_DISAPPEAR,
	PORTRAIT_SWITCH,
	WAIT,
	MENU
};

int scene_position;
u16 scene_wait_time;
enum SCENE_STATE scene_state;

void scene_init();
void sceneLogic();
void VN_TextboxOpen();
void VN_NewBG();
void VN_WarpPortrait(s16 x, s16 y);
void VN_MovePortrait(s16 x, s16 y, u8 speed, bool wait);
void VN_ReloadBG();
void VN_Wait(u16 time);
void wait_process();
void VN_Text(enum ACTOR actor, char dialogue[]);
void VN_OpenMenu();
void updateNametag();
void scene_process();
//////////////////


#endif // _SCENE_H_