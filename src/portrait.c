#include <genesis.h>
#include <shared.h>
#include <portrait.h>
#include <textbox.h>
#include <gfx.h>
#include <background.h>
#include <scene.h>

void portrait_init()
{
	actor_current = NONE;
	portrait_x = PORTRAIT_X_CENTER;
	portrait_y = PORTRAIT_Y_DEFAULT;
	portrait_target_x = portrait_x;
	portrait_target_y = portrait_y;
	portrait_move_speed = 1;
	portrait_blink_x = 88; //Relative to the sprite itself
	portrait_blink_y = 48; //Relative to the sprite itself
	portrait_blink_timer = 255;
	portrait_mouth_x = 96;
	portrait_mouth_y = 64;
	portrait_mouth_timer = 0;
	portrait_actor = NONE;
	portrait_switch_time = 0;
	portrait_slot = 0;
	
	portrait_budd = NONE;
	budd_x = 56;
	budd_y = 64;
	budd_blink_timer = 512;
	budd_float_timer = 0;
	//VDP_setHorizontalScroll(BG_A,portrait_x);
	PAL_setColors(PAL2*16,palette_black,16,DMA);
}

void portrait_retrieve(enum ACTOR actor, enum POSE pose)
{
	
	for (size_t i = 0; i < 3; i++)
	{
		if (portrait_list[i].actor == actor && portrait_list[i].pose == pose)
		{
			
			if (portrait_list[i].portrait_budd!=NONE)
			{
				SPR_setVisibility(portrait_list[i].portrait_budd_sprite,VISIBLE);	
			}
			
			if (portrait_list[portrait_slot].portrait_budd!=portrait_list[i].portrait_budd)
			{
				SPR_setVisibility(portrait_list[portrait_slot].portrait_budd_sprite,HIDDEN);
			}
			portrait_slot=i;
			portrait_actor=actor;
			portrait_x=portrait_list[portrait_slot].x;
			
			
			PAL_fadeInPalette(2,portrait_list[i].image.palette->data,8,TRUE);
			VDP_setTileMapEx(BG_A,portrait_list[i].image.tilemap,TILE_ATTR_FULL(PAL2, false, false, false, portrait_list[i].tileset_ind),0,0,0,0,portrait_list[i].map_width,portrait_list[i].map_height,DMA_QUEUE);
			
		}
	}
}

struct AnimRegion portrait_anim_init(u8 width, u8 height,u8 frames, u16 source_x, u16 source_y, u16 destination_x, u16 destination_y,u8 frame_delay)
{
	struct AnimRegion _region;
	_region.width=width;
	_region.height=height;
	_region.frames=frames;
	_region.source_x=source_x;
	_region.source_y=source_y;
	_region.destination_x=destination_x;
	_region.destination_y=destination_y;
	_region.frame_delay=frame_delay;

	return _region;
}

void portrait_preload(u8 slot, enum ACTOR actor, enum POSE pose)
{
	struct Portrait *_pslot = &portrait_list[slot];

	if (_pslot->actor == actor && _pslot->pose == pose)
	return;	

	if (slot == 0)
		VRAM_ind=portrait_VRAM_ind;

	_pslot->actor=actor;
	_pslot->pose=pose;

	switch (actor)
    {
    case ERIS:
		_pslot->x = PORTRAIT_X_CENTER_BUDD;
		_pslot->y = PORTRAIT_Y_DEFAULT;
		_pslot->map_width = 27;
		_pslot->map_height = 20;
		_pslot->image=portrait_eris_1;
		_pslot->portrait_budd=BOXER;
		_pslot->talk_anim=portrait_anim_init(3,2,3,13,20,12,9,5);
        break;

    case MAYA:
		_pslot->x = PORTRAIT_X_CENTER;
		_pslot->y = PORTRAIT_Y_DEFAULT;
		_pslot->image=portrait_maya_1;
		_pslot->map_width = 27;
		_pslot->map_height = 20;
		_pslot->portrait_budd=NONE;
		_pslot->talk_anim=portrait_anim_init(0,0,0,0,0,0,0,0);
        break;
	
	case CERES:
		_pslot->x = PORTRAIT_X_CENTER_BUDD;
		_pslot->y = PORTRAIT_Y_DEFAULT;
		_pslot->image=portrait_ceres_1;
		_pslot->map_width = 27;
		_pslot->map_height = 20;
		_pslot->portrait_budd=STRATOS;
		_pslot->talk_anim=portrait_anim_init(0,0,0,0,0,0,0,0);
        break;
    default:
        break;
	}
	VDP_loadTileSet(_pslot->image.tileset,VRAM_ind,DMA);
	_pslot->tileset_ind=VRAM_ind;
    VRAM_ind+=_pslot->image.tileset->numTile;
}

