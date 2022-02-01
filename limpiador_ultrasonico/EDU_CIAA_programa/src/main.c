/* Copyright 2017, Pablo Ridolfi, Juan Esteban Alarcon, Juan Manuel Cruz
 * All rights reserved.
 *
 * This file is part of Workspace.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */
 
/** @brief This is a simple statechart example using Yakindu Statechart Tool
 * Plug-in (update site: http://updates.yakindu.org/sct/mars/releases/).
 */

/** \addtogroup statechart Simple UML Statechart example.
 ** @{ */

/*==================[inclusions]=============================================*/

#include "main.h"

#include "sapi.h"       // <= sAPI header

/* Include statechart header file. Be sure you run the statechart C code
 *
 * generation tool!
 */
#include "ProgramaPrincipal.h"

#include "TimerTicks.h"

#include "display.h"

#include "perfil.h"

#include "temp.h"

#include "tiempo.h"


/*==================[macros and definitions]=================================*/

#define TICKRATE_1MS	(1)				/* 1000 ticks per second */
#define TICKRATE_MS		(TICKRATE_1MS)	/* 1000 ticks per second */


/*==================[internal data declaration]==============================*/

volatile bool SysTick_Time_Flag = false;

/*! This is a state machine */
static ProgramaPrincipal statechart;

/*! This is a timed state machine that requires timer services */
#define NOF_TIMERS (sizeof(ProgramaPrincipalTimeEvents)/sizeof(sc_boolean))

TimerTicks ticks[NOF_TIMERS];

pantalla_t pantallas[] = {&pantallaInfo,
				&pantallaPerfil1,
				&pantallaPerfil2,
				&pantallaPerfil3,
				&pantallaMenu,
				&pantallaEleccion,
				&pantallaEdicion,
				&pantallaConfElec,
				&pantallaConfCanc
				};


/*==================[internal functions declaration]=========================*/

/*==================[internal data definition]===============================*/

/*==================[external data definition]===============================*/

/*==================[internal functions definition]==========================*/

/*==================[external functions definition]==========================*/

/*! \file This header defines prototypes for all functions that are required
 *  by the state machine implementation.
 *
 *  This is a state machine uses time events which require access to a timing
 *  service. Thus the function prototypes:
 *  - application_setTimer and
 *  - application_unsetTimer
 *  are defined.
 *
 *  This state machine makes use of operations declared in the state machines
 *  interface or internal scopes. Thus the function prototypes:
 *  - applicationIface_opLED
 *  are defined.
 *
 *  These functions will be called during a 'run to completion step' (runCycle)
 *  of the statechart.
 *  There are some constraints that have to be considered for the
 *  implementation of these functions:
 *  - never call the statechart API functions from within these functions.
 *  - make sure that the execution time is as short as possible.
 */

/** state machine user-defined external function (action)
 *
 * @param handle state machine instance
 * @param LEDNumber number of LED
 * @param onoff state machine operation parameter
 */

void programaPrincipalIface_opLEDs( ProgramaPrincipal* handle, sc_integer LEDNumber)
{

	sc_integer aux;

	aux = LEDNumber;
	if(aux & 1)
		gpioWrite(LEDR, true);
	else
		gpioWrite(LEDR, false);

	aux = LEDNumber;
	if((aux>>1)&1 == 1)
			gpioWrite(LED1, true);
	else
		gpioWrite(LED1, false);

	aux = LEDNumber;
	if((aux>>2)&1 == 1)
		gpioWrite(LED2, true);
	else
		gpioWrite(LED2, false);

	aux = LEDNumber;
	if((aux>>3)&1 == 1)
		gpioWrite(LED3, true);
	else
		gpioWrite(LED3, false);
}


/** state machine user-defined external function (action)
 *
 * @param handle state machine instance
 * @param LEDNumber number of LED
 * @param onoff state machine operation parameter
 */

void programaPrincipalIface_opLED( ProgramaPrincipal* handle, sc_integer LEDNumber, sc_boolean State )
{
	gpioWrite( (LEDR + LEDNumber), State );
}

/** state machine user-defined external function (action)
 *
 * @param handle state machine instance
 * @param LEDNumber number of LED
 * @param onoff state machine operation parameter
 */
void programaPrincipalIface_opMostrarPantalla(ProgramaPrincipal *handle, sc_integer Screen, sc_integer Cursor)
{
	int32_t tiempo_act = programaPrincipalIface_get_time_act(&statechart);
	int32_t temp_act = programaPrincipalIface_get_temp_act(&statechart);
	int32_t datos[3] = {temp_act, tiempo_act, Cursor};
	(*pantallas[Screen])(datos);
}


