/*==================================================================================================
 * Copyright 2025 (c) Foxtron Inc - All Rights Reserved
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
==================================================================================================*/


/*==================================================================================================
*                                         INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include <Spi.h>
#include "Spi_Cfg.h"
#include "pmic_tlf35584.h"
#include <public/Mk_autosar.h>

/*==================================================================================================
*                                      DEFINES AND MACROS
==================================================================================================*/
#define PMIC_TLF35584_SPI_BUFFER_SIZE      (1u)
#define PMIC_TLF35584_SPI_TRANSFER_LENGTH  (1u)

/*! Read / Write masks */
#define PMIC_TLF35584_MASK_SPIADDR                    (0x3Fu)     /*!< Masks address from address byte (1 Byte) */
#define PMIC_TLF35584_MASK_SPIADDR_RAW                (0x7E00u)   /*!< Masks address from complete SPI sequence (2 Bytes) */
#define PMIC_TLF35584_MASK_SPIDATA_RAW                (0x01FEu)   /*!< Masks data from complete SPI sequence (2 Bytes) */
#define PMIC_TLF35584_MASK_CMD_WRITE_RAW              (0x8000u)   /*!< Masks CMD bit from complete SPI sequence (2 Bytes) */
#define PMIC_TLF35584_MASK_ALL_FLAGS                  (0xFFu)     /*!< Mask that selects all flags (i.e. to clear all pending event flags) */
#define PMIC_TLF35584_OFFSET_SPIADDR                  (9u)        /*!< Offset of address bits in SPI command */
#define PMIC_TLF35584_OFFSET_SPIDATA                  (1u)        /*!< Offset of data bits in SPI command */

/*! Main registers addresses */
#define PMIC_TLF35584_REG_ADDR_PROTCFG                (0x03u)     /*!< Protected register */
#define PMIC_TLF35584_REG_ADDR_RSYSPCFG0              (0x0Bu)     /*!< System configuration 0 status */
#define PMIC_TLF35584_REG_ADDR_RSYSPCFG1              (0x0Cu)     /*!< System configuration 1 status */
#define PMIC_TLF35584_REG_ADDR_RWDCFG0                (0x0Du)     /*!< Watchdog configuration 0 status */
#define PMIC_TLF35584_REG_ADDR_RWDCFG1                (0x0Eu)     /*!< Watchdog configuration 1 status */
#define PMIC_TLF35584_REG_ADDR_RFWDCFG                (0x0Fu)     /*!< Functional watchdog configuration status */
#define PMIC_TLF35584_REG_ADDR_RWWDCFG0               (0x10u)     /*!< Window watchdog configuration status 0 */
#define PMIC_TLF35584_REG_ADDR_RWWDCFG1               (0x11u)     /*!< Window watchdog configuration status 1 */

/*! Device control/status register addresses */
#define PMIC_TLF35584_REG_ADDR_DEVCTRL                (0x15u)     /*!< Device control request */
#define PMIC_TLF35584_REG_ADDR_DEVCTRLN               (0x16u)     /*!< Device control inverted request */
#define PMIC_TLF35584_REG_ADDR_DEVSTAT                (0x27u)     /*!< Device status register */

/*! Status flag registers */
#define PMIC_TLF35584_REG_ADDR_SYSFAIL                (0x1Au)     /*!< Failure status flags */
#define PMIC_TLF35584_REG_ADDR_IF                     (0x1Cu)     /*!< Interrupt flags */
#define PMIC_TLF35584_REG_ADDR_MONSF1                 (0x21u)     /*!< Monitor status flags 1 */
#define PMIC_TLF35584_REG_ADDR_MONSF2                 (0x22u)     /*!< Monitor status flags 2 */
#define PMIC_TLF35584_REG_ADDR_MONSF3                 (0x23u)     /*!< Monitor status flags 3 */
#define PMIC_TLF35584_REG_ADDR_OTFAIL                 (0x24u)     /*!< Over temperature failure status flags */
#define PMIC_TLF35584_REG_ADDR_INITERR                (0x1Bu)     /*!< Init error status flags */
#define PMIC_TLF35584_REG_ADDR_SYSSF                  (0x1Du)     /*!< System status flags */
#define PMIC_TLF35584_REG_ADDR_SPISF                  (0x1Fu)     /*!< SPI status flags */
#define PMIC_TLF35584_REG_ADDR_PROTSTAT               (0x28u)     /*!< Protection status */

