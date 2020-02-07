 /******************** (C) COPYRIGHT 2010 Embest Info&Tech Co.,LTD. ************
* 文件名: LPC11xx.h
* 作者  : Wuhan R&D Center, Embest
* 日期  : 01/18/2010
* 描述  : CMSIS Cortex-M0核外围访问层头文件，用于NXP LPC11xx系列设备
*******************************************************************************
*******************************************************************************
* 历史:
* 01/18/2010		 : V1.0		   初始版本
*******************************************************************************/

#ifndef __LPC11xx_H__
#define __LPC11xx_H__

/*
 * ============================================================================
 * ---------- 中断号定义 ------------------------------------------------------
 * ============================================================================
 */

typedef enum IRQn
{
/******  Cortex-M3处理器异常号 ************************************************/
  NonMaskableInt_IRQn           = -14,      /*!< 2 不可屏蔽中断               */
  MemoryManagement_IRQn         = -12,      /*!< 4 Cortex-M0存储器管理故障中断*/
  BusFault_IRQn                 = -11,      /*!< 5 Cortex-M0总线故障中断      */
  UsageFault_IRQn               = -10,      /*!< 6 Cortex-M0用法故障中断      */
  SVCall_IRQn                   = -5,       /*!< 11 Cortex-M0 SV Call中断     */
  DebugMonitor_IRQn             = -4,       /*!< 12 Cortex-M0 DebugMonitor中断*/
  PendSV_IRQn                   = -2,       /*!< 14 Cortex-M0 Pend SV中断     */
  SysTick_IRQn                  = -1,       /*!< 15 Cortex-M0 SystemTick中断  */

/******  LPC11xx 外部中断号 ***************************************************/
  WAKEUP0_IRQn                  = 0,        /*!< 所有的I/O引脚都可用做唤醒源  */
  WAKEUP1_IRQn                  = 1,       
  WAKEUP2_IRQn                  = 2,
  WAKEUP3_IRQn                  = 3,
  WAKEUP4_IRQn                  = 4,   
  WAKEUP5_IRQn                  = 5,        
  WAKEUP6_IRQn                  = 6,        
  WAKEUP7_IRQn                  = 7,        
  WAKEUP8_IRQn                  = 8,        
  WAKEUP9_IRQn                  = 9,        
  WAKEUP10_IRQn                 = 10,       
  WAKEUP11_IRQn                 = 11,       
  WAKEUP12_IRQn                 = 12,       
  CAN_IRQn                      = 13,       /*!< CAN 中断                     */
  SSP1_IRQn                     = 14,       /*!< SSP1 中断                    */
  I2C_IRQn                      = 15,       /*!< I2C 中断                     */
  TIMER_16_0_IRQn               = 16,       /*!< 16-bit Timer0 中断           */
  TIMER_16_1_IRQn               = 17,       /*!< 16-bit Timer1 中断           */
  TIMER_32_0_IRQn               = 18,       /*!< 32-bit Timer0 中断           */
  TIMER_32_1_IRQn               = 19,       /*!< 32-bit Timer1 中断           */
  SSP0_IRQn                     = 20,       /*!< SSP0 中断                    */
  UART_IRQn                     = 21,       /*!< UART 中断                    */
  USB_IRQn                      = 22,       /*!< USB常规中断                  */
  USB_FIQn                      = 23,       /*!< USB快速中断                  */
  ADC_IRQn                      = 24,       /*!< A/D 转换中断                 */
  WDT_IRQn                      = 25,       /*!< Watchdog定时器中断           */  
  BOD_IRQn                      = 26,       /*!< Brown Out Detect(BOD)中断    */
  RESERVED_IRQn                 = 27,       /*!< 保留                         */
  EINT3_IRQn                    = 28,       /*!< 外部PIO3中断                 */
  EINT2_IRQn                    = 29,       /*!< 外部PIO2中断                 */
  EINT1_IRQn                    = 30,       /*!< 外部PIO1中断                 */
  EINT0_IRQn                    = 31,       /*!< 外部PIO0中断                 */
} IRQn_Type;


/*
 * ============================================================================
 * ----------- 处理器和内核外围部分 -------------------------------------------
 * ============================================================================
 */

/* Cortex-M0处理器和内核外围配置 */
#define __MPU_PRESENT             1         /*!< MPU有或无                    */
#define __NVIC_PRIO_BITS          5         /*!< 优先级位数定义               */
#define __Vendor_SysTickConfig    0         /*!< 使能不同的滴答配置，此位置位 */


