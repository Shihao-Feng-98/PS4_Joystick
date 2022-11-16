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

        printf("\rTIME:%8d A:%d B:%d X:%d Y:%d L1:%d R1:%d SHARE:%d OPTIONS:%d LX:%-6d LY:%-6d RX:%-6d RY:%-6d L2:%-6d R2:%-6d XX:%-6d YY:%-6d", 
                ps4->map.TIME, ps4->map.A, ps4->map.B, ps4->map.X, ps4->map.Y, ps4->map.L1, ps4->map.R1, ps4->map.SHARE, ps4->map.OPTIONS, 
                ps4->map.LX, ps4->map.LY, ps4->map.RX, ps4->map.RY, ps4->map.L2, ps4->map.R2, ps4->map.XX, ps4->map.YY);

        fflush(stdout);
    }
    return 0;
}

