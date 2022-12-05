#include <memory>
#include <chrono>
#include <joystick_PS4.h>


int main(int argc, char** argv)
{
    std::unique_ptr<JoystickPS4> ps4 = std::make_unique<JoystickPS4>("/dev/input/js0");

    // auto start = std::chrono::high_resolution_clock::now();
    // ps4->read_data(); // 1-2us
    // auto end = std::chrono::high_resolution_clock::now();
    // auto duration = end - start;
    // printf("%ld ns\n", duration.count());

    while (1)
    {
        usleep(10*1000); // 10ms

        if (!ps4->read_data()) {break;}

        printf("\rTIME:%8d A:%d B:%d X:%d Y:%d L1:%d R1:%d SHARE:%d OPTIONS:%d LX:%-6f LY:%-6f RX:%-6f RY:%-6f L2:%-6f R2:%-6f XX:%-6d YY:%-6d", 
                ps4->ps4_map.TIME, ps4->ps4_map.A, ps4->ps4_map.B, ps4->ps4_map.X, ps4->ps4_map.Y, ps4->ps4_map.L1, ps4->ps4_map.R1, ps4->ps4_map.SHARE, ps4->ps4_map.OPTIONS, 
                ps4->ps4_map.LX, ps4->ps4_map.LY, ps4->ps4_map.RX, ps4->ps4_map.RY, ps4->ps4_map.L2, ps4->ps4_map.R2, ps4->ps4_map.XX, ps4->ps4_map.YY);

        fflush(stdout);
    }
    return 0;
}
