#include<iostream>
#include"interface/interface.hpp"

//g++ main.cpp -fPIC interface/interface.cpp -o prog -lsfml-graphics -lsfml-window -lsfml-system

int main()
{
    Interface interface;

    while(interface.isOpen()){
        interface.events();
        interface.show();
        interface.update();
    }
    return 0;
}