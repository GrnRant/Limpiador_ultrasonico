/*Funciones para el manejo de las pantallas
 *
 */

#ifndef _PERFIL_H
#define _PERFIL_H_

#include "sapi.h"

#define CANTIDAD_PERFILES 3

#define PERFIL1 1
#define PERFIL2 2
#define PERFIL3 3
#define PERFIL_DEFECTO -1

int32_t leerTemp(const int32_t);

int32_t leerTiempo(const int32_t);

void guardarTemp(const int32_t, const int32_t);

void guardarTiempo(const int32_t, const int32_t);

int32_t Board_EEPROM_writeByte(uint32_t addr,uint8_t value);

int32_t Board_EEPROM_readByte(uint32_t addr);

void Board_EEPROM_init(void);

#endif
