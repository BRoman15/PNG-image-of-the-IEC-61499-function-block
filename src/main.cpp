// #include "C:\VSCod\PNG-image-of-the-IEC-61499-function-block\include\FB_lib.h"
// #include "SFML\Graphics.hpp"

// int main(){
//     BasicFB* a = create_basic_fb("C:\\VSCod\\PNG-image-of-the-IEC-61499-function-block\\test_data_xml\\INT2INT.xml");
//     get_name(a);
// }

#include "FB_lib_graphic.h"
#include <iostream>

int main(){
    BasicFB_image a;
    a.addTransparentBeveledRectangle(400, 300, 200, 100, 20);
    while (a.isWindowOpen()) {
        a.update();
    }
}