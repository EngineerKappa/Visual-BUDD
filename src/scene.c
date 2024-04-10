#include <genesis.h>
#include <scene.h>
#include <textbox.h>
#include <portrait.h>
#include <gfx.h>
#include <background.h>
#include <input.h>
#include <interface.h>

void updateNametag(enum ACTOR actor)
{
	char name[14];
	switch (actor)
	{
		case RHEA: strcpy(name,"Rhea"); break;
		case ERIS: strcpy(name,"Eris"); break;
		case CERES: strcpy(name,"Ceres"); break;
		case NONE: strcpy(name,""); break;
		case UNKNOWN: strcpy(name,"?????"); break;
		case MAYA: strcpy(name,"Maya"); break;
		default:break;
	}

	VDP_clearTileMapRect(BG_B,1,TEXTBOX_Y-1,16,1);
	VDP_drawTextBG(BG_B,name,2,TEXTBOX_Y-1);
	VDP_setTileMapXY(BG_B, TILE_ATTR_FULL(PAL0, TRUE, FALSE, FALSE, textbox_VRAM_ind+13),1,TEXTBOX_Y-1);
	VDP_setTileMapXY(BG_B, TILE_ATTR_FULL(PAL0, TRUE, FALSE, FALSE, textbox_VRAM_ind+13),1+strlen(name)+1,TEXTBOX_Y-1);
	return;
}

void scene_init()
{
	scene_position = 1;
	scene_state = TEXTBOX;
	scene_wait_time = 0;
	sceneLogic();
}

void scene_process()
{
	switch (scene_state)
		{
		case TEXTBOX:
			textboxProcess();
			break;
		case WAITING:
			wait_process();
			break;
		case PORTRAIT_SWITCHING:
			portrait_switch_state();
			break;
		case MENU:
			portrait_switch_state();
			break;
		default:
			break;
		}
		portrait_process();
		animateBUDD();
}

void VN_OpenMenu()
{
	scene_state=MENU;
}

void VN_Text(enum ACTOR actor, char dialogue[])
{
	textbox_state = TEXT_DRAWING;
	scene_state=TEXTBOX;
	text_clear();
	strcpy(str_text, dialogue);
	updateNametag(actor);
	actor_current = actor;
	if (actor_current == portrait_actor)
	{
		//SPR_setAnim(s_portrait_mouth, 1);
		portrait_mouth_timer=max(strlen(dialogue)*2,10);
	}
	else
	{
		portrait_mouth_timer=1;
	}
	textbox_state = TEXT_DRAWING;
}

void VN_TextboxOpen()
{
	textbox_state = ENTER;
}

void VN_WarpPortrait(s16 x, s16 y)
{
	portrait_x=x;
	portrait_y=y;
}

void VN_MovePortrait(s16 x, s16 y, u8 speed, bool wait)
{
	portrait_move_speed=speed;
	portrait_target_x=x;
	portrait_target_y=y;
	if (wait)
		scene_state=PORTRAIT_MOVING;
	else
		sceneLogic();
}

void VN_ReloadBG()
{
	VDP_drawImageEx(BG_B, &frame, TILE_ATTR_FULL(PAL0, false, false, false, VRAM_ind),40,21,false,TRUE);
}

void VN_Wait(u16 time)
{
	scene_state=WAITING;
	scene_wait_time=time;
}

void VN_PortraitFadeOut()
{

}

void wait_process()
{
	if (inputBack())
		scene_wait_time=0;

	switch (scene_wait_time)
	{
	case 0:
		scene_wait_time=60;
		sceneLogic();
		break;
	
	default: scene_wait_time--; break;
	}
}