#include "HardwareDummy.hpp"
#include <ostream>
#include <unistd.h>

namespace openiolinklibrary
{

    HardwareDummy::HardwareDummy(/* args */)
    {
        std::cout << "Init HardwareDummy\n";
        testpin.set(false);
        testpin.set(true);
    }

    HardwareDummy::~HardwareDummy()
    {
        std::cout << "Deinit HardwareDummy\n";
    }

    void HardwareDummy::wait_for(uint32_t delay_ms)
    {
        usleep(delay_ms * 1000);
    }

    HardwareDummy::PIN_Dummy::PIN_Dummy(std::string name, std::string mode) : pinname(name)
    {
        IO_PinMode(mode);
    }

    HardwareDummy::PIN_Dummy::~PIN_Dummy()
    {
        IO_PinMode("in");
    }

    void HardwareDummy::PIN_Dummy::set(bool setto)
    {
        if (setto)
        {
            IO_Write(HIGH);
        }
        else
        {
            IO_Write(LOW);
        }
    }

    void HardwareDummy::PIN_Dummy::IO_PinMode(std::string mode)
    {
        std::cout << "Pinmode: " << pinname << "=" << mode << "\n";
    }

    void HardwareDummy::PIN_Dummy::IO_Write(std::string output)
    {
        std::cout << "Pin set: " << pinname << "=" << output << "\n";
    }

} // namespace openiolinklibrary