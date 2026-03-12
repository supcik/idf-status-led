# Status LED Get Started Example

This example shows how to use the `supcik/status_led` component in an ESP-IDF application.
It supports two hardware modes:

- A single WS2812 RGB LED
- A GPIO-controlled status LED

The application creates a `StatusLed` instance, then cycles through a few common states:

- Solid green
- Slow blue blink
- Solid orange
- White flash sequence
- Fast white blink
- Red flash sequence

## Requirements

- ESP-IDF 5.3 or newer
- A supported ESP target
- One of the following LED setups:
	- A WS2812-compatible RGB LED connected to a GPIO pin
	- A GPIO-driven status LED

## Dependency Setup

This example uses a local component override so it builds against the checked out repository instead of downloading the component from the registry.

See [main/idf_component.yml](main/idf_component.yml).

## Configuration

The example exposes its settings in `menuconfig` under `Status LED`.

Available options:

- `Status LED pin`: GPIO used by the LED
- `Status LED mode`: select `WS2811` or `GPIO`
- `Invert status LED GPIO`: invert the GPIO output for active-low LEDs
- `Swap red and green color LEDs`: fix WS2812 devices with swapped color order

Default configuration from [sdkconfig.defaults](sdkconfig.defaults):

- Target: `esp32s3`
- LED pin: `38`
