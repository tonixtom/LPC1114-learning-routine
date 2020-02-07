/******************** (C) COPYRIGHT 2010 Embest Info&Tech Co.,LTD. ************
* 文件名: system_LPC11xx.c
* 作者  : Wuhan R&D Center, Embest
* 日期  : 01/18/2010
* 描述  : CMSIS Cortex-M0核外围访问层源文件，用于NXP LPC11xx系列设备
*******************************************************************************
*******************************************************************************
* 历史:
* 01/18/2010		 : V1.0		   初始版本
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include "LPC11xx.h"

/*
//-------- <<< Use Configuration Wizard in Context Menu >>> ------------------
*/

/*--------------------- 时钟配置 ----------------------------------
//
// <e> 时钟配置
//   <h> 系统控制和状态寄存器 (SCS)
//     <o1.4>    OSCRANGE: 主晶振频率范围选择
//                     <0=>  1 MHz 到 20 MHz
//                     <1=> 15 MHz 到 24 MHz
//     <e1.5>       OSCEN: 主晶振使能
//     </e>
//   </h>
//
//   <h> 时钟源选择寄存器 (CLKSRCSEL)
//     <o2.0..1>   CLKSRC: PLL时钟源选择
//                     <0=> 内部RC晶振
//                     <1=> 主晶振
//                     <2=> RTC晶振
//   </h>
//
//   <e3> PLL0配置 (Main PLL)
//     <h> PLL0配置寄存器 (PLL0CFG)
//                     <i> F_cco0 = (2 * M * F_in) / N
//                     <i> F_in 必须在32kHz到50MHz范围之间
//                     <i> F_cco0必须在275MHz到550MHz范转之间
//       <o4.0..14>  MSEL: PLL倍频选择
//                     <6-32768><#-1>
//                     <i> M Value
//       <o4.16..23> NSEL: PLL分频选择
//                     <1-256><#-1>
//                     <i> N值
//     </h>
//   </e>
//
//   <e5> PLL1配置 (USB PLL)
//     <h> PLL1配置寄存器 (PLL1CFG)
//                     <i> F_usb = M * F_osc 或 F_usb = F_cco1 / (2 * P)
//                     <i> F_cco1 = F_osc * M * 2 * P
//                     <i> F_cco1必须在156MHz到320MHz之间
//       <o6.0..4>   MSEL: PLL倍频选择
//                     <1-32><#-1>
//                     <i> M Value (用于USB时最大值为4)
//       <o6.5..6>   PSEL: PLL分频选择
//                     <0=> 2
//                     <1=> 4
//                     <2=> 8
//                     <3=> 16
//                     <i> P值
//     </h>
//   </e>
//
//   <h> CPU时钟配置寄存器 (CCLKCFG)
//     <o7.0..7>  CCLKSEL: PLL0分频值，用于为CPU提供时钟
//                     <0-255>
//                     <i> 分频值为CCLKSEL + 1。只有0和奇数值有效
//   </h>
//
//   <h> USB时钟配置寄存器 (USBCLKCFG)
//     <o8.0..3>   USBSEL: PLL1分频值用于为USB提供时钟
//                     <0-15>
//                     <i> 分频值为USBSEL + 1
//   </h>
//
// </e>
*/
#define CLOCK_SETUP           1

#define MAIN_PLL_SETUP        1
#define MAIN_CLKSRCSEL_Val    0x00000001
#define MAIN_PLL_M_Val        0x00000003
#define MAIN_PLL_P_Val        0x00000001
#define SYS_AHB_DIV_Val       1			/* 1到255，典型值为1、2或4 */

#define USB_CLK_SETUP         0			/* 当使用USB时，此位必须置位 */
#define USE_USB_PLL           0			/* 当USB_PLL_SETUP为0时，USE_USB_PLL不能置1，
                                       USB时钟由main PLL或USB PLL提供。 */
#define USB_CLKSRCSEL_Val     0x00000001
#define USB_PLL_M_Val         0x00000003
#define USB_PLL_P_Val         0x00000001

/*
//-------- <<< end of configuration section >>> ------------------------------
*/

/*----------------------------------------------------------------------------
  宏定义
 *----------------------------------------------------------------------------*/
    
/*----------------------------------------------------------------------------
  时钟宏定义
 *----------------------------------------------------------------------------*/
#define XTAL        (12000000UL)        /* 晶体振荡器频率                     */
#define OSC_CLK     (      XTAL)        /* 主晶振频率                         */
#define IRC_OSC     ( 4000000UL)        /* 内部RC晶振频率                     */
#define WDT_OSC     (  250000UL)        /* 看门狗晶振频率                     */

/*----------------------------------------------------------------------------
  时钟变量定义
 *----------------------------------------------------------------------------*/
uint32_t ClockSource = IRC_OSC;
uint32_t SystemFrequency = IRC_OSC; /*!< 系统时钟频率 (内核时钟)  */
uint32_t SystemAHBFrequency = IRC_OSC;


 /**
  * @函数名：Main_PLL_Setup
  * @描述：微控制器配置，初始化系统并更新系统时钟频率
  * @参数： 无
  * @返回值：无
  */
