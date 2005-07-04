#include <iostream>
#include <sstream>
#include <string>
#include "gpibDevice.h"

/* Include for Linux and Solaris. */
#ifdef _solaris
#include "ugpib.h"	/* Warning: modified header for C++ compatibility */
#endif

#ifdef linux
#include "ugpib.h"	/* Warning: modified header for C++ compatibility */
#endif

/* Include for Windows. */
#ifdef WIN32
#include <windows.h>
#include "ni488.h"	
#endif

using namespace std;

/**
 * Standard GPIB errors strings.
 */
const string error_array[] = {
    	"EDVR - Unix error (code in ibcnt)",
	"ECIC - Function require GPIB board to be Controller-In-Charge",
	"ENOL - Write handshake error (e.g. no listener)",
	"EADR - GPIB board not addressed correctly",
	"EARG - Invalid argument to function call",
	"ESAC - GPIB board not System Controller as required",
	"EABO - I/O operation aborted (timeout)",
	"ENEB - Non-existent GPIB board",
	"EDMA - DMA hardware problem",
	"EBTO - DMA hardware bus timout",
	"???? - UNKNOWN ERROR !",   // index 10
  	"ECAP - No capability for operation",
        "EFSO - File system error",
	"???? - UNKNOWN ERROR !",   // index 13
	"EBUS - GPIB bus error",
	"ESTB - Serial poll status byte queue overflow",
        "ESRQ - SRQ stuck in ON position",
	"???? - UNKNOWN ERROR !",   // index 17
	"???? - UNKNOWN ERROR !",   // index 18
	"???? - UNKNOWN ERROR !",   // index 19		
	"ETAB - Table problem"
};

/**
 * This is the base constructor for the gpibDevice class.
 * The parameter passed to this constructor, is the device name as 
 * defined in the gpib driver with the ibconf program, and the boardname
 * which is in gpibX form, where x is a digit, where your device is linked on.
 * This constructor has been added to allow multiple board configurations on
 * a single driver. 
 * gpibDevice("dev3", "gpib0") is equivalent to gpibDevice("dev3");
 * VERY IMPORTANT NOTES:
 * All devices plugged in board different from gpibd0 MUST use this constructor.
 * If method doesn't throw exception this not necessarly mean that the gpib
 * device exists. This mean that the name devX exists in the gpib driver !
 */
gpibDevice::gpibDevice(string dev_name, string boardname) 
{
    int pad;    
    string ss;
    
    resetState();
    // Get Device by name.
    devID = ibfind((char *) dev_name.c_str() );
    saveState();
    device_name = dev_name;
    if ( (devID & ERR) || (dev_ibsta & ERR) )
    {
	throw gpibDeviceException( device_name, "Error occurs while connecting to GPIB ",
	                         iberrToString(), ibstaToString(), getiberr(),getibsta());
    }
  
    resetState();
    ibask(devID,0x01,&pad);	// Get PAD;
    saveState();
    if ( (devID & ERR) || (dev_ibsta & ERR) )
    {
	throw gpibDeviceException( device_name, "Error occurs while getting device Addr ",
	                         iberrToString(), ibstaToString(), getiberr(),getibsta());
    }
    devAddr = pad;

    // Save board id.
    ss = boardname.substr(4);
    gpib_board = atoi( ss.c_str() );
    
    if ((gpib_board < 0) || (gpib_board> MAX_BOARD_INDEX) )
    {
	throw gpibDeviceException( device_name, "Error occurs while getting device Addr ",
	                         "Board index is out of range.",
				  "Value must be between 0 and 7",
				  getiberr(),getibsta());
    }
};

/**
 * This is the base constructor for the gpibDevice class.
 * The parameter passed to this constructor, is the device name as 
 * defined in the gpib driver with the ibconf program.
 * VERY IMPORTANT NOTE:
 * If method doesn't throw exception this not necessarly mean that the gpib
 * device exists. This mean that the name devX exists in the gpib driver !
 * This constructor assumes your gpib device to be on board 0 !
 */
