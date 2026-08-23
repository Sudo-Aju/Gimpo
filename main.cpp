#include <iostream>

void PlayerStats(int damage, int health, int speed, std::string PlayerName)
{
 std::cout << "Player Stats:" << std::endl;
 std::cout << "Player's Name:" << PlayerName << std::endl;
 std::cout << "Damage:" << damage << std::endl;
 std::cout << "Health:" << health << std::endl;
 std::cout << "Speed:" << speed << std::endl;
}

int main() 
{  
    
    PlayerStats(1, 100, 2, "Azmeer");
    PlayerStats(40, 90, 3, "Soup");
    return 0;
}

