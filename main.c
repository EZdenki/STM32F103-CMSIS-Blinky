//  Minimalist Blinky for Blue Pill Using Only CMSIS (no HAL)
//  Mike Shegedin, 07/2023
//
//  This project is classic Blinky to blink the bult-in LED on the Blue Pill module. It is
//  useful as a sanity check to ensure that the toolchain used to program the Blue Pill
//  is fully functional.
//
//  Hardware Setup:
//  Only requires connection between the ST-Link programming dongle (plugged into a USB port)
//  and the Blue Pill module via the VCC, GND, SWCLK and SWDIO pins. The programmer jumpers on
//  the Blue Pill should both be in their "0" position. 

#include "stm32f103xb.h"    // Header file that includes the CMSIS definitions for the STM32
int
main( void )
{

  // Setup GPIO port C, pin 13 (C13), as a push-pull output. C13 controls the built-in LED
  // on the Blue Pill

  // Enable GPIO Port C
  RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;

  // To make a GPIO pin as a push-pull output, the CNF bits need to be cleared, and the MODE
  // bits need to be 0b01. Note that one of the CNF bits is set by default, and therefore
  // the bits need to be zeroed out to get zero values.
  GPIOC->CRH &= ~GPIO_CRH_CNF13_Msk;    // Clear both CNF13[1:0] bits
  GPIOC->CRH |= ( GPIO_CRH_MODE13_0 );  // Set MODE13[0]-bit.

  while( 1 )                            // Endless loop
  {
    for( uint32_t x=0; x<200e3; x++) ;  // Delay a bit
    GPIOC->ODR ^= GPIO_ODR_ODR13;       // Flip the GPIO C13 bit
  }
}
