#ifndef _GPIBDEVICEEXCEPTION
#define _GPIBDEVICEEXCEPTION

#include <string>


using namespace std;

/**
 *This class is used to handle gpibDeviceExceptions.
 */
class gpibDeviceException {
    
    public:
    
    gpibDeviceException(string device_name,string origin,string err_msg,string sta_msg,int err, int sta);
    string getMessage();
    string getiberrMessage();
    string getibstaMessage();
    string getDeviceName();
    int getErrorValue();
    int getStateValue();
    protected:
    
    private:
    
    string dname;
    string message;
    string iberrMessage;
    string ibstaMessage;
    int ib_err;
    int ib_sta;
};
#endif
