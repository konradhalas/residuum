#define S(val) val * 1000

#define NEXT_BUTTON_PIN 7 // PE6
#define EDIT_BUTTON_PIN 13 // PC7
#define PREVIOUS_BUTTON_PIN 23 // PF0

#define LCD_LED_PIN 5 // PC6
#define LCD_DC_PIN 8 // PB4
#define LCD_CS_PIN 10 // SCE, PB6
#define LCD_RST_PIN 9 // PB5

#define STATUS_LED_PIN 11

#define RS_1_PIN 2  // PD1
#define RS_2_PIN 0  // PD2
#define RS_3_PIN 1  // PD3
#define RS_4_PIN 4  // PD4
#define RS_5_PIN 12 // PD6
#define RS_6_PIN 18 // PF7
#define RS_7_PIN 19  // PF6
#define RS_8_PIN 20 // PF5

#define BUTTONS_DELAY 500
#define LCD_CONTRAST 55
#define LCD_BAKCLIGHT false
#define NUMBER_OF_REFLECTANT_SENSORS 8
#define HANDLE_TICK_FREQUENCY 20000

#define MOTOR_LEFT 0
#define MOTOR_RIGHT 1
#define MOTOR_BOTH 2
#define MOTOR_LEFT_ENABLE  3  // PD0 (PWM)
#define MOTOR_LEFT_PHASE   22 // PF1
#define MOTOR_RIGHT_ENABLE 6  // PD7 (PWM)
#define MOTOR_RIGHT_PHASE  21 // PF4

#define BASE_MOTOR_SPEED 120
#define MOTOR_CHECK_TIMEOUT S(3)

#define FOLLOW_TIMEOUT S(30)
#define FOLLOW_START_TIMEOUT S(1)
#define FOLLOWER_KP_BASE 100

#define FOLLOWER_KP 0.05
#define FOLLOWER_KD 1
