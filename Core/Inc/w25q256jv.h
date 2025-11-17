/**
  ******************************************************************************
  * @file    n25q128a.h
  * @author  MCD Application Team
  * @brief   This file contains all the description of the N25Q128A QSPI memory.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2015 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __N25Q128A_H
#define __N25Q128A_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/

/** @addtogroup BSP
  * @{
  */ 

/** @addtogroup Components
  * @{
  */ 
  
/** @addtogroup n25q128a
  * @{
  */

/** @defgroup N25Q128A_Exported_Types
  * @{
  */
   
/**
  * @}
  */ 

/** @defgroup N25Q128A_Exported_Constants
  * @{
  */
   
/** 
  * @brief  W25Q256JV Configuration
  */  
#define W25Q256JV_JEDEC_ID_SIZE          	  3         // El JEDEC ID consta de 3 bytes (Fabricante, Tipo, Capacidad)
#define W25Q256JV_JEDEC_ID 			  		  0xEF      // ID del fabricante Winbond

#define W25Q256JV_BLOCK_32K_SIZE        32768U      // 32 KB por bloque
#define W25Q256JV_BLOCK_64K_SIZE        65536U      // 64 KB por bloque
#define W25Q256JV_FLASH_SIZE      (32 * 1024 * 1024U)  // 32 MB
#define W25Q256JV_SECTOR_SIZE     4096U                // 4 KB
#define W25Q256JV_PAGE_SIZE       256U                 // 256 bytes

#define W25Q256JV_PAGE_COUNT            (W25Q256JV_FLASH_SIZE / W25Q256JV_PAGE_SIZE)
#define W25Q256JV_SECTOR_COUNT          (W25Q256JV_FLASH_SIZE / W25Q256JV_SECTOR_SIZE)
#define W25Q256JV_BLOCK_32K_COUNT       (W25Q256JV_FLASH_SIZE / W25Q256JV_BLOCK_32K_SIZE)
#define W25Q256JV_BLOCK_64K_COUNT       (W25Q256JV_FLASH_SIZE / W25Q256JV_BLOCK_64K_SIZE)

#define W25Q256JV_DUMMY_CYCLES_READ           8
#define W25Q256JV_DUMMY_CYCLES_READ_QUAD      10

