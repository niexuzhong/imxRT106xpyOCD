#include <stdint.h>
#include <stdio.h>
// For memcmp used in Verify()
#include "clock_config.h"
#include "flexspi_nor.h"
#include "fsl_flexspi.h"

#include "pin_mux.h"
#include <string.h>

#define FLASH_BASE_ADDR 0x60000000 

char *fill_num(char *str, uint32_t num) {
    if (num >= 1000) {
        *str++ = '0' + (num / 1000 % 10);
    }
    if (num >= 100) {
        *str++ = '0' + (num / 100 % 10);
    }
    if (num >= 10) {
        *str++ = '0' + (num / 10 % 10);
    }
    *str++ = '0' + (num % 10);
    return str;
}

/*
 *  Initialize Flash Programming Functions
 *    Return Value:   0 - OK,  1 - Failed
 */
uint32_t Init(unsigned long adr, unsigned long clk, unsigned long fnc) {
    uint32_t jid;
    uint32_t tmp32;
   

    BOARD_InitBootClocks();
    BOARD_InitBootPins();
	//	SCB_DisableDCache();
    flexspi_nor_initialize(FLEXSPI);


 
    return 0;
}

/*
 *  De-Initialize Flash Programming Functions
 *    Return Value:   0 - OK,  1 - Failed
 */
uint32_t UnInit (unsigned long fnc) { return 0; }

/*
 *  Erase complete Flash Memory
 *    Return Value:   0 - OK,  1 - Failed
 */
uint32_t EraseChip(void) {
    return flexspi_nor_flash_erase_chip(FLEXSPI) == kStatus_Success?
            0:1;
}

/*
 *  Erase Sector in Flash Memory
 *    Parameter:      adr:  Sector Address
 *                numsecs: Number of sectors
 *    Return Value:   0 - OK,  1 - Failed
 */
int EraseSector (unsigned long adr) {

  /* Add your Code */
  int stat;
	
	stat = flexspi_nor_flash_erase_sector(FLEXSPI,adr - FLASH_BASE_ADDR);
	return stat;   
}

/*
 *  Program Page in Flash Memory
 *    Parameter:      adr:  Page Start Address
 *                    sz:   Page Size
 *                    buf:  Page Data
 *    Return Value:   0 - OK,  1 - Failed
 */
uint32_t ProgramPage(unsigned long adr, unsigned long sz, unsigned char *buf) {


    if (flexspi_nor_flash_page_program(FLEXSPI, adr - FLASH_BASE_ADDR,
                                       (const uint32_t *)buf,
                                       sz) != kStatus_Success) {
        return 2;
    } else {
        return 0;
    }
}

/*
 *  Verify Flash Contents
 *    Parameter:      adr:  Start Address
 *                    sz:   Size (in bytes)
 *                    buf:  Data
 *    Return Value:   (adr+sz) - OK, Failed Address
 */
uint32_t Verify(uint32_t adr, uint32_t sz, uint8_t *buf) {


    if ((adr & 0x03) == 0 && sz > 15 && ((uint32_t)buf & 0x03) == 0) {
        uint32_t *ptr32 = (uint32_t *)adr;
        uint32_t *buf32 = (uint32_t *)buf;
        while (sz > 3) {
            if (*ptr32 != *buf32) {
                return (uint32_t)ptr32;
            }
            ptr32++;
            buf32++;
            sz -= 4;
        }

        buf = (uint8_t *)buf32;
        adr = (uint32_t)ptr32;
    }

    uint8_t *ptr8 = (uint8_t *)adr;
    while (sz > 0) {
        if (*ptr8 != *buf) {
            return (uint32_t)ptr8;
        }
        ptr8++;
        buf++;
        sz--;
    }
    return (uint32_t)0;
}
