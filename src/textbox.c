#include <genesis.h>
#include <textbox.h>
#include <input.h>
#include <gfx.h>
#include <background.h>
#include <portrait.h>
#include <scene.h>

void TEXTBOX_init(void)
{
    text_copy_count = 0;
    text_line_count = 0;
    text_line_current = 0;
	text_clear_lines = 0;
    textbox_shrink_x = TEXTBOX_WIDTH-2; //if these are low enough, it underflows, so uh... careful
    textbox_shrink_y = TEXTBOX_HEIGHT-2;
    textbox_state = DISABLED;
	textbox_underline = 0;
 	
	textbox_VRAM_ind = 1; //UI tiles are loaded before the background or the portraits
	PAL_setPalette(PAL0, frame.palette->data, DMA);
	VDP_drawImageEx(BG_B, &frame, TILE_ATTR_FULL(PAL0, false, false, false, VRAM_ind),40,21,false,TRUE);
	
	VRAM_ind += frame.tileset->numTile;
	BG_VRAM_ind = VRAM_ind;

	s_textbox_arrow = SPR_addSprite(&textbox_arrow,304,208, TILE_ATTR(PAL0,true,false,false));

	SPR_setAnim(s_textbox_arrow, 0);
	SPR_setVisibility(s_textbox_arrow,HIDDEN);
}



void draw9slice(u8 x,u8 y,u8 width, u8 height,u16 ind_start,VDPPlane plane)
{
	//top left
	VDP_setTileMapXY(plane, TILE_ATTR_FULL(PAL0, TRUE, FALSE, FALSE, ind_start),x,y);
	//top
	VDP_fillTileMapRect(plane,TILE_ATTR_FULL(PAL0, TRUE, FALSE, FALSE, ind_start+1),x+1,y,width-2,1);
	//top right
	VDP_setTileMapXY(plane, TILE_ATTR_FULL(PAL0, TRUE, FALSE, FALSE, ind_start+2),x+width-1,y);
	//left
	VDP_fillTileMapRect(plane,TILE_ATTR_FULL(PAL0, TRUE, FALSE, FALSE, ind_start+3),x,y+1,1,height-2);
	//center
	VDP_fillTileMapRect(plane,TILE_ATTR_FULL(PAL0, TRUE, FALSE, FALSE, ind_start+4),x+1,y+1,width-2,height-2);
	//right
	VDP_fillTileMapRect(plane,TILE_ATTR_FULL(PAL0, TRUE, FALSE, FALSE, ind_start+5),x+width-1,y+1,1,height-2);
	//bottom left
	VDP_setTileMapXY(plane, TILE_ATTR_FULL(PAL0, TRUE, FALSE, FALSE, ind_start+6),x,y+height-1);
	//bottom
	VDP_fillTileMapRect(plane,TILE_ATTR_FULL(PAL0, TRUE, FALSE, FALSE, ind_start+7),x+1,y+height-1,width-2,1);
	//bottom right
	VDP_setTileMapXY(plane, TILE_ATTR_FULL(PAL0, TRUE, FALSE, FALSE, ind_start+8),x+width-1,y+height-1);
}

void textbox_open()
{

	draw9slice(0,TEXTBOX_Y,TEXTBOX_WIDTH-textbox_shrink_x,TEXTBOX_HEIGHT-textbox_shrink_y,textbox_VRAM_ind,BG_B);

	if (textbox_shrink_x == 0)
	{
		textbox_state=IDLE;
		sceneLogic();
	}

	textbox_shrink_x=clamp(textbox_shrink_x-3,0,TEXTBOX_WIDTH-3);
	textbox_shrink_y=clamp(textbox_shrink_y-1,0,TEXTBOX_HEIGHT-3);
}

void text_clearing()
{
	u8 scroll_speed = 5;

	if (inputBack())
	{
		text_clear_lines=TEXT_CHAR_LIMIT;
	}
	
	for (size_t i = 0; i < scroll_speed; i++)
	{
		VDP_fillTileMapRect(BG_B,TILE_ATTR_FULL(PAL0, TRUE, FALSE, FALSE, textbox_VRAM_ind+4),TEXT_START_X,TEXT_START_y,min(text_clear_lines+4,TEXT_CHAR_LIMIT),7);
		text_clear_lines++;
		if (text_clear_lines > TEXT_CHAR_LIMIT)
		{
			text_clear_lines=0;
			sceneLogic();
		}
	}
}