gpibDevice::gpibDevice(string dev_name) 
{
    int pad;    
    resetState();
    // Get Device by name.
    devID = ibfind((char *) dev_name.c_str() );
    saveState();
    device_name = dev_name;
    if ( (devID & ERR) || (dev_ibsta & ERR) )
    {
	throw gpibDeviceException( device_name, "Error occurs while connecting to GPIB ",
	                         iberrToString(), ibstaToString(), getiberr(),getibsta());
    }
  
    resetState();
    ibask(devID,0x01,&pad);	// Get PAD;
    saveState();
    if ( (devID & ERR) || (dev_ibsta & ERR) )
    {
	throw gpibDeviceException( device_name, "Error occurs while getting device Addr ",
	                         iberrToString(), ibstaToString(), getiberr(),getibsta());
    }
    devAddr = pad;
    gpib_board = GPIB_DEFAULT_BOARD;
};

/**
 * This is the second constructor for the gpibDevice class.
 * The parameter passed to this constructor, is the device address 
 * configured on your device hardware. 
 * Warning: using this constructor assumes that the device name defined in
 * the gpib driver is the original one. Default gpib device name are
 * composed like this:  dev + address ->  hardware at address 4 will use
 * dev4 as defaultname. If you have change this name with ibconf, you will
 * have to use the previous constructor.
 * VERY IMPORTANT NOTES:
 * If method doesn't throw exception this not necessarly mean that the gpib
 * device exists. This mean that the name devX exists in the gpib driver !
 * This constructor assumes your gpib device to be on board 0 !
 * This constructor SHOULD NOT BE USE ANYMORE since it simply concat dev to
 * the address, to build the device name (store in driver). Instead of doing
 * gpibDevice( 4 ) use gpibDevice ("dev4") or, for THE BEST SOLUTION:
 * gpibDevice( "dev4", "gpib0").
 *
 */
gpibDevice::gpibDevice(int add) 
{
    ostringstream os;
    os << add;
    int pad;        
	resetState();
    // Get Device by name + addr.
    device_name = "dev" + os.str();
    devID = ibfind( (char *) device_name.c_str() );
    saveState();
    if ( (devID & ERR) || (dev_ibsta & ERR) )
    {
	throw gpibDeviceException( device_name, "Error occurs while connecting to GPIB ",
	                         iberrToString(), ibstaToString(), getiberr(),getibsta());
    }
  
	resetState();
    ibask(devID,0x01,&pad);	// Get PAD;
    saveState();
    if ( (devID & ERR) || (dev_ibsta & ERR) )
    {
	throw gpibDeviceException( device_name, "Error occurs while getting device Addr ",
	                         iberrToString(), ibstaToString(), getiberr(),getibsta());
    }
    devAddr = pad;
    gpib_board = GPIB_DEFAULT_BOARD;
};

/**
 * ibsta register string conversion.
 * This method returns string describing ibsta register meaning.
 */
string gpibDevice::ibstaToString() 
{
    string ret;
    
   if (dev_ibsta & ERR)  ret  = "GPIB error ";
   if (dev_ibsta & TIMO) ret += "Time limit exceeded ";
   if (dev_ibsta & END)  ret += "END or EOS detected ";
   if (dev_ibsta & SRQI) ret += "SRQ Interrupt received ";
   if (dev_ibsta & RQS)  ret += "Device requesting service ";
   if (dev_ibsta & CMPL) ret += "I/O completed ";
   if (dev_ibsta & LOK)  ret += "Lockout state ";
   if (dev_ibsta & REM)  ret += "Remote state ";
   if (dev_ibsta & CIC)  ret += "Controller-In-Charge ";
   if (dev_ibsta & ATN)  ret += "Attention is asserted ";
   if (dev_ibsta & TACS) ret += "Talker ";
   if (dev_ibsta & LACS) ret += "Listener ";
   if (dev_ibsta & DTAS) ret += "Device trigger state ";
   if (dev_ibsta & DCAS) ret += "Device clear state ";
   return ret;    
}

/**
 * ibserr register string conversion.
 * This method returns error string corresponding to err register.
 */
string gpibDevice::iberrToString() {
   
    string ret;
    
    if (dev_iberr>=0 && dev_iberr<=20) 
    {   
	return error_array[dev_iberr];
    }
    return error_array[20];
}

/**
 * This method returns device's iberr register.
 */
int gpibDevice::getiberr()
{
    return dev_iberr;
}

/**
 * This method returns device's ibsta register.
 */
int gpibDevice::getibsta()
{
    return dev_ibsta;
}

/**
 * This method returns device's ibcnt register.
 */