#include "core_cm0.h"                    /* Cortex-M0处理器和内核外围         */
#include "system_LPC11xx.h"            

extern void SystemInit (void);


/******************************************************************************/
/*                外围设备寄存器                                              */
/******************************************************************************/

#pragma anon_unions

/*------------- 系统控制 (SYSCON) --------------------------------------------*/
typedef struct
{
  __IO uint32_t SYSMEMREMAP;     /* 系统存储器重映射，偏移0x0 */
  __IO uint32_t PRESETCTRL;
  __IO uint32_t SYSPLLCTRL;      /* 系统PLL控制 */
  __IO uint32_t SYSPLLSTAT;
  __IO uint32_t USBPLLCTRL;      /* USB PLL控制，偏移0x10 */
  __IO uint32_t USBPLLSTAT;
       uint32_t RESERVED0[2];

  __IO uint32_t SYSOSCCTRL;      /* 偏移 0x20 */
  __IO uint32_t WDTOSCCTRL;
  __IO uint32_t IRCCTRL;
       uint32_t RESERVED1[1];
  __IO uint32_t SYSRESSTAT;      /* 偏移 0x30 */
       uint32_t RESERVED2[3];
  __IO uint32_t SYSPLLCLKSEL;    /* 偏移 0x40 */	
  __IO uint32_t SYSPLLCLKUEN;
  __IO uint32_t USBPLLCLKSEL;
  __IO uint32_t USBPLLCLKUEN;
       uint32_t RESERVED3[8];

  __IO uint32_t MAINCLKSEL;      /* 偏移 0x70 */
  __IO uint32_t MAINCLKUEN;
  __IO uint32_t SYSAHBCLKDIV;
       uint32_t RESERVED4[1];

  __IO uint32_t SYSAHBCLKCTRL;   /* 偏移 0x80 */
       uint32_t RESERVED5[4];
  __IO uint32_t SSP0CLKDIV;                 
  __IO uint32_t UARTCLKDIV;
  __IO uint32_t SSP1CLKDIV;
       uint32_t RESERVED6[3];
  __IO uint32_t TRACECLKDIV;

  __IO uint32_t SYSTICKCLKDIV;   /* 偏移 0xB0 */           
       uint32_t RESERVED7[3];

  __IO uint32_t USBCLKSEL;       /* 偏移 0xC0 */ 
  __IO uint32_t USBCLKUEN;
  __IO uint32_t USBCLKDIV;
       uint32_t RESERVED8[1];
  __IO uint32_t WDTCLKSEL;       /* 偏移 0xD0 */
  __IO uint32_t WDTCLKUEN;
  __IO uint32_t WDTCLKDIV;
       uint32_t RESERVED9[1];              
  __IO uint32_t CLKOUTCLKSEL;    /* 偏移 0xE0 */
  __IO uint32_t CLKOUTUEN;
  __IO uint32_t CLKOUTDIV;              
       uint32_t RESERVED10[5];
  
  __IO uint32_t PIOPORCAP0;      /* 偏移 0x100 */           
  __IO uint32_t PIOPORCAP1;         
       uint32_t RESERVED11[18];

  __IO uint32_t BODCTRL;         /* 偏移 0x150 */
       uint32_t RESERVED12[1];
  __IO uint32_t SYSTCKCAL;
 	   uint32_t RESERVED13[5];
  __IO uint32_t INT_IRQ_LATENCY; /* 偏移 0x170 */
       uint32_t RESERVED14[35];          

  __IO uint32_t STARTAPRP0;      /* 偏移 0x200 */     
  __IO uint32_t STARTERP0;             
  __IO uint32_t STARTRSRP0CLR;
  __IO uint32_t STARTSRP0;
  __IO uint32_t STARTAPRP1;           
  __IO uint32_t STARTERP1;             
  __IO uint32_t STARTRSRP1CLR;
  __IO uint32_t STARTSRP1;
       uint32_t RESERVED15[4];

  __IO uint32_t PDSLEEPCFG;      /* 偏移 0x230 */
  __IO uint32_t PDAWAKECFG;              
  __IO uint32_t PDRUNCFG;
       uint32_t RESERVED16[110];
  __I  uint32_t DEVICE_ID;
} SYSCON_TypeDef;


