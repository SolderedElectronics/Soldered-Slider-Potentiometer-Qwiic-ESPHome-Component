# Soldered Slider Potentiometer With Qwiic ESPHome Component

| ![Slider Potentiometer With Qwiic](https://cms.soldered.com/products/333131/media/333131_featured-photo_5bd23c.jpg) |
| :------------------------------------------------------------------------------------------------------------------: |
|                           [Slider Potentiometer With Qwiic](https://www.solde.red/333131)                            |

A linear 10k slider potentiometer, like the ones found on mixing desks and other audio equipment. An onboard ATtiny404
samples the slider with its 10-bit ADC and reports the reading over I2C, so no analog pin is needed. The board is part
of the [Qwiic ecosystem](https://soldered.com/collections/qwiic-ecosystem).

External ESPHome component for the Soldered Slider Potentiometer with Qwiic. It is a port of the
[Soldered Slider Potentiometer with easyC Arduino library](https://github.com/SolderedElectronics/Soldered-Slider-Potentiometer-with-easyC-Arduino-Library)
and publishes the slider position in percent and/or the raw ADC value as ESPHome
[sensors](https://esphome.io/components/sensor/).

> For the plain [Slider Potentiometer Breakout](https://www.solde.red/333130) without Qwiic (analog output), use
> ESPHome's built-in [`adc`](https://esphome.io/components/sensor/adc/) component instead.

## Repository Contents

- **components/** - the ESPHome external component (Python config + C++ implementation)
- **examples/** - example YAML configs showing how to use the component

## Usage

Reference this repo directly from your own ESPHome YAML (no need to clone it locally):

```yaml
external_components:
  - source: github://SolderedElectronics/Soldered-Slider-Potentiometer-Qwiic-ESPHome-Component
    components: [soldered_slider_potentiometer]

i2c:
  sda: GPIO21
  scl: GPIO22

sensor:
  - platform: soldered_slider_potentiometer
    position:
      name: "Slider Position"
```

On every update the component reads the slider once and publishes the raw value (`0` - `1023`) and the position
(`raw * 100 / 1023`, so `0` - `100` %) to whichever of the two sensors are configured. To only send updates when the
slider actually moves, add a [`delta`](https://esphome.io/components/sensor/#delta) filter to the sensor.

See [`examples/basic.yaml`](examples/basic.yaml) for a full working example.

### Configuration variables

- **position** (*Optional*): slider position in percent (`0` - `100`). All options from
  [Sensor](https://esphome.io/components/sensor/#config-sensor).
- **raw** (*Optional*): raw 10-bit ADC reading (`0` - `1023`). All options from
  [Sensor](https://esphome.io/components/sensor/#config-sensor).
- **address** (*Optional*, int): I2C address of the board. Defaults to `0x30`; can be set to `0x30` - `0x37` with the
  board's three address-select switches (each one adds 1, 2 or 4).
- **update_interval** (*Optional*, [Time](https://esphome.io/guides/configuration-types#config-time)): how often to
  read the slider. Defaults to `1s`.
- **i2c_id** (*Optional*, [ID](https://esphome.io/guides/configuration-types#config-id)): I2C bus to use, if there is
  more than one.

At least one of `position` or `raw` must be set.

### Hardware design

You can find hardware design for this board in the
[_Slider potentiometer breakout qwiic_](https://github.com/SolderedElectronics/Slider-potentiometer-breakout-qwiic-hardware-design)
hardware repository.

### Documentation

Access library documentation [here](https://docs.soldered.com/).

### About Soldered

<img src="https://raw.githubusercontent.com/SolderedElectronics/Soldered-Generic-Arduino-Library/dev/extras/Soldered-logo-color.png" alt="soldered-logo" width="500"/>

At Soldered, we design and manufacture a wide selection of electronic products to help you turn your ideas into acts and bring you one step closer to your final project. Our products are intented for makers and crafted in-house by our experienced team in Osijek, Croatia. We believe that sharing is a crucial element for improvement and innovation, and we work hard to stay connected with all our makers regardless of their skill or experience level. Therefore, all our products are open-source. Finally, we always have your back. If you face any problem concerning either your shopping experience or your electronics project, our team will help you deal with it, offering efficient customer service and cost-free technical support anytime. Some of those might be useful for you:

- [Web Store](https://www.soldered.com/shop)
- [Tutorials & Projects](https://soldered.com/learn)
- [Documentation](https://docs.soldered.com)

### Open-source license

Soldered invests vast amounts of time into hardware & software for these products, which are all open-source. Please support future development by buying one of our products.

Check license details in the LICENSE file. Long story short, use these open-source files for any purpose you want to, as long as you apply the same open-source licence to it and disclose the original source. No warranty - all designs in this repository are distributed in the hope that they will be useful, but without any warranty. They are provided "AS IS", therefore without warranty of any kind, either expressed or implied. The entire quality and performance of what you do with the contents of this repository are your responsibility. In no event, Soldered (TAVU) will be liable for your damages, losses, including any general, special, incidental or consequential damage arising out of the use or inability to use the contents of this repository.

## Have fun!

And thank you from your fellow makers at Soldered Electronics.
