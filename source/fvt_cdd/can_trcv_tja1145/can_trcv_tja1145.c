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
#include "can_trcv_tja1145.h"
#include <Spi.h>
#include "Spi_Cfg.h"


/*==================================================================================================
*                                      DEFINES AND MACROS
==================================================================================================*/
#define CANTRCV_TJA1145_IS_NOT_INIT         (0u)
#define CANTRCV_TJA1145_IS_INIT             (1u)
#define CANTRCV_TJA1145_SPI_BUFFER_SIZE     (14u)
#define CanTrcv_Tja1145_Req_OpModeMask      (0x0000000Fu)
#define CANTRCV_30_TJA1145_OP_MODE_NORMAL   CANTRCV_TRCVMODE_NORMAL
#define CANTRCV_30_TJA1145_OP_MODE_STANDBY  CANTRCV_TRCVMODE_STANDBY 
#define CANTRCV_30_TJA1145_OP_MODE_SLEEP    CANTRCV_TRCVMODE_SLEEP

#define CanTrcv_Tja1145_GetOpModeReq        (CanTrcv_Tja1145_Prob.requestState & CanTrcv_Tja1145_Req_OpModeMask)
#define CanTrcv_Tja1145_SetOpModeReq(mode) \
   CanTrcv_Tja1145_Prob.requestState &=  (~((uint32)CanTrcv_Tja1145_Req_OpModeMask)); \
   CanTrcv_Tja1145_Prob.requestState |=  (mode)

#define CanTrcv_Tja1145_TrcvModeType          CanTrcv_TrcvModeType
#define CanTrcv_Tja1145_StartTaskChangeOpMode CanTrcv_Tja1145_ChangeModeTaskSync

#define CANTRCV_TJA1145_REQ_NONE             0x00u
#define CANTRCV_TJA1145_REQ_RW_STATUS        0x01u
#define CANTRCV_TJA1145_REQ_RW_MODE          0x02u
#define CANTRCV_TJA1145_REQ_RW_IDMASKDB      0x03u

/* --- RwStatus request types --- */
#define CANTRCV_TJA1145_RT_RD_STATUS         0x01u
#define CANTRCV_TJA1145_RT_CLR_WUF           0x02u
#define CANTRCV_TJA1145_RT_CLR_ALL           0x03u
/*! CC Register */
#define CanTrcv_Tja1145_Cc_CMC_Mask          0x03u         /*!< CAN Mode control mask          */
#define CanTrcv_Tja1145_Cc_CMC_Offline       0x00u         /*!< CMC = Offline                  */
#define CanTrcv_Tja1145_Cc_CMC_Normal        0x01u         /*!< CMC = Normal                   */
#define CanTrcv_Tja1145_Cc_CMC_Listen        0x03u         /*!< CMC = Listen                   */
#define CanTrcv_Tja1145_Cc_CPNC              0x10u         /*!< CAN Partial Networking Control */
#define CanTrcv_Tja1145_Cc_PNCOK             0x20u         /*!< Partiion Networking Config OK  */
#define CanTrcv_Tja1145_Cc_CFDC              0x40u         /*!< CAN FD tolerance enabled       */
/*! Mc Register */
#define CanTrcv_Tja1145_Mc                   0x01u         /*!< Mode Control Register          */
#define CanTrcv_Tja1145_Mc_MC_Mask           0x07u         /*!< Mode Control Mask              */  
#define CanTrcv_Tja1145_Mc_MC_Sleep          0x01u         /*!< Sleep Mode                     */
#define CanTrcv_Tja1145_Mc_MC_Standby        0x04u         /*!< Standby Mode                   */
#define CanTrcv_Tja1145_Mc_MC_Normal         0x07u         /*!< Normal Mode                    */
/*! Tes Register */
#define CanTrcv_Tja1145_Tes_CW               0x01u         /*!< CAN Wake-up event              */
#define CanTrcv_Tja1145_Tes_CF               0x02u         /*!< CAN failure event              */
#define CanTrcv_Tja1145_Tes_CBS              0x10u         /*!< CAN bus silence event          */
#define CanTrcv_Tja1145_Tes_PNFDE            0x20u         /*!< PN Frame Detection Error event */
/*! Wes Register */
#define CanTrcv_Tja1145_Wes_WPF              0x01u         /*!< WAKE pin falling edge event    */
#define CanTrcv_Tja1145_Wes_WPR              0x02u         /*!< WAKE pin rising edge event     */
/*! Ecs Register */
#define CanTrcv_Tja1145_Ecs_SYSE             0x01u         /*!< System event status            */
#define CanTrcv_Tja1145_Ecs_TRXE             0x04u         /*!< Transceiver event status       */
#define CanTrcv_Tja1145_Ecs_WPE              0x08u         /*!< Wake pin event status          */
/*! Ses Register */
#define CanTrcv_Tja1145_Ses_SPIF             0x02u         /*!< SPI failure event              */
#define CanTrcv_Tja1145_Ses_OTW              0x04u         /*!< Overtemperature warning event  */
#define CanTrcv_Tja1145_Ses_PO               0x10u         /*!< Power-on event                 */

