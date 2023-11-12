/*
 * display7seg.h
 *
 *  Created on: Nov 10, 2023
 *      Author: huaho
 */

#ifndef INC_7SEGS_H_
#define INC_7SEGS_H_

#include <stdint.h>
#include "port.h"

void OffAll_7Seg(void);
void display7SEG(uint8_t);
void update7SegBuffer(int, int);
void update7SEG(uint8_t);

#endif /* INC_7SEGS_H_ */
