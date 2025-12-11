// #include "C:\VSCod\PNG-image-of-the-IEC-61499-function-block\include\FB_lib.h"
// #include "SFML\Graphics.hpp"

// int main(){
//     BasicFB a("C://VSCod//PNG-image-of-the-IEC-61499-function-block//test_data_xml//INT2INT.xml");
//     a.get_attributes();
// }

// #include "FB_lib_graphic.h"
// #include <iostream>

// int main(){
//     BasicFB_image a;
//     float b;
//     a.addMainContour(0, 0, 200, 200, 100, 20);
//     a.addText("Normal Execution Request", 200, 200);
//     a.addTriangle(370, 300);
//     a.addLine(200, 200, 30, 1);
//     a.addLine(200, 200 + 15, -30);
//     a.addConnection(90, 90, 1);
//     a.get_width_text("N");
//     while (a.isWindowOpen()) {
//         a.update();
//     }
// }

#include "Connection.h"

int main(){
    Connection a;
    a.load_from_XML("C:\\VSCod\\PNG-image-of-the-IEC-61499-function-block\\test_data_xml\\ADD_2.xml");
    a.rendering_FB();
    a.showWindow();
}