#if !defined(_BTK_FT_INTERNAL_HPP_)
#define _BTK_FT_INTERNAL_HPP_
#include <cassert>
#include <cstring>
#include <mutex>
#include <map>

//SDL2
#include <SDL2/SDL_atomic.h>

//Freetype impl
#include <ft2build.h>
#include FT_FREETYPE_H

namespace BtkFt{
    using FaceIndex = FT_ULong;
    using CharIndex = FT_ULong;
    using Char = char32_t;
    struct Font;
    struct FontMetrics{
        float ascender;
        float descender;
        float height;
    };
    struct Face{
        Face(const char *fname,FaceIndex index = 0);
        Face(const void *buf,size_t buflen,FaceIndex index = 0);
        ~Face();
        FT_Face face;

        int refcount;
        int spinlock;

        void unref(){
            --refcount;
            if(refcount <= 0){
                delete this;
            }
        }
        void ref(){
            ++refcount;
        }
        void lock(){
            SDL_AtomicLock(&spinlock);
        }
        void unlock(){
            SDL_AtomicUnlock(&spinlock);
        }
        /**
         * @brief Get global metrics
         * 
         * @return FontMetrics 
         */
        FontMetrics metrics();
        /**
         * @brief Is the glyph is provieded
         * 
         * @param ch 
         * @return true 
         * @return false 
         */
        bool has_glyph(Char ch);

        void render_glyph();
    };
    /**
     * @brief Slot for 
     * 
     */
    struct GlyphSlots{
        int w;
        int h;
        int pitch;
        Uint8 *buffer;
    };
    /**
     * @brief The font user used
     * 
     */
    struct Font{
        Face *face;
        int refcount;
    };
    struct Library{
        Library();
        ~Library();
        Library(const Library &) = delete;
        /**
         * @brief Freetype library
         * 
         */
        FT_Library ft_lib;
        //Mutex for 
        std::recursive_mutex mtx;

        std::map<std::string,Face*> faces_map;

        
    };
    struct FontStash{

    };
    extern void Init();
    extern void Quit();
    extern Library *library;
    inline Library &Instance(){
        return *library;
    }
}


#endif // _BTK_FT_INTERNAL_HPP_
