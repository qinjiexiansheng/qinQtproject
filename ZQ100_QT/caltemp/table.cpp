/**
 *      - 增加readReviseTable()函数读取校正温度表diff
 * 
 *        使用TFile类来实现配置文件的读取
 *      - 增加函数readReviseTemp4Dist()用来读取距离温度修正表
 */

#include "table.h"
#include <stdio.h>
#include "readcfgfile.cpp"

static TFile *s_file = NULL;

bool TTable::readTable(const char *filename, struct TempInfoTAB* adtempInfo){
        if( s_file == NULL ) {
                s_file = new TFile(filename);        
        } else {
                if( ::strcmp(filename, s_file->filename()) != 0 ) {
                        s_file->setFilename( filename ); 
                        s_file->openFile(); 
                        s_file->readFile();
                } 
        }

        TItem _item;
	int val;

        ::memset(&_item, '\0', sizeof(_item));
        ::strcpy(_item.key, "TabMaxAD");
        s_file->findItem( &_item );
	sscanf(_item.value, "%x", &val);
	adtempInfo->TabMaxAD = val;

        ::memset(&_item, '\0', sizeof(_item));
        ::strcpy(_item.key, "TabMinAD");
        s_file->findItem( &_item );
	sscanf(_item.value, "%x", &val);
	adtempInfo->TabMinAD = val;

        ::memset(&_item, '\0', sizeof(_item));
        ::strcpy(_item.key, "TabBegAD");
        s_file->findItem( &_item );
	sscanf(_item.value, "%x", &val);
	adtempInfo->TabBegAD = val;

        ::memset(&_item, '\0', sizeof(_item));
        ::strcpy(_item.key, "TabBaseTmp");
        s_file->findItem( &_item );
	adtempInfo->TabBaseTmp = atoi( _item.value );

        ::memset(&_item, '\0', sizeof(_item));
        ::strcpy(_item.key, "TabNum");
        s_file->findItem( &_item );
	adtempInfo->TabNum = atoi( _item.value );

	for(int i=0; i<adtempInfo->TabNum; i++){
                ::memset(&_item, '\0', sizeof(_item));
                ::sprintf(_item.key, "temp%d", i+1);
                s_file->findItem( &_item );
		adtempInfo->temp_wtab[i] = atoi( _item.value );

                ::memset(&_item, '\0', sizeof(_item));
                ::sprintf(_item.key, "AD%d", i+1);
                s_file->findItem( &_item );
		sscanf(_item.value, "%x", &val);
		adtempInfo->temp_ad_tab[i] = val;
	}

        return true;
}

bool TTable::readReviseTempTable(const char *filename, float *revise_temp)
{
        if( s_file == NULL ) {
                s_file = new TFile(filename);        
        } else {
                if( ::strcmp(filename, s_file->filename()) != 0 ) {
                        s_file->setFilename( filename ); 
                        s_file->openFile(); 
                        s_file->readFile();
                } 
        }

        TItem _item;
        int _num;

        ::strcpy( _item.key, "TabNum" );
        s_file->findItem( &_item );
        _num = atoi( _item.value );

        for(int i=0; i<_num; i++) {
                ::memset( &_item, '\0', sizeof(_item));
                ::sprintf(_item.key, "diff%d", i+1);
                s_file->findItem( &_item );
                revise_temp[i] = atof( _item.value );
        }

        ::memset( &_item, '\0', sizeof(_item));
        ::strcpy(_item.key, "diff30");
        s_file->findItem( &_item );
        revise_temp[30] = atof( _item.value );

        return true;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  readReviseTemp4Dist
 *  Description:  读取距离相关的温度修正表
 *        Param:  filename 文件名
 *        Param:  m 行(标定时的温度,如0, 30, 40, 60, 90, ...)
 *        Praem:  n 列(标定时的距离, 如0, 1, 2, 3, ...)
 *       Return:  修正的矩阵表
 * =====================================================================================
 */
float **g_DistReviseTable = NULL;
int g_DistReviseTable_M = NULL;
int g_DistReviseTable_N = NULL;
float **TTable::readReviseTemp4Dist(const char *filename, int *m, int *n){
	if( s_file == NULL ) {
                s_file = new TFile(filename);        
        } else {
                if( ::strcmp(filename, s_file->filename()) != 0 ) {
                        s_file->setFilename( filename ); 
                        s_file->openFile(); 
                        s_file->readFile();
                } 
        }

        int _m=0, _n=0;
        TItem _item;
        strcpy( _item.key, "T_M" );
        s_file->findItem( &_item );
        _m = atoi( _item.value );

        strcpy( _item.key, "T_N" );
        s_file->findItem( &_item );
        _n = atoi( _item.value );
        if( _m == 0 || _n == 0 ) {
                return NULL; 
        }
        if( g_DistReviseTable ) {
                for(int i=0; i<g_DistReviseTable_M; i++)
                        delete [] g_DistReviseTable[i];
                delete [] g_DistReviseTable;
        }

        g_DistReviseTable = new float*[_m];
        for(int i=0; i<_m; i++) 
                g_DistReviseTable[i] = new float[_n];

        int _x=0,_y=0;
        ::memset( &_item, 0, sizeof(TItem) );
        while( s_file->travelItem(&_item) > 0 ) {
                if( sscanf( _item.key, "T_%d_%d", &_x, &_y) == 2 ) {
                        g_DistReviseTable[_x][_y] = atof(_item.value);
                }
                ::memset( &_item, 0, sizeof(TItem));
        }

        g_DistReviseTable_M = *m = _m;
        g_DistReviseTable_N = *n = _n;
        return g_DistReviseTable;
}

