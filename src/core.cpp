#include "internal.hpp"

namespace BtkFt{
    Library *library = nullptr;
    void Init(){
        if(library != nullptr){
            library = new Library;
        }
    }
    void Quit(){
        delete library;
        library = nullptr;
    }
}