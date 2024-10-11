include($ENV{IDF_PATH}/tools/cmake/version.cmake)

set(srcs "src/status_led.cpp" "src/led_device.cpp")

idf_component_register(SRCS ${srcs}
                       INCLUDE_DIRS "include"
                       REQUIRES "driver")
