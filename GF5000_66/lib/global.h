/*
 * =====================================================================================
 *
 *       Filename:  global.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2017年11月17日 12时11分50秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Tomson (TR), terran126@qq.com
 *   Organization:  GZ Sat IR Co.,Ltd
 *
 * =====================================================================================
 */

#ifndef GLOBAL_H
#define GLOBAL_H

#include <stdio.h>
#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef bool
//typedef int bool;
#endif
#ifndef true
#define true    1
#endif
#ifndef false
#define false   0
#endif

#ifndef uchar
typedef unsigned char uchar;
#endif
#ifndef ushort
typedef unsigned short ushort;
#endif
#ifndef uint
typedef unsigned int uint;
#endif

#define INFO 	1
#define DEBUG	2
#define WARNING	3
#define ERROR	4

#define DEBUG_LEVEL	WARNING


#ifdef __cplusplus
}
#endif

#endif
