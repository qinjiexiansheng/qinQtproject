#include "yuv2rgbconverter.h"

inline QRgb YUV2RGBConverter::yuv2rgb(uint8_t y, uint8_t u, uint8_t v)
{
    int R = RYV[y][v];
    int G = GYT[y][TUV[u][v]];
    int B = BYU[y][u];
    return qRgb(R, G, B);
}

bool YUV2RGBConverter::m_table_init = false;
uint8_t YUV2RGBConverter::RYV[256][256];
uint8_t YUV2RGBConverter::BYU[256][256];
uint16_t YUV2RGBConverter::TUV[256][256];
uint8_t YUV2RGBConverter::GYT[256][270];


YUV2RGBConverter::YUV2RGBConverter()
{
    int R, G, B, T;
    if(!m_table_init)
    {
        for(int y = 0; y < 256; y++)
        {
            for(int v = 0; v < 256; v++)
            {
                int u = v;
                R = qRound(y + 1.403 * (v - 128));
                B = qRound(y + 1.770 * (u - 128));
                RYV[y][v] = qBound(0, R, 255);
                BYU[y][u] = qBound(0, B, 255);
            }
        }
        for(int u = 0; u < 256; u++)
        {
            for(int v = 0; v < 256; v++)
            {
                T = qRound(-0.343 * (u - 128) - 0.714 * (v - 128));
                // T 的范围 [-134, 135]
                TUV[u][v] = qBound(0, T + 134, 269);
            }
        }
        for(int y = 0; y < 256; y++)
        {
            for(int t = 0; t < 270; t++)
            {
                G = y + (t - 134);
                GYT[y][t] = qBound(0, G, 255);
            }
        }

        m_table_init = true;
    }
}


void YUV2RGBConverter::yuy2(const uint8_t *yuy2, QRgb * rgb, size_t size)
{
    size_t i = 0;
    do
    {
        uint8_t y0 = *yuy2++;
        uint8_t u = *yuy2++;
        uint8_t y1 = *yuy2++;
        uint8_t v = *yuy2++;

        *rgb++ = yuv2rgb(y0, u, v);
        *rgb++ = yuv2rgb(y1, u, v);
        i += 2;
    }while(i < size);
}

void YUV2RGBConverter::vyuy(const uint8_t * yuy2, QRgb * rgb, size_t size)
{
    size_t i = 0;
    do
    {
        uint8_t v = *yuy2++;
        uint8_t y0 = *yuy2++;
        uint8_t u = *yuy2++;
        uint8_t y1 = *yuy2++;

        *rgb++ = yuv2rgb(y0, u, v);
        *rgb++ = yuv2rgb(y1, u, v);
        i += 2;
    }while(i < size);
}

void YUV2RGBConverter::yuv422(const uint8_t * yuv_y,
            const uint8_t * yuv_u,
            const uint8_t * yuv_v,
            QRgb * rgb,
            size_t size)
{
    size_t i = 0;
    do
    {
        uint8_t y0 = *yuv_y++;
        uint8_t y1 = *yuv_y++;
        uint8_t u = *yuv_u++;
        uint8_t v = *yuv_v++;

        *rgb++ = yuv2rgb(y0, u, v);
        *rgb++ = yuv2rgb(y1, u, v);
        i += 2;
    }while(i < size);
}