/*! Protected registers addresses */
#define PMIC_TLF35584_REG_ADDR_SYSPCFG0               (0x04u)     /*!< Protected System configuration request 0 */
#define PMIC_TLF35584_REG_ADDR_SYSPCFG1               (0x05u)     /*!< Protected System configuration request 1 */
#define PMIC_TLF35584_REG_ADDR_WDCFG0                 (0x06u)     /*!< Protected Watchdog configuration request 0 */
#define PMIC_TLF35584_REG_ADDR_WDCFG1                 (0x07u)     /*!< Protected Watchdog configuration request 1 */
#define PMIC_TLF35584_REG_ADDR_FWDCFG                 (0x08u)     /*!< Protected Functional watchdog configuration request */
#define PMIC_TLF35584_REG_ADDR_WWDCFG0                (0x09u)     /*!< Protected Window watchdog configuration request 0 */
#define PMIC_TLF35584_REG_ADDR_WWDCFG1                (0x0Au)     /*!< Protected Window watchdog configuration request 1 */

/*! Protection register values */
#define PMIC_TLF35584_REG_CMD_PROTCFG_UNLOCK_SEQ1     (0xABu)      /*!< First byte of consecutive unlock sequence */
#define PMIC_TLF35584_REG_CMD_PROTCFG_UNLOCK_SEQ2     (0xEFu)      /*!< Second byte of consecutive unlock sequence */
#define PMIC_TLF35584_REG_CMD_PROTCFG_UNLOCK_SEQ3     (0x56u)      /*!< Third byte of consecutive unlock sequence */
#define PMIC_TLF35584_REG_CMD_PROTCFG_UNLOCK_SEQ4     (0x12u)      /*!< Fourth byte of consecutive unlock sequence */

#define PMIC_TLF35584_REG_CMD_PROTCFG_LOCK_SEQ1       (0xDFu)      /*!< First byte of consecutive lock sequence */
#define PMIC_TLF35584_REG_CMD_PROTCFG_LOCK_SEQ2       (0x34u)      /*!< Second byte of consecutive lock sequence */
#define PMIC_TLF35584_REG_CMD_PROTCFG_LOCK_SEQ3       (0xBEu)      /*!< Third byte of consecutive lock sequence */
#define PMIC_TLF35584_REG_CMD_PROTCFG_LOCK_SEQ4       (0xCAu)      /*!< Fourth byte of consecutive lock sequence */

/*! WDCFG0 register bit masks */
#define PMIC_TLF35584_REG_MASK_WDCFG0_WDCYC           (0x01u)      /*!< WDCFG0:0:0 Watchdog cycle time */
#define PMIC_TLF35584_REG_MASK_WDCFG0_WWDTSEL         (0x02u)      /*!< WDCFG0:1:1 Window watchdog trigger selection */
#define PMIC_TLF35584_REG_MASK_WDCFG0_FWDEN           (0x04u)      /*!< WDCFG0:3:3 Functional watchdog enable */
#define PMIC_TLF35584_REG_MASK_WDCFG0_WWDEN           (0x08u)      /*!< WDCFG0:3:3 Window watchdog enable */
#define PMIC_TLF35584_REG_MASK_WDCFG0_ERRTRH          (0xF0u)      /*!< WDCFG0:4:7 Window watchdog error threshold */

/*! Device control register bitmasks */
#define PMIC_TLF35584_DEVCTRL_NORMAL                  (0x02u)     /*!< Go to device state NORMAL */
#define PMIC_TLF35584_DEVCTRL_STANDBY                 (0x04u)     /*!< Go to device state STANDBY */

#define PMIC_TLF35584_DEVSTAT_MASK                    (0xEFu)     /*!< Masks all relevant bits of DEVSTAT */

#define PMIC_TLF35584_WDCFG0_DEFAULT_VAL              (0x9Bu)      /*!< Default value of WDCFG0 */

