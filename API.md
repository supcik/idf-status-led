# API Reference

## Header files

- [status_led.hpp](#file-status_ledhpp)
- [status_led/led_device.hpp](#file-status_ledled_devicehpp)

## File status_led.hpp






## Classes

| Type | Name |
| ---: | :--- |
| class  | [**LedColor**](#class-ledcolor)  <br>[_**LedColor**_](#class-ledcolor)_ class._ |
| class  | [**StatusLed**](#class-statusled)  <br>[_**StatusLed**_](#class-statusled)_ class._ |





## Classes Documentation

### class `LedColor`

[_**LedColor**_](#class-ledcolor)_ class._

This class is used to represent the RGB color of a LED

Variables:

-  uint8\_t b_  <br>_Blue component._

-  uint8\_t g_  <br>_Green component._

-  uint8\_t r_  <br>_Red component._

### class `StatusLed`

[_**StatusLed**_](#class-statusled)_ class._

This class is used to control a RGB Status LED.

Variables:

-  const [**LedColor**](#class-ledcolor) kBlue  <br>_Predefined blue color constant._

-  const [**LedColor**](#class-ledcolor) kDefaultColor  <br>_Default color constant._

-  const [**LedColor**](#class-ledcolor) kGreen  <br>_Predefined green color constant._

-  const [**LedColor**](#class-ledcolor) kOrange  <br>_Predefined orange color constant._

-  const int kQueueSize

-  const [**LedColor**](#class-ledcolor) kRed  <br>_Predefined red color constant._

-  const char \* kTag

-  const int kThreadStackSize

-  const int kTimeUnitMs

-  const [**LedColor**](#class-ledcolor) kWhite  <br>_Predefined white color constant._

-  [**status\_led::LedDevice**](#class-status_ledleddevice) & ledDevice_  <br>_Underlying LED device implementation._

-  QueueHandle\_t queue_

-  TaskHandle\_t task_





## File status_led/led_device.hpp





## Namespaces

| Type | Name |
| ---: | :--- |
| namespace  | [**status\_led**](#namespace-status_led)  <br>_Abstract LED device interface._ |

## Classes

| Type | Name |
| ---: | :--- |
| class  | [**GpioLed**](#class-status_ledgpioled)  <br>_RGB LED implementation backed by discrete GPIO channels._ |
| class  | [**LedDevice**](#class-status_ledleddevice)  <br> |
| class  | [**Ws2812Led**](#class-status_ledws2812led)  <br>_WS2812/NeoPixel LED implementation._ |




## Namespaces Documentation

### namespace `status_led`

_Abstract LED device interface._

## Classes Documentation

### class `status_led::GpioLed`

_RGB LED implementation backed by discrete GPIO channels._

Variables:

-  bool inverse_

### class `status_led::LedDevice`


Variables:

-  int pin_

### class `status_led::Ws2812Led`

_WS2812/NeoPixel LED implementation._

Variables:

-  const int kRmtResolution

-  led\_strip\_handle\_t ledStrip_
