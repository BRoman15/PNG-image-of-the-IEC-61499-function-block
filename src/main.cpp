#include "FB_Visualizer.h"

int main(){
    FB_Visualizer a;
    // Загружаем данные из XML файла
    a.load_from_XML("C:\\VSCod\\PNG-image-of-the-IEC-61499-function-block\\test_data_xml\\ADD_2.xml");
    // Запускаем отрисовку ФБ
    a.rendering_FB();
    // Выводим и сохраняем(При закрытии окна) результат 
    a.show_and_save_FB();
}