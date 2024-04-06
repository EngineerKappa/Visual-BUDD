#include <genesis.h>
#include <input.h>
#include <gfx.h>

inline void input_update()
{
	joypad_data = JOY_readJoypad(JOY_1);
}

void input_update_pressed()
{
	
	if (mouse_enabled)
	{
		cursor_x=clamp(JOY_readJoypadX(PORT_1)/2,0,VDP_getScreenWidth()-2);
		cursor_y=clamp(JOY_readJoypadY(PORT_1)/2,0,VDP_getScreenHeight()-2);
		JOY_writeJoypadX(PORT_1, cursor_x*2);
		JOY_writeJoypadY(PORT_1, cursor_y*2);
		SPR_setPosition(s_mouse_cursor,cursor_x,cursor_y);
	}
	joypad_data_previous = joypad_data;
	input_update();
}

bool inputConfirm()
{
	switch (mouse_enabled)
	{
		case true:
		return (joypad_data & BUTTON_LMB);
	default:
		return (joypad_data & BUTTON_A) || (joypad_data & BUTTON_C);
	}
	
}

bool inputConfirmPressed()
{
	bool apress = ((joypad_data ^ joypad_data_previous) & BUTTON_A) && ((joypad_data) & BUTTON_A);
	bool cpress = ((joypad_data ^ joypad_data_previous) & BUTTON_C) && ((joypad_data) & BUTTON_C);

	switch (mouse_enabled)
	{
		case true:
		return apress;
	default:
		return apress || cpress;
	}
	
}

bool inputBack()
{
	switch (mouse_enabled)
	{
		case true:
		return (joypad_data & BUTTON_RMB);
		break;
	
	default:
		return (joypad_data & BUTTON_B);
		break;
	}
	
}

bool inputBackPressed()
{
	switch (mouse_enabled)
	{
		case true:
		return ((joypad_data ^ joypad_data_previous) & BUTTON_RMB) && ((joypad_data) & BUTTON_RMB);
		break;
	
	default:
		return ((joypad_data ^ joypad_data_previous) & BUTTON_B) && ((joypad_data) & BUTTON_B);
		break;
	}
}

void input_init()
{

	cursor_x = VDP_getScreenWidth() / 2;
	cursor_y = VDP_getScreenHeight() / 2;
	mouse_enabled = false;
	if (JOY_getPortType(PORT_1) == PORT_TYPE_MOUSE)
	{
		JOY_setSupport(PORT_1, JOY_SUPPORT_MOUSE);
		mouse_enabled = true;
		s_mouse_cursor=SPR_addSprite(&mouse_cursor,cursor_x,cursor_y,TILE_ATTR(PAL0,true,false,false));
	}
}