#define CanTrcv_Tja1145_Req_OpModeNormal     0x00000001u   /* Normal operation mode                  */
#define CanTrcv_Tja1145_Req_OpModeStandby    0x00000002u   /* Standby mode                           */
#define CanTrcv_Tja1145_Req_OpModeSleep      0x00000004u   /* Sleep mode                             */

/*! Transceiver Control registers */
#define CanTrcv_Tja1145_Cc                   0x20u         /*!< CAN Control              */
#define CanTrcv_Tja1145_Ts                   0x22u         /*!< Transceiver Status       */
#define CanTrcv_Tja1145_Tee                  0x23u         /*!< Transceiver Event Enable */

/*! Event capturing registers */
#define CanTrcv_Tja1145_Ecs                  0x60u         /*!< Event Capture Status     */
#define CanTrcv_Tja1145_Ses                  0x61u         /*!< System Event Status      */
#define CanTrcv_Tja1145_Tes                  0x63u         /*!< Transceiver Event Status */
#define CanTrcv_Tja1145_Wes                  0x64u         /*!< WAKE pin Event Status    */

/* Events */
#define CANTRCV_TJA1145_TASK_EV_START        0x02u
#define CANTRCV_TJA1145_TASK_EV_RW_STATUS    0x03u
#define CANTRCV_TJA1145_TASK_EV_RW_MODE      0x04u
#define CANTRCV_TJA1145_TASK_EV_RW_IDMASKDB  0x05u
#define CANTRCV_TJA1145_TASK_EV_CYCLE        0x0Eu
#define CANTRCV_TJA1145_TASK_EV_NONE         0xFFu   

/* Build an address */
#define CanTrcv_Tja1145_MkAdr(adr,ro)        (uint8)((( (adr)<<1 )&0xFEu) | (ro))

/*==================================================================================================
*                                  STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/
typedef struct CanTrcv_Tja1145_StatusFlagType_Tag
{
  uint8 Ts;   /*!< Transceiver status register */
  uint8 Ecs;  /*!< Event capture status register */
  uint8 Ses;  /*!< System event capture status register */
  uint8 Tes;  /*!< Transceiver event capture status register */
  uint8 Wes;  /*!< Wake pin event capture status register */
} CanTrcv_Tja1145_StatusFlagsType;

typedef enum
{
  CANTRCV_TRCVMODE_NORMAL = 0,  /**< Transceiver mode NORMAL */
  CANTRCV_TRCVMODE_SLEEP,       /**< Transceiver mode SLEEP */
  CANTRCV_TRCVMODE_STANDBY      /**< Transceiver mode STANDBY */
} CanTrcv_TrcvModeType;

typedef struct
{
    uint32 requestState;                       /* ! Holds the current request state */
    CanTrcv_Tja1145_TrcvModeType curOpMode;    /* ! Holds the current operation mode */
    uint8 isInit;
    uint8 CanControlWrite;                     /*!< Content of the Can Control Register -> Write access */
    uint8 ModeControlWrite;                    /*!< Content of the Mode Control Register -> Write access */
    uint8 CanTrcvSpiReqType;                   /* Stores the last requested spi command */
} CanTrcv_Tja1145_Prob_Type;

