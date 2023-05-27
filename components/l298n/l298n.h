#pragma once

#include "esphome/core/component.h"
#include "esphome/core/hal.h"
#include "esphome/components/stepper/stepper.h"
#include <Arduino.h>
#include <inttypes.h>

namespace esphome {
namespace l298n {

class L298N : public stepper::Stepper, public Component {
 public:
  void set_output_pin1(GPIOPin *output_pin1) { this->output_pin1_ = output_pin1; }
  void set_output_pin2(GPIOPin *output_pin2) { this->output_pin2_ = output_pin2; }
  void set_output_pin3(GPIOPin *output_pin3) { this->output_pin3_ = output_pin3; }
  void set_output_pin4(GPIOPin *output_pin4) { this->output_pin4_ = output_pin4; }
  void set_sleep_when_done(bool sleep_when_done) { this->sleep_when_done_ = sleep_when_done; }
  void setup() override;
  void dump_config() override;
  void loop() override;
  float get_setup_priority() const override { return setup_priority::HARDWARE; }

 protected:
  GPIOPin *output_pin1_;
  GPIOPin *output_pin2_;
  GPIOPin *output_pin3_;
  GPIOPin *output_pin4_;
  bool sleep_when_done_{false};
  HighFrequencyLoopRequester high_freq_;
  void set_step_signal();
};

}  // namespace a4988
}  // namespace esphome
