#include "internal.hpp"

namespace BtkFt{
    System *System::instance = nullptr;
    void *FtLibrary(){
        return __TTF_FtLibrary();
    }
    void Init(){
        TTF_Init();
        System::instance = new System();
    }
    void Quit(){
        delete System::instance;
        TTF_Quit();
    }
}