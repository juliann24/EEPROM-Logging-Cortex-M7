/*
 * Dev_Inf.c
 *
 */
#include "Dev_Inf.h"
#include "quadspi.h"

/* This structure contains information used by ST-LINK Utility to program and erase the device */
#if defined (__ICCARM__)
__root struct StorageInfo const StorageInfo  =  {
#else
struct StorageInfo const StorageInfo = {
#endif
    "QSPI_Loader_Palta",                  // Device Name + version number
    NOR_FLASH,                           // Device Type
    0x90000000,                          // Device Start Address
	W25Q256JV_FLASH_SIZE,                   // Device Size in Bytes
	W25Q256JV_PAGE_SIZE,                    // Programming Page Size
    0xFF,                                // Initial Content of Erased Memory

    // Specify Size and Address of Sectors (view example below)
    {   {
            (W25Q256JV_FLASH_SIZE / W25Q256JV_SECTOR_SIZE),  // Sector Numbers,
            (uint32_t) W25Q256JV_SECTOR_SIZE
        },       //Sector Size

        { 0x00000000, 0x00000000 }
    }
};