typedef struct
{
  uint8 reg; /* Value of register / address to access (LSB signals whether write ('0') or read access ('1') */
  uint8 size; /* Length of payload (the one byte required for register/address excluded) */
  P2CONST(uint8, TYPEDEF, CANTRCV_30_TJA1145_APPL_VAR) ptr;
} CanTrcv_Tja1145_SpiTxBlockType;

typedef struct
{
  CanTrcv_Tja1145_SpiTxBlockType block[4];
  uint8 numberOfBlocks; /* Signals how many "blocks" are / shall be used */
} CanTrcv_Tja1145_SpiTxBlockSeqType;

#define rdwr_block(bk, r, sz, p) \
  (bk).reg = (r); (bk).size = (sz); (bk).ptr = (P2CONST(uint8, AUTOMATIC, CANTRCV_TJA1145_APPL_VAR))(p)

#define write_block(bk, r, sz, p) rdwr_block(bk, CanTrcv_Tja1145_MkAdr(r, 0u), sz, p)
#define read_block(bk, r, sz, p) rdwr_block(bk, CanTrcv_Tja1145_MkAdr(r, 1u), sz, p)

/*==================================================================================================
*                                       LOCAL VARIABLES
==================================================================================================*/
static CanTrcv_Tja1145_Prob_Type CanTrcv_Tja1145_Prob;
static uint8 CanTrcv_Tja1145_SpiInBuffer[CANTRCV_TJA1145_SPI_BUFFER_SIZE]; /* PRQA S 3408 */ /* MD_CanTrcv_30_Tja1145_3408 */
static uint8 CanTrcv_Tja1145_SpiOutBuffer[CANTRCV_TJA1145_SPI_BUFFER_SIZE]; /* PRQA S 3408 */ /* MD_CanTrcv_30_Tja1145_3408 */

/*==================================================================================================
*                                       LOCAL FUNCTIONS
==================================================================================================*/
static Std_ReturnType CanTrcv_Tja1145_PrepareTxBlock(uint8 blockIdx, const CanTrcv_Tja1145_SpiTxBlockSeqType *blockInfo, Spi_ChannelType spiChannel)
{
  /* ----- Local Variables ---------------------------------------------- */
  uint8 i;
  uint8 bufferSize;
  uint8 bufferOffset;
  Std_ReturnType retval;
  const CanTrcv_Tja1145_SpiTxBlockType *curBlock;

  /* ----- Implementation ----------------------------------------------- */
  /* #100 Initialize local variables concerning: block, buffer-size, buffer-offset and out-buffer according to passed parameters. */
  curBlock = &blockInfo->block[blockIdx];
  bufferSize = curBlock->size + 1u;
  bufferOffset = (uint8)(blockIdx << 2);
  CanTrcv_Tja1145_SpiOutBuffer[bufferOffset] = curBlock->reg; /* SBSW_CANTRCV_LL_TJA1145_5 */

  /* #110 Copy data into out-buffer. */
  if (curBlock->ptr != NULL_PTR)
  {
    for (i = 1; i < bufferSize; ++i)
    {
      CanTrcv_Tja1145_SpiOutBuffer[bufferOffset + i] = curBlock->ptr[i - 1u]; /* SBSW_CANTRCV_LL_TJA1145_5 */
    }
  }

  /* #120 Set up the previously initialized out-buffer as external buffer within the SPI-driver. */
  retval = Spi_SetupEB(
      spiChannel,
      &CanTrcv_Tja1145_SpiOutBuffer[bufferOffset],
      &CanTrcv_Tja1145_SpiInBuffer[bufferOffset],
      bufferSize); /* SBSW_CANTRCV_LL_TJA1145_5 */

  return retval;
}

