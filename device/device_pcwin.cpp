/**
 * @file device_pcwin.cpp
 * @brief device for Win personal computer
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2016-10-25
 */

#include "device_p.h"

namespace DplDevice {

QString DevicePrivate::get_serial_number()
{
    return "1234-5678-90ab";
}

}