/** state machine user-defined external function (action)
 *
 * @param handle state machine instance
 * @param LEDNumber number of LED
 * @param onoff state machine operation parameter
 */
void programaPrincipalIface_opGetActTemp(ProgramaPrincipal *handle)
{
	uint32_t temp = calcTemp( adcRead(CH2));
	programaPrincipalIface_set_temp_act(&statechart, temp);
}

/** state machine user-defined external function (action)
 *
 * @param handle state machine instance
 * @param LEDNumber number of LED
 * @param onoff state machine operation parameter
 */
sc_integer programaPrincipalIface_opGetPerfilTemp(ProgramaPrincipal *handle, sc_integer Perfil)
{
	if(Perfil <= CANTIDAD_PERFILES && Perfil > 0)
		return leerTemp(Perfil);
	else if(Perfil == PERFIL_DEFECTO)
		return MIN_TEMP;
	return 0;
}

/** state machine user-defined external function (action)
 *
 * @param handle state machine instance
 * @param LEDNumber number of LED
 * @param onoff state machine operation parameter
 */
sc_integer programaPrincipalIface_opGetPerfilTiempo(ProgramaPrincipal *handle, sc_integer Perfil)
{
	if(Perfil <= CANTIDAD_PERFILES && Perfil > 0)
		return leerTiempo(Perfil);
	return 0;
}


/** state machine user-defined external function (action)
 *
 * @param handle state machine instance
 * @param LEDNumber number of LED
 * @param onoff state machine operation parameter
 */
void programaPrincipalIface_opSetTemp(ProgramaPrincipal *handle, sc_integer Temp, sc_integer Perfil)
{
	if(Perfil <= CANTIDAD_PERFILES && Perfil > 0)
		guardarTemp(Temp, Perfil);
}

/** state machine user-defined external function (action)
 *
 * @param handle state machine instance
 * @param LEDNumber number of LED
 * @param onoff state machine operation parameter
 */
void programaPrincipalIface_opSetTiempo(ProgramaPrincipal *handle, sc_integer Tiempo, sc_integer Perfil)
{
	if(Perfil <= CANTIDAD_PERFILES && Perfil > 0)
	{
		guardarTiempo(Tiempo, Perfil);
	}

}

/** state machine user-defined external function (action)
 *
 * @param handle state machine instance
 * @param LEDNumber number of LED
 * @param onoff state machine operation parameter
 */
void programaPrincipalIface_opCalentador(ProgramaPrincipal *handle, sc_boolean Estado)
{
	gpioWrite(LEDR, Estado);
	gpioWrite(GPIO8, Estado);
}

/** state machine user-defined external function (action)
 *
 * @param handle state machine instance
 * @param LEDNumber number of LED
 * @param onoff state machine operation parameter
 */
void programaPrincipalIface_opTransductor(ProgramaPrincipal *handle, sc_boolean Estado)
{
	gpioWrite(LED1, Estado);
	gpioWrite(GPIO5, Estado);
}


/** state machine user-defined external function (action)
 *
 * @param handle state machine instance
 * @param LEDNumber number of LED
 * @param onoff state machine operation parameter
 */
sc_boolean programaPrincipalIface_opCheckEnd(ProgramaPrincipal *handle, sc_integer Tiempo_act)
{
	if(Tiempo_act > 0)
		return true;
	return false;
}

/*! * This is a timed state machine that requires timer services
 */

/*! This function has to set up timers for the time events that are required
 *  by the state machine.
 */
/*! This function will be called for each time event that is relevant for a
 *  state when a state will be entered.
 *  \param evid An unique identifier of the event.
 *  \time_ms The time in milli seconds
 *  \periodic Indicates the the time event must be raised periodically until
 *   the timer is unset
 */
void programaPrincipal_setTimer( ProgramaPrincipal* handle, const sc_eventid evid, const sc_integer time_ms, const sc_boolean periodic )
{
	SetNewTimerTick(ticks, NOF_TIMERS, evid, time_ms, periodic);
}

/*! This function has to unset timers for the time events that are required
 *  by the state machine.
 */
/*! This function will be called for each time event that is relevant for a
 *  state when a state will be left.
 *  \param evid An unique identifier of the event.
 */
void programaPrincipal_unsetTimer( ProgramaPrincipal* handle, const sc_eventid evid )
{
	UnsetTimerTick( ticks, NOF_TIMERS, evid );
}


/**
 * @brief	Hook on Handle interrupt from SysTick timer
 * @return	Nothing
 */
void myTickHook( void *ptr ){

	/* The sysTick Interrupt Handler only set a Flag */
	SysTick_Time_Flag = true;
}


