#include "sapi.h"
#include "display.h"
#include "perfil.h"
#include "temp.h"
#include "tiempo.h"
#include "ProgramaPrincipal.h"



// Caracter personalizado carita feliz :)
const char smile[8] = {
   0b00000000,
   0b00001010,
   0b00001010,
   0b00001010,
   0b00000000,
   0b00010001,
   0b00001110,
   0b00000000,
};

// Caracter personalizado letra e
const char e_char[8] = {
   0b11111,
   0b10000,
   0b10000,
   0b11100,
   0b10000,
   0b10000,
   0b10000,
   0b11111
};

// Caracter personalizado letra r
const char r_char[8] = {
   0b00000,
   0b00000,
   0b00000,
   0b01110,
   0b01000,
   0b01000,
   0b01000,
   0b01000
};

// Caracter personalizado letra i
const char i_char[8] = {
   0b00000,
   0b00100,
   0b00000,
   0b00100,
   0b00100,
   0b00100,
   0b00100,
   0b00110
};

// Caracter personalizado letra c
const char c_char[8] = {
   0b00000,
   0b00000,
   0b00000,
   0b00110,
   0b01000,
   0b01000,
   0b01001,
   0b00110
};

//Temperatura - Termometro
const char tempChar[8] = {
   0b01110,
   0b01010,
   0b01010,
   0b01110,
   0b01110,
   0b10111,
   0b11111,
   0b01110
};

// Flecha - Cursor
const char curChar[8] = {
   0b00000,
   0b11000,
   0b01100,
   0b00110,
   0b00011,
   0b00110,
   0b01100,
   0b11000
};

// Viento
const char vieChar[8] = {
   0b00111,
   0b11100,
   0b00000,
   0b00111,
   0b11100,
   0b00000,
   0b00111,
   0b11100
};

// Simbolo grados
const char graChar[8] = {
   0b01110,
   0b01010,
   0b01110,
   0b00000,
   0b00000,
   0b00000,
   0b00000,
   0b00000
};


/*Funciones para el manejo de las pantallas
 *
 *
 *
 *
 */

/*Inicialización y configuración lcd
 *
 */
void displayConfig()
{
	delay( LCD_STARTUP_WAIT_MS );   // Wait for stable power (some LCD need that)

	// Inicializar LCD de 16x2 (caracteres x lineas) con cada caracter de 5x8 pixeles
	lcdInit( 16, 2, 5, 8 );

	// Cargar el caracter a CGRAM
	// El primer parametro es el codigo del caracter (0 a 7).
	// El segundo es el puntero donde se guarda el bitmap (el array declarado
	// anteriormente)
	lcdCreateChar( TEMP_CHAR, tempChar );
	lcdCreateChar( CUR_CHAR, curChar );
	lcdCreateChar( VIE_CHAR, vieChar );
	lcdCreateChar( E_CHAR, e_char );
	lcdCreateChar( R_CHAR, r_char );
	lcdCreateChar( I_CHAR, i_char );
	lcdCreateChar( C_CHAR, c_char );
	lcdCreateChar( GRA_CHAR, graChar );
	lcdCursorSet( LCD_CURSOR_OFF );// Apaga el cursor
	lcdClear();                     // Borrar la pantalla
}


/*Pantalla Info
 *
 */
void pantallaInfo(const int32_t *datos)
{
	char aux[5];

	if(datos == NULL)
		return;
	lcdClear();
	lcdGoToXY(1, 0);
	lcdSendStringRaw("Temp:");
	sprintf(aux, "%d", datos[0]);
	lcdSendStringRaw(aux);
	lcdData(GRA_CHAR);
	lcdSendStringRaw("C");

	lcdGoToXY(1, 1);
	lcdSendStringRaw("Tiempo:");
	sprintf(aux, "%d", datos[1]);
	lcdSendStringRaw(aux);
}

/*Pantalla Menu
 *
 */
void pantallaMenu(const int32_t *datos)
{
	char aux[5];

	if(datos == NULL)
		return;
	lcdClear();
	lcdGoToXY(1, 0);
	lcdSendStringRaw("Volver");

	lcdGoToXY(1, 1);
	lcdSendStringRaw("Elegir");

	lcdGoToXY(10, 0);
	lcdSendStringRaw("Editar");

	if(datos[2] == 1)
		lcdGoToXY(9, 0);
	else if(datos[2] == 2)
		lcdGoToXY(0, 1);
	else
		lcdGoToXY(0, 0);
	lcdData(CUR_CHAR);
}


/*Pantalla eleccion de pefil a usar en limpieza
 *
 */
void pantallaEleccion(const int32_t *datos)
{
	char aux[5];

	if(datos == NULL)
		return;
	lcdClear();
	lcdGoToXY(1, 0);
	lcdSendStringRaw("Volver");

	lcdGoToXY(10, 0);
	lcdSendStringRaw("Perf#1");

	lcdGoToXY(1, 1);
	lcdSendStringRaw("Perf#2");

	lcdGoToXY(10, 1);
	lcdSendStringRaw("Perf#3");

	if(datos[2] == 1)
		lcdGoToXY(9, 0);
	else if(datos[2] == 2)
		lcdGoToXY(0, 1);
	else if(datos[2] == 3)
		lcdGoToXY(9, 1);
	else
		lcdGoToXY(0, 0);
	lcdData(CUR_CHAR);
}

/*Pantalla eleccion de perfil a editar
 *
 */