void text_clear()
{
	draw9slice(0,TEXTBOX_Y,TEXTBOX_WIDTH-textbox_shrink_x,TEXTBOX_HEIGHT-textbox_shrink_y,textbox_VRAM_ind,BG_B);
	text_copy_count=0;
	text_line_count=0;
	text_line_current=0;
	
}

bool textbox_find_keyword(char source_string[], u8 position, char keyword[])
{
	u8 keyword_length = strlen(keyword);
	u8 source_length = strlen(source_string);

	for (size_t i = 1; i < keyword_length; i++) //If we've already checked for [, we can just skip the first character. We also don't need to check the other bracket
	{
		if (position+i > source_length)
		return false;
		if (source_string[position+i]!=keyword[i]) 
		return false;
	}
	text_copy_count+=keyword_length;
	return true;
}

inline void textbox_line_break()
{
	text_line_count=0;
	text_line_current++;
}

bool textbox_keywords()
{
	if (textbox_find_keyword(str_text,text_copy_count,"#!"))
	{
		textbox_underline=1;
		return true;
	}

	if (textbox_find_keyword(str_text,text_copy_count,"#<3"))	
	{
		VDP_setTileMapXY(BG_B, TILE_ATTR_FULL(PAL0, TRUE, FALSE, FALSE, textbox_VRAM_ind+12),TEXT_START_X+text_line_count,TEXT_START_y+text_line_current*2);
		text_line_count++;
		return true;
	}

	if (textbox_find_keyword(str_text,text_copy_count,"#P"))
	{
		textbox_underline=2;
		return true;
	}

	if (textbox_find_keyword(str_text,text_copy_count,"#L"))
	{
		textbox_underline=3;
		return true;
	}

	if (textbox_find_keyword(str_text,text_copy_count,"#/"))
	{
		textbox_underline=0;
		return true;
	}
	return false;
}

void textbox_draw_char(char* destination_char)
{
	VDP_setTileMapXY(BG_B, TILE_ATTR_FULL(PAL0, TRUE, FALSE, FALSE, TILE_FONT_INDEX-' '+*destination_char),TEXT_START_X+text_line_count,TEXT_START_y+text_line_current*2);
	if (textbox_underline>0)
	VDP_setTileMapXY(BG_B, TILE_ATTR_FULL(PAL0, TRUE, FALSE, FALSE, textbox_VRAM_ind+8+textbox_underline),TEXT_START_X+text_line_count,TEXT_START_y+1+text_line_current*2);

}

void updateText(){
	u8 string_length = strlen(str_text);
	char *char_current;
	u8 chars_drawn = 1;

	if (inputConfirm())
		chars_drawn=min(3,string_length-text_copy_count);
	if (inputBack())
	{
		chars_drawn=string_length-text_copy_count;
		textbox_state = TEXT_COMPLETE;
		SPR_setVisibility(s_textbox_arrow,VISIBLE);
	}
	//start drawing the text
	for (size_t i = 0; i < chars_drawn; i+=1)
	{
		char_current=&str_text[text_copy_count];

		switch (*char_current)
		{
			case '#': 
				if (textbox_keywords())
			continue;

			case '\0':
				textbox_state = TEXT_COMPLETE;
				SPR_setVisibility(s_textbox_arrow,VISIBLE);
			return;

			case '\n':
				textbox_line_break();
				text_copy_count++;
			continue;
					
			default:
				textbox_draw_char(char_current);
			break;
		}

		text_copy_count++;
		text_line_count++;

		if ((text_line_count>=TEXT_CHAR_LIMIT))
		textbox_line_break();
	}
	return;
}

void textboxProcess()
{
	switch (textbox_state)
	{
	case TEXT_COMPLETE:
		if (inputConfirmPressed())
		{
			SPR_setVisibility(s_textbox_arrow,HIDDEN);
			textbox_state=TEXT_CLEARING;
		}
		break;
	case TEXT_DRAWING:
		updateText();
		break;
	case ENTER:
		textbox_open();
		break;
	case TEXT_CLEARING:
		text_clearing();
		break;
	default:
		break;
	}

	
}
