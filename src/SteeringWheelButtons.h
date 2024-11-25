#ifndef STEERING_WHEEL_BUTTONS_H
#define STEERING_WHEEL_BUTTONS_H

class SteeringWheelButtons {
public:
  enum STEERING_WHEEL_BUTTON {
    NONE,
    NXT,
    SEEK_DOWN,
    SEEK_UP,
    SRC,
    VOL_UP,
    VOL_DOWN
  };
  static STEERING_WHEEL_BUTTON decode(const unsigned char &data);
  static void onFrame(unsigned char data[8]);
};

#endif // STEERING_WHEEL_BUTTONS_H
