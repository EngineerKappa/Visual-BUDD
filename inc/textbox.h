#ifndef _TEXTBOX_H_
#define _TEXTBOX_H_

#define TEXT_CHAR_LIMIT     36
#define TEXTBOX_Y			19//20
#define TEXT_START_X        2
#define TEXT_START_y        20//21 
#define TEXT_WIDTH          65
#define TEXTBOX_WIDTH       40
#define TEXTBOX_HEIGHT      9

enum MENU {
	DISABLED,
	IDLE,
  	ENTER,
  	OPENED,
  	TEXT_DRAWING,
  	TEXT_COMPLETE,
  	TEXT_CLEARING,
  	CLOSE
};


int text_copy_count;
int text_line_count;
int text_line_current;
u8 text_clear_lines;
u16 textbox_shrink_x;
u16 textbox_shrink_y;
u16 textbox_VRAM_ind;
u8 textbox_underline;
enum MENU textbox_state;
void TEXTBOX_init();

void textbox_open();
void text_clear();
void updateText();
void textboxProcess();
void text_clearing();
void draw9slice(u8 x,u8 y,u8 width, u8 height,u16 ind_start,VDPPlane plane);

Sprite* s_textbox_arrow;

char str_text[255];//"------------------------------------------------------------------------------------------------------------------------------------------------";
//We can only show roughly 144 characters in a single textbox, but we might need more for keywords.

#endif // _TEXTBOX_H_
