#include <stdio.h>
#include <stdlib.h>
#include "ttf.hpp"

namespace ttf
{
    void ttf_close(File *font){
        fclose(font->file);
        free(font->char_mapping);
        free(font);
    }
} // namespace ttf