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

using namespace std;

/** 
 * This class is designed to handle gpibDevices. It's point of
 * view is very device oriented: For example, setting device in remote mode, is
 * done with 'goToRemoteMode' device's method. It totaly hides the fact that this
 * is done by sending a command to gpib board. Due to ESRF gpib bus usage, this
 * class is designed to work on a single CIC (Controler In Charge) bus. In simple
 * word this class can't handle multi board buses. The default CIC selected is
 * "gpib0".
 *
 * The usual way to include gpib feature into a Tango device server consists in
 * single or multiple instance of a gpibDevice / gpibBoard.
 * Once simply use read / write functions to handle devices. Note that All 
 * operations made on gpibDevice or gpibBoard can potentialy throw a 
 * gpibDeviceException.<link ref ="code example" href "code-example.txt"> 
 */
class gpibDevice {

    public:

	gpibDevice(string,string);	// class constructor.
	gpibDevice(string Name);	// class constructor.
        gpibDevice(int add);		// class constructor.
		
	string ibstaToString();		// Get string from ibsta string.	
	string iberrToString();		// Get string from iberr string. 	
	int getiberr();			// Get device iberr value.		
	int getibsta();			// Get device ibsta value.		
	int getDeviceID();		// Get internal device ID.
	int getDeviceAddr();		// Get device gpib address;
	unsigned int getibcnt();	// Get device ibsta value.		
	void clear();				// Clear the gpib device.		
        void config(int opt,int v);	// Send a ibconfig request.
	void trigger();			// Trigger the device.		
	void lock();			// Lock Gpib Bus.
	void unlock();			// Unlock Gpib Bus.
	int write(string);		// Send a string to a gpib device. 	
	string read();			// Read a string from a gpib device. 	
	string writeRead(string);	// Perform a write/read operation in a row.
	string read(unsigned long s);	// Read a string from a gpib device. 	
        void setOffLine();		// Free / rest, set offline gpibDevice taken with ibdev.
	string getName();		// Return device name. Provided by constructor.
        void goToLocalMode();		// Device goes to locale mode (opp to remote mode).
	void setTimeOut(int tmo);	// Set Device Time out.
        void goToRemoteMode();		// Device goes to remote mode (opp to local mode).   
        short isAlive();		// Check the presence of the device on the bus.
	char*	receiveData(unsigned short count);	// Read binary data from a GPIB device
	void	sendData(const char *, long count);	// Write binary data on a GPIB device
	
    protected:

	void saveState();		// save iberr/ibstat in dev_ibsta/dev_iberr. 
	void resetState();		// reset iberr/ibstat in dev_ibsta/dev_iberr.

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
	char rd_buffer[RD_BUFFER_SIZE];	 

	/**
	 * gpib device name passed in constructor, or built on address e.g dev4
	 */
	string device_name;		 

	/**
	 * Status Byte value, polled by ReadStatusByte funct.
	 */
	short alive;
	 
    private:

	/**
	 * This is the gpib board, where our device is connected to.
	 */
        int gpib_board;	
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
class gpibBoard : public gpibDevice {

    public:

	gpibBoard();			// Class default constructor for gpib0.
	gpibBoard(string board);	// Constructor for specified board.
	~gpibBoard();			// Classs destructor.


	vector<gpibDeviceInfo>& getConnectedDeviceList();
	// NI-488.2 methods call.
	void sendIFC();			// Send GPIB Interface Clear 	(Board command).

        // NI-488 methods call.
	void llo(int dev);		// Send Local Lockout to a dev. (Board command).
	int cmd(string);		// Send GPIB command message 	(Board command).
	void clr(int dev);		// Clear specified device.	(Board command).
	
    private:

	int board_id;		// Board number.
};

#endif