unsigned int gpibDevice::getibcnt()
{
    return dev_ibcnt;
}    

/**
 * This method returns device's ID. This is usefull for controlling.
 * device from a gpib board. For example : Method BCclr needs this value
 * to clear a device.
 */
int gpibDevice::getDeviceID()
{
    return devID;
}

/**
 * This method returns device's name. 
 * This mean, the name passed to the constructor as string, or the name 
 * built with the constructor using address e.g. dev4
 */
string gpibDevice::getName()
{
    return device_name;
}

/**
 * This method returns device's name. 
 * This mean, the name passed to the constructor as string, or the name 
 * built with the constructor using address e.g. dev4
 */
int gpibDevice::getDeviceAddr()
{
    return devAddr;
}
/**
 * This method is for internal class use. 
 * GPIB iberr, ibsta and ibcnt are global to all devices. The gpibDevice 
 * class will call this method after all NI488 / NI488.2 function call, 
 * to save a specific device state. This method is must not be used from
 * outside the gpibDevice class.
 */
void gpibDevice::saveState()
{
#ifdef WIN32
    dev_iberr = ThreadIberr ();
    dev_ibsta = ThreadIbsta ();
    dev_ibcnt = ThreadIbcntl ();
#else
    dev_iberr = iberr;
    dev_ibsta = ibsta;
    dev_ibcnt = ibcntl;
#endif
}

/**
 * This method is for internal class use. 
 * GPIB iberr, ibsta and ibcnt are global to all devices. The gpibDevice 
 * class will call this method before all NI488 / NI488.2 function call, 
 * to reset a specific device state. This method must not be used from
 * outside the gpibDevice class.
 */
void gpibDevice::resetState()
{
    dev_iberr = 0;
    dev_ibsta = 0;
    dev_ibcnt = 0;
}

/**
 * This method test if the device is alive on the bus.
 * If returns 0: nobody there, else ok.
 */

short gpibDevice::isAlive() {

    resetState();
    ibln( gpib_board , devAddr, 0, &alive);
    saveState();
    if (dev_ibsta & ERR)
    {
	throw gpibDeviceException( device_name,"Device not answering to ibln (isAlive() method).",
	                         iberrToString(), ibstaToString(), getiberr(),getibsta() );
    } 
    return alive;
}

/**
 * This method reads a string from the encapsulated device.
 * Read a string from the encapsulated device. Return the string readed. 
 * A byte read value is store in private int 'dev_ibcnt' and is valid 
 * until another call to a NI488 function is made. It should not be accessed
 * throught get_ibcnt, because string.length() already do that.
 * Coders should use this method rather than read(int) cause its buffer
 * of RD_BUFFER_SIZE size is almost enough all time. Only use read(int) when
 * you expect return buffer > RD_BUFFER_SIZE ( but this method is slowest due to
 * dynamic buffer allocation).
 */
string gpibDevice::read()
{
    string ret;

	resetState();
    memset(rd_buffer,0, (RD_BUFFER_SIZE+1));    
    ibrd(devID,rd_buffer,RD_BUFFER_SIZE);    
    ret = rd_buffer;
    saveState();
    if (dev_ibsta & ERR)
    {
	throw gpibDeviceException( device_name,"Error occurs while reading to GPIB ",
	                         iberrToString(), ibstaToString(), getiberr(),getibsta() );
    } 
    return ret;
}

/**
 * This method send a string to the encapsulated device. 
 * Return the number of data written. 
 */
int gpibDevice::write(string m) 
{
    
	resetState();
    ibwrt(devID,(char *) m.c_str(),m.length() );  
    saveState();
    if (dev_ibsta & ERR)
    {
	throw gpibDeviceException( device_name,"Error occurs while writing to GPIB ",
	                         iberrToString(), ibstaToString(), getiberr(),getibsta() );
    } 
    return dev_ibcnt;	/* Return saved incnt value */
}


string gpibDevice::writeRead(string m)
{
    string ret;
    
	resetState();
    // Make the first Operation: Write.
    ibwrt(devID,(char *) m.c_str(),m.length() );  
    saveState();
    if (dev_ibsta & ERR)
    {
	throw gpibDeviceException( device_name,"Error occurs while writing to GPIB ",
	                         iberrToString(), ibstaToString(), getiberr(),getibsta() );
    } 

    // Make second operation: Read.
	resetState();
    memset(rd_buffer,0, (RD_BUFFER_SIZE+1));    
    ibrd(devID,rd_buffer,RD_BUFFER_SIZE);    
    ret = rd_buffer;
    saveState();
    if (dev_ibsta & ERR)
    {
	throw gpibDeviceException( device_name,"Error occurs while reading to GPIB ",
	                         iberrToString(), ibstaToString(), getiberr(),getibsta() );
    } 
    return ret;
}

