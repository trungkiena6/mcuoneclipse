/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : SM2.c
**     Project     : ProcessorExpert
**     Processor   : MK64FN1M0VLL12
**     Component   : SPIMaster_LDD
**     Version     : Component 01.111, Driver 01.08, CPU db: 3.00.000
**     Repository  : Kinetis
**     Compiler    : GNU C Compiler
**     Date/Time   : 2016-07-07, 11:18, # CodeGen: 165
**     Abstract    :
**         This component "SPIMaster_LDD" implements MASTER part of synchronous
**         serial master-slave communication.
**     Settings    :
**          Component name                                 : SM2
**          Device                                         : SPI1
**          Interrupt service/event                        : Enabled
**            Input interrupt                              : INT_SPI1
**            Input interrupt priority                     : medium priority
**            Output interrupt                             : INT_SPI1
**            Output interrupt priority                    : medium priority
**          Settings                                       : 
**            Input pin                                    : Enabled
**              Pin                                        : ADC1_SE5a/PTE1/LLWU_P0/SPI1_SOUT/UART1_RX/SDHC0_D0/TRACE_D3/I2C1_SCL/SPI1_SIN
**            Output pin                                   : Enabled
**              Pin                                        : ADC0_DM2/ADC1_SE7a/PTE3/SPI1_SIN/UART1_RTS_b/SDHC0_CMD/TRACE_D1/SPI1_SOUT
**            Clock pin                                    : 
**              Pin                                        : ADC0_DP2/ADC1_SE6a/PTE2/LLWU_P1/SPI1_SCK/UART1_CTS_b/SDHC0_DCLK/TRACE_D2
**            Chip select list                             : 0
**            CS external demultiplexer                    : Disabled
**            Attribute set list                           : 2
**              Attribute set 0                            : 
**                Width                                    : 8 bits
**                MSB first                                : yes
**                Clock polarity                           : Low
**                Clock phase                              : Capture on leading edge
**                Parity                                   : None
**                Chip select toggling                     : no
**                Clock rate index                         : 0
**                Delay after transfer index               : 0
**                CS to CLK delay index                    : 0
**                CLK to CS delay index                    : 0
**              Attribute set 1                            : 
**                Width                                    : 8 bits
**                MSB first                                : yes
**                Clock polarity                           : Low
**                Clock phase                              : Capture on leading edge
**                Parity                                   : None
**                Chip select toggling                     : no
**                Clock rate index                         : 1
**                Delay after transfer index               : 0
**                CS to CLK delay index                    : 0
**                CLK to CS delay index                    : 0
**            Clock rate                                   : 375 kHz
**            Delay after transfer                         : 0.033333 �s
**            CS to CLK delay                              : 0.033333 �s
**            CLK to CS delay                              : 0.033333 �s
**            HW input buffer size                         : 1
**            HW input watermark                           : 1
**            HW output buffer size                        : 1
**            HW output watermark                          : 1
**          Initialization                                 : 
**            Initial chip select                          : 0
**            Initial attribute set                        : 0
**            Enabled in init. code                        : yes
**            Auto initialization                          : yes
**            Event mask                                   : 
**              OnBlockSent                                : Disabled
**              OnBlockReceived                            : Enabled
**              OnError                                    : Disabled
**          CPU clock/configuration selection              : 
**            Clock configuration 0                        : This component enabled
**            Clock configuration 1                        : This component disabled
**            Clock configuration 2                        : This component disabled
**            Clock configuration 3                        : This component disabled
**            Clock configuration 4                        : This component disabled
**            Clock configuration 5                        : This component disabled
**            Clock configuration 6                        : This component disabled
**            Clock configuration 7                        : This component disabled
**     Contents    :
**         Init                - LDD_TDeviceData* SM2_Init(LDD_TUserData *UserDataPtr);
**         Deinit              - void SM2_Deinit(LDD_TDeviceData *DeviceDataPtr);
**         Enable              - LDD_TError SM2_Enable(LDD_TDeviceData *DeviceDataPtr);
**         Disable             - LDD_TError SM2_Disable(LDD_TDeviceData *DeviceDataPtr);
**         SendBlock           - LDD_TError SM2_SendBlock(LDD_TDeviceData *DeviceDataPtr, LDD_TData...
**         ReceiveBlock        - LDD_TError SM2_ReceiveBlock(LDD_TDeviceData *DeviceDataPtr, LDD_TData...
**         SelectConfiguration - LDD_TError SM2_SelectConfiguration(LDD_TDeviceData *DeviceDataPtr, uint8_t...
**
**     Copyright : 1997 - 2015 Freescale Semiconductor, Inc. 
**     All Rights Reserved.
**     
**     Redistribution and use in source and binary forms, with or without modification,
**     are permitted provided that the following conditions are met:
**     
**     o Redistributions of source code must retain the above copyright notice, this list
**       of conditions and the following disclaimer.
**     
**     o Redistributions in binary form must reproduce the above copyright notice, this
**       list of conditions and the following disclaimer in the documentation and/or
**       other materials provided with the distribution.
**     
**     o Neither the name of Freescale Semiconductor, Inc. nor the names of its
**       contributors may be used to endorse or promote products derived from this
**       software without specific prior written permission.
**     
**     THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**     ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**     WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**     DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**     ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**     LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**     ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**     (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**     SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**     
**     http: www.freescale.com
**     mail: support@freescale.com
** ###################################################################*/
/*!
** @file SM2.c
** @version 01.08
** @brief
**         This component "SPIMaster_LDD" implements MASTER part of synchronous
**         serial master-slave communication.
*/         
/*!
**  @addtogroup SM2_module SM2 module documentation
**  @{
*/         

/* MODULE SM2. */
/*lint -save  -e926 -e927 -e928 -e929 Disable MISRA rule (11.4) checking. */

#include "FATM1.h"
#include "SM2.h"
#include "FreeRTOS.h" /* FreeRTOS interface */

#ifdef __cplusplus
extern "C" {
#endif 

#define AVAILABLE_EVENTS_MASK (LDD_SPIMASTER_ON_BLOCK_RECEIVED)

/* These constants contain pins masks */
#define SM2_AVAILABLE_PIN_MASK (LDD_SPIMASTER_INPUT_PIN | LDD_SPIMASTER_OUTPUT_PIN | LDD_SPIMASTER_CLK_PIN)

static const uint32_t ConfigurationSet[SM2_CONFIGURATION_COUNT] = {
0xB8020006U,0xB8010000U
};

static const uint32_t TxCommandList[SM2_CONFIGURATION_COUNT] = {
0x80000000U,0x80000000U
};

typedef struct {
  bool EnUser;                         /* Enable/Disable device */
  uint32_t TxCommand;                  /* Current Tx command */
  LDD_SPIMASTER_TError ErrFlag;        /* Error flags */
  uint16_t InpRecvDataNum;             /* The counter of received characters */
  uint8_t *InpDataPtr;                 /* The buffer pointer for received characters */
  uint16_t InpDataNumReq;              /* The counter of characters to receive by ReceiveBlock() */
  uint16_t OutSentDataNum;             /* The counter of sent characters */
  uint8_t *OutDataPtr;                 /* The buffer pointer for data to be transmitted */
  uint16_t OutDataNumReq;              /* The counter of characters to be send by SendBlock() */
  LDD_TUserData *UserData;             /* User device data structure */
} SM2_TDeviceData;                     /* Device data structure type */

typedef SM2_TDeviceData* SM2_TDeviceDataPtr ; /* Pointer to the device data structure. */

/* {FreeRTOS RTOS Adapter} Static object used for simulation of dynamic driver memory allocation */
static SM2_TDeviceData DeviceDataPrv__DEFAULT_RTOS_ALLOC;
/* {FreeRTOS RTOS Adapter} Global variable used for passing a parameter into ISR */
static SM2_TDeviceDataPtr INT_SPI1__BAREBOARD_RTOS_ISRPARAM;
/* Internal method prototypes */
static void HWEnDi(LDD_TDeviceData *DeviceDataPtr);

/*
** ===================================================================
**     Method      :  SM2_Init (component SPIMaster_LDD)
*/
/*!
**     @brief
**         Initializes the device. Allocates memory for the device data
**         structure, allocates interrupt vectors and sets interrupt
**         priority, sets pin routing, sets timing, etc.
**         If the "Enable in init. code" is set to "yes" value then the
**         device is also enabled(see the description of the Enable()
**         method). In this case the Enable() method is not necessary
**         and needn't to be generated. 
**         This method can be called only once. Before the second call
**         of Init() the Deinit() must be called first.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. This pointer will be
**                           passed as an event or callback parameter.
**     @return
**                         - Device data structure pointer.
*/
/* ===================================================================*/
LDD_TDeviceData* SM2_Init(LDD_TUserData *UserDataPtr)
{
  /* Allocate LDD device structure */
  SM2_TDeviceDataPtr DeviceDataPrv;

  /* {FreeRTOS RTOS Adapter} Driver memory allocation: Dynamic allocation is simulated by a pointer to the static object */
  DeviceDataPrv = &DeviceDataPrv__DEFAULT_RTOS_ALLOC;
  DeviceDataPrv->UserData = UserDataPtr; /* Store the RTOS device structure */
  /* Interrupt vector(s) allocation */
  /* {FreeRTOS RTOS Adapter} Set interrupt vector: IVT is static, ISR parameter is passed by the global variable */
  INT_SPI1__BAREBOARD_RTOS_ISRPARAM = DeviceDataPrv;
  DeviceDataPrv->EnUser = TRUE;        /* Enable device */
  DeviceDataPrv->TxCommand = 0x80000000U; /* Initialization of current Tx command */
  DeviceDataPrv->ErrFlag = 0x00U;      /* Clear error flags */
  /* Clear the receive counters and pointer */
  DeviceDataPrv->InpRecvDataNum = 0x00U; /* Clear the counter of received characters */
  DeviceDataPrv->InpDataNumReq = 0x00U; /* Clear the counter of characters to receive by ReceiveBlock() */
  DeviceDataPrv->InpDataPtr = NULL;    /* Clear the buffer pointer for received characters */
  /* Clear the transmit counters and pointer */
  DeviceDataPrv->OutSentDataNum = 0x00U; /* Clear the counter of sent characters */
  DeviceDataPrv->OutDataNumReq = 0x00U; /* Clear the counter of characters to be send by SendBlock() */
  DeviceDataPrv->OutDataPtr = NULL;    /* Clear the buffer pointer for data to be transmitted */
  /* SIM_SCGC6: SPI1=1 */
  SIM_SCGC6 |= SIM_SCGC6_SPI1_MASK;
  /* Interrupt vector(s) priority setting */
  /* NVICIP27: PRI27=0x70 */
  NVICIP27 = NVIC_IP_PRI27(0x70);
  /* NVICISER0: SETENA|=0x08000000 */
  NVICISER0 |= NVIC_ISER_SETENA(0x08000000);
  /* SIM_SCGC5: PORTE=1 */
  SIM_SCGC5 |= SIM_SCGC5_PORTE_MASK;
  /* PORTE_PCR1: ISF=0,MUX=7 */
  PORTE_PCR1 = (uint32_t)((PORTE_PCR1 & (uint32_t)~(uint32_t)(
                PORT_PCR_ISF_MASK
               )) | (uint32_t)(
                PORT_PCR_MUX(0x07)
               ));
  /* PORTE_PCR3: ISF=0,MUX=7 */
  PORTE_PCR3 = (uint32_t)((PORTE_PCR3 & (uint32_t)~(uint32_t)(
                PORT_PCR_ISF_MASK
               )) | (uint32_t)(
                PORT_PCR_MUX(0x07)
               ));
  /* PORTE_PCR2: ISF=0,MUX=2 */
  PORTE_PCR2 = (uint32_t)((PORTE_PCR2 & (uint32_t)~(uint32_t)(
                PORT_PCR_ISF_MASK |
                PORT_PCR_MUX(0x05)
               )) | (uint32_t)(
                PORT_PCR_MUX(0x02)
               ));
  /* SPI1_MCR: MSTR=0,CONT_SCKE=0,DCONF=0,FRZ=0,MTFE=0,PCSSE=0,ROOE=1,??=0,??=0,PCSIS=0,DOZE=0,MDIS=0,DIS_TXF=0,DIS_RXF=0,CLR_TXF=0,CLR_RXF=0,SMPL_PT=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,HALT=1 */
  SPI1_MCR = SPI_MCR_DCONF(0x00) |
             SPI_MCR_ROOE_MASK |
             SPI_MCR_PCSIS(0x00) |
             SPI_MCR_SMPL_PT(0x00) |
             SPI_MCR_HALT_MASK;        /* Set Configuration register */
  /* SPI1_MCR: MSTR=1,CONT_SCKE=0,DCONF=0,FRZ=0,MTFE=0,PCSSE=0,ROOE=1,??=0,??=0,PCSIS=0,DOZE=0,MDIS=0,DIS_TXF=1,DIS_RXF=1,CLR_TXF=1,CLR_RXF=1,SMPL_PT=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,HALT=1 */
  SPI1_MCR = SPI_MCR_MSTR_MASK |
             SPI_MCR_DCONF(0x00) |
             SPI_MCR_ROOE_MASK |
             SPI_MCR_PCSIS(0x00) |
             SPI_MCR_DIS_TXF_MASK |
             SPI_MCR_DIS_RXF_MASK |
             SPI_MCR_CLR_TXF_MASK |
             SPI_MCR_CLR_RXF_MASK |
             SPI_MCR_SMPL_PT(0x00) |
             SPI_MCR_HALT_MASK;        /* Set Configuration register */
  /* SPI1_CTAR0: DBR=1,FMSZ=7,CPOL=0,CPHA=0,LSBFE=0,PCSSCK=0,PASC=0,PDT=0,PBR=2,CSSCK=0,ASC=0,DT=0,BR=6 */
  SPI1_CTAR0 = SPI_CTAR_DBR_MASK |
               SPI_CTAR_FMSZ(0x07) |
               SPI_CTAR_PCSSCK(0x00) |
               SPI_CTAR_PASC(0x00) |
               SPI_CTAR_PDT(0x00) |
               SPI_CTAR_PBR(0x02) |
               SPI_CTAR_CSSCK(0x00) |
               SPI_CTAR_ASC(0x00) |
               SPI_CTAR_DT(0x00) |
               SPI_CTAR_BR(0x06);      /* Set Clock and Transfer Attributes register */
  /* SPI1_SR: TCF=1,TXRXS=0,??=0,EOQF=1,TFUF=1,??=0,TFFF=1,??=0,??=0,??=0,??=1,??=0,RFOF=1,??=0,RFDF=1,??=0,TXCTR=0,TXNXTPTR=0,RXCTR=0,POPNXTPTR=0 */
  SPI1_SR = SPI_SR_TCF_MASK |
            SPI_SR_EOQF_MASK |
            SPI_SR_TFUF_MASK |
            SPI_SR_TFFF_MASK |
            SPI_SR_RFOF_MASK |
            SPI_SR_RFDF_MASK |
            SPI_SR_TXCTR(0x00) |
            SPI_SR_TXNXTPTR(0x00) |
            SPI_SR_RXCTR(0x00) |
            SPI_SR_POPNXTPTR(0x00) |
            0x00200000U;               /* Clear flags */
  /* SPI1_RSER: TCF_RE=0,??=0,??=0,EOQF_RE=0,TFUF_RE=0,??=0,TFFF_RE=0,TFFF_DIRS=0,??=0,??=0,??=0,??=0,RFOF_RE=0,??=0,RFDF_RE=1,RFDF_DIRS=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0 */
  SPI1_RSER = SPI_RSER_RFDF_RE_MASK;   /* Set DMA Interrupt Request Select and Enable register */
  /* Registration of the device structure */
  PE_LDD_RegisterDeviceStructure(PE_LDD_COMPONENT_SM2_ID,DeviceDataPrv);
  return ((LDD_TDeviceData *)DeviceDataPrv); /* Return pointer to the data data structure */
}

/*
** ===================================================================
**     Method      :  SM2_Deinit (component SPIMaster_LDD)
*/
/*!
**     @brief
**         This method deinitializes the device. It switches off the
**         device, frees the device data structure memory, interrupts
**         vectors, etc.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
*/
/* ===================================================================*/
void SM2_Deinit(LDD_TDeviceData *DeviceDataPtr)
{
  (void)DeviceDataPtr;                 /* Parameter is not used, suppress unused argument warning */
  /* SPI1_MCR: MSTR=0,CONT_SCKE=0,DCONF=0,FRZ=0,MTFE=0,PCSSE=0,ROOE=0,??=0,??=0,PCSIS=0,DOZE=0,MDIS=1,DIS_TXF=0,DIS_RXF=0,CLR_TXF=0,CLR_RXF=0,SMPL_PT=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,HALT=1 */
  SPI1_MCR = SPI_MCR_DCONF(0x00) |
             SPI_MCR_PCSIS(0x00) |
             SPI_MCR_MDIS_MASK |
             SPI_MCR_SMPL_PT(0x00) |
             SPI_MCR_HALT_MASK;        /* Disable device */
  /* Restoring the interrupt vector */
  /* {FreeRTOS RTOS Adapter} Restore interrupt vector: IVT is static, no code is generated */
  /* Unregistration of the device structure */
  PE_LDD_UnregisterDeviceStructure(PE_LDD_COMPONENT_SM2_ID);
  /* Deallocation of the device structure */
  /* {FreeRTOS RTOS Adapter} Driver memory deallocation: Dynamic allocation is simulated, no deallocation code is generated */
  /* SIM_SCGC6: SPI1=0 */
  SIM_SCGC6 &= (uint32_t)~(uint32_t)(SIM_SCGC6_SPI1_MASK);
}

/*
** ===================================================================
**     Method      :  SM2_Enable (component SPIMaster_LDD)
*/
/*!
**     @brief
**         This method enables SPI device. This method is intended to
**         be used together with [Disable()] method to temporary switch
**         On/Off the device after the device is initialized. This
**         method is required if the [Enabled in init. code] property
**         is set to "no" value.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - The device doesn't work in the
**                           active clock configuration
*/
/* ===================================================================*/
LDD_TError SM2_Enable(LDD_TDeviceData *DeviceDataPtr)
{
  if (!((SM2_TDeviceDataPtr)DeviceDataPtr)->EnUser) { /* Is the device disabled by user? */
    ((SM2_TDeviceDataPtr)DeviceDataPtr)->EnUser = TRUE; /* If yes then set the flag "device enabled" */
    HWEnDi((SM2_TDeviceDataPtr)DeviceDataPtr); /* Enable the device */
  }
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  SM2_Disable (component SPIMaster_LDD)
*/
/*!
**     @brief
**         Disables the SPI device. When the device is disabled, some
**         component methods should not be called. If so, error
**         ERR_DISABLED may be reported. This method is intended to be
**         used together with [Enable()] method to temporary switch
**         on/off the device after the device is initialized. This
**         method is not required. The [Deinit()] method can be used to
**         switch off and uninstall the device.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - The device doesn't work in the
**                           active clock configuration
*/
/* ===================================================================*/
LDD_TError SM2_Disable(LDD_TDeviceData *DeviceDataPtr)
{
  if (((SM2_TDeviceDataPtr)DeviceDataPtr)->EnUser) { /* Is the device enabled by user? */
    ((SM2_TDeviceDataPtr)DeviceDataPtr)->EnUser = FALSE; /* If yes then set the flag "device disabled" */
    HWEnDi((SM2_TDeviceDataPtr)DeviceDataPtr); /* Disable the device */
  }
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  SM2_ReceiveBlock (component SPIMaster_LDD)
*/
/*!
**     @brief
**         This method specifies the number of data to receive. The
**         method returns ERR_BUSY until the specified number of
**         characters is received. The method [CancelBlockReception]
**         can be used to cancel a running receive operation. If a
**         receive operation is not in progress (the method was not
**         called or a previous operation has already finished) all
**         received characters will be lost without any notification.
**         To prevent the loss of data call the method immediately
**         after the last receive operation has finished (e.g. from the
**         [OnBlockReceived] event). This method finishes immediately
**         after calling it - it doesn't wait the end of data reception.
**         Use event [OnBlockReceived] to check the end of data
**         reception or method GetReceivedDataNum to check the state of
**         receiving.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @param
**         BufferPtr       - Pointer to A buffer where
**                           received characters will be stored.
**     @param
**         Size            - Size of the block
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active clock configuration
**                           ERR_DISABLED - Component is disabled
**                           ERR_BUSY - The previous receive request is
**                           pending
*/
/* ===================================================================*/
LDD_TError SM2_ReceiveBlock(LDD_TDeviceData *DeviceDataPtr, LDD_TData *BufferPtr, uint16_t Size)
{
  /* Device state test - this test can be disabled by setting the "Ignore enable test"
     property to the "yes" value in the "Configuration inspector" */
  if (!((SM2_TDeviceDataPtr)DeviceDataPtr)->EnUser) { /* Is the device disabled by user? */
    return ERR_DISABLED;               /* If yes then error */
  }
  if (((SM2_TDeviceDataPtr)DeviceDataPtr)->InpDataNumReq != 0x00U) { /* Is the previous receive operation pending? */
    return ERR_BUSY;                   /* If yes then error */
  }
  /* {FreeRTOS RTOS Adapter} Critical section begin (RTOS function call is defined by FreeRTOS RTOS Adapter property) */
  EnterCritical();
  ((SM2_TDeviceDataPtr)DeviceDataPtr)->InpDataPtr = (uint8_t*)BufferPtr; /* Store a pointer to the input data. */
  ((SM2_TDeviceDataPtr)DeviceDataPtr)->InpDataNumReq = Size; /* Store a number of characters to be received. */
  ((SM2_TDeviceDataPtr)DeviceDataPtr)->InpRecvDataNum = 0x00U; /* Set number of received characters to zero. */
  /* {FreeRTOS RTOS Adapter} Critical section ends (RTOS function call is defined by FreeRTOS RTOS Adapter property) */
  ExitCritical();
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  SM2_SendBlock (component SPIMaster_LDD)
*/
/*!
**     @brief
**         Sends a block of characters. The method returns ERR_BUSY
**         when the previous block transmission is not completed. The
**         method [CancelBlockTransmission] can be used to cancel a
**         transmit operation. This method finishes immediately after
**         calling it - it doesn't wait the end of data transmission.
**         Use event [OnBlockSent] to check the end of data
**         transmission or method GetSentDataNum to check the state of
**         sending.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @param
**         BufferPtr       - Pointer to the block of data
**                           to send.
**     @param
**         Size            - Number of characters in the buffer.
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active clock configuration
**                           ERR_DISABLED - Component is disabled
**                           ERR_BUSY - The previous transmit request is
**                           pending
*/
/* ===================================================================*/
LDD_TError SM2_SendBlock(LDD_TDeviceData *DeviceDataPtr, LDD_TData *BufferPtr, uint16_t Size)
{
  /* Device state test - this test can be disabled by setting the "Ignore enable test"
     property to the "yes" value in the "Configuration inspector" */
  if (!((SM2_TDeviceDataPtr)DeviceDataPtr)->EnUser) { /* Is the device disabled by user? */
    return ERR_DISABLED;               /* If yes then error */
  }
  if (((SM2_TDeviceDataPtr)DeviceDataPtr)->OutDataNumReq != 0x00U) { /* Is the previous transmit operation pending? */
    return ERR_BUSY;                   /* If yes then error */
  }
  /* {FreeRTOS RTOS Adapter} Critical section begin (RTOS function call is defined by FreeRTOS RTOS Adapter property) */
  EnterCritical();
  ((SM2_TDeviceDataPtr)DeviceDataPtr)->OutDataPtr = (uint8_t*)BufferPtr; /* Set a pointer to the output data. */
  ((SM2_TDeviceDataPtr)DeviceDataPtr)->OutDataNumReq = Size; /* Set the counter of characters to be sent. */
  ((SM2_TDeviceDataPtr)DeviceDataPtr)->OutSentDataNum = 0x00U; /* Clear the counter of sent characters. */
  SPI_PDD_EnableDmasInterrupts(SPI1_BASE_PTR, SPI_PDD_TX_FIFO_FILL_INT_DMA); /* Enable TX interrupt */
  /* {FreeRTOS RTOS Adapter} Critical section ends (RTOS function call is defined by FreeRTOS RTOS Adapter property) */
  ExitCritical();
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  SM2_SelectConfiguration (component SPIMaster_LDD)
*/
/*!
**     @brief
**         This method selects attributes of communication from the
**         [Attribute set list] and select a chip select from the [Chip
**         select list]. Once any configuration is selected, a
**         transmission can be started multiple times. This method is
**         available if number of chip selects or number of attribute
**         set is greater than 1. If the device doesn't support chip
**         select functionality the ChipSelect parameter is ignored.
**     @param
**         DeviceDataPtr   - Device data structure
**                           pointer returned by [Init] method.
**     @param
**         ChipSelect      - Chip select index from the
**                           [Chip select list].
**     @param
**         AttributeSet    - Communication attribute
**                           index from the [Attribute set list]
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active clock configuration
**                           ERR_DISABLED - Component is disabled
**                           ERR_PARAM_CHIP_SELECT - Chip select index
**                           is out of range
**                           ERR_PARAM_ATTRIBUTE_SET - Attribute set
**                           index is out of range
**                           ERR_BUSY - Transmission is in progress
*/
/* ===================================================================*/
LDD_TError SM2_SelectConfiguration(LDD_TDeviceData *DeviceDataPtr, uint8_t ChipSelect, uint8_t AttributeSet)
{
  /* Device state test - this test can be disabled by setting the "Ignore enable test"
     property to the "yes" value in the "Configuration inspector" */
  if (!((SM2_TDeviceDataPtr)DeviceDataPtr)->EnUser) { /* Is the device disabled by user? */
    return ERR_DISABLED;               /* If yes then error */
  }
  (void)ChipSelect;                    /* Parameter is not used, suppress unused argument warning */
  if (AttributeSet >= SM2_CONFIGURATION_COUNT) { /* Is Attribute set index out of range? */
    return ERR_PARAM_ATTRIBUTE_SET;    /* Yes, return ERR_PARAM */
  }
  if ((((SM2_TDeviceDataPtr)DeviceDataPtr)->InpDataNumReq != 0x00U) || (((SM2_TDeviceDataPtr)DeviceDataPtr)->OutDataNumReq != 0x00U)) { /* Is the previous receive operation pending? */
    return ERR_BUSY;                   /* If yes then error */
  }
  SPI_PDD_EnableHaltMode(SPI1_BASE_PTR,PDD_ENABLE); /* Enter to STOPPED mode */
  while (SPI_PDD_GetTxRxActiveFlag(SPI1_BASE_PTR)) {} /* Wait until the current transmission finished */
  SPI_PDD_WriteMasterClockTransferAttributeReg(SPI1_BASE_PTR,0U,ConfigurationSet[AttributeSet]); /* Set required configuration */
  ((SM2_TDeviceDataPtr)DeviceDataPtr)->TxCommand = TxCommandList[AttributeSet]; /* Prepare command for transmision */
  SPI_PDD_EnableHaltMode(SPI1_BASE_PTR,PDD_DISABLE); /* Leave the STOPPED mode */
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  SM2_Interrupt (component SPIMaster_LDD)
**
**     Description :
**         The ISR function handling the device receive/transmit 
**         interrupt.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
PE_ISR(SM2_Interrupt)
{
  /* {FreeRTOS RTOS Adapter} ISR parameter is passed through the global variable */
  SM2_TDeviceDataPtr DeviceDataPrv = INT_SPI1__BAREBOARD_RTOS_ISRPARAM;
  uint32_t StatReg = SPI_PDD_GetInterruptFlags(SPI1_BASE_PTR); /* Read status register */
  uint16_t Data;                       /* Temporary variable for data */

  if ((StatReg & SPI_PDD_RX_FIFO_OVERFLOW_INT) != 0U) { /* Is any error flag set? */
    SPI_PDD_ClearInterruptFlags(SPI1_BASE_PTR,SPI_PDD_RX_FIFO_OVERFLOW_INT); /* Clear error flags */
  }
  if ((StatReg & SPI_PDD_RX_FIFO_DRAIN_INT_DMA) != 0U) { /* Is any char in HW buffer? */
    Data = (uint16_t)SPI_PDD_ReadPopRxFIFOReg(SPI1_BASE_PTR); /* Read character from receiver */
    SPI_PDD_ClearInterruptFlags(SPI1_BASE_PTR,SPI_PDD_RX_FIFO_DRAIN_INT_DMA); /* Clear Rx FIFO drain flags */
    if (DeviceDataPrv->InpDataNumReq != 0x00U) { /* Is the receive block operation pending? */
      *(DeviceDataPrv->InpDataPtr++) = (uint8_t)Data; /* Put a character to the receive buffer and increment pointer to receive buffer */
      DeviceDataPrv->InpRecvDataNum++; /* Increment received char. counter */
      if (DeviceDataPrv->InpRecvDataNum == DeviceDataPrv->InpDataNumReq) { /* Is the requested number of characters received? */
        DeviceDataPrv->InpDataNumReq = 0x00U; /* If yes then clear number of requested characters to be received. */
        SM2_OnBlockReceived(DeviceDataPrv->UserData);
      }
    }
  }
  if ((StatReg & SPI_PDD_TX_FIFO_FILL_INT_DMA) != 0U) { /* Is HW buffer empty? */
    if (DeviceDataPrv->OutSentDataNum < DeviceDataPrv->OutDataNumReq) { /* Is number of sent characters less than the number of requested incoming characters? */
      DeviceDataPrv->OutSentDataNum++; /* Increment the counter of sent characters. */
      SPI_PDD_WriteMasterPushTxFIFOReg(SPI1_BASE_PTR, (uint32_t)(*((uint8_t *)DeviceDataPrv->OutDataPtr++) | DeviceDataPrv->TxCommand)); /* Put a character with command to the transmit register and increment pointer to the transmitt buffer */
      if (DeviceDataPrv->OutSentDataNum == DeviceDataPrv->OutDataNumReq) {
        DeviceDataPrv->OutDataNumReq = 0x00U; /* Clear the counter of characters to be send by SendBlock() */
      }
    } else {
      SPI_PDD_DisableDmasInterrupts(SPI1_BASE_PTR, SPI_PDD_TX_FIFO_FILL_INT_DMA); /* Disable TX interrupt */
    }
    SPI_PDD_ClearInterruptFlags(SPI1_BASE_PTR,SPI_PDD_TX_FIFO_FILL_INT_DMA); /* Clear Tx FIFO fill flags */
  }
}

/*
** ===================================================================
**     Method      :  HWEnDi (component SPIMaster_LDD)
**
**     Description :
**         Enables or disables the peripheral(s) associated with the 
**         component. The method is called automatically as a part of the 
**         Enable and Disable methods and several internal methods.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
static void HWEnDi(LDD_TDeviceData *DeviceDataPtr)
{
  if (((SM2_TDeviceDataPtr)DeviceDataPtr)->EnUser) { /* Enable device? */
    ((SM2_TDeviceDataPtr)DeviceDataPtr)->OutDataNumReq = 0x00U; /* Clear the counter of requested outgoing characters. */
    ((SM2_TDeviceDataPtr)DeviceDataPtr)->OutSentDataNum = 0x00U; /* Clear the counter of sent characters. */
    ((SM2_TDeviceDataPtr)DeviceDataPtr)->InpDataNumReq = 0x00U; /* Clear the counter of requested incoming characters. */
    ((SM2_TDeviceDataPtr)DeviceDataPtr)->InpRecvDataNum = 0x00U; /* Clear the counter of received characters. */
    SPI_PDD_EnableDevice(SPI1_BASE_PTR,PDD_ENABLE); /* Enable device */
    SPI_PDD_ClearTxFIFO(SPI1_BASE_PTR); /* Clear Tx FIFO */
    SPI_PDD_ClearRxFIFO(SPI1_BASE_PTR); /* Clear Rx FIFO */
    SPI_PDD_ClearInterruptFlags(SPI1_BASE_PTR,SPI_PDD_ALL_INT); /* Clear all HW flags */
    SPI_PDD_EnableHaltMode(SPI1_BASE_PTR,PDD_DISABLE); /* Leave the STOPPED mode */
  }
  else {
    SPI_PDD_EnableHaltMode(SPI1_BASE_PTR,PDD_ENABLE); /* Enter to STOPPED mode */
    SPI_PDD_EnableDevice(SPI1_BASE_PTR,PDD_DISABLE); /* Disable device */
  }
}

/*lint -restore Enable MISRA rule (11.4) checking. */
/* END SM2. */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.5 [05.21]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
