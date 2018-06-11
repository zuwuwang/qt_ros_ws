/******************************************************************************** 
 *      Copyright:  (C) 2017 zoulei 
 *                  All rights reserved. 
 * 
 *       Filename:  gps.h 
 *    Description:  This head file 
 * 
 *        Version:  1.0.0(2017年06月19日) 
 *         Author:  zoulei <zoulei121@gmail.com> 
 *      ChangeLog:  1, Release initial version on "2017年06月19日 12时25分59秒" 
 * 
 ********************************************************************************/  
  
#ifndef __GPS_H__  
#define __GPS_H__  
  
typedef unsigned int UINT;  
typedef int BYTE;  
  
typedef struct __gprmc__  
{  
   UINT time;/* gps定位时间 */  
   char pos_state;/*gps状态位*/  
   float latitude;/*纬度 */  
   float longitude;/* 经度 */  
   float speed; /* 速度 */  
   float direction;/*航向 */  
   UINT date;  /*日期  */  
   float declination; /* 磁偏角 */  
   char dd;  
   char mode;/* GPS模式位 */  
  
}GPRMC;  
extern int set_serial(int fd,int nSpeed, int nBits, char nEvent, int nStop);  
extern int print_gps(GPRMC *gps_date);  
extern int gps_analyse(char *buff,GPRMC *gps_data);  
#endif 