/*------------- 引脚连接 (IOCON) ---------------------------------------------*/
typedef struct
{
  __IO uint32_t PIO2_6;
       uint32_t RESERVED0[1];
  __IO uint32_t PIO2_0;
  __IO uint32_t RESET_PIO0_0;
  __IO uint32_t PIO0_1;
  __IO uint32_t PIO1_8;
       uint32_t RESERVED1[1];
  __IO uint32_t PIO0_2;

  __IO uint32_t PIO2_7;
  __IO uint32_t PIO2_8;
  __IO uint32_t PIO2_1;
  __IO uint32_t PIO0_3;
  __IO uint32_t PIO0_4;
  __IO uint32_t PIO0_5;
  __IO uint32_t PIO1_9;
  __IO uint32_t PIO3_4;

  __IO uint32_t PIO2_4;
  __IO uint32_t PIO2_5;
  __IO uint32_t PIO3_5;
  __IO uint32_t PIO0_6;
  __IO uint32_t PIO0_7;
  __IO uint32_t PIO2_9;
  __IO uint32_t PIO2_10;
  __IO uint32_t PIO2_2;

  __IO uint32_t PIO0_8;
  __IO uint32_t PIO0_9;
  __IO uint32_t JTAG_TCK_PIO0_10;
  __IO uint32_t PIO1_10;
  __IO uint32_t PIO2_11;
  __IO uint32_t JTAG_TDI_PIO0_11;
  __IO uint32_t JTAG_TMS_PIO1_0;
  __IO uint32_t JTAG_TDO_PIO1_1;

  __IO uint32_t JTAG_nTRST_PIO1_2;
  __IO uint32_t PIO3_0;
  __IO uint32_t PIO3_1;
  __IO uint32_t PIO2_3;
  __IO uint32_t ARM_SWDIO_PIO1_3;
  __IO uint32_t PIO1_4;
  __IO uint32_t PIO1_11;
  __IO uint32_t PIO3_2;

  __IO uint32_t PIO1_5;
  __IO uint32_t PIO1_6;
  __IO uint32_t PIO1_7;
  __IO uint32_t PIO3_3;
  __IO uint32_t SCKLOC; 
  __IO uint32_t DSRLOC;
  __IO uint32_t DCDLOC;
  __IO uint32_t RILOC;
} IOCON_TypeDef;


/*------------- 电源管理单元 (PMU) -------------------------------------------*/
typedef struct
{
  __IO uint32_t PCON;
  __IO uint32_t GPREG0;
  __IO uint32_t GPREG1;
  __IO uint32_t GPREG2;
  __IO uint32_t GPREG3;
  __IO uint32_t GPREG4;
} PMU_TypeDef;


/*------------- 通用IO (GPIO) ------------------------------------------------*/
typedef struct
{
  union {
    __IO uint32_t MASKED_ACCESS[4096];
    struct {
         uint32_t RESERVED0[4095];
    __IO uint32_t DATA;
    };
  };
       uint32_t RESERVED1[4096];
  __IO uint32_t DIR;
  __IO uint32_t IS;
  __IO uint32_t IBE;
  __IO uint32_t IEV;
  __IO uint32_t IE;
  __IO uint32_t RIS;
  __IO uint32_t MIS;
  __IO uint32_t IC;
} GPIO_TypeDef;


/*------------- 定时器 (TMR) -------------------------------------------------*/
typedef struct
{
  __IO uint32_t IR;
  __IO uint32_t TCR;
  __IO uint32_t TC;
  __IO uint32_t PR;
  __IO uint32_t PC;
  __IO uint32_t MCR;
  __IO uint32_t MR0;
  __IO uint32_t MR1;
  __IO uint32_t MR2;
  __IO uint32_t MR3;
  __IO uint32_t CCR;
  __I  uint32_t CR0;
       uint32_t RESERVED1[3];
  __IO uint32_t EMR;
       uint32_t RESERVED2[12];
  __IO uint32_t CTCR;
  __IO uint32_t PWMC;
} TMR_TypeDef;

/*------------- 通用异步收发器(UART) -----------------------------------------*/
typedef struct
{
  union {
  __I  uint32_t  RBR;
  __O  uint32_t  THR;
  __IO uint32_t  DLL;
  };
  union {
  __IO uint32_t  DLM;
  __IO uint32_t  IER;
  };
  union {
  __I  uint32_t  IIR;
  __O  uint32_t  FCR;
  };
  __IO uint32_t  LCR;
  __IO uint32_t  MCR;
  __I  uint32_t  LSR;
  __I  uint32_t  MSR;
  __IO uint32_t  SCR;
  __IO uint32_t  ACR;
  __IO uint32_t  ICR;
  __IO uint32_t  FDR;
       uint32_t  RESERVED0;
  __IO uint32_t  TER;
       uint32_t  RESERVED1[6];
  __IO uint32_t  RS485CTRL;
  __IO uint32_t  ADRMATCH;
  __IO uint32_t  RS485DLY;
  __I  uint32_t  FIFOLVL;
} UART_TypeDef;

