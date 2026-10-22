#ifndef _TTF_H
#define _TTF_H

#include <stdio.h>
#include <stdint.h>
#include <wchar.h>

namespace ttf
{
    struct Table {
        uint32_t tag;
        uint32_t checksum;
        uint32_t offset;
        uint32_t lenght;
    };

    struct CharMapping {
        uint32_t start_char;
        uint32_t end_char;
        uint32_t start_glyph;
        int type;
        uint32_t flags;
    };

    #define TTF_CMAP_SAME  1
    #define TTF_CMAP_INC   2
    #define TTF_CMAP_MOD16 0x01

    struct File {
        FILE *file;
        size_t file_size;
        Table head;
        Table cmap;
        Table glyf;
        Table loca;
        Table maxp;
        uint16_t unit_per_em;
        uint16_t reserved;
        uint32_t flags;
        uint32_t char_mapping_count;
        CharMapping *char_mapping;
        int font_size;
        int curves_seg;
    };

    struct Point {
        int32_t x;
        int32_t y;
        uint8_t flags;
    };

    struct Glyph {
        File *font;
        int16_t num_contours;
        int16_t x_min;
        int16_t y_min;
        int16_t x_max;
        int16_t y_max;
        uint16_t *ends_pts; //last point of each contour
        uint16_t num_pts;
        Point *pts;
    };

    struct Bitmap {
        int width;
        int height;
        uint8_t *bitmap;
    };

    #define TTF_FLAG_LONG_OFF (1 << 16)

    extern const char *__ttf_error;

    File *ttf_open(const char *path);
    void ttf_close(File *file);
    const char *ttf_error(void);
    uint32_t ttf_char2glyph(File *font,wchar_t c);
    Glyph *ttf_getglyph(File *font,wchar_t c);
    void ttf_free_glyph(Glyph *glyph);
    void ttf_set_font_size(File *font,int size);
    void ttf_set_curves_seg(File *font,int count);
    Bitmap *ttf_render_glyph(Glyph *glyph);
} // namespace ttf

#define TAG(str) (str[0] << 24 | str[1] << 16 | str[2] << 8 | str[3])
#endif