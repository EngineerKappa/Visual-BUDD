#ifndef _BACKGROUND_H_
#define _BACKGROUND_H_

#define VIEW_SIZE 18
#define PORTRAIT_SIZE 19
u16 VRAM_ind;
u16 BG_VRAM_ind;
u16 portrait_VRAM_ind;
s16 background_x;
s16 background_y;
s16 scroll_data_b[VIEW_SIZE];
s16 scroll_data_a[PORTRAIT_SIZE];

bool palcycle_portrait_enabled;
void BG_init();
void loadBackground(Image image);
void bg_scroll();


void palcycle_process(u8 pal);



#endif // _BACKGROUND_H_