void portrait_load(Image image)
{
	portrait_blink_timer = 255;
	portrait_target_x = portrait_x;
	portrait_target_y = portrait_y;
	
	VDP_drawImageEx(BG_A, &image, TILE_ATTR_FULL(PAL2, false, false, false, portrait_VRAM_ind),0,0,false,TRUE);
	PAL_fadeInPalette(2,image.palette->data,8,TRUE);
	//PAL_setPalette(PAL2, image.palette->data, DMA);
	
	VRAM_ind += image.tileset->numTile;
}

void portrait_anim_play(u8 slot, struct AnimRegion *region)
{
	
	portrait_anim_set_frame(slot, region, region->current_frame);

	region->frame_wait++;
	if (region->frame_wait>=region->frame_delay)
	{
		region->frame_wait=0;
		region->current_frame++;

		if (region->current_frame >= region->frames)
		region->current_frame=0;
	}

	if (region->frame_wait==0)
	{
		portrait_anim_set_frame(slot, region, region->current_frame);
	}
}

void portrait_anim_set_frame(u8 slot, struct AnimRegion *region, u8 frame)
{
	if (region->frames == 0)
	return;
	VDP_setTileMapEx(BG_A,portrait_list[slot].image.tilemap,TILE_ATTR_FULL(PAL2, false, false, false, portrait_list[slot].tileset_ind),region->destination_x,region->destination_y,region->source_x + (frame * region->width),region->source_y,region->width,region->height,DMA_QUEUE);
}

void portrait_free()
{
	PAL_setColors(PAL2*16,palette_black,16,DMA);
	VDP_clearPlane(BG_A,true);
	portrait_x = PORTRAIT_X_CENTER;
	portrait_y = PORTRAIT_Y_DEFAULT;
	/*
	if (portrait_actor!=NONE)
	{
		SPR_releaseSprite(s_portrait_blink);
		SPR_releaseSprite(s_portrait_mouth);
		
	}
	if (portrait_budd!=NONE)
	SPR_releaseSprite(s_portrait_budd);
	
	SPR_update();
	*/
	portrait_actor = NONE;
	SPR_defragVRAM();
}

void portrait_switch(enum ACTOR actor, enum POSE pose)
{
	scene_state=PORTRAIT_SWITCH;
	textbox_state=DISABLED;
	portrait_switch_actor=actor;
	portrait_switch_pose=pose;
	
	PAL_fadeOutPalette(2,6,TRUE);
	portrait_switch_time=0;
	palcycle_portrait_enabled=false;
}

void portrait_switch_state()
{
	switch (portrait_switch_time)
	{
	case 8:
		portrait_retrieve(portrait_switch_actor, portrait_switch_pose);
		;
		break;
	case 9:
		portrait_switch_time=0;
		if (portrait_actor == CERES)
			palcycle_portrait_enabled=true;
		sceneLogic();
		break;
	default:
		break;
	}
	portrait_switch_time++;
}

void portrait_process()
{
	if (portrait_actor == NONE)
	return;
	portrait_anim_play(portrait_slot,&portrait_list[portrait_slot].talk_anim);
	if (palcycle_portrait_enabled) 
	{
		palcycle_process(PAL2);
	}
	
	

	if (portrait_mouth_timer>0)
	portrait_mouth_timer--;


	
	/*
	
	portrait_x-=max(portrait_x-portrait_target_x,-portrait_move_speed);
	portrait_y-=max(portrait_y-portrait_target_y,-portrait_move_speed);
	if ((scene_state == PORTRAIT_MOVE) && (portrait_x == portrait_target_x) && (portrait_y == portrait_target_y))
		sceneLogic();

	portrait_blink_timer--;

	if (portrait_blink_timer == 4)
		SPR_setAnim(s_portrait_blink,1);
	if (portrait_blink_timer == 0)
	{
		SPR_setAnim(s_portrait_blink,0);
		portrait_blink_timer = random() % ( 600 - 8 + 1) + 8;
	}
	SPR_setPosition(s_portrait_blink ,portrait_x+portrait_blink_x,-portrait_y+portrait_blink_y);
	SPR_setPosition(s_portrait_mouth,portrait_x+portrait_mouth_x,-portrait_y+portrait_mouth_y);
	
	VDP_setHorizontalScroll(BG_A,portrait_x);
	VDP_setVerticalScroll(BG_A,portrait_y);
	*/
}

void animateBUDD()
{
	/*if (portrait_budd==NONE) //Checks for the main portrait, replace when we get a BUDD variable
	return;

	budd_blink_timer--;
	budd_float_timer=budd_float_timer+4 % 360;
	if (budd_blink_timer == 4)
		SPR_setAnim(s_portrait_budd,1);

	if (budd_blink_timer == 0)
	{
		SPR_setAnim(s_portrait_budd,0);
		budd_blink_timer = 255;
	}
	SPR_setPosition(s_portrait_budd,budd_x,budd_y+((sinFix16(budd_float_timer)/4)));
	*/
}