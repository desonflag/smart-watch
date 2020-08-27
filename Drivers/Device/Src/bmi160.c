//加速度三轴数据获取源码
//#define 	uint8_t u8
//#define 	uint16_t u16

#include <stdint.h>
#include "bmi160.h"

#define 	Delay_Ms delay_ms
#define BMI160_Write_Reg max30100_Bus_Write
#define BMI160_Read_Reg max30100_Bus_Read
#define BMI_address  (0x68<<1)
void BMI160_init(void)
{   uint8_t ui8Status = 0;
//	signed short acc_x,acc_y,acc_z;
//	unsigned short x,y,z;
    uint8_t ui8Attempts = 20;
    //向命令寄存器写入0x11,使加速度处于正常工作模式
//		  	BMI160_Write_Reg(0x7e,0xB0,BMI_address);
//	Delay_Ms(100);
    while (ui8Status != 0x20 && ui8Attempts--)
    {
//		  	BMI160_Write_Reg(0x7e,0xB0,BMI_address);
        Delay_Ms(1);

        BMI160_Write_Reg(0x7e,0x12,BMI_address);
        Delay_Ms(1);

        BMI160_Write_Reg(0x7e,0x14,BMI_address);
        Delay_Ms(1);
        ui8Status = BMI160_Read_Reg(0x03,BMI_address);
        Delay_Ms(1);


    }

    //切换工作模式之后，延时100ms
    Delay_Ms(100);

//	ui8Status = BMI160_Read_Reg(0x03,BMI_address);
    BMI160_Write_Reg( 0x7A, 0x15,BMI_address);//计步功能
    BMI160_Write_Reg( 0x7B, 0x0B,BMI_address);
    BMI160_Write_Reg( 0x41, 0x05,BMI_address);//设置加速度计+-4g


}
//获得步数
void bmi160_getStep(uint16_t *rawStep)
{
    uint16_t buf[2];

    buf[0]= BMI160_Read_Reg(0x79,BMI_address);
    buf[1]= BMI160_Read_Reg(0x78,BMI_address);
//	printf("%Xbuf0\n",buf[0]);
//		printf("%Xbuf2\n",buf[1]);
    uint16_t GG=buf[0]<<8;
//	buf[0]<<8
//	printf("%X!!",(uint16_t)buf[0]<<8);
//	printf("%d",GG|buf[1]);

    *rawStep=GG|buf[1];
}
