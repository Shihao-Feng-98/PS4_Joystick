#include <joystick_PS4.h>

JoystickPS4::JoystickPS4(const char *file_name)
{
    _ps4_fd = open(file_name, O_RDONLY);
    if (_ps4_fd < 0){
        printf("[JoystickPS4]: open error(%d), %s\n", errno, strerror(errno));
    }
    map.L2 = PS4_AXIS_VEL_MIN;
    map.R2 = PS4_AXIS_VEL_MIN;
}

JoystickPS4::~JoystickPS4()
{
    close(_ps4_fd);
}

bool JoystickPS4::read_data()
{
    _len = read(_ps4_fd, &_js, sizeof(struct js_event));
    if (_len < 0)
    {
        printf("[JoystickPS4]: read error(%d), %s\n", errno, strerror(errno));
        return false;
    }
    // Extrast data
    _type = _js.type;
    _number = _js.number;
    _value = _js.value;

    map.TIME = _js.time;
    if (_type == JS_EVENT_BUTTON)
    {
        switch (_number)
        {
            case PS4_BUTTON_A:
                map.A = _value;
                break;

            case PS4_BUTTON_B:
                map.B = _value;
                break;

            case PS4_BUTTON_X:
                map.X = _value;
                break;         

            case PS4_BUTTON_Y:
                map.Y = _value;
                break;

            case PS4_BUTTON_L1:
                map.L1 = _value;
                break;

            case PS4_BUTTON_R1:
                map.R1 = _value;
                break;
                
            case PS4_BUTTON_SHARE:
                map.SHARE = _value;
                break;

            case PS4_BUTTON_OPTIONS:
                map.OPTIONS = _value;
                break;

            default:
                break;
        }
    }
    else if (_type == JS_EVENT_AXIS)
    {
        switch (_number)
        {
        case PS4_AXIS_LX:
            map.LX = _value;
            break;

        case PS4_AXIS_LY:
            map.LY = _value;
            break;

        case PS4_AXIS_RX:
            map.RX = _value;
            break;

        case PS4_AXIS_RY:
            map.RY = _value;
            break;

        case PS4_AXIS_L2:
            map.L2 = _value;
            break;        

        case PS4_AXIS_R2:
            map.R2 = _value;
            break;  

        case PS4_AXIS_XX:
            map.XX = _value;
            break;  

        case PS4_AXIS_YY:
            map.YY = _value;
            break;  

        default:
            break;
        }
    }
    return true;
}
