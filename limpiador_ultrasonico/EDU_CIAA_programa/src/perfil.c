#include "sapi.h"
#include "perfil.h"

/*Funciones para el manejo de los datos de los perfiles
 *
 */

int32_t leerTemp(const int32_t perfil)
{
	if(perfil <= CANTIDAD_PERFILES && perfil > 0)
		return Board_EEPROM_readByte(2*perfil - 1);
	return -1;
}

int32_t leerTiempo(const int32_t perfil)
{
	if(perfil <= CANTIDAD_PERFILES && perfil > 0)
		return Board_EEPROM_readByte(2*(perfil - 1));
	return -1;
}

void guardarTemp(const int32_t temp, const int32_t perfil)
{
	if(perfil <= CANTIDAD_PERFILES || perfil > 0)
		Board_EEPROM_writeByte(2*perfil - 1, (uint8_t) temp);
}

void guardarTiempo(const int32_t tiempo, const int32_t perfil)
{
	if(perfil <= CANTIDAD_PERFILES || perfil > 0)
			Board_EEPROM_writeByte(2*(perfil - 1), (uint8_t) tiempo);
}

//================================================[EEPROM Management]========================================================

int32_t Board_EEPROM_writeByte(uint32_t addr,uint8_t value)
{
	if(addr>=(16*1024))
		return -1;

	uint32_t addr4 = addr/4;
	uint32_t pageAddr = addr4/EEPROM_PAGE_SIZE;
	uint32_t pageOffset = addr4 - pageAddr*EEPROM_PAGE_SIZE;

	uint32_t *pEepromMem = (uint32_t*)EEPROM_ADDRESS(pageAddr,pageOffset*4);

	// read 4 bytes in auxValue
	uint32_t auxValue = pEepromMem[0];
	uint8_t* pAuxValue = (uint8_t*)&auxValue;

	// modify auxValue with new Byte value
	uint32_t indexInBlock = addr % 4;
	pAuxValue[indexInBlock] = value;

	//write auxValue back in eeprom
	pEepromMem[0] = auxValue;
	Chip_EEPROM_WaitForIntStatus(LPC_EEPROM, EEPROM_INT_ENDOFPROG);
	return 0;
}

int32_t Board_EEPROM_readByte(uint32_t addr)
{
    if(addr>=(16*1024))
        return -1;

	uint32_t addr4 = addr/4;
	uint32_t pageAddr = addr4/EEPROM_PAGE_SIZE;
	uint32_t pageOffset = addr4 - pageAddr*EEPROM_PAGE_SIZE;

	uint32_t *pEepromMem = (uint32_t*)EEPROM_ADDRESS(pageAddr,pageOffset*4);

	// read 4 bytes in auxValue
	uint32_t auxValue = pEepromMem[0];
	uint8_t* pAuxValue = (uint8_t*)&auxValue;

	// modify auxValue with new Byte value
	uint32_t indexInBlock = addr % 4;
	return (int32_t) pAuxValue[indexInBlock];

}
void Board_EEPROM_init(void)
{
	Chip_EEPROM_Init(LPC_EEPROM);
  	/* Set Auto Programming mode */
 	Chip_EEPROM_SetAutoProg(LPC_EEPROM,EEPROM_AUTOPROG_AFT_1WORDWRITTEN);
}
