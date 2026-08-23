#include <iostream>

void Player2();
void Player1();

int main() 
{
    Player1();
    Player2();
    return 0;
}

void Player2()
{
    std::cout << "Welcome" << std::endl;;
}

void Player1()
{
    std::cout << "Hello!" << std::endl;
}

