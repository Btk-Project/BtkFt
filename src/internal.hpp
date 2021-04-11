#if !defined(_BTK_FT_INTERNAL_HPP_)
#define _BTK_FT_INTERNAL_HPP_
#include <map>
#include "SDL_ttf.hpp"
namespace BtkFt{
    struct Font{
        TTF_Font *font;
    };
    struct GlyphSlots{

    };
    struct System{
        static System *instance;

        std::map<int,Font*> fontmap;
        std::map<std::string,Font*> namemap;
    };
    struct Fontstash{

    };
    void *FtLibrary();
    void Init();
    void Quit();
}


#endif // _BTK_FT_INTERNAL_HPP_