#define PMIC_TLF35584_REG_MASK_PROTSTAT_LOCK          (0x01u)      /*!< PROTSTAT:1:1 Protected register lock status */

#define PMIC_MkWrCommand(addr, data)           (uint16)((((((uint16)(addr) & 0xFFu) << 8u) | ((uint16)(data) & 0xFFu) ) << PMIC_TLF35584_OFFSET_SPIDATA) | PMIC_TLF35584_MASK_CMD_WRITE_RAW)
#define PMIC_MkRdCommand(addr)                 (uint16)( (uint16)( (addr) & PMIC_TLF35584_MASK_SPIADDR) << PMIC_TLF35584_OFFSET_SPIADDR)

#define PMIC_ReadRegister(addr, target)        PMIC_RwRegister(PMIC_CalcSpiParity(PMIC_MkRdCommand((addr))), (target));*(target)>>=PMIC_TLF35584_OFFSET_SPIDATA
#define PMIC_WriteRegister(addr, data)         PMIC_RwRegister(PMIC_CalcSpiParity(PMIC_MkWrCommand((addr), (data))), NULL_PTR)

#define PMIC_GetAddrOfProtRegFromIdx(idx)      (uint16)((uint16)(idx) + PMIC_TLF35584_REG_ADDR_SYSPCFG0)
#define PMIC_GetAddrOfReadProtRegFromIdx(idx)  (uint16)((uint16)(idx) + PMIC_TLF35584_REG_ADDR_RSYSPCFG0)

/*==================================================================================================
*                                  STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/
typedef enum
{
  SYSPCFG0 = 0, /*!< Index for buffered value of register SYSPCFG0. */
  SYSPCFG1 = 1, /*!< Index for buffered value of register SYSPCFG1. */
  WDCFG0 = 2,   /*!< Index for buffered value of register WDCFG0. */ /* PRQA S 3205 */ /* MD_Sbc_3205_UnusedIdentifier */
  WDCFG1 = 3,   /*!< Index for buffered value of register WDCFG1. */ /* PRQA S 3205 */ /* MD_Sbc_3205_UnusedIdentifier */
  FWDCFG = 4,   /*!< Index for buffered value of register FWDCFG. */ /* PRQA S 3205 */ /* MD_Sbc_3205_UnusedIdentifier */
  WWDCFG0 = 5,  /*!< Index for buffered value of register WWDCFG0. */ /* PRQA S 3205 */ /* MD_Sbc_3205_UnusedIdentifier */
  WWDCFG1 = 6,   /*!< Index for buffered value of register WWDCFG1. */ /* PRQA S 3205 */ /* MD_Sbc_3205_UnusedIdentifier */
  PMIC_TLF35584_NUMBER_OF_PROTECTED_REGISTERS = 7 /*!< Number of protected registers. */
} PMIC_ProtectedRegisterValueIndex_Type; /* PRQA S 3205 */ /* MD_Sbc_3205_UnusedIdentifier */

typedef struct sPMIC_Tlf35584_SupplyConfigType
{
  uint8 DEVCTRLnormalOfSupplyConfig;  /**< A byte value that is used by the driver to configure the DEVCTRL register for SBC_SYS_NORMAL. */
  uint8 DEVCTRLstandbyOfSupplyConfig;  /**< A byte value that is used by the driver to configure the DEVCTRL register for SBC_SYS_STANDBY. */
  uint8 SYSPCFG0normalOfSupplyConfig;  /**< A byte value that is used by the driver to configure the SYSPCFG0 register for SBC_SYS_NORMAL. */
  uint8 SYSPCFG0sleepOfSupplyConfig;  /**< A byte value that is used by the driver to configure the SYSPCFG0 register for SBC_SYS_SLEEP. */
  uint8 SYSPCFG0standbyOfSupplyConfig;  /**< A byte value that is used by the driver to configure the SYSPCFG0 register for SBC_SYS_STANDBY. */
} PMIC_Tlf35584_SupplyConfigType;

typedef struct sPMIC_30_Tlf35584_InitConfigType
{
  uint8 SYSPCFG1OfInitConfig;  /**< A byte value that is used by the driver to configure the SYSPCFG1 register in Sbc initialization sequence. */
} PMIC_Tlf35584_InitConfigType;

