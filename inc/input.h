#ifndef _INPUT_H_
#define _INPUT_H_

u16 joypad_data;
u16 joypad_data_previous;

void input_update_pressed();
void input_update();
bool inputConfirm();
bool inputConfirmPressed();
bool inputBack();
bool inputBackPressed();

#endif // _INPUT_H_
