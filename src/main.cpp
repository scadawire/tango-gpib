static const char *RcsId = "$Header: /users/chaize/newsvn/cvsroot/Communication/Gpib/src/main.cpp,v 1.3 2005-03-15 11:03:33 xavela Exp $";
//+=============================================================================
//
// file :        main.cpp
//
// description : C++ source for a TANGO device server main.
//               The main rule is to initialise (and create) the Tango
//               system and to create the DServerClass singleton.
//               The main should be the same for every Tango device server.
//
// project :     TANGO Device Server
//
// $Author: xavela $
//
// $Revision: 1.3 $ $
//
// $Log: not supported by cvs2svn $
// Revision 1.6  2005/03/15 10:40:04  elattaoui
// xavier.el : final version updated. Official version, to avoid local copies.
//
// Revision 1.5  2005/02/22 11:00:52  elattaoui
// xavier : makefile.vc changed.
//
// Revision 1.4  2004/06/30 08:57:58  elattaoui
// xavier : ajout de #ifdef linux
// changement de #define MAX_... par const int !
//
// Revision 1.3  2004/06/29 10:16:09  elattaoui
// xavier : ajout du .obj dans le repertoire lib
//
// Revision 1.2  2004/06/29 10:05:59  elattaoui
// xavier : verion finale du DServer
// partage des commandes en mode Operator et
// Expert
// ajout d'un CTOR par address avec la fonction ibdev
//
// Revision 1.1.1.1  2004/02/11 09:06:06  root
// initial import
//
// Revision 1.1.1.1  2003/10/08 09:30:46  verdier
// Imported using TkCVS
//
//
// copyleft :    European Synchrotron Radiation Facility
//               BP 220, Grenoble 38043
//               FRANCE
//
//-=============================================================================
//
//  		This file is generated by POGO
//	(Program Obviously used to Generate tango Object)
//
//         (c) - Software Engineering Group - ESRF
//=============================================================================

#include <tango.h>


int main(int argc,char *argv[])
{

	Tango::Util *tg;
	try
	{
		// Initialise the device server
		//----------------------------------------
		tg = Tango::Util::init(argc,argv);

		// Create the device server singleton 
		//	which will create everything
		//----------------------------------------
		tg->server_init(false);

		// Run the endless loop
		//----------------------------------------
		cout << "Ready to accept request" << endl;
		tg->server_run();
	}
	catch (bad_alloc)
	{
		cout << "Can't allocate memory to store device object !!!" << endl;
		cout << "Exiting" << endl;
	}
	catch (CORBA::Exception &e)
	{
		Tango::Except::print_exception(e);
		
		cout << "Received a CORBA_Exception" << endl;
		cout << "Exiting" << endl;
	}
	return(0);
}
