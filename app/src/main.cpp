#include <zephyr/drivers/gpio.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/init.h>
#include <stdio.h>
#define MY_INIT_PRIO 32
#define SYS_INIT(executeBeforeMain, APPLICATION, MY_INIT_PRIO); 
#define SLEEP_TIME_MS CONFIG_APP_HEARTBEAT_PERIOD_MS
#define LED_NODE DT_ALIAS(app_led)

static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED_NODE, gpios);
static int executeBeforeMain(void) {
    printf("This is a function that executes before main() is called.\n");
    return 0;
}
LOG_MODULE_REGISTER(main, LOG_LEVEL_INF);

int main(void)
{
    //bool led_state = true;
    bool led_state = false;

    if (!gpio_is_ready_dt(&led)) return 0;

    if (gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE) < 0) return 0;

    while (1) {
        if (gpio_pin_toggle_dt(&led) < 0) return 0;

        led_state = !led_state;
        LOG_INF("LED state: %s", led_state ? "ON" : "OFF");
        k_msleep(SLEEP_TIME_MS);
    }
    return 0;
}