/*------------- 同步串行通信 (SSP) -------------------------------------------*/

typedef struct
{
  __IO uint32_t CR0;
  __IO uint32_t CR1;
  __IO uint32_t DR;
  __I  uint32_t SR;
  __IO uint32_t CPSR;
  __IO uint32_t IMSC;
  __IO uint32_t RIS;
  __IO uint32_t MIS;
  __IO uint32_t ICR;
} SSP_TypeDef;

/*------------- I2C ----------------------------------------------------------*/
typedef __packed struct
{
  __IO uint32_t CONSET;
  __I  uint32_t STAT;
  __IO uint32_t DAT;
  __IO uint32_t ADR0;
  __IO uint32_t SCLH;
  __IO uint32_t SCLL;
  __O  uint32_t CONCLR;
  __IO uint32_t MMCTRL;
  __IO uint32_t ADR1;
  __IO uint32_t ADR2;
  __IO uint32_t ADR3;
  __I  uint32_t DATA_BUFFER;
  __IO uint32_t MASK0;
  __IO uint32_t MASK1;
  __IO uint32_t MASK2;
  __IO uint32_t MASK3;
} I2C_TypeDef;

/*------------- 看门狗定时器 (WDT) -------------------------------------------*/


typedef struct
{
  __IO uint32_t MOD;
  __IO uint32_t TC;
  __O  uint32_t FEED;
  __I  uint32_t TV;
} WDT_TypeDef;

/*------------- 模数转换器 (ADC) ---------------------------------------------*/

typedef struct
{
  __IO uint32_t CR;
  __IO uint32_t GDR;
       uint32_t RESERVED0;
  __IO uint32_t INTEN;
  __I  uint32_t DR0;
  __I  uint32_t DR1;
  __I  uint32_t DR2;
  __I  uint32_t DR3;
  __I  uint32_t DR4;
  __I  uint32_t DR5;
  __I  uint32_t DR6;
  __I  uint32_t DR7;
  __I  uint32_t STAT;
} ADC_TypeDef;

/*------------- CAN控制器 (CAN) ----------------------------------------------*/
typedef struct
{
  __IO uint32_t CNTL;				/* 0x000 */
  __IO uint32_t STAT;
  __IO uint32_t EC;
  __IO uint32_t BT;
  __IO uint32_t INT;
  __IO uint32_t TEST;
  __IO uint32_t BRPE;
       uint32_t RESERVED0;
  __IO uint32_t IF1_CMDREQ;			/* 0x020 */
  __IO uint32_t IF1_CMDMSK;
  __IO uint32_t IF1_MSK1;
  __IO uint32_t IF1_MSK2;
  __IO uint32_t IF1_ARB1;
  __IO uint32_t IF1_ARB2;
  __IO uint32_t IF1_MCTRL;
  __IO uint32_t IF1_DA1;
  __IO uint32_t IF1_DA2;
  __IO uint32_t IF1_DB1;
  __IO uint32_t IF1_DB2;
       uint32_t RESERVED1[13];   
  __IO uint32_t IF2_CMDREQ;			/* 0x080 */
  __IO uint32_t IF2_CMDMSK;
  __IO uint32_t IF2_MSK1;
  __IO uint32_t IF2_MSK2;
  __IO uint32_t IF2_ARB1;
  __IO uint32_t IF2_ARB2;
  __IO uint32_t IF2_MCTRL;
  __IO uint32_t IF2_DA1;
  __IO uint32_t IF2_DA2;
  __IO uint32_t IF2_DB1;
  __IO uint32_t IF2_DB2;
	   uint32_t RESERVED2[21];
  __I  uint32_t TXREQ1;				/* 0x100 */
  __I  uint32_t TXREQ2;
	   uint32_t RESERVED3[6];
  __I  uint32_t ND1;				/* 0x120 */
  __I  uint32_t ND2;
	   uint32_t RESERVED4[6];
  __I  uint32_t IR1;				/* 0x140 */
  __I  uint32_t IR2;
	   uint32_t RESERVED5[6];
  __I  uint32_t MSGV1;				/* 0x160 */
  __I  uint32_t MSGV2;
	   uint32_t RESERVED6[6];
  __IO uint32_t CLKDIV;				/* 0x180 */
} CAN_TypeDef;

/*------------- 通用串行总线 (USB) -------------------------------------------*/

