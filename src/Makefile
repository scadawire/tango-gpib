#=============================================================================
#
# file :        Makefile
#
# description : gpib test program
#
# project :     Makefile to generate a gpib test program
#
# $Author: Vedder Bruno.
#
# $Revision: 1.3 $
#
# $Log: not supported by cvs2svn $
# Revision 1.6  2005/03/15 10:40:04  elattaoui
# xavier.el : final version updated. Official version, to avoid local copies.
#
# Revision 1.5  2005/02/22 11:00:52  elattaoui
# xavier : makefile.vc changed.
#
# Revision 1.4  2004/06/30 08:57:58  elattaoui
# xavier : ajout de #ifdef linux
# changement de #define MAX_... par const int !
#
# Revision 1.3  2004/06/29 10:16:09  elattaoui
# xavier : ajout du .obj dans le repertoire lib
#
# Revision 1.2  2004/06/29 10:05:59  elattaoui
# xavier : verion finale du DServer
# partage des commandes en mode Operator et
# Expert
# ajout d'un CTOR par address avec la fonction ibdev
#
# Revision 1.1.1.1  2004/02/11 09:06:06  root
# initial import
#
# Revision 1.1.1.1  2003/11/19 10:12:12  vedder
# Imported using TkCVS
#
#
# copyleft :    European Synchrotron Radiation Facility
#               BP 220, Grenoble 38043
#               FRANCE
#
#=============================================================================
#

#
# The -instances=static is needed to avoid unresolved symbols (error 5) during
# link.
#
ifdef _solaris
AR = ar -rv 
CC = CC -instances=static
GEN_DOC = 	doxygen
BIN_DIR = 	solaris7_CC
LIB_DIR = 	-L/usr/lib 
INC_DIR = 	-I/usr/include/
TST_CFLAGS  = 	-mt -g -lgpibDevice 
TST_LFLAGS  = 	-Bdynamic
NO_LIB_CFLAGS= 	-mt -g -lgpib -DCPLUSPLUS -D_solaris
LIB_CFLAGS  = 	-mt -g -G -lgpib -DCPLUSPLUS -D_solaris
LIB_LFLAGS  = 	-Bdynamic
endif

# Test program dynamicaly linked to libgpibDevice.so
TST_NAME = 		gpibtst

# shared library libgpibDevice.so
SHARED_LIB_NAME = 	libgpibDevice.so

# library libgpibDevice.a
LIB_NAME = 		libgpibDevice.a

# Test program without libgpibDevice.so nor libgpibDevice.a
NO_LIB_NAME = 		gpibtst_nolib


TSTSRC = 		gpibtst.cpp 

LIBSRC = 		gpibDevice.cpp \
			gpibDeviceException.cpp 

LIB_OBJ =		gpibDevice.o \
			gpibDeviceException.o

NO_LIB =		gpibtst.cpp \
	  		gpibDevice.cpp \
	 		gpibDeviceException.cpp 


all: clean slib lib gpibtst gpibtst_nolib

gpibtst:
	
	@echo "\n(*) Building gpib test program using shared library."	
	@echo "----------------------------------------------------"	
	$(CC) $(TST_CFLAGS) $(INC_DIR) $(TST_LFLAGS) $(LIB_DIR) -L./  $(TSTSRC) -o $(TST_NAME)

slib:
	@echo "\n(*) Building gpibDevice shared library."
	@echo "---------------------------------------"	
	$(CC) $(LIB_CFLAGS) $(INC_DIR) $(LIB_LFLAGS) $(LIB_DIR) $(LIBSRC) -o $(SHARED_LIB_NAME)

lib:
	@echo "\n(*) Building gpibDevice library."
	@echo "-------------------------------"	
	$(AR) $(LIB_NAME) $(LIB_OBJ)
	
gpibtst_nolib:
	@echo "\n(*) Building gpib test program without shared library."
	@echo "------------------------------------------------------"	
	$(CC) $(NO_LIB_CFLAGS) $(INC_DIR) $(TST_LFLAGS) $(LIB_DIR) $(NO_LIB) -o $(NO_LIB_NAME)
	
clean:
	@echo "\n(*) Cleaning directory."	
	@echo "-----------------------"	
	rm -f *.o core $(TST_NAME) $(SHARED_LIB_NAME) $(NO_LIB_NAME) $(LIB_NAME)
doc:
	$(GEN_DOC)