typedef struct sPMIC_30_Tlf35584_DeviceConfigurationType
{
  uint8 CtrlLoopMaxCyclesOfDeviceConfiguration;  /**< Number of cycles after hardware-dependent loop timeout occurs. */
  uint8 NumberOfCanTrcvOfDeviceConfiguration;  /**< Specifies the number of CAN Transceivers that are used on this device */
  uint8 NumberOfLinTrcvOfDeviceConfiguration;  /**< Specifies the number of LIN Transceivers that are used on this device */
  uint8 NumberOfWdgOfDeviceConfiguration;  /**< Specifies the number of Watchdogs that are used on this device */
  uint8 WdgConfigEndIdxOfDeviceConfiguration;  /**< the end index of the 0:n relation pointing to Sbc_30_Tlf35584_WdgConfig */
  uint8 WdgConfigStartIdxOfDeviceConfiguration;  /**< the start index of the 0:n relation pointing to Sbc_30_Tlf35584_WdgConfig */
  uint8 WuSrcPorOfDeviceConfiguration;  /**< The wakeup source that is used to notify power-on wakeup events */
} PMIC_Tlf35584_DeviceConfigurationType;

/* Stores the system status */
typedef struct Pmic_SystemStatusTypeTag
{
  /* Stores the events */
  uint16 Events;
  /* Stores the states */
  uint8  States;
  /* Stores the current mode */
  Pmic_SystemModeType Mode;
} Pmic_SystemStatusType;


/*==================================================================================================
*                                       LOCAL VARIABLES
==================================================================================================*/
static uint8 PMIC_Tlf35584_ProtectedRegisterValues[PMIC_TLF35584_NUMBER_OF_PROTECTED_REGISTERS];
Pmic_SystemStatusType Pmic_SystemStatus;
static uint16 Pmic_SpiInBuffer;
static uint16 Pmic_SpiOutBuffer;

static const PMIC_Tlf35584_SupplyConfigType PMIC_Tlf35584_SupplyConfig =  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    DEVCTRLnormal  DEVCTRLstandby  SYSPCFG0normal  SYSPCFG0sleep  SYSPCFG0standby */
  { /*     0 */         0xE8u,          0xE8u,          0x01u,         0x01u,           0x01u };

static const PMIC_Tlf35584_InitConfigType PMIC_Tlf35584_InitConfig =  /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    SYSPCFG1 */
  { /*     0 */    0x00u };

static const PMIC_Tlf35584_DeviceConfigurationType PMIC_Tlf35584_DeviceConfiguration =   /* PRQA S 1514, 1533 */  /* MD_CSL_ObjectOnlyAccessedOnce */
    /* Index    CtrlLoopMaxCycles  NumberOfCanTrcv  NumberOfLinTrcv  NumberOfWdg  WdgConfigEndIdx  WdgConfigStartIdx  WuSrcPor        Comment */
  { /*     0 */               15u,              0u,              0u,          1u,              1u,                0u,    0x00u };   /* [SbcDevice] */

/*==================================================================================================
*                                       LOCAL FUNCTIONS
==================================================================================================*/
static uint16 PMIC_CalcSpiParity(uint16 in)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 i;
  uint16 res = 0;

  /* ----- Implementation ----------------------------------------------- */
  for(i = 0; i < 16u; i++)
  {
      res = res ^ ((in >> i) & 0x01u);
  }
  return (((in & (~(0x01u))) | res));
}

static Std_ReturnType PMIC_RwRegister(uint16 out, uint16 *in)
{

  /* ----- Local Variables ---------------------------------------------- */
  /* PRQA S 2981 2 */ /* MD_MSR_RetVal */
  Std_ReturnType result = E_NOT_OK;

  /* ----- Implementation ----------------------------------------------- */
  SuspendAllInterrupts();
  /* >>> CRITICAL SECTION START >>> */
  
  /* #10 Write command to SPI out buffer */
  Pmic_SpiOutBuffer = out; /* SBSW_SBC_VALID_DID */

  /* #20 Transmit command synchronously via SPI */
  result = Spi_SyncTransmit(SpiConf_SpiSequence_SpiSequence_TLF35584Q);

  /* #30 If parameter target is not a NULL_PTR, write read back value to pointer */
  if(in != NULL_PTR)
  {
    *in = Pmic_SpiInBuffer; /* SBSW_SBC_VALID_INPTR */
  }

  /* <<< CRITICAL SECTION END <<< */
  ResumeAllInterrupts();

  return result;
}

