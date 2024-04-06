#include <genesis.h>
#include <background.h>
#include <gfx.h>
#include <portrait.h>

u16 palcycle_AB[6];
u8 palcycle_index;
u8 palcycle_wait;
bool palcycle_portrait_enabled;
bool palcycle_bg_enabled;
void palcycle_Init();
void palcycle_process(u8 pal);
u16 palette[64];




void BG_init()
{
	background_x = 0;
	background_y = 0;
	VRAM_ind = 1;
	BG_VRAM_ind = 1;
	portrait_VRAM_ind = 1;
	palcycle_Init();
	PAL_setColors(PAL1*16,palette_black,16,DMA);
	memset(scroll_data_b, 0, sizeof(scroll_data_b));
	VDP_setScrollingMode(HSCROLL_TILE,VSCROLL_PLANE);
}

void bg_scroll()
{
	for (int i=0;i<19;i++) 
		{
			scroll_data_a[i] = portrait_x;  
		}

	for (int i=0;i<VIEW_SIZE;i++) 
	{
		scroll_data_b[i] = background_x;  
	}

  		VDP_setHorizontalScrollTile(BG_B, 0, scroll_data_b, VIEW_SIZE, DMA);
		VDP_setHorizontalScrollTile(BG_A, 0, scroll_data_a, PORTRAIT_SIZE, DMA);
}

void palcycle_Init()
{
	palcycle_AB[0]=RGB24_TO_VDPCOLOR(0x000055);
	palcycle_AB[1]=RGB24_TO_VDPCOLOR(0x5500aa);
	palcycle_AB[2]=RGB24_TO_VDPCOLOR(0xaa00aa);
	palcycle_AB[3]=RGB24_TO_VDPCOLOR(0xff55aa);
	palcycle_AB[4]=RGB24_TO_VDPCOLOR(0xffaa00);
	palcycle_AB[5]=RGB24_TO_VDPCOLOR(0xffff00);
	
	palcycle_index = 0;
	palcycle_portrait_enabled = false;
	palcycle_wait = 3;
}

void palcycle_process(u8 pal)
{
	u8 col2 = palcycle_index+1;
	u8 col3 = palcycle_index+2;
	
	if (palcycle_wait == 0)
	{
		palcycle_wait=5;

		if (col2 > 5)
		col2-=5;
		if (col3 > 5)
		col3-=5;
		PAL_setColor(pal*16+13, palcycle_AB[palcycle_index]);
		PAL_setColor(pal*16+14, palcycle_AB[col2]);
		PAL_setColor(pal*16+15, palcycle_AB[col3]);
		palcycle_index++;
		if (palcycle_index>6)
		palcycle_index=0;
	}
	else
	{
		palcycle_wait--;
	}
}

void loadBackground(Image image)
{
	PAL_fadeInPalette(1,image.palette->data,30,TRUE);
	VDP_drawImageEx(BG_B, &image, TILE_ATTR_FULL(PAL1, false, false, false, BG_VRAM_ind),0,1,false,TRUE);
	VRAM_ind = BG_VRAM_ind+image.tileset->numTile;
	portrait_VRAM_ind=VRAM_ind;
	waitMs(800);
}