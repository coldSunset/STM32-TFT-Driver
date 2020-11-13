/**
  ******************************************************************************
  * @file           : user_setting.h
  * @brief          : Header for GPIO Pins.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Date : 13/11/2020
  * Author: Ravindu Sirimanna
  *
  *
  ******************************************************************************
  */

#ifndef USER_SETTING_H_
#define USER_SETTING_H_

/* Control Pins */
#define RD_PORT 			GPIOA
#define RD_PIN  			GPIO_PIN_1
#define WR_PORT 			GPIOA
#define WR_PIN  			GPIO_PIN_2
#define CD_PORT 			GPIOA          // RS PORT
#define CD_PIN 			    GPIO_PIN_3     // RS PIN
#define CS_PORT 			GPIOA
#define CS_PIN  			GPIO_PIN_4
#define RESET_PORT 			GPIOA
#define RESET_PIN  			GPIO_PIN_5

/* Data Pins */
#define D0_PORT 			GPIOC
#define D0_PIN 				GPIO_PIN_0
#define D1_PORT 			GPIOC
#define D1_PIN 				GPIO_PIN_1
#define D2_PORT 			GPIOC
#define D2_PIN 				GPIO_PIN_2
#define D3_PORT 			GPIOC
#define D3_PIN 				GPIO_PIN_3
#define D4_PORT 			GPIOC
#define D4_PIN 				GPIO_PIN_4
#define D5_PORT 			GPIOC
#define D5_PIN 				GPIO_PIN_5
#define D6_PORT 			GPIOC
#define D6_PIN 				GPIO_PIN_6
#define D7_PORT 			GPIOC
#define D7_PIN 				GPIO_PIN_7

#define  WIDTH    ((uint16_t)240)
#define  HEIGHT   ((uint16_t)320)

/* delay in microseconds */

// configure macros for the data pins.

/* First of all clear all the LCD_DATA pins i.e. LCD_D0 to LCD_D7
 * We do that by writing the HIGHER bits in BSRR Register
 *
 * For example :- To clear Pins B3, B4 , B8, B9, we have to write GPIOB->BSRR = 0b0000001100011000 <<16
 *
 *
 *
 * To write the data to the respective Pins, we have to write the lower bits of BSRR :-
 *
 * For example say the PIN LCD_D4 is connected to PB7, and LCD_D6 is connected to PB2
 *
 * GPIOB->BSRR = (data & (1<<4)) << 3.  Here first select 4th bit of data (LCD_D4), and than again shift left by 3 (Total 4+3 =7 i.e. PB7)
 *
 * GPIOB->BSRR = (data & (1<<6)) >> 4.  Here first select 6th bit of data (LCD_D6), and than again shift Right by 4 (Total 6-4 =2 i.e. PB2)
 *
 *
 */
  #define write_8(d) { \
   GPIOC->BSRR = 0b0000000011111111 << 16; \
   GPIOC->BSRR = ((d) & (1<<0)) \
               | ((d) & (1<<1)) \
			   | ((d) & (1<<2)) \
			   | ((d) & (1<<3)) \
			   | ((d) & (1<<4)) \
			   | ((d) & (1<<5)) \
			   | ((d) & (1<<6)) \
			   | ((d) & (1<<7)) ; \

    }


  /* To read the data from the Pins, we have to read the IDR Register
   *
   * Take the same example say LCD_D4 is connected to PB7, and LCD_D6 is connected to PB2
   *
   * To read data we have to do the following
   *
   * GPIOB->IDR & (1<<7) >> 3. First read the PIN (1<<7 means we are reading PB7) than shift it to the position, where it is connected to
   * and in this example, that would be 4 (LCD_D4). (i.e. 7-3=4)
   *
   * GPIOB->IDR & (1<<2) << 4. First read the PIN (1<<2 means we are reading PB2) than shift it to the position, where it is connected to
   * and in this case, that would be 6 (LCD_D6). (i.e. 2+4= 6). Shifting in the same direction
   *
   */
  #define read_8() (          (((GPIOC->IDR & (1<<0)) >> 0) \
                           | ((GPIOC->IDR & (1<<1))) \
                           | ((GPIOC->IDR & (1<<2))) \
                           | ((GPIOC->IDR & (1<<3))) \
                           | ((GPIOC->IDR & (1<<4))) \
                           | ((GPIOC->IDR & (1<<5))) \
                           | ((GPIOC->IDR & (1<<6))) \
                           | ((GPIOC->IDR & (1<<7)))))

#endif /* USER_SETTING_H_ */
