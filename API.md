# API Reference

## Header files

- [led_color.hpp](#file-led_colorhpp)
- [status_led.hpp](#file-status_ledhpp)
- [status_led/gpio_led_device.hpp](#file-status_ledgpio_led_devicehpp)
- [status_led/led_device.hpp](#file-status_ledled_devicehpp)
- [status_led/ws2812_led_device.hpp](#file-status_ledws2812_led_devicehpp)

## File led_color.hpp






## Classes

| Type | Name |
| ---: | :--- |
| class  | [**LedColor**](#class-ledcolor)  <br>[_**LedColor**_](#class-ledcolor)_ class._ |





## Classes Documentation

### class `LedColor`

[_**LedColor**_](#class-ledcolor)_ class._

This class is used to represent the RGB color of a LED

Variables:

-  uint8\_t b_  

-  uint8\_t g_  

-  uint8\_t r_  





## File status_led.hpp






## Classes

| Type | Name |
| ---: | :--- |
| class  | [**StatusLed**](#class-statusled)  <br>[_**StatusLed**_](#class-statusled)_ class._ |





## Classes Documentation

### class `StatusLed`

[_**StatusLed**_](#class-statusled)_ class._

This class is used to control a RGB Status LED.

Variables:

-  const [**LedColor**](#class-ledcolor) kBlue  

-  const [**LedColor**](#class-ledcolor) kDefaultColor  

-  const [**LedColor**](#class-ledcolor) kGreen  

-  const [**LedColor**](#class-ledcolor) kOrange  

-  const int kQueueSize  

-  const [**LedColor**](#class-ledcolor) kRed  

-  const char \* kTag  

-  const int kThreadStackSize  

-  const int kTimeUnitMs  

-  const [**LedColor**](#class-ledcolor) kWhite  

-  std::unique\_ptr&lt; [**status\_led::LedDevice**](#class-status_ledleddevice) &gt; ledDevice_  <br>_Underlying LED device implementation._

-  QueueHandle\_t queue_  

-  TaskHandle\_t task_  





## File status_led/gpio_led_device.hpp





## Namespaces

| Type | Name |
| ---: | :--- |
| namespace  | [**status\_led**](#namespace-status_led)  <br>_Abstract LED device interface._ |

## Classes

| Type | Name |
| ---: | :--- |
| class  | [**GpioLed**](#class-status_ledgpioled)  <br>_RGB LED implementation backed by discrete GPIO channels._ |




## Namespaces Documentation

### namespace `status_led`

_Abstract LED device interface._

## Classes Documentation

### class `status_led::GpioLed`

_RGB LED implementation backed by discrete GPIO channels._

Variables:

-  bool inverse_  

-  gpio\_num\_t pin_  





## File status_led/led_device.hpp





## Namespaces

| Type | Name |
| ---: | :--- |
| namespace  | [**status\_led**](#namespace-status_led)  <br>_Abstract LED device interface._ |

## Classes

| Type | Name |
| ---: | :--- |
| class  | [**LedDevice**](#class-status_ledleddevice)  <br> |




## Namespaces Documentation

### namespace `status_led`

_Abstract LED device interface._

## Classes Documentation

### class `status_led::LedDevice`





## File status_led/ws2812_led_device.hpp





## Namespaces

| Type | Name |
| ---: | :--- |
| namespace  | [**status\_led**](#namespace-status_led)  <br>_Abstract LED device interface._ |

## Classes

| Type | Name |
| ---: | :--- |
| class  | [**Ws2812Led**](#class-status_ledws2812led)  <br>_WS2812/NeoPixel LED implementation._ |




## Namespaces Documentation

### namespace `status_led`

_Abstract LED device interface._

## Classes Documentation

### class `status_led::Ws2812Led`

_WS2812/NeoPixel LED implementation._

Variables:

-  led\_strip\_handle\_t ledStrip_  

-  gpio\_num\_t pin_  