static Std_ReturnType CanTrcv_Tja1145_SpiTransmitBlock(const CanTrcv_Tja1145_SpiTxBlockSeqType *blockInfo)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retval;
  Spi_SequenceType sequence = SpiConf_SpiSequence_SpiSequence_TJA1145_CAN0_N;

  /* ----- Implementation ----------------------------------------------- */
  retval = E_OK;

  /* #100 Prepare the external buffer for transmission via the SPI-driver according to passed parameters.  */
  switch(blockInfo->numberOfBlocks) {
  case 4:
    retval  = CanTrcv_Tja1145_PrepareTxBlock(3, blockInfo, SpiConf_SpiChannel_SpiChannel_TJA1145_CAN0_3); /* SBSW_CANTRCV_HL_TJA1145_3 */
    /* This comment is required to fix: ESCAN00087596. */
  case 3: /* PRQA S 2003 */ /* MD_CanTrcv_30_Tja1145_2003 */
    retval |= CanTrcv_Tja1145_PrepareTxBlock(2, blockInfo, SpiConf_SpiChannel_SpiChannel_TJA1145_CAN0_2); /* SBSW_CANTRCV_HL_TJA1145_3 */
    retval |= CanTrcv_Tja1145_PrepareTxBlock(1, blockInfo, SpiConf_SpiChannel_SpiChannel_TJA1145_CAN0_1); /* SBSW_CANTRCV_HL_TJA1145_3 */
    /* This comment is required to fix: ESCAN00087596. */
  case 1: /* PRQA S 2003 */ /* MD_CanTrcv_30_Tja1145_2003 */
    retval |= CanTrcv_Tja1145_PrepareTxBlock(0, blockInfo, SpiConf_SpiChannel_SpiChannel_TJA1145_CAN0_0); /* SBSW_CANTRCV_HL_TJA1145_3 */
    break;
  default: /* COV_CANTRCV_HL_LL_TJA1145_CODECOV_DEFAULT */
    retval = E_NOT_OK; /* PRQA S 2982 */ /* MD_MSR_RetVal */
    break;
  }

  /* #110 Determine the correct SPI-sequence from passed parameters */
  switch(blockInfo->numberOfBlocks) {
  case 4:
    sequence = SpiConf_SpiSequence_SpiSequence_TJA1145_CAN0_L;
    break;
  case 3:
    sequence = SpiConf_SpiSequence_SpiSequence_TJA1145_CAN0_M;
    break;
  default: /* COV_CANTRCV_HL_LL_TJA1145_CODECOV_DEFAULT */
    retval = E_NOT_OK;
    break;
  }

  if (retval == E_OK)
  {
    /* #120 If passed parameters are OK do transmit via SPI-driver. */
    retval = Spi_SyncTransmit(sequence);
  }

  return retval;

}

