#include <genesis.h>
#include <shared.h>
#include <sound.h>
#include <gfx.h>
#include <input.h>
#include <textbox.h>
#include <background.h>
#include <scene.h>
#include <portrait.h>

enum GAME_STATE 
{
	EKLOGO,
	TITLE,
	SCENE
};


void sceneLogic()
{
	switch (scene_position)
	{
	case 1: loadBackground(bg1); portrait_preload(0,ERIS,NORMAL); portrait_preload(1,MAYA,NORMAL);
	case 2: VN_TextboxOpen();  break;
	case 3: portrait_retrieve(ERIS,NORMAL);VN_Wait(10); break;
	case 4: VN_Text(ERIS, "Portrait 1"); break;
	case 5: portrait_switch(MAYA,NORMAL); break;
	case 6: portrait_preload(0,CERES,NORMAL);VN_Text(MAYA, "Portrait 2"); break;
	case 7: portrait_switch(CERES,NORMAL); break;
	case 8: portrait_preload(1,ERIS,NORMAL);VN_Text(CERES,"Portrait 3"); break;
	case 9: portrait_switch(ERIS,NORMAL); break;
	case 10: VN_Text(ERIS, "Back to portrait 1!"); break;

	//case 6: portrait_switch(CERES,NORMAL); break;
	default: PAL_fadeOutPalette(1,16,TRUE);waitMs(300);PAL_fadeOutPalette(2,15,TRUE);waitMs(300);portrait_free();VN_Text(UNKNOWN, "Nothing to see here."); VRAM_ind=0; scene_position=0; break;
	}	
	scene_position++;
}

void scene_test_1()
{
	switch (scene_position)
	{
	case 1: loadBackground(bg1); portrait_preload(0,ERIS,NORMAL); portrait_preload(1,MAYA,NORMAL); portrait_preload(2,CERES,NORMAL);
	case 2: VN_TextboxOpen();  break;
	case 3: VN_Text(RHEA, "(It looks like #PEris#/ and #PBoxer#/ are\nhere early.)"); break;
	case 4: portrait_retrieve(ERIS,NORMAL);VN_Text(ERIS, "Oh, hi Rhea!!"); break;
	case 5: VN_Text(ERIS, "Are we doing the #!visual novel#/ thing\nalready?"); break;
	case 6: VN_Text(RHEA, "\"It seems like it.\""); break;
	case 7: portrait_switch(MAYA,NORMAL);break;//VN_Text(ERIS, "Wait, does that mean we're going\non a #!date!?#/ Isn't that what you're\nsupposed do in these things!?!?"); break;
	case 8: VN_Text(RHEA, "\"Hey!!\nI never said anything about--\""); break;
	case 9: portrait_switch(CERES,NORMAL);VN_Text(ERIS, "Oh my gosh!!#<3 We can go on a date,\nand talk to eachother and get\nmarried, and have children, and..."); break;
	case 10: VDP_setHilightShadow(1);VN_Text(RHEA, "(I can't with this girl.)"); break;
	case 11: VN_Wait(30); break;
	case 12: VN_Text(RHEA, "(...She's so cute, though.#<3)"); break;
	case 13: VDP_setHilightShadow(0);load_actor(MAYA, NORMAL); VN_Text(RHEA, "...Wait, who are you?"); break;
	case 14: VN_Text(MAYA, "I'm #PMaya Fey#/!\nI... don't actually know what I'm\ndoing on #Lthis beach#/."); break;
	case 15: VN_Text(MAYA, "Have you seen #Psomebody#/ around with\nspiky hair that really likes to\npoint at things?"); break;
	case 16: load_actor(ERIS, NORMAL); VN_Text(ERIS, "I like to point at things!\nI don't have spiky hair though.\n...Not anymore, anyway."); break;
	case 17: VN_Text(ERIS, "Rhea, do you think she's talking\nabout Alice?"); break;
	case 18: load_actor(MAYA, NORMAL); VN_Text(MAYA, "Nonono, He's a guy in a suit!\nA #!defense attorney#/ with a few high\nprofile cases to his name."); break;
	case 19: load_actor(ERIS, NORMAL); VN_Text(ERIS, "Woah...\nWhoever this attorney guy is, he\nseems like a total ace!"); break;
	case 20: VN_Text(RHEA, "\"An ace attorney, huh?\nI feel like I've heard that one\nbefore somewhere.\""); break;
	case 21: VN_Text(ERIS, "Rhea! We should help this girl find\nthe person she's looking for!"); break;
	case 22: VN_Text(ERIS, "You never know when you'll need an\nattorney for... reasons."); break;
	case 23: load_actor(MAYA, NORMAL); VN_Text(MAYA, "Thanks, both of you! I'm sure I can\nconvince him to be your attorney if\nyou uh... get in trouble."); break;
	case 24: VN_Text(RHEA, "\"H-Hey!\nI never agreed to any of this!\""); break;
	case 25: PAL_fadeOutPalette(1,30,TRUE); waitMs(600); VN_Text(RHEA, "(I sometimes wonder how different\nthings would've been if I'd just\nstayed in law school instead of\njoining MARI-XIII's staff. Heh...)"); break;
	case 26: PAL_fadeOutPalette(2,15,TRUE); waitMs(300);portrait_free(); VN_Text(RHEA, "(The girl in strange clothes took us\nto some #Loffice building#/, somewhere.)"); break;
	case 27: loadBackground(bg2); break;
	default: PAL_fadeOutPalette(2,10,TRUE); waitMs(300);portrait_free();VN_Text(UNKNOWN, "Testing! 1, 2, 3! Did you know that\nTextboxes can support up to 4 lines\nnow? Isn't that kind of crazy??????\nSo uh, what do I say now? Oh HECK AA"); scene_position=0; break;
	}
}

int main()
{
	SPR_init();
	BG_init();
	scene_init();
	TEXTBOX_init();
	portrait_init();
	
	VDP_loadFont(custom_font.tileset, DMA);
	VDP_setTextPlane(BG_B);
	XGM_startPlay(music);
	sceneLogic();
	
	while(1)
	{   
		input_update_pressed();
		switch (scene_state)
		{
		case TEXTBOX:
			textboxProcess();
			break;
		case WAIT:
			wait_process();
			break;
		case PORTRAIT_SWITCH:
			portrait_switch_state();
			break;
		
		default:
			break;
		}
		portrait_process();
		animateBUDD();
		SPR_update();
		SYS_doVBlankProcess();
		bg_scroll();
		
	}
	return (0);
}

