#include "gpibDeviceException.h"

using namespace std;

/**
 * This class is used to handle gpibDeviceExceptions.
 * The constructor parameters are:
 * Device name, origin, gpib error message, gpib ibsta string representation.
 */
gpibDeviceException::gpibDeviceException(string device_name,string origin,string err_msg,string sta_msg,int err,int sta)
{
    message = origin;
    iberrMessage = err_msg;
    ibstaMessage = sta_msg;
    dname = device_name;
    ib_sta = sta;
    ib_err = err;
}

/**
 * Get gpibDevice Class message / origin.
 */ 
string gpibDeviceException::getMessage()
{
    return message;
}


/**
 * Get gpib library low level error message.
 */ 
string gpibDeviceException::getiberrMessage()
{
    return iberrMessage;
}

/**
 * Get gpib ibsta in string form.
 */ 
string gpibDeviceException::getibstaMessage()
{
    return ibstaMessage;
}

/**
 * Get device name on which exception occurs.
 */ 
string gpibDeviceException::getDeviceName()
{
    return dname;
}

/**
 * Get iberr value from the device on which error occurs.
 */ 
int gpibDeviceException::getErrorValue()
{
    return ib_err;
}

/**
 * Get ibsta value from the device on which error occurs.
 */ 
int gpibDeviceException::getStateValue()
{
    return ib_sta;
}

