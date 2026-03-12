include($ENV{IDF_PATH}/tools/cmake/version.cmake)

set(srcs
    "src/status_led.cpp"
    "src/led_color.cpp"
    "src/gpio_led_device.cpp"
    "src/ws2812_led_device.cpp")

idf_component_register(SRCS ${srcs}
                       INCLUDE_DIRS "include"
                       REQUIRES "driver" "esp_driver_gpio" "led_strip")
