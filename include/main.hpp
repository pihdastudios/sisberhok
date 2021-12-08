#pragma once
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/event_groups.h>
// #include "esp_system.h"
// #include "esp_event.h"
#include "nvs_flash.h"
#include "driver/gpio.h"
// #include "driver/uart.h"
#include "esp_vfs_dev.h"
#include "esp_wifi.h"
#include "esp_log.h"

#include "mqtt_client.h"

#define LED_PIN GPIO_NUM_21
#define MANUAL_PIN GPIO_NUM_5
// #define DHT_PIN GPIO_NUM_23
#define BTN_PIN GPIO_NUM_2

#define EXAMPLE_ESP_WIFI_SSID "UWAW"
#define EXAMPLE_ESP_WIFI_PASS "aassddff"
#define EXAMPLE_ESP_MAXIMUM_RETRY 5

/* FreeRTOS event group to signal when we are connected*/
static EventGroupHandle_t s_wifi_event_group;

/* The event group allows multiple bits for each event, but we only care about two events:
 * - we are connected to the AP with an IP
 * - we failed to connect after the maximum amount of retries */
#define WIFI_CONNECTED_BIT BIT0
#define WIFI_FAIL_BIT BIT1

TaskHandle_t ISR = nullptr;
// TaskHandle_t MAN_ISR = nullptr;
static bool led_status = false;
static bool manual_status = false;

esp_mqtt_client_handle_t global_client = nullptr;

static void event_handler(void *arg, esp_event_base_t event_base,
                          int32_t event_id, void *event_data);
static void log_error_if_nonzero(const char *message, int error_code);
static void mqtt_event_handler(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data);
static void mqtt_app_start();
static void mqtt_set_default();

static int s_retry_num = 0;

const char TAG[] = "MQTT_EXAMPLE";

char ip_address[16];

void IRAM_ATTR button_isr_handler(void *pvParameter);
void button_task(void *pvParameter);
// void manual_task(void *pvParameter);
// void serial_task(void *pvParameter);
void init_gpio();
void init_wifi();

void update_lamp_status();

#define MQTT_ADDRESS "mqtt://broker.emqx.io:1883"

extern "C"
{
    void app_main();
}