static Std_ReturnType PMIC_ReadAndUnlockProtectedRegisters(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  /* PRQA S 2981 2 */ /* MD_MSR_RetVal */
  Std_ReturnType result = E_OK;
  uint16 tmp;
  uint8 regIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Unlock protected registers */
  SuspendAllInterrupts();
  /* >>> CRITICAL SECTION START >>> */

  result  = PMIC_WriteRegister(PMIC_TLF35584_REG_ADDR_PROTCFG, PMIC_TLF35584_REG_CMD_PROTCFG_UNLOCK_SEQ1);  /* SBSW_SBC_NULLPTR_PARAM */
  result |= PMIC_WriteRegister(PMIC_TLF35584_REG_ADDR_PROTCFG, PMIC_TLF35584_REG_CMD_PROTCFG_UNLOCK_SEQ2);  /* SBSW_SBC_NULLPTR_PARAM */
  result |= PMIC_WriteRegister(PMIC_TLF35584_REG_ADDR_PROTCFG, PMIC_TLF35584_REG_CMD_PROTCFG_UNLOCK_SEQ3);  /* SBSW_SBC_NULLPTR_PARAM */
  result |= PMIC_WriteRegister(PMIC_TLF35584_REG_ADDR_PROTCFG, PMIC_TLF35584_REG_CMD_PROTCFG_UNLOCK_SEQ4);  /* SBSW_SBC_NULLPTR_PARAM */

  /* <<< CRITICAL SECTION END <<< */
  ResumeAllInterrupts();

  /* #20 Check if unlock procedure was successful */
  result |= PMIC_ReadRegister(PMIC_TLF35584_REG_ADDR_PROTSTAT, &tmp);  /* SBSW_SBC_LOCALPTR_PARAM */ /* SBSW_SBC_ACCESS_LOCAL */
  if (((uint8)tmp & PMIC_TLF35584_REG_MASK_PROTSTAT_LOCK) != 0u) /* COV_SBC_LL_EVENTS */
  {
    result |= E_NOT_OK;
  }
  else
  {
    /* #30 Read values of protected register to buffer */
    for (regIdx = 0; regIdx < ((uint8) PMIC_TLF35584_NUMBER_OF_PROTECTED_REGISTERS); regIdx++)
    {
      /* PRQA S 2985 2 */ /* MD_Sbc_2985_2986_RedundantOperation */
      result |= PMIC_ReadRegister(PMIC_GetAddrOfReadProtRegFromIdx(regIdx), &tmp);  /* SBSW_SBC_LOCALPTR_PARAM */ /* SBSW_SBC_ACCESS_LOCAL */
      PMIC_Tlf35584_ProtectedRegisterValues[regIdx] = (uint8)tmp; /* SBSW_SBC_VALID_REG_IDX_LOOP */
    }
  }

  return result;
}

