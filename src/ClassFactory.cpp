static const char *RcsId = "$Header: /users/chaize/newsvn/cvsroot/Communication/Gpib/src/ClassFactory.cpp,v 1.3 2005-03-15 11:03:32 xavela Exp $";
//+=============================================================================
//
// file :        ClassFactory.cpp
//
// description : C++ source for the class_factory method of the DServer
//               device class. This method is responsible to create
//               all class singletin for a device server. It is called
//               at device server startup
//
// project :     TANGO Device Server
//
// $Author: xavela $
//
// $Revision: 1.3 $
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
#include <GpibDeviceServerClass.h>

/**
 *	Create GpibDeviceServerClass singleton and store it in DServer object.
 *
 * @author	$Author: xavela $
 * @version	$Revision: 1.3 $ $
 */

void Tango::DServer::class_factory()
{

	add_class(GpibDeviceServer::GpibDeviceServerClass::init("GpibDeviceServer"));

}