static Std_ReturnType CanTrcv_Tja1145_RwStatus(uint32 requestType)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retval;
  CanTrcv_Tja1145_StatusFlagsType clrFlags;

  /* ----- Implementation ----------------------------------------------- */

  /* #110 Allocate the SPI. */
  CanTrcv_Tja1145_Prob.CanTrcvSpiReqType = CANTRCV_TJA1145_REQ_RW_STATUS; /* SBSW_CANTRCV_HL_TJA1145_1 */

  clrFlags.Ecs = 0;
  clrFlags.Ses = 0;
  clrFlags.Tes = 0;
  clrFlags.Wes = 0;    

  /* #120 Clear the status flags depending on <requestType>. */
  switch(requestType)
  {
      case CANTRCV_TJA1145_RT_RD_STATUS:
      {
        clrFlags.Tes = CanTrcv_Tja1145_Tes_CF;
      }
      break;
    case CANTRCV_TJA1145_RT_CLR_WUF:
    {
      clrFlags.Tes = (uint8)(CanTrcv_Tja1145_Tes_CF | CanTrcv_Tja1145_Tes_CW);
      clrFlags.Wes = (uint8)(CanTrcv_Tja1145_Wes_WPR | CanTrcv_Tja1145_Wes_WPF);  
    }
    break;
    case CANTRCV_TJA1145_RT_CLR_ALL:
    {
      clrFlags.Ecs = (uint8)(CanTrcv_Tja1145_Ecs_SYSE | CanTrcv_Tja1145_Ecs_TRXE | CanTrcv_Tja1145_Ecs_WPE);
      clrFlags.Ses = (uint8)(CanTrcv_Tja1145_Ses_SPIF | CanTrcv_Tja1145_Ses_OTW | CanTrcv_Tja1145_Ses_PO);
      clrFlags.Tes = (uint8)(CanTrcv_Tja1145_Tes_CW | CanTrcv_Tja1145_Tes_CF | CanTrcv_Tja1145_Tes_CBS | CanTrcv_Tja1145_Tes_PNFDE);
      clrFlags.Wes = (uint8)(CanTrcv_Tja1145_Wes_WPR | CanTrcv_Tja1145_Wes_WPF);          
    }
    break;
    default: /* COV_CANTRCV_HL_LL_TJA1145_CODECOV_DEFAULT */
    {
      /* Do nothing */
    }
    break;
  }
  
 
  /* #130 Set-up the external buffer within the SPI-driver.  */
  CanTrcv_Tja1145_SpiOutBuffer[0] = CanTrcv_Tja1145_MkAdr(CanTrcv_Tja1145_Ts, 1u); /* SBSW_CANTRCV_LL_TJA1145_5 */
  
  retval  = Spi_SetupEB(SpiConf_SpiChannel_SpiChannel_TJA1145_CAN0_0,
                      &CanTrcv_Tja1145_SpiOutBuffer[0],
                      &CanTrcv_Tja1145_SpiInBuffer[0],
                      2); /* SBSW_CANTRCV_LL_TJA1145_5 */
  
  
  CanTrcv_Tja1145_SpiOutBuffer[2] = CanTrcv_Tja1145_MkAdr(CanTrcv_Tja1145_Ecs, 0u); /* SBSW_CANTRCV_LL_TJA1145_5 */
  CanTrcv_Tja1145_SpiOutBuffer[3] = clrFlags.Ecs; /* SBSW_CANTRCV_LL_TJA1145_5 */
  CanTrcv_Tja1145_SpiOutBuffer[4] = clrFlags.Ses; /* SBSW_CANTRCV_LL_TJA1145_5 */
  
  
  retval |= Spi_SetupEB(SpiConf_SpiChannel_SpiChannel_TJA1145_CAN0_1,
                      &CanTrcv_Tja1145_SpiOutBuffer[2],
                      &CanTrcv_Tja1145_SpiInBuffer[2],
                      3); /* SBSW_CANTRCV_LL_TJA1145_5 */

  
  CanTrcv_Tja1145_SpiOutBuffer[5] = CanTrcv_Tja1145_MkAdr(CanTrcv_Tja1145_Tes, 0u); /* SBSW_CANTRCV_LL_TJA1145_5 */
  CanTrcv_Tja1145_SpiOutBuffer[6] = clrFlags.Tes; /* SBSW_CANTRCV_LL_TJA1145_5 */
  CanTrcv_Tja1145_SpiOutBuffer[7] = clrFlags.Wes; /* SBSW_CANTRCV_LL_TJA1145_5 */
  
  retval |= Spi_SetupEB(SpiConf_SpiChannel_SpiChannel_TJA1145_CAN0_2,
                      &CanTrcv_Tja1145_SpiOutBuffer[5],
                      &CanTrcv_Tja1145_SpiInBuffer[5],
                      3); /* SBSW_CANTRCV_LL_TJA1145_5 */

  /* #140 Process the set-up SPI-access. */
  if (retval == E_OK)
  {
    retval = Spi_SyncTransmit(SpiConf_SpiSequence_SpiSequence_TJA1145_CAN0_M);
  }

  if (retval == E_NOT_OK)
  {
    /* #160 If SPI-access FAILED: Unlock the SPI. */
    CanTrcv_Tja1145_Prob.CanTrcvSpiReqType = CANTRCV_TJA1145_REQ_NONE; /* SBSW_CANTRCV_HL_TJA1145_1 */
  }
  return retval;
}

static Std_ReturnType CanTrcv_Tja1145_CmtActionReqRwStatus(void)
{
  Std_ReturnType retVal;

  /* #110 Request all status-flags and by the way clear them. */
  retVal = CanTrcv_Tja1145_RwStatus(CANTRCV_TJA1145_RT_CLR_ALL);

  return retVal;
} /* CanTrcv_30_Tja1145_CmtActionReqRwStatus */