/*
 * This method reads a string from the encapsulated device.
 * Read a specified size string from the device. Return the string readed. 
 * A byte read value is store in private int 'dev_ibcnt' and is valid 
 * until another call to a NI488 function is made. It should not be accessed
 * throught get_ibcnt, because string.length() already do that.
 */
string gpibDevice::read(unsigned long size)
{
    string ret;
    char *tmp_buffer;
    // TODO size+1
	resetState();
    tmp_buffer = new char[size+1];
    memset(tmp_buffer,0, (size+1));  // AJOUT  
    ibrd(devID, tmp_buffer, size);    
//TODO    ret = string(tmp_buffer);
    ret = tmp_buffer;
    delete []tmp_buffer; 
    
    saveState();
    if (dev_ibsta & ERR)
    {
	throw gpibDeviceException( device_name,"Error occurs while reading to GPIB ",
	                         iberrToString(), ibstaToString(), getiberr(),getibsta() );
    } 
    return ret;
}

/******************************************************************************************/
/*
 *	These methods perform a write or a read of binary data on the GPIB device
 *
 *
/******************************************************************************************/
void gpibDevice::sendData(const char *argin, long count)
{
	
    resetState();
    Send ( gpib_board , MakeAddr(devAddr, 0),(char *)argin, count, NLend);
    saveState();
    if (dev_ibsta & ERR)
    {
        throw gpibDeviceException( device_name, 
	    string("Error occurs while writing to GPIB binary data"), 
            iberrToString(),
	    ibstaToString(),
	    getiberr(),
	    getibsta());
    } 
}

char *gpibDevice::receiveData(unsigned short count)
{

// allocate buffer for reading data on the GPIB bus
char* buffer = new char [count];

	memset(buffer,0, count);

	if (buffer == NULL)
	{
  	    throw gpibDeviceException( device_name, 
		string("Cannot allocate memory for receiveData"),
		iberrToString(),
		ibstaToString(),
		getiberr(),
		getibsta());
	}
  
	resetState();
	
	Receive ( gpib_board, MakeAddr(devAddr, 0), buffer, count, STOPend);
	// The actual number of bytes transferred is returned in the  variable, ibcntl.
	// we use ThreadIbcntl for thread safety
	saveState();

    if (dev_ibsta & ERR)
    {
	delete [] buffer;
	throw gpibDeviceException(device_name,
	    "Error occurs while reading binary data from GPIB",
	    iberrToString(), ibstaToString(), getiberr(),getibsta() );
    } 

	//long bytes_read=ThreadIbcntl ();
	// CAUTION/TODO : If long bytes_read != count what should we do : 
	// a) throw an exception: but it may be too much to take such a decision at low level
	// b) reallocate a data buffer of the right size (long bytes_read), copy the buffer data into it, 
	// and return this buffer of the rigth size to the caller . this last opion is our prefered but 
	// for now we prefer to avoid this potential extracopy of data 
	// 
	// 

	return buffer;
}
/******************************************************************************************/

/**
 * This method clears the encapsulated device.
 * This method sends clear device signal on the GPIB bus.
 */
void gpibDevice::clear()
{
    resetState();
    ibclr(devID);  
    saveState();
    if (dev_ibsta & ERR)
    {
	throw gpibDeviceException(device_name, "Error occurs while clearing to GPIB ",
	                         iberrToString(), ibstaToString(), getiberr(),getibsta() );
    } 
}

/**
 * This method send a configuration request to the device.
 */
void gpibDevice::config(int option, int value)
{
    resetState();
    ibconfig(devID, option, value);  
    saveState();
    if (dev_ibsta & ERR)
    {
	throw gpibDeviceException(device_name, "Error occurs while clearing to GPIB ",
	                         iberrToString(), ibstaToString(), getiberr(),getibsta() );
    } 
}