static Std_ReturnType PMIC_WriteAndLockProtectedRegisters(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType result = E_OK;
  uint16 tmp;
  uint8 checkSum = 0xFF;
  uint8 regIdx;

  /* ----- Implementation ----------------------------------------------- */
  /* #10 Write buffered values of protected registers */
  for (regIdx = 0; regIdx < ((uint8) PMIC_TLF35584_NUMBER_OF_PROTECTED_REGISTERS); regIdx++)
  {
	/* PRQA S 2985 2 */ /* MD_Sbc_2985_2986_RedundantOperation */
    result |= PMIC_WriteRegister(PMIC_GetAddrOfProtRegFromIdx(regIdx), PMIC_Tlf35584_ProtectedRegisterValues[regIdx]);  /* SBSW_SBC_NULLPTR_PARAM */
  }

  /* #20 Check if data was written successfully to protected registers */
  for (regIdx = 0; regIdx < ((uint8) PMIC_TLF35584_NUMBER_OF_PROTECTED_REGISTERS); regIdx++)
  {
	/* PRQA S 2985 2 */ /* MD_Sbc_2985_2986_RedundantOperation */
    result |= PMIC_ReadRegister(PMIC_GetAddrOfProtRegFromIdx(regIdx), &tmp); /* SBSW_SBC_LOCALPTR_PARAM */ /* SBSW_SBC_ACCESS_LOCAL */
    checkSum &= (PMIC_Tlf35584_ProtectedRegisterValues[regIdx] ^ (uint8)tmp);
  }

  if(checkSum != 0xFFu)
  {
    result |= E_NOT_OK;
  }

  SuspendAllInterrupts();
  /* >>> CRITICAL SECTION START >>> */

  /* #30 Lock protected registers */
  result |= PMIC_WriteRegister(PMIC_TLF35584_REG_ADDR_PROTCFG, PMIC_TLF35584_REG_CMD_PROTCFG_LOCK_SEQ1);  /* SBSW_SBC_NULLPTR_PARAM */
  result |= PMIC_WriteRegister(PMIC_TLF35584_REG_ADDR_PROTCFG, PMIC_TLF35584_REG_CMD_PROTCFG_LOCK_SEQ2);  /* SBSW_SBC_NULLPTR_PARAM */
  result |= PMIC_WriteRegister(PMIC_TLF35584_REG_ADDR_PROTCFG, PMIC_TLF35584_REG_CMD_PROTCFG_LOCK_SEQ3);  /* SBSW_SBC_NULLPTR_PARAM */
  result |= PMIC_WriteRegister(PMIC_TLF35584_REG_ADDR_PROTCFG, PMIC_TLF35584_REG_CMD_PROTCFG_LOCK_SEQ4);  /* SBSW_SBC_NULLPTR_PARAM */

  /* <<< CRITICAL SECTION END <<< */
  ResumeAllInterrupts();

  /* #40 Check if unlock procedure was successful */
  result |= PMIC_ReadRegister(PMIC_TLF35584_REG_ADDR_PROTSTAT, &tmp);  /* SBSW_SBC_LOCALPTR_PARAM */ /* SBSW_SBC_ACCESS_LOCAL */
  if (((uint8)tmp & PMIC_TLF35584_REG_MASK_PROTSTAT_LOCK) != PMIC_TLF35584_REG_MASK_PROTSTAT_LOCK) /* COV_SBC_LL_EVENTS */
  {
    result |= E_NOT_OK;
  }

  return result;
}

static Std_ReturnType PMIC_CheckProtectedRegisterValues(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType result = E_OK;
  uint16 tmp;
  uint8 regIdx;

  /* ----- Implementation ----------------------------------------------- */
  for (regIdx = 0; regIdx < ((uint8) PMIC_TLF35584_NUMBER_OF_PROTECTED_REGISTERS); regIdx++)
  {
	/* PRQA S 2985 2 */ /* MD_Sbc_2985_2986_RedundantOperation */
    result |= PMIC_ReadRegister(PMIC_GetAddrOfReadProtRegFromIdx(regIdx), &tmp);  /* SBSW_SBC_LOCALPTR_PARAM */ /* SBSW_SBC_ACCESS_LOCAL */
    if(PMIC_Tlf35584_ProtectedRegisterValues[regIdx] != (uint8)tmp)
    {
      result |= E_NOT_OK;
      break;
    }
  }

  return result;
}

