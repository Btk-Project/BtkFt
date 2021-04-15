#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_ERRORS_H

#include <cmath>
#include <algorithm>

#include "internal.hpp"

namespace BtkFt{
    Library::Library(){
        FT_Error err = FT_Init_FreeType(&ft_lib);
        assert(err == 0);
    }
    Library::~Library(){
        FT_Done_FreeType(ft_lib);
        
    }
}
namespace BtkFt{
    Face::Face(const char *fname,FaceIndex index){
        std::lock_guard locker(Instance().mtx);

        FT_Error err = FT_New_Face(Instance().ft_lib,fname,index,&face);
        if(err){
            //...
        }
    }
    Face::Face(const void *buf,size_t buflen,FaceIndex index){
        std::lock_guard locker(Instance().mtx);
        
        FT_Error err = FT_New_Memory_Face(
            Instance().ft_lib,
            static_cast<const FT_Byte*>(buf),
            buflen,
            index,
            &face
        );
    }
    Face::~Face(){
        std::lock_guard locker(Instance().mtx);
        FT_Done_Face(face);
    }
    bool Face::has_glyph(Char ch){
        return FT_Get_Char_Index(face,ch) != 0;
    }
    //Global metrics
    FontMetrics Face::metrics(){
        FontMetrics m;
        if(FT_IS_SCALABLE(face)){
            FT_Fixed scale = face->size->metrics.y_scale;

            m.ascender =  FT_MulFix(face->ascender,scale);
            m.descender = FT_MulFix(face->descender,scale);
            m.height =    FT_MulFix(face->ascender - face->descender,scale);
        }
        else{
            m.ascender = face->size->metrics.ascender;
            m.descender = face->size->metrics.descender;
            m.height = face->size->metrics.height;
        }
        return m;
    }
}