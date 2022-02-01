/*Funciones para el manejo de las pantallas
 *
 */
#ifndef DISPLAY_H_
#define DISPLAY_H_

#include "sapi.h"

typedef void (*pantalla_t)(const int32_t *);

void displayConfig();

void pantallaInfo(const int32_t *);

void pantallaMenu(const int32_t *);

void pantallaEleccion(const int32_t *);

void pantallaEdicion(const int32_t *);

void pantallaConfElec(const int32_t *);

void pantallaConfCanc(const int32_t *);

void pantallaPerfil1(const int32_t *);

void pantallaPerfil2(const int32_t *);

void pantallaPerfil3(const int32_t *);

void pantallaErrorTemp(void);

typedef enum{
   TEMP_CHAR = 0,
   CUR_CHAR  = 1,
   VIE_CHAR  = 2,
   E_CHAR    = 3,
   R_CHAR    = 4,
   I_CHAR    = 5,
   C_CHAR    = 6,
   GRA_CHAR  = 7,
} spchar_t;

#endif
