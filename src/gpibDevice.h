#ifndef _GPIBDEVICE_H
#define _GPIBDEVICE_H

#include <string>
#include <vector>
#include "gpibDeviceException.h"

/**
 * Device's default size buffer for read operations.
 */
#define RD_BUFFER_SIZE 		512

/**
 * Drivers are by default limited to 8 gpibBoard per driver.
 */
#define MAX_BOARD_INDEX		7

/**
 * Maximum number of device on the GPIB bus. 
 * This is used to limit bus scan with getConnectedDeviceList method.
 */
#define MAX_DEV_ON_BOARD	16

/**
 * Maximum size of string received, when identifying devices connected on
 * the bus.( string return by device in answer to "*IDN?"
 */
#define MAX_DEV_IDN_STR		128

/**
 * Device's default gpib board.
 */
#define GPIB_DEFAULT_BOARD	  0

/**
 * Nb of configuration options (each one can be set with ibconfig
 * or obatined with ibask)
 */
#define GPIB_NB_CONF_OPT          34



using namespace std;

enum GpibProbeMethod
{
	GPIB_PROBE_UNKNOWN = 0,
	GPIB_PROBE_DEVICE = 1,
	GPIB_PROBE_BOARD = 2
};


/** 
 * This class is designed to handle gpibDevices. It's point of
 * view is very device oriented: For example, setting device in remote mode, 
 * is done with 'goToRemoteMode' device's method. It totaly hides the fact 
 * that this is done by sending a command to gpib board. Due to ESRF gpib 
 * bus usage, this class is designed to work on a single CIC (Controler In 
 * Charge) bus. In simple words this class can't handle multi board buses. 
 * The default CIC selected is "gpib0".
 *
 * The usual way to include gpib feature into a Tango device server consists in
 * single or multiple instance of a gpibDevice / gpibBoard.
 * One simply uses read / write functions to handle devices. Note that All 
 * operations made on gpibDevice or gpibBoard can potentialy throw a 
 * gpibDeviceException.<link ref ="code example" href "code-example.txt"> 
 */
class gpibDevice 
{

public:

        gpibDevice(string dev_name ,string boardname);  // class constructor.
        gpibDevice(string dev_name);                    // class constructor.
        gpibDevice(int primary_add, string boardname);  // class constructor.
        gpibDevice(int primary_add);                    // class constructor.

	string ibstaToString(void);	// Get string from ibsta string.	
	string iberrToString(void);	// Get string from iberr string. 	
	int getiberr(void);		// Get device iberr value.		
	int getibsta(void);		// Get device ibsta value.		
	int getDeviceID(void);		// Get internal device ID.
	int getDeviceAddr(void);	// Get device gpib address;
	unsigned int getibcnt(void);	// Get device ibsta value.		
	void clear(void);		// Clear the gpib device.		
        void config(int opt,int v);	// Send a ibconfig request. (= set config)
        short getconfig(short opt);     // Send a ibask request     (= get config)
	void trigger(void);		// Trigger the device.		
        short getSerialPoll(void);      // Get serial-poll byte from device.
	int write(string);		// Send a string to a gpib device. 	
	string read(void);		// Read a string from a gpib device. 	
	string writeRead(string);	// Perform a write/read operation in a row.
	string read(unsigned long s);	// Read a string from a gpib device. 	
        void setOffLine(void);		// Free / rest, set offline gpibDevice 
                                        // taken with ibdev.
	string getName(void);		// Return device name. Provided by constructor.
        void goToLocalMode(void);	// Device goes to local mode(opp to remote mode).
	void setTimeOut(int tmo);	// Set Device Time out.
        void goToRemoteMode(void);	// Device goes to remote mode(opp to local mode).   
        short isAlive(void);		// Check the presence of the device on the bus.
	char* receiveData(long count);	// Read binary data from a GPIB device
	void sendData(const char *, long count); // Write binary data on a GPIB device
	
protected:

	void saveState(void);		// save iberr/ibstat in dev_ibsta/dev_iberr. 
	void resetState(void);		// reset iberr/ibstat in dev_ibsta/dev_iberr.

	/**
	 * Internal gpib handler.
	 */
	int devID;		

	/**
	 * gpib PAD return by driver at ibask(devID,IbaPAD,...).
	 */
	int devAddr;		

	/**
	 * Internal gpib ibsta copy.
	 */
	int dev_ibsta;			

	/**
	 * Internal gpib iberr copy.
	 */
	int dev_iberr;			

	/**
	 * Internal gpib ibcnt copy.
	 */
	unsigned int dev_ibcnt;			

	/**
	 * Internal read operation buffer.
	 */
	char rd_buffer[RD_BUFFER_SIZE+1];	 

	/**
	 * gpib device name passed in constructor, or built on address e.g dev4
	 */
	string device_name;		 

	/**
	 * Status Byte value, polled by ReadStatusByte funct.
	 */
	short alive;
	 
private:

	 void findIsAliveMethod(void);
	/**
	 * This is the gpib board, where our device is connected to.
	 */
        int             gpib_board;	
	GpibProbeMethod	probe_method; 
};

/**
 * This class is a container for Device Info.
 * No methods are implemented, it only feature public fields. This class
 * is mainly used with getConnectedDeviceList method.
 */
class gpibDeviceInfo {

    public:
        /**
	 * This string contains device's answer to "*IDN?"
	 */
        string 	dev_idn;		

        /**
	 * This int contains device's Primary ADdress.
	 */
	int	dev_pad;		

        /**
	 * This int contains device's Secondary ADdress.
	 */
	int 	dev_sad;		
};


/**
 * Static vector of gpibDeviceInfo.
 * This var is declared here to allow getConnectedDeviceList method to
 * return reference on object. User can avoid his own vector<gpibDeviceInfo>
 * declaration.
 */
static vector<gpibDeviceInfo> inf;


/** 
 * This class is designed to handle gpibBoards. gpidBoard can be
 * seen as gpibDevice with more feature that's why this class inherits from
 * gpibDevice and adds methods to handle board features. 
 */
class gpibBoard : public gpibDevice 
{

public:

	gpibBoard(void);		// Class default constructor for gpib0.
	gpibBoard(string board);	// Constructor for specified board.
	~gpibBoard(void);		// Classs destructor.

	vector<gpibDeviceInfo>& getConnectedDeviceList();
	// NI-488.2 methods call.
	void sendIFC(void);		// Send GPIB Interface Clear 	(Board command).

        // NI-488 methods call.
	void llo(int dev);		// Send Local Lockout to a dev. (Board command).
	int cmd(string);		// Send GPIB command message 	(Board command).
	void clr(int dev);		// Clear specified device.	(Board command).
        int  getBoardInd(void);         // Get Board Index (0,1,2,...)
	
private:

	int board_id;		        // Board number.
};

#endif
