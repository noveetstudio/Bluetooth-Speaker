#include <LilyGo_RGBPanel.h>
#include <LV_Helper.h>
#include "ui.h"

int number = 100;

// Create an instance for the RGB panel
LilyGo_RGBPanel rgbPanel;

void setup() {
    Serial.begin(115200);

    // Initialize the RGB panel
    bool rslt = rgbPanel.begin();

    if (!rslt) {
        while (1) {
            Serial.println("The board model cannot be detected. Please raise the Core Debug Level to an error.");
            delay(1000);
        }
    }

    // Initialize LVGL helper with the RGB panel
    beginLvglHelper(rgbPanel);

    // Initialize the UI created in Squareline Studio
    ui_init();

    // Optional: Set brightness for the RGB display
    rgbPanel.setBrightness(16); // Adjust brightness as needed
}

void loop() {
    // Handle LVGL tasks
    lv_task_handler();
    delay(5);
}
