#include "Controller.h"
#include <iostream>

int main()
{
    int target;
    std::cout << "Enter target ADC (0-1023): ";
    if (!(std::cin >> target))
    {
        std::cerr << "Invalid input\n";
        return 1;
    }
    if (target < 0 || target > 1023)
    {
        std::cerr << "Target out of range\n";
        return 1;
    }

    Controller controller(target);
    controller.run();

    return 0;
}
