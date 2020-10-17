#ifndef __EXIFPARAM_H__
#define __EXIFPARAM_H__
#endif
typedef unsigned char   UCHAR;
typedef unsigned long   ULONG;
typedef unsigned int    UINT;
typedef unsigned long   DWORD;
typedef unsigned int    UINT32;
typedef int             INT32;
typedef unsigned char   UINT8;
//typedef enum {FALSE, TRUE} BOOL;


typedef struct tagExifFileInfo
{
        char    Make[32];
        char    Model[32];
        char    Version[32];
        char    DateTime[32];
        char    CopyRight[32];

        UINT    Height;
        UINT    Width;
        UINT    Orientation;
        UINT    ColorSpace;
        UINT    Process;
        UINT    Flash;

        UINT    FocalLengthNum;
        UINT    FocalLengthDen;

        UINT    ExposureTimeNum;
        UINT    ExposureTimeDen;

        UINT    FNumberNum;
        UINT    FNumberDen;

        UINT    ApertureFNumber;

        int             SubjectDistanceNum;
        int             SubjectDistanceDen;

        UINT    CCDWidth;

        int             ExposureBiasNum;
        int             ExposureBiasDen;


        int             WhiteBalance;

        UINT    MeteringMode;

        int             ExposureProgram;

        UINT    ISOSpeedRatings[2];

        UINT    FocalPlaneXResolutionNum;
        UINT    FocalPlaneXResolutionDen;

        UINT    FocalPlaneYResolutionNum;
        UINT    FocalPlaneYResolutionDen;

        UINT    FocalPlaneResolutionUnit;

        UINT    XResolutionNum;
        UINT    XResolutionDen;
        UINT    YResolutionNum;
        UINT    YResolutionDen;
        UINT    RUnit;

        int             BrightnessNum;
        int             BrightnessDen;

        char    UserComments[150];
        UCHAR   GpsLatitudeRef;         
        UCHAR   GpsLatitude[20];                
        UCHAR   GpsLongitudeRef;        
        UCHAR   GpsLongitude[20];               
        UCHAR   GpsAltitude[10];                

}ExifFileInfo;