/**
 * This method sends a trigger signal to the gpib device. The device was
 * previously set to wait for a trigger command. When it receivces the signal,
 * the device sends its measurement. You can get it with read Command.
 */
void gpibDevice::trigger()
{
    resetState();
    ibtrg(devID);  
    saveState();
    if (dev_ibsta & ERR)
    {
	throw gpibDeviceException(device_name, "Error occurs while triggering device ",
	                         iberrToString(), ibstaToString(), getiberr(),getibsta() );
    } 
}


/**
 * Set the device time out value. 
 * Warning: These values are predefined. With GPIB you can only choose
 * between 16 differents time out values. #defined values can be found 
 * in gpibDevice.h.
 */
void gpibDevice::setTimeOut(int v)
{
    resetState();
    if ( (v >= 0) && (v <= 15) )
    {
        ibtmo(devID,v);  
        saveState();

    } else {
    
	throw gpibDeviceException(device_name, "Error occurs while setting time out on ",
	                         "Value out of range.", " [0-15] value expected.", getiberr(),getibsta() );
    }

    // v contains correct value, does the cmd terminate correctly ?
    if ( dev_ibsta & ERR )
    {
	throw gpibDeviceException(device_name, "Error occurs while setting time out on ",
	                         iberrToString(), ibstaToString(), getiberr(),getibsta() );
    } 
}


/**
 * This method should be called to free the device.
 * This method should be called to free device after use. In special case,
 * device not freed can be invisible for other gpib applications.
 */
void gpibDevice::setOffLine() 
{
    resetState();
    ibonl(devID, 0);  
    saveState();
    if (dev_ibsta & ERR)
    {

	throw gpibDeviceException( device_name,"Error occurs with setOffline method ",
	                         iberrToString(), ibstaToString(), getiberr(),getibsta() );

    } 
}

/**
 * This method tries to put the device in local control mode.
 * Sending commands to the device automatically turns in remote mode.
 * This get the control back to the manual operator.
 * WARNING: This method can conflict with device server polling since 
 * network access to gpibDevice automatically put the device in remote
 * mode.
 */
void gpibDevice::goToLocalMode()
{
    resetState();
    ibloc(devID);		
    saveState();
    if (dev_ibsta & ERR)
    {
	
	throw gpibDeviceException( device_name,"Error occurs with ibloc() command",
	                         iberrToString(), ibstaToString(), getiberr(),getibsta() );
    } 
}

/**
 * This method tries to put the device in remote control mode.
 * (Sending commands to the device automatically turns it into remote mode.
 * This method is provided for backward compatibility.
 */
void gpibDevice::goToRemoteMode()
{
    resetState();
    ibsre( gpib_board , devID); 
    saveState();
    if (dev_ibsta & ERR)
    {
	
	throw gpibDeviceException( device_name,"Error occurs with ibsre() command",
	                         iberrToString(), ibstaToString(), getiberr(),getibsta() );
    } 
}


//+----------------------------------------------------------------------------
//
// 	Classc gpibBoard Implementation:
//
//-----------------------------------------------------------------------------

/**
 * This is the default gpibBoard constructor. It passes board_name argument
 * to the super-class gpibDevice. 
 */
gpibBoard::gpibBoard() :gpibDevice( "gpib0" )
{
    board_id = GPIB_DEFAULT_BOARD;
}

/**
 * This is a gpibBoard constructor for a specific board. It passes board_name
 *  argument to the super-class gpibDevice. 
 */
gpibBoard::gpibBoard(string boardname) :gpibDevice( boardname )
{
    string ss;
    ss = boardname.substr(4);
    board_id = atoi( ss.c_str() );
}

/**
 * This method sends an Interface Clear on the bus. 
 * All devices are cleared and the device @0 becomes Controler In Charge.
 */
void gpibBoard::sendIFC()
{
    resetState();
    
    // Note: sendIFC() != SendIFC() / gpibDevice NI.488.2 func SendIFC () 
    SendIFC( board_id );		
    saveState();
    if (dev_ibsta & ERR)
    {
	
	throw gpibDeviceException( device_name,"Error occurs with sendIFC() command",
	                         iberrToString(), ibstaToString(), getiberr(),getibsta() );
    } 
}

/**
 * Send a GPIB command message. 
 * This method is not used to transmit programming instruction to devices,
 * This kind of instructions are transmitted with the read / write methods.
 */
