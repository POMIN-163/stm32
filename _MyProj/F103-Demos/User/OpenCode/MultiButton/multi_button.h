/*
 * Copyright (c) 2016 Zibin Zheng <znbin@qq.com>
 * All rights reserved
 */

#ifndef _MULTI_BUTTON_H_
#define _MULTI_BUTTON_H_

#include "stdint.h"
#include "string.h"

//According to your need to modify the constants.
#define TICKS_INTERVAL    1	// ms
#define DEBOUNCE_TICKS    3	// MAX 8
#define SHORT_TICKS       (100 /TICKS_INTERVAL)
#define LONG_TICKS        (1000 /TICKS_INTERVAL)


typedef void (*BtnCallback)(void*); // 回调
extern uint8_t buttonNum;           // 按键序号

typedef enum {
	PRESS_DOWN = 0,   // 按键按下，每次按下都触发
	PRESS_UP,         // 按键弹起，每次松开都触发
	PRESS_REPEAT,     // 变量 repeat 计数连击次数 (阈值由TICKS宏控制)
	SINGLE_CLICK,     // 单击按键事件
	DOUBLE_CLICK,     // 双击按键事件
	LONG_PRESS_START, // 达到长按时间词值时触发一次
	LONG_PRESS_HOLD,  // 长段期间一直触发
	number_of_event,
	NONE_PRESS
}PressEvent;





typedef struct Button {
	uint16_t ticks;
	uint8_t  repeat : 4;
	uint8_t  event : 4;
	uint8_t  state : 3;
	uint8_t  debounce_cnt : 3;
	uint8_t  active_level : 1;
	uint8_t  button_level : 1;
	uint8_t  (*hal_button_Level)(void);
	BtnCallback  cb[number_of_event];
	struct Button* next;
}Button;

#ifdef __cplusplus
extern "C" {
#endif

void button_init(struct Button* handle, uint8_t(*pin_level)(), uint8_t active_level);
void button_attach(struct Button* handle, PressEvent event, BtnCallback cb);
PressEvent get_button_event(struct Button* handle);
int  button_start(struct Button* handle);
void button_stop(struct Button* handle);
void button_ticks(void);

#ifdef __cplusplus
}
#endif

#endif
