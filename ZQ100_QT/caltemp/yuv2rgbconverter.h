#ifndef YUV2RGBCONVERTER_H
#define YUV2RGBCONVERTER_H

#include <stdint.h>
#include <QColor>


class YUV2RGBConverter
{
public:
    YUV2RGBConverter();
    QRgb yuv2rgb(uint8_t y, uint8_t u, uint8_t v);
    void yuy2(const uint8_t * yuy2, QRgb * rgb, size_t size);
    void vyuy(const uint8_t * yuy2, QRgb * rgb, size_t size);
    void yuv422(const uint8_t * yuv_y,
                const uint8_t * yuv_u,
                const uint8_t * yuv_v,
                QRgb * rgb,
                size_t size);
private:
    static uint8_t RYV[256][256];
    static uint8_t BYU[256][256];
    static uint16_t TUV[256][256];
    static uint8_t GYT[256][270];
    static bool m_table_init;
};

#endif // YUV2RGBCONVERTER_H
