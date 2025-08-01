#include "fix/FixClient.hpp"

#include <iostream>
#include <sstream>

int main()
{
    try
    {
        auto client = FixClient();
        client.connect();
        std::cout
            << "Press <ENTER> to quit" << std::endl;
        std::cin.get();
        client.disconnect();
    }
    catch (std::exception &e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
        return 1;
    }
    return 0;
}