static Std_ReturnType pmic_initDevice(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  /* PRQA S 2981 2 */ /* MD_MSR_RetVal */
  Std_ReturnType result = E_OK;
  uint16 ctrlLoopCycles = 0u;
  uint16 devStatValue;
  uint8 tmp;

  /* ----- Implementation ----------------------------------------------- */

  /* #10 Setup SPI buffers */
  result = Spi_SetupEB(
    SpiConf_SpiChannel_SpiChannel_TLF35584Q, /* SBSW_SBC_CALL_SPI_SETUPEB */
    (Spi_DataBufferType*) &Pmic_SpiOutBuffer,
    (Spi_DataBufferType*) &Pmic_SpiInBuffer,
    PMIC_TLF35584_SPI_TRANSFER_LENGTH);

  /* #20 Unlock protected registers */
  result |= PMIC_ReadAndUnlockProtectedRegisters();

  /* #30 Configure SYSPCFG0 (LDO_Stby) */
  PMIC_Tlf35584_ProtectedRegisterValues[SYSPCFG0] = PMIC_Tlf35584_SupplyConfig.SYSPCFG0normalOfSupplyConfig; /* SBSW_SBC_VALID_REG_IDX */

  /* #35 Configure SYSPCFG1 (ErrPin Monitoring, SS2 delay) */
  PMIC_Tlf35584_ProtectedRegisterValues[SYSPCFG1] = PMIC_Tlf35584_InitConfig.SYSPCFG1OfInitConfig; /* SBSW_SBC_VALID_REG_IDX */

  /* #40 Disable both watchdog peripherals */
  PMIC_Tlf35584_ProtectedRegisterValues[WDCFG0] = (PMIC_TLF35584_WDCFG0_DEFAULT_VAL /* SBSW_SBC_VALID_REG_IDX */
    & ~(PMIC_TLF35584_REG_MASK_WDCFG0_FWDEN | PMIC_TLF35584_REG_MASK_WDCFG0_WWDEN));

  /* #50 Lock protected registers */
  result |= PMIC_WriteAndLockProtectedRegisters();

  /* #55 Wait until the hardware has applied the requested values for the protected registers */
  while(PMIC_CheckProtectedRegisterValues() == E_NOT_OK)
  {
    if(ctrlLoopCycles > PMIC_Tlf35584_DeviceConfiguration.CtrlLoopMaxCyclesOfDeviceConfiguration)
    {
      result |= E_NOT_OK;
      break;
    }
    ctrlLoopCycles++;
  }

  /* #60 Set DEVCTRL (power supplies) and request device NORMAL state */
  tmp = (PMIC_Tlf35584_SupplyConfig.DEVCTRLnormalOfSupplyConfig | PMIC_TLF35584_DEVCTRL_NORMAL);
  /* PRQA S 2985 3 */ /* MD_Sbc_2985_2986_RedundantOperation */
  result |= PMIC_WriteRegister(PMIC_TLF35584_REG_ADDR_DEVCTRL, tmp); /* SBSW_SBC_NULLPTR_PARAM */
  result |= PMIC_WriteRegister(PMIC_TLF35584_REG_ADDR_DEVCTRLN, (uint8)((tmp) ^ 0xFFu)); /* SBSW_SBC_NULLPTR_PARAM */

  /* #70 Read back register and check values. */
  result |= PMIC_ReadRegister(PMIC_TLF35584_REG_ADDR_DEVSTAT, &devStatValue); /* SBSW_SBC_LOCALPTR_PARAM */ /* SBSW_SBC_ACCESS_LOCAL */
  if((devStatValue & PMIC_TLF35584_DEVSTAT_MASK) != tmp) /* COV_SBC_LL_EVENTS */
  {
    result |= E_NOT_OK;
  }
  return result;
}


/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/
void pmic_tlf35584_init(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType deviceResult;

  /* ----- Implementation ----------------------------------------------- */

  /* Reset the system data. No need for a critical area here as module is not initialized. */
  Pmic_SystemStatus.Events = 0; /* SBSW_SBC_DEVICE_INIT_LOOP */
  Pmic_SystemStatus.States = 0; /* SBSW_SBC_DEVICE_INIT_LOOP */
  Pmic_SystemStatus.Mode = PMIC_SYS_MODE_NORMAL; /* SBSW_SBC_DEVICE_INIT_LOOP */

  /* #50 Initialize hardware specific parts of SBC instance */
  deviceResult = pmic_initDevice();
  
  /* #60 If hardware specific parts of SBC instance is not initialized successfully */
  if (deviceResult == E_NOT_OK)
  {
    /* #70 Set the error flag and cancel initialization loop */
    Pmic_SystemStatus.Mode = PMIC_SYS_MODE_INVALID;
  }
} /* Sbc_Init() */ /* PRQA S 6010,6030 */ /* MD_MSR_STPTH,MD_MSR_STCYC */