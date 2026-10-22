#include "ttf.hpp"

namespace ttf
{
    const char *__ttf_error = "undefined";

    const char *ttf_error(void){
        return __ttf_error;
    }
} // namespace ttf