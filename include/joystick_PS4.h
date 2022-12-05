#ifndef JOYSTICK_PS4_H
#define JOYSTICK_PS4_H

#include <stdio.h>
#include <string.h>
#include <errno.h> 
#include <unistd.h>  // sleep
// open() close() read()
#include <sys/types.h>  
#include <sys/stat.h> 
#include <fcntl.h>  
#include <linux/input.h>  
#include <linux/joystick.h>  


#define PS4_BUTTON_OFF      0x00
#define PS4_BUTTON_ON       0x01

#define PS4_AXIS_VEL_MID    0x00
#define PS4_AXIS_VEL_LIMIT  32767

#define PS4_BUTTON_A        0x00    // 叉
#define PS4_BUTTON_B        0x01    // 圆
#define PS4_BUTTON_X        0x02    // 三角形
#define PS4_BUTTON_Y        0x03    // 方形
#define PS4_BUTTON_L1       0x04    // 左上扳机按键
#define PS4_BUTTON_R1       0x05    // 右上扳机按键
#define PS4_BUTTON_SHARE    0x08
#define PS4_BUTTON_OPTIONS  0x09    

#define PS4_AXIS_LX         0x00    // 左摇杆x轴
#define PS4_AXIS_LY         0x01    // 左摇杆y轴
#define PS4_AXIS_RX         0x03    // 右摇杆x轴
#define PS4_AXIS_RY         0x04    // 右摇杆y轴
#define PS4_AXIS_L2         0x02    // 左上扳机
#define PS4_AXIS_R2         0x05    // 右上扳机
#define PS4_AXIS_XX         0x06    // 方向键x轴
#define PS4_AXIS_YY         0x07    // 方向键y轴

struct PS4_map_t
{
    int TIME;
    int SHARE;
    int OPTIONS;
    
    int A, B, X, Y; // right button (0, 1) default 0
    int L1, R1;     // button (0, 1) default 0
    
    double LX, LY;     // left axis [-1, 1] defaut 0
    double RX, RY;     // right axis [-1, 1] defaut 0
    double L2, R2;     // top axis [-1, 1] defaut -1
    int XX, YY;     // left button (-1, 0, 1) default 0
};

class JoystickPS4
{
public:
    JoystickPS4(const char *file_name);
    ~JoystickPS4();
    bool read_data();

    PS4_map_t ps4_map;
    
private:
    int _ps4_fd; // -1 is valid
    int _len, _type, _number, _value;
    struct js_event _js;
};

#endif
