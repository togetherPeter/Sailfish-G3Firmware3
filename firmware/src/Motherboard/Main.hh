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

#ifndef MAIN_HH_
#define MAIN_HH_

#include <avr/interrupt.h>

/// Test for stack / SRAM corruption
/// Returns the number of bytes that haven't been touched on the stack
extern uint16_t StackCount(void);

/// Reset the machine.
/// \param[in] hard_reset Pass in true if this is a power-up reset
void reset(bool hard_reset);

#endif // MAIN_HH_
