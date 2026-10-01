import esphome.codegen as cg
from esphome.components import i2c, sensor
import esphome.config_validation as cv
from esphome.const import CONF_ID, CONF_POSITION, STATE_CLASS_MEASUREMENT, UNIT_PERCENT

DEPENDENCIES = ["i2c"]

CONF_RAW = "raw"
ICON_SLIDER = "mdi:tune-vertical-variant"

soldered_slider_potentiometer_ns = cg.esphome_ns.namespace("soldered_slider_potentiometer")
SolderedSliderPotentiometer = soldered_slider_potentiometer_ns.class_(
    "SolderedSliderPotentiometer", cg.PollingComponent, i2c.I2CDevice
)

CONFIG_SCHEMA = cv.All(
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(SolderedSliderPotentiometer),
            cv.Optional(CONF_POSITION): sensor.sensor_schema(
                unit_of_measurement=UNIT_PERCENT,
                icon=ICON_SLIDER,
                accuracy_decimals=0,
                state_class=STATE_CLASS_MEASUREMENT,
            ),
            cv.Optional(CONF_RAW): sensor.sensor_schema(
                icon=ICON_SLIDER,
                accuracy_decimals=0,
                state_class=STATE_CLASS_MEASUREMENT,
            ),
        }
    )
    .extend(cv.polling_component_schema("1s"))
    .extend(i2c.i2c_device_schema(0x30)),
    cv.has_at_least_one_key(CONF_POSITION, CONF_RAW),
)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await i2c.register_i2c_device(var, config)

    if CONF_POSITION in config:
        sens = await sensor.new_sensor(config[CONF_POSITION])
        cg.add(var.set_position_sensor(sens))

    if CONF_RAW in config:
        sens = await sensor.new_sensor(config[CONF_RAW])
        cg.add(var.set_raw_sensor(sens))
