#include "utility.h"

/**
 * @name    Utility()
 * @details 通用工具类
 * @author  lee
 * @date    2018-12-21
**/
Utility::Utility()
{

}

/**
 * @name    void HSL2RGB(unsigned char hh, unsigned char ss, unsigned char LL,unsigned char &rr, unsigned char &gg,
             unsigned char &bb)
 * @details HSL格式转RGB格式
 * @param   hh  色调
 * @param   ss  饱和度
 * @param   ll  亮度
 * @param   rr  红
 * @param   gg  绿
 * @param   bb  蓝
 * @author  lee
 * @date    2018-12-21
**/
void Utility::HSL2RGB(unsigned char hh, unsigned char ss, unsigned char LL,unsigned char &rr, unsigned char &gg,
             unsigned char &bb)
{
    double h, s, L;
    double v,m,sv, vs0, c1, c2,xiaoshu,r,g,b;
    int ih;

    h = (double)hh/240;
    s = (double)ss/240;
    L = (double)LL/240;

    r = L; g = L;b = L;
    if (L <= 0.5) v = L * (1.0 + s); else v = L + s - L * s;
    if (v > 0) {
        m = L + L - v; sv = (v - m ) / v;
        h = h * 6.0; ih = (int)h;
        xiaoshu = h - ih;
        vs0 = v * sv * xiaoshu; c1 = m + vs0; c2 = v - vs0;
        switch (ih) {
        case 0: r = v; g = c1; b = m; break;
        case 1: r = c2; g = v; b = m; break;
        case 2: r = m;  g = v; b = c1; break;
        case 3: r = m; g = c2; b = v; break;
        case 4: r = c1; g = m; b = v; break;
        case 5: r = v;  g = m; b = c2; break;
        default: break;
        }
    }
    rr =  (int) (r * 0xff);
    gg =  (int) (g * 0xff);
    bb =  (int) (b * 0xff);
}

/**
 * @name    rgb_item * Utility::HSL2RGB_(const rgb_item *hsl_color_t, unsigned int size)
 * @details HSL数组转换RGB数组
 * @param   hsl_color_t HSL数组
 * @return  RGB数组
 * @author  lee
 * @date    2018-12-21
**/
rgb_item * Utility::HSL2RGB_(const rgb_item *hsl_color_t, unsigned int size)
{
    rgb_item *rgb_color_t = (rgb_item *)malloc(size * sizeof(rgb_item));

    memset(rgb_color_t, 0, size * sizeof(rgb_item));

    for(int i=0; i<size; i++)
    {
       HSL2RGB(hsl_color_t[i].r, hsl_color_t[i].g,hsl_color_t[i].b,
               rgb_color_t[i].r, rgb_color_t[i].g, rgb_color_t[i].b);
    }
    return rgb_color_t;
}