#define W25Q256JV_BULK_ERASE_MAX_TIME         250000
#define W25Q256JV_SECTOR_ERASE_MAX_TIME       3000
#define W25Q256JV_SUBSECTOR_ERASE_MAX_TIME    800

 /******************************************************************************/
 /* COMANDOS DE MEMORIA QSPI                       */
 /******************************************************************************/

 #define W25Q256JV_READ_JEDEC_ID_CMD 			   0x9F      // Instrucción para leer el JEDEC ID
 #define W25Q256JV_WRITE_ENABLE_CMD                0x06U
 #define W25Q256JV_WRITE_DISABLE_CMD               0x04U

 #define W25Q256JV_READ_STATUS_REG1_CMD            0x05U // Leer el registro de estado 1
 #define W25Q256JV_WRITE_STATUS_REG1_CMD           0x01U // Escribir el registro de estado 1
 #define W25Q256JV_READ_STATUS_REG2_CMD            0x35U // Leer el registro de estado 2
 #define W25Q256JV_WRITE_STATUS_REG2_CMD           0x31U // Escribir el registro de estado 2
 #define W25Q256JV_READ_STATUS_REG3_CMD            0x15U // Leer el registro de estado 3
 #define W25Q256JV_WRITE_STATUS_REG3_CMD           0x31U // Escribir el registro de estado 3

 #define W25Q256JV_READ_DATA_CMD                   0x03U
 #define W25Q256JV_FAST_READ_CMD                   0x0BU

 #define W25Q256JV_PAGE_PROGRAM_DUAL_INPUT_CMD	   0xA2U
 #define W25Q256JV_FAST_READ_DUAL_OUT_CMD		   0x3BU
 #define W25Q256JV_FAST_READ_DUAL_IO_CMD		   0xBBU
 #define W25Q256JV_FAST_READ_QUAD_OUT_CMD          0x6BU // Lectura rápida con salida Quad
 #define W25Q256JV_FAST_READ_QUAD_IO_CMD           0xEBU // Lectura rápida con E/S Quad (usado en quadspi.c)
 #define W25Q256JV_FAST_READ_QUAD_IO_4BYTE_ADD_CMD 0xECU

 #define W25Q256JV_PAGE_PROGRAM_CMD                0x02U
 #define W25Q256JV_PAGE_PROGRAM_QUAD_INPUT_CMD     0x32U // Programación de Página Quad (usado en quadspi.c)

 #define W25Q256JV_SECTOR_ERASE_CMD                0x20U // Borrado de Sector (4KB)
 #define W25Q256JV_BLOCK_ERASE_32K_CMD             0x52U // Borrado de Bloque (32KB)
 #define W25Q256JV_BLOCK_ERASE_64K_CMD             0xD8U // Borrado de Bloque (64KB)
 #define W25Q256JV_CHIP_ERASE_CMD                  0xC7U // Borrado de Chip


 #define W25Q256JV_ENABLE_RESET_CMD                0x66U // Comando de Habilitar Reset
 #define W25Q256JV_RESET_DEVICE_CMD                0x99U // Comando de Reset
 #define W25Q256JV_ENTER_4BYTE_ADDRESS_MODE_CMD	   0xB7U // Entrar en modo 4Byte
 #define W25Q256JV_EXIT_4BYTE_ADDRESS_MODE_CMD	   0xE9U // Salir de modo 4Byte

 /******************************************************************************/
 /* MASCARAS DE REGISTROS DE ESTADO                        */
 /******************************************************************************/
 #define W25Q256JV_STATUS_REG1_BUSY_MASK           0x01U // Bit 0: Busy (1=Operación en curso, 0=Lista)
 #define W25Q256JV_STATUS_REG1_WEL_MASK            0x02U // Bit 1: Write Enable Latch (1=Habilitado, 0=Deshabilitado)
 #define W25Q256JV_STATUS_REG3_ADS_MASK			   0x01
 #define W25Q256JV_STATUS_REG2_QE_MASK             0x02U  // Bit 1: Quad Enable (QE)

 /* Status Register 1 */
 #define W25Q256JV_SR1_WIP                    ((uint8_t)0x01)    /*!< Write In Progress (Busy) */
 #define W25Q256JV_SR1_WEL                    ((uint8_t)0x02)    /*!< Write Enable Latch */
 #define W25Q256JV_SR1_BP                     ((uint8_t)0x3C)    /*!< Block Protection Bits (BP3, BP2, BP1, BP0) */
 #define W25Q256JV_SR1_SRWD                   ((uint8_t)0x80)    /*!< Status Register Write Disable */

 /* Status Register 2 (The most important for QSPI activation) */
 #define W25Q256JV_SR2_QE                     ((uint8_t)0x02)    /*!< Quad Enable (Bit 1) - Must be set to 1 for Quad I/O */
 #define W25Q256JV_SR2_TB                     ((uint8_t)0x04)    /*!< Top/Bottom Protect (For Block Protection) */
 #define W25Q256JV_SR2_CMP                    ((uint8_t)0x40)    /*!< Complement Protect (Changes BP behavior) */
 #define W25Q256JV_SR2_SUS                    ((uint8_t)0x80)    /*!< Erase/Program Suspend Status */

 /* Status Register 3 */
 #define W25Q256JV_SR3_ADS                    ((uint8_t)0x01)    /*!< Address Bit Setting (3-Byte/4-Byte) */

 /* Flag Status Register (Not explicitly defined in the W25Q datasheet, but often handled by SR1/SR2 in Winbond) */

 /**
   * @}
   */

 /** @defgroup W25Q256JV_Exported_Functions
   * @{
   */
 /**
   * @}
   */

 /**
   * @}
   */

 /**
   * @}
   */

 /**
   * @}
   */
  
#ifdef __cplusplus
}
#endif

#endif /* __N25Q128A_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
