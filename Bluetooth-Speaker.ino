#include <driver/i2s.h>
#include <BluetoothA2DPSink.h>

// Define pins
#define I2S_BCLK GPIO7
#define I2S_LRCLK GPIO8
#define I2S_DOUT GPIO6
#define LOW_BATTERY_LED GPIO9
#define BUTTON_PIN GPIO21
#define ADC_PIN GPIO3

#define LOW_BATTERY_THRESHOLD 3300  // 3.3V in millivolts
//Voltage divider setup R1=10kOhm R2=2.2kOhm
#define VOLTAGE_DIVIDER_FACTOR 10000/2200    // 1 if directly connected, else Battery+ -[R1]- GPIO3 -[R2]- GND

#define DEBOUNCE_TIME 200  // Debounce time in milliseconds

BluetoothA2DPSink a2dp_sink;

void setup() {
  Serial.begin(115200);
  
  // Configure I2S for MAX98357
  i2s_config_t i2s_config = {
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX),
    .sample_rate = 44100,
    .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
    .channel_format = I2S_CHANNEL_FMT_ONLY_RIGHT, // Mono output
    .communication_format = I2S_COMM_FORMAT_I2S,
    .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
    .dma_buf_count = 8,
    .dma_buf_len = 64
  };
  i2s_driver_install(I2S_NUM_0, &i2s_config, 0, NULL);
  i2s_pin_config_t pin_config = {
    .bck_io_num = I2S_BCLK,
    .ws_io_num = I2S_LRCLK,
    .data_out_num = I2S_DOUT,
    .data_in_num = I2S_PIN_NO_CHANGE
  };
  i2s_set_pin(I2S_NUM_0, &pin_config);

  // Configure Bluetooth
  a2dp_sink.start("My Speaker");

  // Configure pins
  pinMode(LOW_BATTERY_LED, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  // ADC setup for battery monitoring
  analogReadResolution(12);
}

void loop() {
  static unsigned long lastUpdateTime = 0;

  // Check battery voltage every second
  if (millis() - lastUpdateTime > 1000) {
    lastUpdateTime = millis();  // Update last check time

    // Read battery voltage
    int adcReading = analogRead(ADC_PIN);
    float batteryVoltage = (adcReading * 3.3 / 4095) * VOLTAGE_DIVIDER_FACTOR;  // Convert to actual voltage

    // Check against threshold
    if (batteryVoltage < (LOW_BATTERY_THRESHOLD / 1000.0)) {
      digitalWrite(LOW_BATTERY_LED, HIGH);  // Turn on LED
    } else {
      digitalWrite(LOW_BATTERY_LED, LOW);   // Turn off LED
    }

    // Debugging
    Serial.print("ADC Reading: ");
    Serial.println(adcReading);
    Serial.print("Battery Voltage: ");
    Serial.println(batteryVoltage);
  }

  // Handle button press
  static unsigned long lastPressTime = 0;

  // Check if button is pressed
  if (digitalRead(BUTTON_PIN) == LOW) {
    // Check if debounce time has passed
    if (millis() - lastPressTime > DEBOUNCE_TIME) {
      lastPressTime = millis();  // Update the last press time
      Serial.println("Button pressed. Toggling power...");
      a2dp_sink.stop();          // Stop Bluetooth streaming
      esp_sleep_enable_ext0_wakeup(GPIO_NUM_21, 0); // Wake on button press
      ESP.deepSleep(0);          // Enter deep sleep mode
    }
  }
}
