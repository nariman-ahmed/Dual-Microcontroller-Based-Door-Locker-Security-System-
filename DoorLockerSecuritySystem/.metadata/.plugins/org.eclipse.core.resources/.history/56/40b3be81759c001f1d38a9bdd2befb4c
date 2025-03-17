/*
 * timer.c
 *
 *  Created on: 2 Nov 2024
 *      Author: NARIMAN AHMED
 */
#include "timer.h"
#include "common_macros.h"
#include <avr/io.h>
#include <avr/interrupt.h>

/*******************************************************************************
 *                      Global Variables                                       *
 *******************************************************************************/
static volatile void (*g_callBackPtr0)(void) = NULL_PTR;
static volatile void (*g_callBackPtr1_OVF)(void) = NULL_PTR;
static volatile void (*g_callBackPtr1_CMP)(void) = NULL_PTR;
static volatile void (*g_callBackPtr2)(void) = NULL_PTR;

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
void Timer_init(const Timer_ConfigType * Config_Ptr) {
    switch (Config_Ptr->timer_ID) {
        case TIMER0:
            TCNT0 = Config_Ptr->timer_InitialValue; /* Set initial value */
            if (Config_Ptr->timer_mode == NORMAL_MODE) {
                TCCR0 = (1 << FOC0); /* Normal mode */
                TIMSK |= (1 << TOIE0); /* Enable overflow interrupt */
            } else if (Config_Ptr->timer_mode == COMPARE_MODE) {
                TCCR0 = (1 << FOC0) | (1 << WGM01); /* CTC mode */
                OCR0 = Config_Ptr->timer_compare_MatchValue; /* Set compare value */
                TIMSK |= (1 << OCIE0); /* Enable compare interrupt */
            }
            TCCR0 = (TCCR0 & 0xF8) | (Config_Ptr->timer_clock); /* Set clock */
            break;

        case TIMER1:
            TCNT1 = Config_Ptr->timer_InitialValue; /* Set initial value */
            if (Config_Ptr->timer_mode == NORMAL_MODE) {
                TCCR1A = (1 << FOC1A); /* Normal mode */
                TIMSK |= (1 << TOIE1); /* Enable overflow interrupt */
            } else if (Config_Ptr->timer_mode == COMPARE_MODE) {
                TCCR1A = (1 << FOC1A); /* CTC mode */
                TCCR1B = (1 << WGM12);
                OCR1A = Config_Ptr->timer_compare_MatchValue; /* Set compare value */
                TIMSK |= (1 << OCIE1A); /* Enable compare interrupt */
            }
            TCCR1B = (TCCR1B & 0xF8) | (Config_Ptr->timer_clock); /* Set clock */
            break;

        case TIMER2:
            TCNT2 = Config_Ptr->timer_InitialValue; /* Set initial value */
            if (Config_Ptr->timer_mode == NORMAL_MODE) {
                TCCR2 = (1 << FOC2); /* Normal mode */
                TIMSK |= (1 << TOIE2); /* Enable overflow interrupt */
            } else if (Config_Ptr->timer_mode == COMPARE_MODE) {
                TCCR2 = (1 << FOC2) | (1 << WGM21); /* CTC mode */
                OCR2 = Config_Ptr->timer_compare_MatchValue; /* Set compare value */
                TIMSK |= (1 << OCIE2); /* Enable compare interrupt */
            }
            TCCR2 = (TCCR2 & 0xF8) | (Config_Ptr->timer_clock); /* Set clock */
            break;
    }
}

void Timer_deInit(Timer_ID_Type timer_type) {
    switch (timer_type) {
        case TIMER0:
            TCCR0 = 0x00;
            TIMSK &= ~((1 << TOIE0) | (1 << OCIE0));
            break;

        case TIMER1:
            TCCR1A = 0x00;
            TCCR1B = 0x00;
            TIMSK &= ~((1 << TOIE1) | (1 << OCIE1A));
            break;

        case TIMER2:
            TCCR2 = 0x00;
            TIMSK &= ~((1 << TOIE2) | (1 << OCIE2));
            break;
    }
}

void Timer_setCallBack(void (*a_ptr)(void), Timer_ID_Type a_timer_ID) {
    switch (a_timer_ID) {
        case TIMER0:
            g_callBackPtr0 = a_ptr;
            break;

        case TIMER1:
            g_callBackPtr1_OVF = a_ptr;
            break;

        case TIMER2:
            g_callBackPtr2 = a_ptr;
            break;
    }
}

/*******************************************************************************
 *                      Interrupt Service Routines                            *
 *******************************************************************************/
ISR(TIMER0_OVF_vect) {
    if (g_callBackPtr0 != NULL_PTR) {
        (*g_callBackPtr0)();
    }
}

ISR(TIMER0_COMP_vect) {
    if (g_callBackPtr0 != NULL_PTR) {
        (*g_callBackPtr0)();
    }
}

ISR(TIMER1_OVF_vect) {
    if (g_callBackPtr1_OVF != NULL_PTR) {
        (*g_callBackPtr1_OVF)();
    }
}

ISR(TIMER1_COMPA_vect) {
    if (g_callBackPtr1_CMP != NULL_PTR) {
        (*g_callBackPtr1_CMP)();
    }
}

ISR(TIMER2_OVF_vect) {
    if (g_callBackPtr2 != NULL_PTR) {
        (*g_callBackPtr2)();
    }
}

ISR(TIMER2_COMP_vect) {
    if (g_callBackPtr2 != NULL_PTR) {
        (*g_callBackPtr2)();
    }
}