static Std_ReturnType CanTrcv_Tja1145_RwMode(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retval;
  CanTrcv_Tja1145_SpiTxBlockSeqType seqBufferInfo;


  /* ----- Implementation ----------------------------------------------- */

  /* #100 Allocate the SPI. */
  CanTrcv_Tja1145_Prob.CanTrcvSpiReqType = CANTRCV_TJA1145_REQ_RW_MODE; /* SBSW_CANTRCV_HL_TJA1145_1 */

  /* #110 Set-up the SPI-out-buffers for write- and read-access of Mode-registers. */

  /* *** WRITE *** */
  /* #120 Set-up write-access to Can-control and Mode-control registers. */
  write_block(seqBufferInfo.block[0], CanTrcv_Tja1145_Cc, 1, &CanTrcv_Tja1145_Prob.CanControlWrite); /* PRQA S 0312 */ /* MD_CanTrcv_30_Tja1145_0312 */ /* SBSW_CANTRCV_LL_TJA1145_2 */ /* SBSW_CANTRCV_LL_TJA1145_2 */ /* SBSW_CANTRCV_LL_TJA1145_2 */
  write_block(seqBufferInfo.block[1], CanTrcv_Tja1145_Mc, 1, &CanTrcv_Tja1145_Prob.ModeControlWrite); /* PRQA S 0312 */ /* MD_CanTrcv_30_Tja1145_0312 */ /* SBSW_CANTRCV_LL_TJA1145_2 */ /* SBSW_CANTRCV_LL_TJA1145_2 */ /* SBSW_CANTRCV_LL_TJA1145_2 */
  /* *** WRITE *** */

  /* *** READ *** */
  /* #130 Set-up read-access to Can-control register. */
  read_block(seqBufferInfo.block[2], CanTrcv_Tja1145_Cc, 1, NULL_PTR); /* SBSW_CANTRCV_LL_TJA1145_2 */ /* SBSW_CANTRCV_LL_TJA1145_2 */ /* SBSW_CANTRCV_LL_TJA1145_2 */

  /* #140 Set-up read-access to Mode-control register. */
  read_block(seqBufferInfo.block[3], CanTrcv_Tja1145_Mc, 1, NULL_PTR); /* SBSW_CANTRCV_LL_TJA1145_2 */ /* SBSW_CANTRCV_LL_TJA1145_2 */ /* SBSW_CANTRCV_LL_TJA1145_2 */
  seqBufferInfo.numberOfBlocks = 4;
  /* *** READ *** */

  /* #150 Process the set-up SPI-access. */
  retval = CanTrcv_Tja1145_SpiTransmitBlock(&seqBufferInfo); /* SBSW_CANTRCV_HL_TJA1145_3 */

  if (retval == E_NOT_OK)
  {
    /* #170 If SPI-access FAILED: Unlock the SPI. */
    CanTrcv_Tja1145_Prob.CanTrcvSpiReqType = CANTRCV_TJA1145_REQ_NONE; /* SBSW_CANTRCV_HL_TJA1145_1 */
  }
  return retval;
}

