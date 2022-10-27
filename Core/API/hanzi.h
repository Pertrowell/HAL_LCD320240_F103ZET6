#ifndef _HANZI_H_
#define _HANZI_H_

extern unsigned char zf[];
extern unsigned char zf_index[];
extern unsigned char hz_index[];
extern unsigned char hz[];
extern unsigned char dzb[];
extern unsigned char zifu_32X56[];
extern unsigned char zifu_24X33[];
extern unsigned char zifu_32X29[];
extern unsigned char zifu_64X56[];
extern unsigned char zifu_24X24[];
extern unsigned char zifu_24X20[];
extern unsigned char zifuFST_16X20[];
extern unsigned char zifuSND_16X20[];
extern unsigned char zifuTHR_16X20[];
extern unsigned char zifuLED_16X20[];
extern unsigned char zifuLED_24X24[];
 /*****************************************************************************
*****函数名：  ASCII_NUM()
*****参数：    无
*****功能：    返回ASCII字符个数
*****作者：    陈志发
*****创建时间：2013-11-16
*****备注：创建这个函数是解决KEIL中sizeof()必须和结构变量同一个文件才准确识别的BUGE
*****************************************************************************/  
extern unsigned int ASCII_NUM(void);

 /*****************************************************************************
*****函数名：  GB16_NUM()
*****参数：    无
*****功能：    返回GB16字符个数
*****作者：    陈志发
*****创建时间：2013-11-16
*****备注：创建这个函数是解决KEIL中sizeof()必须和结构变量同一个文件才准确识别的BUGE
*****************************************************************************/  
extern unsigned int GB16_NUM(void) ;
#endif
