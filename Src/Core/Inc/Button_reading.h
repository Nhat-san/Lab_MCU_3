
#ifndef INC_INPUT_PROCESSING_H_
#define INC_INPUT_PROCESSING_H_
#include <stdint.h>
#include <stdbool.h>
#include "main.h"

void initButton();
void read_button();
uint8_t is_button_pressed(uint8_t i);
uint8_t is_button_long_pressed(uint8_t i);

#endif /* INC_INPUT_PROCESSING_H_ */
