#include "display.h"

#include <stdint.h>
#include <stdio.h>

#include "forward.h"
#include "lcd.h"
#include "lcd_driver.h"
#include "lcd_fonts.h"
#include "nmea.h"
#include "stm32f4xx_hal.h"

void get_device_id_str(char* buf) {
    sprintf(buf,
            "%02X%02X%02X%02X-%02X%02X%02X%02X-%02X%02X%02X%02X",
            HEXIFY_U32(HAL_GetUIDw0()),
            HEXIFY_U32(HAL_GetUIDw1()),
            HEXIFY_U32(HAL_GetUIDw2()));
}

// Interface
void display_init(void) {
    ILI9341_Init();
    ILI9341_FillScreen(WHITE);
    ILI9341_SetRotation(SCREEN_VERTICAL_2);

    HAL_Delay(100);
    char id_string[50];
    get_device_id_str(id_string);
    ILI9341_DrawText("Device:", FONT2, 5, 5, BLUE, WHITE);
    ILI9341_DrawText(id_string, FONT1, 5, 20, BLACK, WHITE);
}

void display_update() {
    static char gps_string[50];
    static char time_string[50];

    const nmea_sentence_t* gps_sent = nmea_get_last_sentence();
    sprintf(gps_string,
            "Lat: %d.%.02f%c, Lon: %d.%.02f%c",
            gps_sent->lat.deg,
            gps_sent->lat.min,
            gps_sent->lat.dir,
            gps_sent->lon.deg,
            gps_sent->lon.min,
            gps_sent->lon.dir);

    sprintf(time_string,
            "Time: %02d:%02d:%02d.%02f",
            gps_sent->timestamp.hr,
            gps_sent->timestamp.min,
            gps_sent->timestamp.sec,
            gps_sent->timestamp.subsec);

    ILI9341_DrawText("GPS:", FONT2, 5, 40, BLUE, WHITE);
    ILI9341_DrawText(gps_string, FONT1, 5, 55, BLACK, WHITE);
    ILI9341_DrawText(time_string, FONT1, 5, 70, BLACK, WHITE);
}
