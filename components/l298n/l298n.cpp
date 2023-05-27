#include "l298n.h"
#include "esphome/core/log.h"

namespace esphome {
namespace l298n {

static const char *const TAG = "l298n.stepper";

void L298N::setup() {
  ESP_LOGCONFIG(TAG, "Setting up L298N...");
  this->output_pin1_->setup();
  this->output_pin1_->digital_write(false);
  this->output_pin2_->setup();
  this->output_pin2_->digital_write(false);
  this->output_pin3_->setup();
  this->output_pin3_->digital_write(false);
  this->output_pin4_->setup();
  this->output_pin4_->digital_write(false);
}
void L298N::dump_config() {
  ESP_LOGCONFIG(TAG, "L298N:");
  LOG_PIN("  Output1 Pin: ", this->output_pin1_);
  LOG_PIN("  Output2 Pin: ", this->output_pin2_);
  LOG_PIN("  Output3 Pin: ", this->output_pin3_);
  LOG_PIN("  Output4 Pin: ", this->output_pin4_);
  LOG_STEPPER(this);
}
void L298N::loop() {
  bool at_target = this->has_reached_target();

  if (at_target) {
    this->high_freq_.stop();
    
    if (this->sleep_when_done_) {
      output_pin1_->digital_write(LOW);
      output_pin2_->digital_write(LOW);
      output_pin3_->digital_write(LOW);
      output_pin4_->digital_write(LOW);
    }
  } else {
    this->high_freq_.start();
  }

  int32_t dir = this->should_step_();
  if (dir == 0)
    return;

  set_step_signal();
}

void L298N::set_step_signal() {
  switch (current_position % 4) {
    case 0:  // 1010
      output_pin1_->digital_write(HIGH);
      output_pin2_->digital_write(LOW);
      output_pin3_->digital_write(HIGH);
      output_pin4_->digital_write(LOW);
      break;
    case 1:  // 0110
      output_pin1_->digital_write(LOW);
      output_pin2_->digital_write(HIGH);
      output_pin3_->digital_write(HIGH);
      output_pin4_->digital_write(LOW);
      break;
    case 2:  //0101
      output_pin1_->digital_write(LOW);
      output_pin2_->digital_write(HIGH);
      output_pin3_->digital_write(LOW);
      output_pin4_->digital_write(HIGH);
      break;
    case 3:  //1001
      output_pin1_->digital_write(HIGH);
      output_pin2_->digital_write(LOW);
      output_pin3_->digital_write(LOW);
      output_pin4_->digital_write(HIGH);
      break;
  }
}

}  // namespace l298n
}  // namespace esphome
