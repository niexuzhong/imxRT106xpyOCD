#ifndef __DRV_FLEXSPI_NOR_H__
#define __DRV_FLEXSPI_NOR_H__
#include "fsl_common.h"
#include "fsl_flexspi.h"
void flexspi_nor_initialize(FLEXSPI_Type *base);
void flexspi_nor_setup(FLEXSPI_Type *base,uint32_t flashSize,uint32_t busyPol,uint32_t busyOffset);
status_t flexspi_nor_write_status_register(FLEXSPI_Type *base,uint8_t cmd,uint8_t value);
status_t flexspi_nor_flash_erase_chip(FLEXSPI_Type *base);
status_t flexspi_nor_flash_erase_sector(FLEXSPI_Type *base, uint32_t address);
status_t flexspi_nor_flash_page_program(FLEXSPI_Type *base, uint32_t dstAddr, const uint32_t *src,size_t pagesize);
status_t flexspi_nor_get_jedec_id(FLEXSPI_Type *base, uint32_t *jedecId);
#endif
