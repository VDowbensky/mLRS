//*******************************************************
// Copyright (c) MLRS project
// GPL3
// https://www.gnu.org/licenses/gpl-3.0.de.html
// OlliW @ www.olliw.eu
//*******************************************************
// Display Interface
//********************************************************
#ifndef DISP_H
#define DISP_H
#pragma once


#include "../Common/hal/hal.h"


#ifdef USE_DISPLAY

#include <stdlib.h>
#include <ctype.h>
#include "../Common/thirdparty/gfxfont.h"
#include "../Common/thirdparty/gfxfontFreeMono12pt7b.h"
#include "../Common/thirdparty/gfxfontFreeMono9pt7b.h"
#include "../Common/thirdparty/gdisp.h"


extern tGDisplay gdisp;


#define DISP_START_TMO_MS       SYSTICK_DELAY_MS(500)
#define DISP_START_PAGE_TMO_MS  SYSTICK_DELAY_MS(1500)
#define KEYS_DEBOUNCE_TMO_MS    SYSTICK_DELAY_MS(40)


typedef enum {
    PAGE_STARTUP = 0,
    PAGE_NOTIFY_BIND,
    PAGE_NOTIFY_STORE,

    // left-right navigation menu
    PAGE_MAIN,
    PAGE_COMMON,
    PAGE_TX,
    PAGE_RX,
    PAGE_ACTIONS,

    PAGE_NAV_MIN = PAGE_MAIN, // left endpoint
    PAGE_NAV_MAX = PAGE_ACTIONS, //PAGE_RX, // right endpoint

    PAGE_UNDEFINED, // this is also used to time startup page sequence
} PAGE_ENUM;


typedef enum {
    SUBPAGE_DEFAULT = 0,

    // sub pages for main page
    SUBPAGE_MAIN_SUB0 = SUBPAGE_DEFAULT,
    SUBPAGE_MAIN_SUB1,
    SUBPAGE_MAIN_SUB2,
    SUBPAGE_MAIN_SUB3,

    SUBPAGE_MAIN_NUM,
} SUBPAGE_ENUM;


    typedef struct 
	{
        uint8_t list[SETUP_PARAMETER_NUM];
        uint8_t num;
        uint8_t allowed_num[SETUP_PARAMETER_NUM];
        void clear(void) { num = 0; }
        void add(uint8_t param_idx) { list[num] = param_idx; allowed_num[num] = param_get_allowed_opt_num(param_idx); num++; }
    } tParamList;

//public:
    void tTxDisp_Init(void);
    void tTxDisp_Tick_ms(void);
    void tTxDisp_UpdateMain(void);
    void tTxDisp_SetBind(void);
    void tTxDisp_Draw(void);
    uint8_t tTxDisp_Task(void);
    void tTxDisp_DrawNotify(const char* s);
    void tTxDisp_DrawBoot(void);
    void tTxDisp_DrawFlashEsp(void);

    bool key_has_been_pressed(uint8_t key_idx);

    void tTxDisp_draw_page_startup(void);
    void tTxDisp_draw_page_notify(const char* s);
    void tTxDisp_draw_page_main(void);
    void tTxDisp_draw_page_common(void);
    void tTxDisp_draw_page_tx(void);
    void tTxDisp_draw_page_rx(void);
    void tTxDisp_draw_page_actions(void);

    void tTxDisp_draw_page_main_sub0(void);
    void tTxDisp_draw_page_main_sub1(void);
    void tTxDisp_draw_page_main_sub2(void);
    void tTxDisp_draw_page_main_sub3(void);

    void tTxDisp_draw_header(const char* s);
    void tTxDisp_draw_options(tParamList* list);
	
    void tTxDisp_load_rx_list(void);
    tParamList* tTxDisp_ current_list(void);

    void tTxDisp_page_init(void);
    bool tTxDisp_edit_setting(void);
    void tTxDisp_run_action(void);

    bool initialized;
    uint8_t task_pending;
    bool connected_last; // to detect connection changes
    bool setupmetadata_rx_available_last; // to detect changes

    uint16_t keys_tick;
    uint8_t keys_state;
    uint8_t keys_ct0;
    uint8_t keys_ct1;
    uint8_t keys_has_been_pressed;
    uint16_t keys_pressed_tmo;
    uint8_t keys_pending;

    uint8_t page;
    uint16_t page_startup_tmo;
    bool page_modified; // requires complete redraw of page
    bool page_update; // only update some elements of page

    uint8_t subpage; // for pages which may have different screens
    uint8_t subpage_max;

    uint8_t idx_first;          // index of first param displayed on page
    uint8_t idx_max;            // index of last param in list
    uint8_t idx_focused;        // index of highlighted param
    bool idx_focused_in_edit;   // if param is in edit
    uint8_t idx_focused_pos;    // pos in str6 (bind phrase) parameter
    uint8_t idx_focused_task_pending;

    tParamList common_list;
    tParamList tx_list;
    tParamList rx_list;

bool tTxDisp_key_has_been_pressed(uint8_t key_idx);
void _diversity_str(char* s, uint8_t div);
void _draw_dot2(uint8_t x, uint8_t y);

#endif // USE_DISPLAY

#endif // DISP_H


/* some timings
19.09.2023

G491RE 170 MHz
  draw   t2-t1 ca 1.5 ms (main)
  update t2-t1 ca 24 ms (determined by I2C speed)

  after optimization w O3 and page_update
  main      draw   t2-t1 ca 1.0 ms
  main/2    draw   t2-t1 ca 0 ms
  main/3    draw   t2-t1 ca 0.4 ms
  main/4    draw   t2-t1 ca 0 ms

FRM303 F072 48 MHz
  main      draw   t2-t1 ca 7 ms    w O3: ca 4.8 ms
            update t2-t1 ca 25 ms (determined by I2C speed)
  main/2    draw   t2-t1 ca 9 ms    w O3: ca 6.4 ms
  main/3    draw   t2-t1 ca 7 ms    w O3: ca 4.7 ms
  main/4    draw   t2-t1 ca 10 ms   w O3: ca 6.8 ms

  the other pages are not updated repeatedly, some take up to 14 ms
  compiling disp.h with O3 doesn't really do anything
  compiling gdisp.c with O3 helps quite a bit, costs just 1.1 kB flash, so worth it

  after optimization w O3 and page_update
  main      draw   t2-t1 ca 4.8 ms
  main/2    draw   t2-t1 ca 0 ms
  main/3    draw   t2-t1 ca 2 ms
  main/4    draw   t2-t1 ca 0 ms

  after optimization w O3 and not drawing background for 6x8 font
  main      draw   t2-t1 ca 3.0-3.2 ms
  main/2    draw   t2-t1 ca 0 ms
  main/3    draw   t2-t1 ca 2.2-2.4 ms
  main/4    draw   t2-t1 ca 0 ms
  advantage: also the other pages get significantly faster, down to 4-5 ms

  on FRM303, OLED and FLRC do not work well together

20.09.2023
  further optimization
  - no gdisp_u_() in gdisp_setpixel_()
  - func ptr for gdisp_setpixel_()
*/

