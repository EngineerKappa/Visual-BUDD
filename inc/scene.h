#ifndef _SCENE_H_
#define _SCENE_H_


//
enum COMMAND {
	TEXT_SHOW,
	BG_LOAD,
	BG_FADE_OUT,
	CHAR_PRELOAD,
	CHAR_SHOW,
	CHAR_SWITCH,
	CHAR_SET_EYES,
	CHAR_SET_MOUTH,
	CHAR_SET_PALETTE,
	CHAR_FADE_IN,
	CHAR_FADE_OUT,
	CHAR_MOVE,
	BUDD_SET_ANIM,
	VARIABLE_SET,
	VARIABLE_ADD,
	FLAG_SET,
	ITEM_ADD,
	ITEM_REMOVE,
	ITEM_SHOW,
	JUMP_ITEM_CHECK,
	JUMP_VARIABLE_CHECK,
	JUMP_FLAG_CHECK,
	JUMP_CHOICE_LIST,
	BGM_PLAY,
	BGM_STOP,
	SFX_PLAY,
	WAIT,
	MENU_RETURN
};



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

struct EventCommand
{
    enum COMMAND command;
    union {
		Image* bg;
		enum ACTOR actor;
		int slot;
		int time;
    } params;
};

enum ACTOR actor_current;
enum ACTOR portrait_actor;
enum ACTOR portrait_budd;

enum SCENE_STATE {
	FADEIN,
  	TEXTBOX,
	PORTRAIT_MOVING,
	PORTRAIT_DISAPPEARING,
	PORTRAIT_SWITCHING,
	WAITING,
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