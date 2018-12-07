/* 

Latest examples is located at https://github.com/xethru/XeThru-ModuleConnector-Examples.

Target module: 
#X4M200
#X4M300
#X4M03(XEP)


Introduction: XeThru modules support both RF and baseband data output. This is an example of radar raw data manipulation. Developer can use Module Connecter API to read, record radar raw data, and also playback recorded data. 

prerequisite:

1. This example should be placed in ModuleConnector/examples.
2. Your computer should have a building toolchain. MinGW-w64 in MYSYS2 is suggested for Windows https://www.msys2.org/.

Command to run: 

1. Compile the source code by using make command under source code folder in terminal.
2. Run "./xt_modules_print_record_playback_radar_raw_data_message.exe comx" 

ToDo:
add settings
add print functions
add recording functions
add playback functions.

*/

#include "ModuleConnector.hpp"
#include "XEP.hpp"
#include "X4M300.hpp"
#include "xtid.h"
#include <iostream>

using namespace XeThru;

void usage()
{
    std::cout << "plot_radar_raw_data_message <com port or device file>" << std::endl;
}

int handle_error(std::string message)
{
    std::cerr << "ERROR: " << message << std::endl;
    return 1;
}

int plot_radar_raw_data_message(const std::string &device_name)
{
    XeThru::DataFloat radar_raw_data;
    const unsigned int log_level = 0;
    ModuleConnector mc(device_name, log_level);
    X4M300 &x4m300 = mc.get_x4m300();

    // ignore status. This might fail and that is ok.
    std::cout << "Set the module to Stop mode" << std::endl;
    x4m300.set_sensor_mode(XTID_SM_STOP, 0);
    std::cout << "Set the module to Manual mode" << std::endl;
    x4m300.set_sensor_mode(XTID_SM_MANUAL, 0);

    XEP &xep = mc.get_xep();

    // start the module and profile
    std::cout << "Set the module FPS and start to output radar raw data." << std::endl;
    if (xep.x4driver_set_fps(1))
    {
        return handle_error("Set FPS failed");
    }

    std::cout << "Printout radar raw message:" << std::endl;

    while (xep.peek_message_data_float() >= 0)
    {
        xep.read_message_data_float(&radar_raw_data);
        std::cout << "radar_raw_data_message:" << std::endl;
        for (auto x = std::end(radar_raw_data.data); x != std::begin(radar_raw_data.data);)
        {
            std::cout << *--x << ' ';
        }
    }

    std::cout << "Set the module in STOP state" << std::endl;
    if (x4m300.set_sensor_mode(XTID_SM_STOP, 0))
    {
        return handle_error("set output controll failed");
    }

    std::cout << "Messages output finish!" << std::endl;
    return 0;
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        usage();
        return -1;
    }

    const std::string device_name = argv[1];

    return plot_radar_raw_data_message(device_name);
}
