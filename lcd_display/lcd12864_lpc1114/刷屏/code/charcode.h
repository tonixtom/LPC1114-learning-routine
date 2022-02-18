#include "lpc11xx.h"

#ifndef __CHARCODE_H
#define __CHARCODE_H



// ------------------  汉字字模的数据结构定义 ------------------------ //
struct Cn16CharTypeDef                  // 汉字字模数据结构 
{
	uint8_t  Index[2];            // 汉字内码索引,一个汉字占两个字节	
	uint8_t  Msk[32];             // 点阵码数据(16*16有32个数据) 
};


struct Cn16CharTypeDef  CN16CHAR[]=
{
/*--  文字:  普  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
"普",0x00,0x40,0x44,0x54,0x64,0x45,0x7E,0x44,0x44,0x44,0x7E,0x45,0x64,0x54,0x44,0x40,
0x00,0x00,0x00,0x00,0xFF,0x49,0x49,0x49,0x49,0x49,0x49,0x49,0xFF,0x00,0x00,0x00,

/*--  文字:  中  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
"中",0x00,0x00,0xFC,0x08,0x08,0x08,0x08,0xFF,0x08,0x08,0x08,0x08,0xFC,0x08,0x00,0x00,
0x00,0x00,0x07,0x02,0x02,0x02,0x02,0xFF,0x02,0x02,0x02,0x02,0x07,0x00,0x00,0x00,
/*--  文字:  科  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
"科",0x00,0x00,0x00,0xFF,0x00,0x00,0xCC,0x22,0x00,0x91,0x51,0xFE,0x72,0x92,0x12,0x10,
0x00,0x01,0x01,0xFF,0x02,0x02,0x02,0x04,0x04,0x04,0x00,0xFF,0x00,0x01,0x02,0x04,
/*--  文字:  技  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
"技",0x00,0x08,0x48,0xC8,0x48,0x7F,0x48,0x48,0xC8,0x00,0x28,0x48,0xFF,0x88,0x08,0x08,
0x00,0x20,0x60,0x21,0x12,0x0C,0x0C,0x13,0x20,0x40,0x40,0x00,0x7F,0x80,0x41,0x01,
/*--  文字:  有  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
"有",0x00,0x04,0x04,0x04,0xE4,0x24,0x24,0x24,0x27,0x2C,0x34,0xE4,0x44,0x84,0x04,0x00,
0x00,0x00,0x00,0x00,0x7F,0xC9,0x49,0x29,0x09,0x09,0x09,0xFF,0x00,0x00,0x01,0x02,

/*--  文字:  限  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
"限",0x00,0x00,0x00,0x7E,0x4A,0x4A,0x4A,0xCA,0x4A,0xFE,0x00,0x82,0x4E,0x32,0x02,0xFE,
0x00,0x20,0x60,0x21,0x12,0x0C,0x03,0x20,0x40,0xFF,0x00,0x03,0x04,0x02,0x00,0xFF,

/*--  文字:  公  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
"公",0x00,0x80,0x80,0xC0,0x60,0x10,0x0E,0x00,0x00,0x84,0x0E,0x30,0x40,0x80,0x00,0x00,
0x00,0x00,0x01,0x30,0x78,0x14,0x10,0x10,0x31,0x23,0x24,0x28,0x70,0x20,0x01,0x00,

/*--  文字:  司  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
"司",0x00,0x00,0xFE,0x02,0x02,0x12,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x92,0x10,0x00,
0x00,0x00,0x3F,0x40,0x20,0x00,0x0F,0x04,0x04,0x04,0x04,0x04,0x04,0x1F,0x00,0x00,

};



#endif
