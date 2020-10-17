/*
 * =====================================================================================
 *
 *       Filename:  client.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017年12月06日 10时01分33秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Tomson (TR), terran126@qq.com
 *   Organization:  GZ Sat IR Co.,Ltd
 *
 * =====================================================================================
 */

#ifndef CLIENT_H
#define CLIENT_H

#include "global.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * 连接到服务器
 * 在使用如下函数调用之前都必须先调用此函数连接到服务器
 * 
 * @return 连接到服务器的socket套接字
 */
int connect_server();

/** 
 * 关闭socket连接
 */
void close_connection();

/**
 * 得到点(x,y)的AD值
 *
 * @param x 坐标
 * @param y 坐标
 *
 * @return AD值
 */
ushort getAD(int x, int y);

/**
 * 设置探测器的FID
 *
 * @param fid
 */
void setFID(ushort fid);

/** 
 * 得到探测器的FID值
 *
 * @return fid
 */
ushort getFID();

/**
 * 设置探测器的GSK
 *
 * @param gsk 
 */
void setGSK(ushort gsk);

/**
 * 得到探测器的GSK
 *
 * @param gsk 
 */
ushort getGSK();
/**
 * 设置探测器的GAIN
 *
 * @param gain 
 */
void setGAIN(int gain);

/**
 * 得到探测器的GAIN
 *
 * @param gain
 */
int getGAIN();

/**
 * 设置探测器的TINT
 *
 * @param tint 
 */
void setTINT(int tint);

/**
 * 得到探测器的TINT
 *
 * @param tint
 */
int getTINT();

/**
 * 得到区域内的最大最小值
 *
 * @param x 区域的左上角X坐标
 * @param y 区域的左上角Y坐标
 * @param width 区域的宽
 * @param height 区域的高
 * @param *max_x 返回最大值的X坐标
 * @param *max_y 返回最大值的Y坐标
 * @param *max 返回最大值
 * @param *min_x 返回最小值的X坐标
 * @param *min_y 返回最小值的X坐标
 * @param *min 返回最小值
 *
 * @return -1 失败，0 成功
 */
int getMaxMin(int x, int y, int width, int height, int *max_x, int *max_y, ushort *max, int *min_x, int *min_y, ushort *min);

/**
 * 得到探测器的DET
 *
 * @param det 
 */
int getDET();
/**
 * 得到温度传感器温度值 SENSOR
 *
 * @param temperature 
 */
float getSENSOR();
/**
 * 得到电池电量状态 
 *
 * @param battery_val 
 */
int getBatteryV();
/**
 * 得到电池是否在充电  0.空闲  1.充电中
 *
 * @param battery_status 
 */
int getBatteryStatus();
/**
 * 得到图像全局AD平均值
 *
 * @param ad_ave 
 */
short getGlobalADave();
/**
 * 得到图像点原始AD值，坐标由getAD确定
 *
 * @param original_AD 
 */
short getDotOriginalAD();
/**
 * 设置红外图像模式
 *
 * @param irmode   伪彩色: 0.铁红; 1.反铁红; 2.彩虹; 3. 羽红; 4.黑热; 5.白热
 */

void setIrmode(int irmode);
/**
 * 设置图像是否启用降噪模式
 *
 * @param denoise   0.关闭; 1.开启
 */
void setDenoise(int denoise);
/**
 * 设置图像是否冻结
 *
 * @param freeze   0.解冻; 1.冻结
 */
void setImageFreeze(int freeze);
/**
 * 设置机器拍照
 *
 * @param camera   1.拍照
 */
//void setCamera(int camera);

char *setCamera(int camera);


/**
 * 设置机器录像
 *
 * @param video   0.结束 1.开始
 */
void SetVideo(int video);
/**
 * 设置机器打档
 *
 * @param shutter   1.打档
 */
void SetShutter(int shutter);
/**
 * 设置非均匀性矫正
 *
 * @param kcal   1.低温矫正  2.高温矫正
 */
void SetKcal(int kcal);
/**
 * 设置重新加载K值，K值表更新
 *
 * @param krflag   1.重新加载
 */
void SetReloadK(int krflag);
/**
 * 设置内外置打档
 *
 * @param shutflag  0.外置  1.内置 
 */
void SetShutter_tpye(int shutflag);
/**
 * 设置激光
 *
 * @param shutflag  0.关闭  1.开启 
 */
void SetLaser(int laser);
#ifdef __cplusplus
}
#endif

#endif