/*! This function scan all EDU-CIAA-NXP buttons (TEC1, TEC2, TEC3 and TEC4),
 *  and return ID of pressed button (TEC1 or TEC2 or TEC3 or TEC4)
 *  or false if no button was pressed.
 */
uint32_t Buttons_GetStatus_(void) {
	uint8_t ret = false;
	uint32_t idx;

	for (idx = 0; idx < 4; ++idx) {
		if (gpioRead( TEC1 + idx ) == 0)
			ret |= 1 << idx;
	}
	return ret;
}


/**
 * @brief	main routine for statechart example: EDU-CIAA-NXP - Application
 * @return	Function should not exit.
 */
int main(void)
{
	uint32_t i;

	uint32_t BUTTON_Status;

	int32_t temp;

	int32_t temp_counter = 0;


	/* Generic Initialization */
	boardConfig();

	/* Init Ticks counter => TICKRATE_MS */
	tickConfig( TICKRATE_MS );

	/* Add Tick Hook */
	tickCallbackSet( myTickHook, (void*)NULL );

	/* Init Timer Ticks */
	InitTimerTicks( ticks, NOF_TIMERS );

	/*Init ADC*/
	adcInit(ADC_ENABLE);

	/*Init lcd display*/
	displayConfig();

	/* Statechart Initialization */
	programaPrincipal_init( &statechart );
	programaPrincipal_enter( &statechart );

	/*EEPROM (interna) Initialization*/
	Board_EEPROM_init();

	/*Inicialización  puertos*/
	gpioInit(GPIO8, GPIO_OUTPUT);
	gpioInit(GPIO5, GPIO_OUTPUT);
	gpioInit(GPIO6, GPIO_OUTPUT);
	gpioWrite(GPIO6, true);

	/*Por si hay valores basura invalidos en la EEPROM interna*/
	for(i = 1; i <= CANTIDAD_PERFILES; i++)
	{
		int32_t temp_set = leerTemp(i);
		int32_t tiempo_set = leerTiempo(i);
		if(temp_set < MIN_TEMP || temp_set > MAX_TEMP)
			guardarTemp(MIN_TEMP, i);
		if(tiempo_set < 0 || tiempo_set > MAX_TIEMPO)
			guardarTiempo(MAX_TIEMPO, i);
	}

	/* LED state is toggled in the main program */
	while (1) {
		/* The uC sleeps waiting for an interruption */
		__WFI();

		/* When a interrupt wakes to the uC, the main program validates it,
		 * checking the waited Flag */
		if (SysTick_Time_Flag == true) {

			/* Then reset its Flag */
			SysTick_Time_Flag = false;

			/* Then Update all Timer Ticks */
			UpdateTimers( ticks, NOF_TIMERS );

			/* Then Scan all Timer Ticks */
			for (i = 0; i < NOF_TIMERS; i++) {

				/* Then if there are pending events */
				if (IsPendEvent( ticks, NOF_TIMERS, ticks[i].evid ) == true) {

					/* Then Raise an Event -> Ticks.evid => OK */
					programaPrincipal_raiseTimeEvent( &statechart, ticks[i].evid );

					/* Then Mark as Attached -> Ticks.evid => OK */
					MarkAsAttEvent( ticks, NOF_TIMERS, ticks[i].evid );
				}
			}

			/* Then Get status of buttons */
			BUTTON_Status = Buttons_GetStatus_();

			/* Then if there are a pressed button */
			if (BUTTON_Status != 0)

				/* Then Raise an Event -> evTECXOprimodo => OK,
				 * and Value of pressed button -> viTecla */
				programaPrincipalIface_raise_evTECXOprimido(&statechart, BUTTON_Status);
			else
				/* Then else Raise an Event -> evTECXNoOprimido => OK */
				programaPrincipalIface_raise_evTECXNoOprimido(&statechart);

			/* Then Run an Cycle of Statechart */
			programaPrincipal_runCycle(&statechart);		// Run Cycle of Statechart

			/*Chequea si llego a su fin el limpiado*/
			if(programaPrincipalIface_get_limpieza(&statechart) == false)
				programaPrincipalIface_raise_siTimeOff(&statechart);
			if(programaPrincipalIface_get_temp_act(&statechart) >= (MAX_TEMP + 5))
				temp_counter += 1;
			else
				temp_counter = 0;
			if(temp_counter == MAX_TEMP_COUNT)
			{
				programaPrincipalIface_opCalentador(&statechart, false);
				programaPrincipalIface_opTransductor(&statechart, false);
				pantallaErrorTemp();
				break;
			}
		}

	}
}


/** @} doxygen end group definition */

/*==================[end of file]============================================*/