void pantallaEdicion(const int32_t *datos)
{
	char aux[5];

	if(datos == NULL)
		return;
	lcdClear();
	lcdGoToXY(1, 0);
	lcdSendStringRaw("Volver");

	lcdGoToXY(10, 0);
	lcdSendStringRaw("Perf#1");

	lcdGoToXY(1, 1);
	lcdSendStringRaw("Perf#2");

	lcdGoToXY(10, 1);
	lcdSendStringRaw("Perf#3");

	if(datos[2] == 1)
		lcdGoToXY(9, 0);
	else if(datos[2] == 2)
		lcdGoToXY(0, 1);
	else if(datos[2] == 3)
		lcdGoToXY(9, 1);
	else
		lcdGoToXY(0, 0);
	lcdData(CUR_CHAR);
}

/*Pantalla confirmacion de eleccion
 *
 *
 */
void pantallaConfElec(const int32_t *datos)
{
	if(datos == NULL)
		return;
	lcdClear();
	lcdGoToXY(4, 0);
	lcdSendStringRaw("Iniciar?");

	lcdGoToXY(1, 1);
	lcdSendStringRaw("NO");

	lcdGoToXY(13, 1);
	lcdSendString("SI");

	if(datos[2] == 1)
		lcdGoToXY(12, 1);
	else
		lcdGoToXY(0, 1);
	lcdData(CUR_CHAR);
}


/*Pantalla confirmacion de cancelado de limpieza
 *
 */
void pantallaConfCanc(const int32_t *datos)
{
	if(datos == NULL)
		return;
	lcdClear();
	lcdGoToXY(3, 0);
	lcdSendStringRaw("Cancelar?");

	lcdGoToXY(1, 1);
	lcdSendStringRaw("NO");

	lcdGoToXY(13, 1);
	lcdSendString("SI");

	if(datos[2] == 1)
		lcdGoToXY(12, 1);
	else
		lcdGoToXY(0, 1);
	lcdData(CUR_CHAR);
}

/*Pantalla edicion perfil 1
 *
 */
void pantallaPerfil1(const int32_t *datos)
{
	if(datos == NULL)
		return;
	lcdClear();
	char aux[5];
	int temp_set = leerTemp(PERFIL1);
	int tiempo_set = leerTiempo(PERFIL1);
	if(temp_set < 0 || temp_set > MAX_TEMP)
		return;
	if(tiempo_set < 0 || tiempo_set > MAX_TIEMPO)
		return;
	lcdGoToXY(10, 0);
	lcdSendStringRaw("Perf#1");

	lcdGoToXY(1, 0);
	lcdSendStringRaw("Volver");

	sprintf(aux, "%d", temp_set);
	lcdGoToXY(10, 1);
	lcdSendStringRaw("T:");
	lcdSendStringRaw(aux);
	lcdData(GRA_CHAR);
	lcdSendStringRaw("C");

	sprintf(aux, "%d", tiempo_set);
	lcdGoToXY(1, 1);
	lcdSendStringRaw("t:");
	lcdSendString(aux);

	if(datos[2] == 1)
		lcdGoToXY(0, 1);
	else if(datos[2] == 2)
		lcdGoToXY(9, 1);
	else
		lcdGoToXY(0, 0);
	lcdData(CUR_CHAR);
}

/*Pantalla edicion perfil 2
 *
 */
void pantallaPerfil2(const int32_t *datos)
{
	if(datos == NULL)
		return;
	lcdClear();
	char aux[5];
	int temp_set = leerTemp(PERFIL2);
	int tiempo_set = leerTiempo(PERFIL2);
	if(temp_set < 0 || temp_set > MAX_TEMP)
		return;
	if(tiempo_set < 0 || tiempo_set > MAX_TIEMPO)
		return;
	lcdGoToXY(10, 0);
	lcdSendStringRaw("Perf#2");

	lcdGoToXY(1, 0);
	lcdSendStringRaw("Volver");

	sprintf(aux, "%d", temp_set);
	lcdGoToXY(10, 1);
	lcdSendStringRaw("T:");
	lcdSendStringRaw(aux);
	lcdData(GRA_CHAR);
	lcdSendStringRaw("C");

	sprintf(aux, "%d", tiempo_set);
	lcdGoToXY(1, 1);
	lcdSendStringRaw("t:");
	lcdSendString(aux);
	if(datos[2] == 1)
		lcdGoToXY(0, 1);
	else if(datos[2] == 2)
		lcdGoToXY(9, 1);
	else
		lcdGoToXY(0, 0);
	lcdData(CUR_CHAR);
}

/*Pantalla edicion perfil 3
 *
 */
void pantallaPerfil3(const int32_t *datos)
{
	if(datos == NULL)
		return;
	lcdClear();
	char aux[5];
	int temp_set = leerTemp(PERFIL3);
	int tiempo_set = leerTiempo(PERFIL3);
	if(temp_set < 0 || temp_set > MAX_TEMP)
		return;
	if(tiempo_set < 0 || tiempo_set > MAX_TIEMPO)
		return;
	lcdGoToXY(10, 0);
	lcdSendStringRaw("Perf#3");

	lcdGoToXY(1, 0);
	lcdSendStringRaw("Volver");

	sprintf(aux, "%d", temp_set);
	lcdGoToXY(10, 1);
	lcdSendStringRaw("T:");
	lcdSendStringRaw(aux);
	lcdData(GRA_CHAR);
	lcdSendStringRaw("C");

	sprintf(aux, "%d", tiempo_set);
	lcdGoToXY(1, 1);
	lcdSendStringRaw("t:");
	lcdSendString(aux);

	if(datos[2] == 1)
		lcdGoToXY(0, 1);
	else if(datos[2] == 2)
		lcdGoToXY(9, 1);
	else
		lcdGoToXY(0, 0);
	lcdData(CUR_CHAR);
}


/*Pantalla error temp
 *
 */
void pantallaErrorTemp()
{
	lcdClear();
	lcdGoToXY(1, 0);
	lcdSendStringRaw("ERROR TEMP");

}










