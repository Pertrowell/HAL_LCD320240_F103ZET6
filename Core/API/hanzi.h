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
*****��������  ASCII_NUM()
*****������    ��
*****���ܣ�    ����ASCII�ַ�����
*****���ߣ�    ��־��
*****����ʱ�䣺2013-11-16
*****��ע��������������ǽ��KEIL��sizeof()����ͽṹ����ͬһ���ļ���׼ȷʶ���BUGE
*****************************************************************************/  
extern unsigned int ASCII_NUM(void);

 /*****************************************************************************
*****��������  GB16_NUM()
*****������    ��
*****���ܣ�    ����GB16�ַ�����
*****���ߣ�    ��־��
*****����ʱ�䣺2013-11-16
*****��ע��������������ǽ��KEIL��sizeof()����ͽṹ����ͬһ���ļ���׼ȷʶ���BUGE
*****************************************************************************/  
extern unsigned int GB16_NUM(void) ;
#endif