typedef struct
{
  __I  uint32_t DevIntSt;            /* USB设备中断寄存器                     */
  __IO uint32_t DevIntEn;
  __O  uint32_t DevIntClr;
  __O  uint32_t DevIntSet;
 
  __O  uint32_t CmdCode;             /* USB设备SIE命令寄存器                  */
  __I  uint32_t CmdData;

  __I  uint32_t RxData;              /* USB设备发送寄存器                     */
  __O  uint32_t TxData;
  __I  uint32_t RxPLen;
  __O  uint32_t TxPLen;
  __IO uint32_t Ctrl;
  __O  uint32_t DevFIQSel;
} USB_TypeDef;

#pragma no_anon_unions

/******************************************************************************/
/*                         外围存储器映射                                     */
/******************************************************************************/
/* 基地址 */
#define FLASH_BASE            (0x00000000UL)
#define RAM_BASE              (0x10000000UL)
#define APB0_BASE             (0x40000000UL)
#define AHB_BASE              (0x50000000UL)

/* APB0外围 */
#define I2C_BASE              (APB0_BASE + 0x00000)
#define WDT_BASE              (APB0_BASE + 0x04000)
#define UART_BASE             (APB0_BASE + 0x08000)
#define CT16B0_BASE           (APB0_BASE + 0x0C000)
#define CT16B1_BASE           (APB0_BASE + 0x10000)
#define CT32B0_BASE           (APB0_BASE + 0x14000)
#define CT32B1_BASE           (APB0_BASE + 0x18000)
#define ADC_BASE              (APB0_BASE + 0x1C000)
#define USB_BASE              (APB0_BASE + 0x20000)
#define PMU_BASE              (APB0_BASE + 0x38000)
#define SSP0_BASE             (APB0_BASE + 0x40000)
#define IOCON_BASE            (APB0_BASE + 0x44000)
#define SYSCON_BASE           (APB0_BASE + 0x48000)
#define CAN_BASE              (APB0_BASE + 0x50000)
#define SSP1_BASE             (APB0_BASE + 0x58000)

/* AHB外围 */	
#define GPIO_BASE             (AHB_BASE  + 0x00000)
#define GPIO0_BASE            (AHB_BASE  + 0x00000)
#define GPIO1_BASE            (AHB_BASE  + 0x10000)
#define GPIO2_BASE            (AHB_BASE  + 0x20000)
#define GPIO3_BASE            (AHB_BASE  + 0x30000)

/******************************************************************************/
/*                         外围声明                                           */
/******************************************************************************/
#define LPC_I2C                   ((      I2C_TypeDef *)       I2C_BASE)
#define LPC_WDT                   ((      WDT_TypeDef *)       WDT_BASE)
#define LPC_UART                  ((     UART_TypeDef *)      UART_BASE)
#define LPC_TMR16B0               ((      TMR_TypeDef *)    CT16B0_BASE)
#define LPC_TMR16B1               ((      TMR_TypeDef *)    CT16B1_BASE)
#define LPC_TMR32B0               ((      TMR_TypeDef *)    CT32B0_BASE)
#define LPC_TMR32B1               ((      TMR_TypeDef *)    CT32B1_BASE)
#define LPC_ADC                   ((      ADC_TypeDef *)       ADC_BASE)
#define LPC_PMU                   ((      PMU_TypeDef *)       PMU_BASE)
#define LPC_SSP0                  ((      SSP_TypeDef *)      SSP0_BASE)
#define LPC_SSP1                  ((      SSP_TypeDef *)      SSP1_BASE)
#define LPC_CAN                   ((      CAN_TypeDef *)       CAN_BASE)
#define LPC_IOCON                 ((    IOCON_TypeDef *)     IOCON_BASE)
#define LPC_SYSCON                ((   SYSCON_TypeDef *)    SYSCON_BASE)
#define LPC_USB                   ((      USB_TypeDef *)       USB_BASE)

#define LPC_GPIO0                 ((     GPIO_TypeDef *)     GPIO0_BASE)
#define LPC_GPIO1                 ((     GPIO_TypeDef *)     GPIO1_BASE)
#define LPC_GPIO2                 ((     GPIO_TypeDef *)     GPIO2_BASE)
#define LPC_GPIO3                 ((     GPIO_TypeDef *)     GPIO3_BASE)

#endif  // __LPC11xx_H__
/**
  * @}
  */ 

/**
  * @}
  */ 
/************* (C) COPYRIGHT 2010 Wuhan R&D Center, Embest *****文件结束*******/
