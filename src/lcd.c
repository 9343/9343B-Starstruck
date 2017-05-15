#include <API.h>
#include <input.h>
#include <string.h>

int state = 0;
int current_file = 0;
char available_files[8][9] = {"autoprog"};
int max_files = 8;

void UpdateLCDButtons()
{
    if(!isOnline()) {
        state = lcdReadButtons(uart1) - state;
        if(state < 0) state = 0;
    } else {
        state = 0;
    }
}

void lcd_thread(void* v)
{
    while(true)
    {
        UpdateLCDButtons();

        if(state && LCD_BTN_LEFT) {
            if(current_file == 0) {
                current_file = max_files;
            }
            current_file--;
            lcdClear(uart1);
        }

        if(state && LCD_BTN_RIGHT) {
            current_file++;
            if(current_file == max_files) {
                current_file = 0;
            }
            lcdClear(uart1);
        }

        if(state && LCD_BTN_CENTER) {
            lcdClear(uart1);
            while(true) {
                UpdateLCDButtons();

                if(state && LCD_BTN_CENTER) break;

                if(state && LCD_BTN_LEFT) {
                    lcdClear(uart1);
                    lcdSetText(uart1, 1, "   LOADING...   ");

                    autonomous_load(available_files[current_file]);

                    break;
                }

                if(state && LCD_BTN_RIGHT) {
                    lcdClear(uart1);
                    lcdSetText(uart1, 1, "   SAVING...    ");

                    autonomous_save(available_files[current_file]);

                    break;
                }

                lcdSetText(uart1, 2, "LOAD  BACK  SAVE");
            }
        }

        lcdPrint(uart1, 1, "    %8s    ", available_files[current_file]);
        lcdSetText(uart1, 2, "PREV  MENU  NEXT");
    }
}

void lcd_init()
{
    taskCreate(lcd_thread, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
}
