#include <joystick_PS4.h>

JoystickPS4::JoystickPS4(const char *file_name)
{
    _ps4_fd = open(file_name, O_RDONLY);
    if (_ps4_fd < 0){
        printf("[JoystickPS4]: open error(%d), %s\n", errno, strerror(errno));
    }
    ps4_map.L2 = 0.;
    ps4_map.R2 = 0.;
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

    ps4_map.TIME = _js.time;
    if (_type == JS_EVENT_BUTTON)
    {
        switch (_number)
        {
            case PS4_BUTTON_A:
                ps4_map.A = _value;
                break;

            case PS4_BUTTON_B:
                ps4_map.B = _value;
                break;

            case PS4_BUTTON_X:
                ps4_map.X = _value;
                break;         

            case PS4_BUTTON_Y:
                ps4_map.Y = _value;
                break;

            case PS4_BUTTON_L1:
                ps4_map.L1 = _value;
                break;

            case PS4_BUTTON_R1:
                ps4_map.R1 = _value;
                break;
                
            case PS4_BUTTON_SHARE:
                ps4_map.SHARE = _value;
                break;

            case PS4_BUTTON_OPTIONS:
                ps4_map.OPTIONS = _value;
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
            ps4_map.LX = (double)_value/PS4_AXIS_VEL_LIMIT;
            break;

        case PS4_AXIS_LY:
            ps4_map.LY = (double)-_value/PS4_AXIS_VEL_LIMIT;
            break;

        case PS4_AXIS_RX:
            ps4_map.RX = (double)_value/PS4_AXIS_VEL_LIMIT;
            break;

        case PS4_AXIS_RY:
            ps4_map.RY = (double)-_value/PS4_AXIS_VEL_LIMIT;
            break;

        case PS4_AXIS_L2:
            ps4_map.L2 = (double)(_value+PS4_AXIS_VEL_LIMIT)/(2*PS4_AXIS_VEL_LIMIT);
            break;        

        case PS4_AXIS_R2:
            ps4_map.R2 = (double)(_value+PS4_AXIS_VEL_LIMIT)/(2*PS4_AXIS_VEL_LIMIT);
            break;  

        case PS4_AXIS_XX:
            if (_value == 0) {
                ps4_map.XX = 0;
            }
            else {
                ps4_map.XX = (_value == PS4_AXIS_VEL_LIMIT ? 1 : -1);
            }
            break;  

        case PS4_AXIS_YY:
            if (_value == 0) {
                ps4_map.YY = 0;
            }
            else {
                ps4_map.YY = (_value == PS4_AXIS_VEL_LIMIT ? -1 : 1);
            }
            break;

        default:
            break;
        }
    }
    return true;
}