void Main_PLL_Setup ( void )
{
  uint32_t regVal;

  ClockSource = OSC_CLK;
  LPC_SYSCON->SYSPLLCLKSEL = MAIN_CLKSRCSEL_Val;   /* 选择OSC */
  LPC_SYSCON->SYSPLLCLKUEN = 0x01;                 /* 更新时钟源 */
  LPC_SYSCON->SYSPLLCLKUEN = 0x00;                 /* 切换更新寄存器一次 */
  LPC_SYSCON->SYSPLLCLKUEN = 0x01;
  while ( !(LPC_SYSCON->SYSPLLCLKUEN & 0x01) ); /* 等待更新完成 */

  regVal = LPC_SYSCON->SYSPLLCTRL;
  regVal &= ~0x1FF;
  LPC_SYSCON->SYSPLLCTRL = (regVal | (MAIN_PLL_P_Val<<5) | MAIN_PLL_M_Val);
  
  /* 使能主系统PLL时钟，主系统PLL为PDRUNCFG寄存器中第七位 */
  LPC_SYSCON->PDRUNCFG &= ~(0x1<<7);
  while ( !(LPC_SYSCON->SYSPLLSTAT & 0x01) );	/* 等待直到被锁定 */

  LPC_SYSCON->MAINCLKSEL = 0x03;		/* PLL时钟输出选择 */
  LPC_SYSCON->MAINCLKUEN = 0x01;		/* 更新MCLK时钟源  */
  LPC_SYSCON->MAINCLKUEN = 0x00;		/* 切换更新寄存器一次 */
  LPC_SYSCON->MAINCLKUEN = 0x01;
  while ( !(LPC_SYSCON->MAINCLKUEN & 0x01) );	/* 等待更新完成 */

  LPC_SYSCON->SYSAHBCLKDIV = SYS_AHB_DIV_Val;	/* SYS AHB时钟，典型值为1、2、4 */

#if MAIN_PLL_SETUP
  SystemFrequency = ClockSource * (MAIN_PLL_M_Val+1);
#else
  SystemFrequency = ClockSource;
#endif
  SystemAHBFrequency = (uint32_t)(SystemFrequency/SYS_AHB_DIV_Val);
  return;
}

void USB_PLL_Setup ( void )
{
  uint32_t regVal;

  /* 使能USB PLL时钟。 USB时钟和PHY分别为PDRUNCFG寄存器的第8位和第10位 */
  LPC_SYSCON->PDRUNCFG &= ~((0x1<<8)|(0x1<<10));

  LPC_SYSCON->USBPLLCLKSEL = USB_CLKSRCSEL_Val;    /* 选择系统OSC */
  LPC_SYSCON->USBPLLCLKUEN = 0x01;                 /* 更新时钟源*/
  LPC_SYSCON->USBPLLCLKUEN = 0x00;                 /* 切换更新寄存器一次 */
  LPC_SYSCON->USBPLLCLKUEN = 0x01;
  while ( !(LPC_SYSCON->USBPLLCLKUEN & 0x01) );    /* 等待更新完成 */

  regVal = LPC_SYSCON->USBPLLCTRL;
  regVal &= ~0x1FF;
  LPC_SYSCON->USBPLLCTRL = (regVal | (USB_PLL_P_Val<<5) | USB_PLL_M_Val);
  
  while ( !(LPC_SYSCON->USBPLLSTAT & 0x01) );	/* 等待直到被锁定 */

#if USE_USB_PLL
  LPC_SYSCON->USBCLKSEL = 0x00;               /* 选择USB PLL */
#else
  /* 如果运行到此，则Main PLL时钟必须是48Mhz的倍数 */ 
  LPC_SYSCON->USBCLKSEL = 0x01;               /* 选择主时钟 */
#endif
  
  LPC_SYSCON->USBCLKUEN = 0x01;               /* 更新时钟 */
  LPC_SYSCON->USBCLKUEN = 0x00;               /* 切换更新寄存器一次 */
  LPC_SYSCON->USBCLKUEN = 0x01;
  while ( !(LPC_SYSCON->USBCLKUEN & 0x01) );  /* 等待更新完成 */
  LPC_SYSCON->USBCLKDIV = 1;                  /* USB时钟必须是48Mhz. */
#if !USE_USB_PLL
  /* 当USB PLL不被用做USB时钟时，用于USB PLL的PDRUN不能关闭 */
  LPC_SYSCON->PDRUNCFG |= (0x1<<8);
#endif 
  return;
}

  /**
  * @函数名：SystemInit
  * @描述：微控制器配置，初始化系统并更新系统时钟频率
  * @参数： 无
  * @返回值：无
  */
void SystemInit (void)
{
  uint32_t i;

#ifdef __DEBUG_RAM    
  LPC_SYSCON->SYSMEMREMAP = 0x1;		/* 重映射到片内RAM */ 
#else
#ifdef __DEBUG_FLASH    
  LPC_SYSCON->SYSMEMREMAP = 0x2;		/* 重映射到片内flash */
#endif
#endif

#if (CLOCK_SETUP)                       /* 时钟设置 */
  /*第0位默认为晶振旁路
  第1位 0=0~20Mhz晶振输入, 1=15~50Mhz晶振输入 */
  LPC_SYSCON->SYSOSCCTRL = 0x00;

  /* 主系统OSC运行被清除，对应PDRUNCFG寄存器中的第5位 */
  LPC_SYSCON->PDRUNCFG &= ~(0x1<<5);
  /* 等待200us，直到OSC稳定，没有状态标志*/
  for ( i = 0; i < 0x100; i++ );

#if (MAIN_PLL_SETUP)
  Main_PLL_Setup();  
#endif

#if (USB_CLK_SETUP)
  USB_PLL_Setup();
#else 
  /* 使能USB时钟 */
  LPC_SYSCON->PDRUNCFG &= ~((0x1<<8)|(0x1<<10));
#endif

#endif	/* CLOCK_SETUP结束 */

  /* 系统时钟IOCON使能，此位不使能大部分IO不可用 */
  LPC_SYSCON->SYSAHBCLKCTRL |= (1<<16);
  return;
}

/**
  * @}
  */ 

/**
  * @}
  */ 
/************* (C) COPYRIGHT 2010 Wuhan R&D Center, Embest *****文件结束*******/
