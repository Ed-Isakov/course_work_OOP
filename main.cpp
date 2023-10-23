#include "cl_application.h"
#include "cl_base.h"
#include <iostream>

int main()
{
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);
    cl_application  ob_cl_application ( nullptr ); // создание корневого объекта
    ob_cl_application.build_tree_objects ( ); // конструирование системы, построение дерева объектов
    return ob_cl_application.exec_app ( ); // запуск системы
}
/* Test:
5
r001xx-77 -1 -3
r003xx-77 1 -4
End of cars
Display the system status
Switching traffic lights red 3
Switching traffic lights green 3
Car r001xx-77
Car r003xx-77


Display the system status


Display the system status
Turn off the system
*/
