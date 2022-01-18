/*
 * Copyright 2010 by Adam Mayer	 <adam@makerbot.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>
 */

#include <avr/io.h>
#include <util/atomic.h>
#include "Configuration.hh"

// Enable pin D5 is also OC0B.

int16_t last_extruder_speed;

// TIMER0 is used to PWM motor driver A enable on OC0B, and
// channel C on OC0A.
void initExtruderMotor() {
	last_extruder_speed = 0;
	TCCR0A = 0b00000011;  // Leave pins off by default
	TCCR0B = 0b00000011;
	OCR0B = 0;
	TIMSK0 = 0; // no interrupts needed.
	MOTOR_ENABLE_PIN.setDirection(true);
	MOTOR_ENABLE_PIN.setValue(false);
	MOTOR_DIR_PIN.setDirection(true);
}

void setExtruderMotor(int16_t speed) {
	if (speed == last_extruder_speed) return;
	last_extruder_speed = speed;
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
		if (speed == 0) {
			TCCR0A &= 0b11001111;
			MOTOR_ENABLE_PIN.setValue(false);
		} else {
			MOTOR_ENABLE_PIN.setValue(true);
			TCCR0A |= 0b00100000;
		}
		bool backwards = speed < 0;
		if (backwards) { speed = -speed; }
		if (speed > 255) { speed = 255; }
		MOTOR_DIR_PIN.setValue(!backwards);
		OCR0B = speed;
	}
}