int gpibBoard::cmd(string cmd) 
{
    resetState();
    ibcmd( board_id ,(char *) cmd.c_str(),cmd.length() );  
    saveState();
    if (dev_ibsta & ERR)
    {
	throw gpibDeviceException(device_name, "Error occurs with cmd on GPIB ",
	                         iberrToString(), ibstaToString(), getiberr(),getibsta() );

    } 
    return dev_ibcnt;	/* Return saved incnt value */
}

/**
 * Send a Local Lockout to a specified device.
 * This method send a local lockout to a specified device, prohibiting manual
 * values / setup modifications.
 */
void gpibBoard::llo(int dev) 
{
    resetState();
    // TODO : find ibllo for WIN32
#ifdef _solaris
    ibllo( dev );  
#endif

    saveState();
    if (dev_ibsta & ERR)
    {
	throw gpibDeviceException(device_name, "Error occurs with ibllo on GPIB ",
	                         iberrToString(), ibstaToString(), getiberr(),getibsta() );
    } 
}

/**
 * Clear a specified device.
 * This method sends a clear signal on the GPIB bus for a specified device.
 */
void gpibBoard::clr(int dev) 
{
    resetState();
    ibclr( dev );  
    saveState();
    if (dev_ibsta & ERR)
    {
	throw gpibDeviceException(device_name, "Error occurs with ibclr on GPIB ",
	                         iberrToString(), ibstaToString(), getiberr(),getibsta() );

    } 
}

/**
 * Get a list of devices connected on the bus.
 * This method returns a reference on vector of gpibDeviceInfo, containing 
 * information on all gpibDevice found on the gpib bus. The referenced variable
 * is  just below. Provided info are device *IDN string, primary address,
 * secondary address. See gpibDeviceInfo for more information on these fields.
 * Board must be CIC to perform FindLstn !
 */
vector<gpibDeviceInfo>& gpibBoard::getConnectedDeviceList()
{
    char idn_buffer[MAX_DEV_IDN_STR];
    int loop, nb_listener;
    Addr4882_t scanlist[MAX_DEV_ON_BOARD+1]; // +1 for terminal NOADDR
    Addr4882_t result[MAX_DEV_ON_BOARD];
    
    
    inf.clear(); // Empty vector first.
    // Build address list to scan, add NOADDR list terminator 
    for (loop = 0; loop < MAX_DEV_ON_BOARD; loop++)
        scanlist[loop] = loop;
    scanlist[MAX_DEV_ON_BOARD] = NOADDR;
    
    resetState();
    
    FindLstn(board_id, scanlist, result, MAX_DEV_ON_BOARD);
    saveState();
    
    if (dev_ibsta & ERR)
    {
	throw gpibDeviceException(device_name, "Error occurs with FindLstn on GPIB ",
	                         iberrToString(), ibstaToString(), getiberr(),getibsta() );

    } 

    nb_listener = dev_ibcnt -1;//-1; MODIF
    // Start from 1 to avoid gpib board 0 who does not answer to "*IDN?"
    for (loop = 1; loop <= nb_listener; loop++ )    
    {
        gpibDeviceInfo *t = new gpibDeviceInfo();
	
	t->dev_pad = GetPAD( result[loop] );
	t->dev_sad = GetSAD( result[loop] );
	t->dev_idn = "Device does not support *IDN? command.\n";

	resetState();
	Send(board_id, result[loop],(char *)"*IDN?", 5L, NLend);
	saveState();
	if (! (dev_ibsta & ERR) )
	{
	    memset(idn_buffer,0, MAX_DEV_IDN_STR);
	    Receive(board_id, result[loop], idn_buffer, MAX_DEV_IDN_STR, STOPend);
	    
	    // Most of gpib device understand '*IDN?' command, and return a string
	    // of identification. Some old device does implement this command, like
	    // Tektronik 2440 who implements his own ID command: 'ID?'. On *IDN?
	    // cmd the 2440 return char 255, as bad command.
	    // Thats why if a device return an ID string < 5 byte, or finish in 
	    //Time Out error, we admit that it does not implement command.
	    if ( (!(dev_ibsta & ERR)) && (ibcnt > 5) ) // Ibcnt = nb of byte received.
	    {
	        t->dev_idn = idn_buffer;
	    } 
	} 
	inf.push_back( *t );
    }
    return inf;
}
 
