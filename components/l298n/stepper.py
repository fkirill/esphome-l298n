from esphome import pins
from esphome.components import stepper
import esphome.config_validation as cv
import esphome.codegen as cg
from esphome.const import CONF_ID, CONF_SLEEP_WHEN_DONE


l298n_ns = cg.esphome_ns.namespace("l298n")
l298n = l298n_ns.class_("L298N", stepper.Stepper, cg.Component)

CONFIG_SCHEMA = stepper.STEPPER_SCHEMA.extend(
    {
        cv.Required(CONF_ID): cv.declare_id(l298n),
        cv.Required("output_pin1"): pins.gpio_output_pin_schema,
        cv.Required("output_pin2"): pins.gpio_output_pin_schema,
        cv.Required("output_pin3"): pins.gpio_output_pin_schema,
        cv.Required("output_pin4"): pins.gpio_output_pin_schema,
        cv.Optional(CONF_SLEEP_WHEN_DONE, default=False): cv.boolean,
    }
).extend(cv.COMPONENT_SCHEMA)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    await stepper.register_stepper(var, config)

    output_pin1 = await cg.gpio_pin_expression(config["output_pin1"])
    cg.add(var.set_output_pin1(output_pin1))
    output_pin2 = await cg.gpio_pin_expression(config["output_pin2"])
    cg.add(var.set_output_pin2(output_pin2))
    output_pin3 = await cg.gpio_pin_expression(config["output_pin3"])
    cg.add(var.set_output_pin3(output_pin3))
    output_pin4 = await cg.gpio_pin_expression(config["output_pin4"])
    cg.add(var.set_output_pin4(output_pin4))
    cg.add(var.set_sleep_when_done(config[CONF_SLEEP_WHEN_DONE]))
