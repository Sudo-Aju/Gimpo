#include <iostream>

int main() 
{
    int health = 100;
    int damage = 15;
    health -= damage;

    std::cout << "The remaining health is: " << health << std::endl;
    return 0;
}