/* 

Latest examples is located at https://github.com/xethru/XeThru-ModuleConnector-Examples.

Target module: X4M200

Introduction: This is an example of how to print out application messages from X4M200 module.

prerequisite:

1. This example should be placed in ModuleConnector/examples.
2. Your computer should have a building toolchain. MinGW-w64 in MYSYS2 is suggested for Windows https://www.msys2.org/.

Command to run: 

1. Compile the source code by using make command under source code folder in terminal.
2. Run "./x4m200_print_record_playback_RESP_SLEEP_message.exe comx" 

ToDo:
add settings
add print functions
add recording functions
add playback functions
*/

#include "ModuleConnector.hpp"
#include "X4M200.hpp"
#include "xtid.h"
#include <iostream>

using namespace XeThru;

void usage()
{
    std::cout << "print_x4m200_messages <com port or device file>" << std::endl;
}

int handle_error(std::string message)
{
    std::cerr << "ERROR: " << message << std::endl;
    return 1;
}

int print_x4m200_messages(const std::string &device_name)
{
    XeThru::SleepData respiration_sleep_signal;
    char respiration_sensor_state_text[5][20] = {"BREATHING", "MOVEMENT", "MOVEMENT TRACKING", "NO MOVEMENT", "INITIALIZING"};
    const unsigned int log_level = 0;
    ModuleConnector mc(device_name, log_level);
    X4M200 &x4m200 = mc.get_x4m200();

    // ignore status. This might fail and that is ok.
    std::cout << "Stop the module" << std::endl;
    x4m200.set_sensor_mode(XTID_SM_STOP, 0);

    std::cout << "Load presence profile" << std::endl;
    if (x4m200.load_profile(XTS_ID_APP_RESPIRATION_2))
    {
        return handle_error("load_profile failed");
    }

    std::cout << "Turn on presence single packages" << std::endl;
    if (x4m200.set_output_control(XTS_ID_SLEEP_STATUS, XTID_OUTPUT_CONTROL_ENABLE))
    {
        return handle_error("set output controll failed");
    }

    // start the module and profile
    std::cout << "Set the module in RUN state" << std::endl;
    if (x4m200.set_sensor_mode(XTID_SM_RUN, 0))
    {
        return handle_error("Set sensor mode to running failed");
    }

    std::cout << "Printout respiration sleep message:" << std::endl;

    while (x4m200.peek_message_respiration_sleep() >= 0)
    {
        x4m200.read_message_respiration_sleep(&respiration_sleep_signal);
        std::cout << "message_respiration_sleep: frame_counter: " << respiration_sleep_signal.frame_counter << " sensor_state: " << respiration_sensor_state_text[respiration_sleep_signal.sensor_state] << " respiration_rate : " << respiration_sleep_signal.respiration_rate << " distance : " << respiration_sleep_signal.distance << " movement_slow : " << respiration_sleep_signal.movement_slow << " movement_fast : " << respiration_sleep_signal.movement_fast << std::endl;
    }

    std::cout << "Set the module in STOP state" << std::endl;
    if (x4m200.set_sensor_mode(XTID_SM_STOP, 0))
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

    return print_x4m200_messages(device_name);
}