static Std_ReturnType CanTrcv_Tja1145_CmtActionReqRwMode(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;
  uint32 requestedOpMode;

  /* ----- Implementation ----------------------------------------------- */
  
  /* #100 Determine from global request flag which operating mode is requested. */
  requestedOpMode = CanTrcv_Tja1145_GetOpModeReq;

  /* #200 Depending on requested operating mode change set the corresponding values for Mode-registers: CanControl and ModeControl. */
  switch (requestedOpMode)
  {
  case CanTrcv_Tja1145_Req_OpModeNormal:
    CanTrcv_Tja1145_Prob.CanControlWrite = CanTrcv_Tja1145_Cc_CMC_Normal; /* SBSW_CANTRCV_HL_TJA1145_1 */
    CanTrcv_Tja1145_Prob.ModeControlWrite = CanTrcv_Tja1145_Mc_MC_Normal; /* SBSW_CANTRCV_HL_TJA1145_1 */
    break;

  case CanTrcv_Tja1145_Req_OpModeStandby:
    CanTrcv_Tja1145_Prob.CanControlWrite = CanTrcv_Tja1145_Cc_CMC_Offline; /* SBSW_CANTRCV_HL_TJA1145_1 */
    CanTrcv_Tja1145_Prob.ModeControlWrite = CanTrcv_Tja1145_Mc_MC_Standby; /* SBSW_CANTRCV_HL_TJA1145_1 */
    break;

  case CanTrcv_Tja1145_Req_OpModeSleep: /* COV_CANTRCV_HL_LL_TJA1145_CODECOV_EMULATED_SLEEP */
    CanTrcv_Tja1145_Prob.CanControlWrite = CanTrcv_Tja1145_Cc_CMC_Offline; /* SBSW_CANTRCV_HL_TJA1145_1 */
    CanTrcv_Tja1145_Prob.ModeControlWrite = CanTrcv_Tja1145_Mc_MC_Sleep; /* SBSW_CANTRCV_HL_TJA1145_1 */
    break;

  default: /* COV_CANTRCV_HL_LL_TJA1145_CODECOV_DEFAULT */
    /* Maybe Det */
    break;
  }

  CanTrcv_Tja1145_Prob.CanControlWrite |= (CanTrcv_Tja1145_Cc_CFDC); /* SBSW_CANTRCV_HL_TJA1145_1 */

  /* #300 Request the SPI to transmit the prepared HW-register. */
  retVal = CanTrcv_Tja1145_RwMode();

  return retVal;
} /* CanTrcv_30_Tja1145_CmtActionReqRwMode */

static Std_ReturnType CanTrcv_Tja1145_ChangeModeTaskSync(void)
{
  /* ----- Local Variables ---------------------------------------------- */
  Std_ReturnType retVal;
  uint32 requestedOpMode;

  /* ----- Implementation ----------------------------------------------- */
  retVal = E_NOT_OK;
  requestedOpMode = CanTrcv_Tja1145_GetOpModeReq;

  if (requestedOpMode == CanTrcv_Tja1145_Req_OpModeNormal)
  {
    /* #100 In case of requested mode is NORMAL request and clear the status flags of CAN transceiver HW. */
    if (CanTrcv_Tja1145_CmtActionReqRwStatus() == E_OK)
    {
      retVal = E_OK;
    }
  }
  else
  {
    retVal = E_OK;
  }

  /* #110 Do further processing only if the previous one succeeded. */
  if (retVal == E_OK)
  {
    /* #120 Re-set the return value to not OK for further processing. */
    retVal = E_NOT_OK;

    /* #130 Request the CAN transceiver HW to change the operating mode. */
    if (CanTrcv_Tja1145_CmtActionReqRwMode() == E_OK)
    {
        retVal = E_OK;
    }
  }

  if (retVal == E_NOT_OK)
  {
    /* #220 Unlock the SPI. */
    CanTrcv_Tja1145_Prob.CanTrcvSpiReqType = CANTRCV_TJA1145_REQ_NONE; /* SBSW_CANTRCV_HL_TJA1145_1 */
  }

  return retVal;
}

/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/
void can_trcv_tja1145_init(void)
{
    Std_ReturnType modeSet = E_NOT_OK;

    CanTrcv_Tja1145_SetOpModeReq(CanTrcv_Tja1145_Req_OpModeNormal);
    modeSet = CanTrcv_Tja1145_StartTaskChangeOpMode();

    if (modeSet == E_OK)
    {
        /* #310 Mode change was successful: Store the current operating mode. (only SPI-interface) */
        CanTrcv_Tja1145_Prob.curOpMode = CANTRCV_30_TJA1145_OP_MODE_NORMAL; /* SBSW_CANTRCV_HL_TJA1145_1 */

        /* #320 Mode change was successful: Clear all pending requests. (only SPI-interface) */
        CanTrcv_Tja1145_Prob.requestState = CANTRCV_TJA1145_REQ_NONE; /* SBSW_CANTRCV_HL_TJA1145_1 */
        /* #330 Mode change was successful: Set current transceiver channel to initialized. */
        CanTrcv_Tja1145_Prob.isInit = CANTRCV_TJA1145_IS_INIT; /* SBSW_CANTRCV_HL_TJA1145_1 */
    }
}