/*
 * User GPIB Include File
 * National Instruments GPIB-ENET                         
 *       
 * Copyright (c) 2001 National Instruments Corp.           
 * All rights reserved.                                  
 */
#ifndef UGPIB_INCLUDED
#define UGPIB_INCLUDED

#include <sys/param.h>
#include <sys/types.h>

#ifdef NI4882
#define	ibfind ibfindA
#endif

extern	int	ibsta;
extern  int	iberr;
extern	unsigned int	ibcnt;
extern	long	ibcntl;


/* GPIB commands */
#define UNL  0x3f  /* GPIB unlisten command                */
#define UNT  0x5f  /* GPIB untalk command                  */
#define GTL  0x01  /* GPIB go to local                     */
#define SDC  0x04  /* GPIB selected device clear           */
#define PPC  0x05  /* GPIB parallel poll configure         */
#define GET  0x08  /* GPIB group execute trigger           */
#define TCT  0x09  /* GPIB take control                    */
#define LLO  0x11  /* GPIB local lock out                  */
#define DCL  0x14  /* GPIB device clear                    */
#define PPU  0x15  /* GPIB parallel poll unconfigure       */
#define SPE  0x18  /* GPIB serial poll enable              */
#define SPD  0x19  /* GPIB serial poll disable             */
#define PPE  0x60  /* GPIB parallel poll enable            */
#define PPD  0x70  /* GPIB parallel poll disable           */

/* GPIB status bit vector */
#define ERR     (1<<15) /* Error detected */
#define TIMO    (1<<14) /* timeout */
#define END     (1<<13) /* EOI or eos detected */
#define SRQI    (1<<12) /* SRQ detected by CIC */
#define RQS     (1<<11) /* Device requires service */
#define CMPL    (1<<8)  /* DMA completed (SH/AH synch'd) */
#define LOK     (1<<7)  /* local lockout state */
#define REM     (1<<6)  /* remote state */
#define CIC     (1<<5)  /* controller-in-charge */
#define ATN     (1<<4)  /* attention asserted */
#define TACS    (1<<3)  /* talker active */
#define LACS    (1<<2)  /* listener active */
#define DTAS    (1<<1)  /* device trigger state */
#define DCAS    (1<<0)  /* device clear state */

/* GPIB Bus Control Lines bit vector */
#define BUS_DAV         0x100           /* DAV line status bit  */
#define BUS_NDAC        0x200           /* NDAC line status bit */
#define BUS_NRFD        0x400           /* NRFD line status bit */
#define BUS_IFC         0x800           /* IFC line status bit  */
#define BUS_REN         0x1000          /* REN line status bit  */
#define BUS_SRQ         0x2000          /* SRQ line status bit  */
#define BUS_ATN         0x4000          /* ATN line status bits */
#define BUS_EOI         0x8000          /* EOI line status bits */

/* Error messages in ibsta */
#define EDVR  0  /* System error */
#define ECIC  1  /* Not CIC (or lost CIC during command) */
#define ENOL  2  /* write detected no listeners */
#define EADR  3  /* board not addressed correctly */
#define EARG  4  /* bad argument to function call */
#define ESAC  5  /* function requires board to be SAC */
#define EABO  6  /* asynchronous operation was aborted */
#define ENEB  7  /* non-existent board */
#define EDMA  8  /* DMA hardware error detected */
#define EBTO  9  /* DMA hardware uP bus timeout */
#define EOIP 10  /* new I/O attempted with old I/O in progress  */
#define ECAP 11  /* no capability for intended opeation         */
#define EFSO 12  /* file system operation error                 */
#define EOWN 13  /* shareable board exclusively owned */
#define EBUS 14  /* bus error */
#define ESTB 15  /* serial poll queue overflow */
#define ESRQ 16  /* SRQ line 'stuck' on */
#define ETAB 20  /* The return buffer is full */
#define ELCK 21  /* LOCK error (trying to access a locked brd/dev */

/* EOS flags */
#define  REOS   0x0400  /* terminate read on eos */
#define  XEOS   0x0800  /* assert EOI with eos byte */
#define  BIN    0x1000  /* eight-bit compare */

/* Timeout values and meanings                          */
#define TNONE    0   /* Infinite timeout (disabled)     */
#define T10us    1   /* Timeout of 10 us (ideal)        */
#define T30us    2   /* Timeout of 30 us (ideal)        */
#define T100us   3   /* Timeout of 100 us (ideal)       */
#define T300us   4   /* Timeout of 300 us (ideal)       */
#define T1ms     5   /* Timeout of 1 ms (ideal)         */
#define T3ms     6   /* Timeout of 3 ms (ideal)         */
#define T10ms    7   /* Timeout of 10 ms (ideal)        */
#define T30ms    8   /* Timeout of 30 ms (ideal)        */
#define T100ms   9   /* Timeout of 100 ms (ideal)       */
#define T300ms  10   /* Timeout of 300 ms (ideal)       */
#define T1s     11   /* Timeout of 1 s (ideal)          */
#define T3s     12   /* Timeout of 3 s (ideal)          */
#define T10s    13   /* Timeout of 10 s (ideal)         */
#define T30s    14   /* Timeout of 30 s (ideal)         */
#define T100s   15   /* Timeout of 100 s (ideal)        */
#define T300s   16   /* Timeout of 300 s (ideal)        */
#define T1000s  17   /* Timeout of 1000 s (maximum)     */

/* Secondary address constant used by IBLN() */
#define NO_SAD         (0)        /* No secondary address */
#define ALL_SAD     (0xFFFFFFFF)        /* send all secondary addresses */

/*  The following constants are used for the second parameter of the 
 *  ibconfig function.  They are the "option" selection codes.
 */
#define  IbcPAD        0x0001      /* Primary Address                      */
#define  IbcSAD        0x0002      /* Secondary Address                    */
#define  IbcTMO        0x0003      /* Timeout Value                        */
#define  IbcEOT        0x0004      /* Send EOI with last data byte?        */
#define  IbcPPC        0x0005      /* Parallel Poll Configure              */
#define  IbcREADDR     0x0006      /* Repeat Addressing                    */
#define  IbcAUTOPOLL   0x0007      /* Disable Auto Serial Polling          */
#define  IbcCICPROT    0x0008      /* Use the CIC Protocol?                */
#define  IbcIRQ        0x0009      /* Use PIO for I/O                      */
#define  IbcSC         0x000A      /* Board is System Controller?          */
#define  IbcSRE        0x000B      /* Assert SRE on device calls?          */
#define  IbcEOSrd      0x000C      /* Terminate reads on EOS               */
#define  IbcEOSwrt     0x000D      /* Send EOI with EOS character          */
#define  IbcEOScmp     0x000E      /* Use 7 or 8-bit EOS compare           */
#define  IbcEOSchar    0x000F      /* The EOS character.                   */
#define  IbcPP2        0x0010      /* Use Parallel Poll Mode 2.            */
#define  IbcTIMING     0x0011      /* NORMAL, HIGH, or VERY_HIGH timing.   */
#define  IbcDMA        0x0012      /* Use DMA for I/O                      */
#define  IbcReadAdjust 0x0013      /* Swap bytes during an ibrd.           */
#define  IbcWriteAdjust 0x014      /* Swap bytes during an ibwrt.          */
#define  IbcEventQueue 0x0015      /* Enable/disable the event queue.         */
#define  IbcSPollBit   0x0016      /* Enable/disable the visibility of SPOLL. */
#define  IbcSendLLO    0x0017      /* Enable/disable the sending of LLO.      */
#define  IbcSPollTime  0x0018      /* Set the timeout value for serial polls. */
#define  IbcPPollTime  0x0019      /* Set the parallel poll length period.    */
#define  IbcEndBitIsNormal  0x001A /* Remove EOS from END bit of IBSTA.       */
#define  IbcUnAddr          0x001B /* Enable/disable device unaddressing.     */
#define  IbcSignalNumber    0x001C /* Set UNIX signal number - unsupported */
#define  IbcHSCableLength   0x001F /* Enable/disable high-speed handshaking.  */
#define  IbcIst             0x0020 /* Set the IST bit.                     */
#define  IbcRsv             0x0021 /* Set the RSV byte.                    */
#define  IbcLON             0x0022 /* Enable listen only mode.                */

/*
 *    Constants that can be used (in addition to the ibconfig constants)
 *    when calling the ibask() function.
 */
#define  IbaPAD            IbcPAD            
#define  IbaSAD            IbcSAD            
#define  IbaTMO            IbcTMO            
#define  IbaEOT            IbcEOT            
#define  IbaPPC            IbcPPC            
#define  IbaREADDR         IbcREADDR         
#define  IbaAUTOPOLL       IbcAUTOPOLL       
#define  IbaCICPROT        IbcCICPROT        
#define  IbaIRQ            IbcIRQ            
#define  IbaSC             IbcSC             
#define  IbaSRE            IbcSRE            
#define  IbaEOSrd          IbcEOSrd          
#define  IbaEOSwrt         IbcEOSwrt         
#define  IbaEOScmp         IbcEOScmp         
#define  IbaEOSchar        IbcEOSchar        
#define  IbaPP2            IbcPP2            
#define  IbaTIMING         IbcTIMING         
#define  IbaDMA            IbcDMA            
#define  IbaReadAdjust     IbcReadAdjust     
#define  IbaWriteAdjust    IbcWriteAdjust    
#define  IbaEventQueue     IbcEventQueue     
#define  IbaSPollBit       IbcSPollBit       
#define  IbaSendLLO        IbcSendLLO        
#define  IbaSPollTime      IbcSPollTime      
#define  IbaPPollTime      IbcPPollTime      
#define  IbaEndBitIsNormal IbcEndBitIsNormal
#define  IbaUnAddr         IbcUnAddr         
#define  IbaSignalNumber   IbcSignalNumber
#define  IbaHSCableLength  IbcHSCableLength
#define  IbaLON            IbcLON
#define  IbaIst            IbcIst
#define  IbaRsv            IbcRsv   
#define  IbaBNA            0x0200   /* A device's access board.                  */
#define  IbaBaseAddr       0x0201   /* A GPIB board's base I/O address.          */
#define  IbaDmaChannel     0x0202   /* A GPIB board's DMA channel.               */
#define  IbaIrqLevel       0x0203   /* A GPIB board's IRQ level.                 */
#define  IbaBaud           0x0204   /* Baud rate used to communicate to CT box.  */
#define  IbaParity         0x0205   /* Parity setting for CT box.                */
#define  IbaStopBits       0x0206   /* Stop bits used for communicating to CT.   */
#define  IbaDataBits       0x0207   /* Data bits used for communicating to CT.   */
#define  IbaComPort        0x0208   /* System COM port used for CT box.          */
#define  IbaComIrqLevel    0x0209   /* System COM port's interrupt level.        */
#define  IbaComPortBase    0x020A   /* System COM port's base I/O address.       */
#define  IbaSingleCycleDma 0x020B   /* Does the board use single cycle DMA?      */
#define  IbaSocketNumber   0x020C   /* Board's socket number.                    */
#define  IbaLPTNumber      0x020D   /* Parallel port number */
#define  IbaLPTType        0x020E   /* Parallel port protocol */

/*
 *  The following values are used by the iblines function.  The unsigned
 *  integer returned by iblines contains:
 *       The lower byte will contain a "monitor" bit mask.  If a bit is
 *          set (1) in this mask, then the corresponding line can be
 *          monitiored by the driver.  If the bit is clear (0),
 *          then the line cannot be monitored.
 *       The upper byte will contain the status of the bus lines.
 *          Each bit corresponds to a certain bus line, and has
 *          a corresponding "monitor" bit in the lower byte.
 *
 */
#define  ValidEOI   (unsigned short)0x0080
#define  ValidATN   (unsigned short)0x0040
#define  ValidSRQ   (unsigned short)0x0020
#define  ValidREN   (unsigned short)0x0010
#define  ValidIFC   (unsigned short)0x0008
#define  ValidNRFD  (unsigned short)0x0004
#define  ValidNDAC  (unsigned short)0x0002
#define  ValidDAV   (unsigned short)0x0001
#define  BusEOI     (unsigned short)0x8000
#define  BusATN     (unsigned short)0x4000
#define  BusSRQ     (unsigned short)0x2000
#define  BusREN     (unsigned short)0x1000
#define  BusIFC     (unsigned short)0x0800
#define  BusNRFD    (unsigned short)0x0400
#define  BusNDAC    (unsigned short)0x0200
#define  BusDAV     (unsigned short)0x0100

/* Miscellaneous                                           */
#define S    0x08    /* parallel poll sense bit            */
#define LF   0x0A    /* ASCII linefeed character           */

/*
 *  This macro can be used to easily create an entry in address list
 *  that is required by many of the 488.2 functions.  An address list is
 *  just an array of unsigned integers.  The primary address goes in the
 *  lower 8-bits and the secondary address goes in the upper 8-bits.
 */
typedef unsigned short Addr4882_t;

#define MakeAddr(pad, sad) ((Addr4882_t)((0xff&(pad))|((0xff&(sad))<<8)))

/*
 *  The following two macros are used to "break apart" an address list
 *  entry.  They take an unsigned integer and return either the primary
 *  or secondary address stored in the integer.
 */
#define  GetPAD(val)    ((unsigned char)(val))
#define  GetSAD(val)    ((unsigned char)((val) >> 8))


/*
 *  This value is used to terminate an address list.  It should be
 *  assigned to the last entry.
 */
#define  NOADDR    ((Addr4882_t)(0xFFFF))


/* These are the values that are used by the Send 488.2 command. */
#define  NULLend (unsigned short)0x00 /* Do nothing at the end of a transfer.*/
#define  NLend   (unsigned short)0x01 /* Send NL with EOI after a transfer.  */
#define  DABend  (unsigned short)0x02 /* Send EOI with the last DAB.         */


/* This value is used by the 488.2 Receive command.
 */
#define  STOPend     (unsigned short)0x0100


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
#ifdef __STDC__
extern int ibbna(int handle, char *bdname);
extern int ibcac(int handle, int v);
extern int ibclr(int handle);
extern int iblock(int handle);
extern int ibunlock(int handle);
extern int ibcmd(int handle, char *buffer, int cnt);
extern int ibcmda(int handle, char *buffer, int cnt);
extern int ibdev(int boardid, int padval, int sadval, int tmoval, int eotval, int eosval);
extern int ibdma(int handle, int v);
extern int ibeos(int handle, int v);
extern int ibeot(int handle, int v);
#ifdef NI4882
extern int ibfindA(char *bdname);
#else
extern int ibfind(char *bdname);
#endif
extern int ibgts(int handle, int v);
extern int ibist(int handle, int v);
extern int iblines(int handle, short *lines);
extern int ibln(int handle, int padval, int sadval, short *listenflag);
extern int ibloc(int handle);
extern int ibllo(int handle);
extern int ibonl(int handle, int v);
extern int ibpad(int handle, int v);
extern int ibpct(int handle);
extern int ibppc(int handle, int v);
extern int ibrd(int handle, char *buffer, int cnt);
extern int ibrda(int handle, char *buffer, int cnt);
extern int ibrdkey(int handle, char *buffer, int cnt);
extern int ibdiag(int handle, char *buffer, int cnt);
extern int ibrdf(int handle, char *flname);
extern int ibrpp(int handle, char *ppr);
extern int ibrsc(int handle, int v);
extern int ibrsp(int handle, char *spr);
extern int ibrsv(int handle, int v);
extern int ibsad(int handle, int v);
extern int ibsgnl(int handle, int v);
extern int ibsic(int handle);
extern int ibsre(int handle, int v);
extern int ibtmo(int handle, int v);
extern int ibtrg(int handle);
extern int ibwait(int handle, int mask);
extern int ibwrt(int handle, char *buffer, int cnt);
extern int ibwrta(int handle, char *buffer, int cnt);
extern int ibwrtkey(int handle, char *buffer, int cnt);
extern int ibwrtf(int handle, char *flname);
extern int ibpoke(int handle, int value);
extern int ibconfig(int handle, int code, int val);
extern int ibask(int handle, int code, int *val);

extern void SendCmds(int boardid, char *buf, int cnt);
extern void SendSetup(int boardid, Addr4882_t listen[]);
extern void SendDataBytes(int boardid, char *buffer, int cnt, int eot_mode);
extern void Send(int boardid, Addr4882_t listener, char *databuf, int datacnt, int eotmode);
extern void SendList(int boardid, Addr4882_t listeners[], char *databuf, int datacnt, int eotmode);
extern void ReceiveSetup(int boardid, Addr4882_t talker);
extern void RcvRespMsg(int boardid, char *buffer, int cnt, int eotmode);
extern void Receive(int boardid, Addr4882_t talker,char *buffer, int cnt, int eotmode);
extern void SendIFC(int boardid);
extern void DevClear(int boardid, Addr4882_t address);
extern void DevClearList(int boardid, Addr4882_t addrlist[]);
extern void EnableLocal(int boardid, Addr4882_t laddrs[]);
extern void EnableRemote(int boardid, Addr4882_t laddrs[]);
extern void SetRWLS(int boardid, Addr4882_t laddrs[]);
extern void SendLLO(int boardid);
extern void PassControl(int boardid, Addr4882_t talker);
extern void ReadStatusByte(int boardid, Addr4882_t talker, short *result);
extern void Trigger(int boardid, Addr4882_t laddrs);
extern void TriggerList(int boardid, Addr4882_t laddrs[]);
extern void PPollConfig(int boardid, Addr4882_t laddr, int dataline, int linesense);
extern void PPollUnconfig(int boardid, Addr4882_t laddrs[]);
extern void PPoll(int boardid, short *res_ptr);
extern void TestSRQ(int boardid, short *result);
extern void WaitSRQ(int boardid, short *result);
extern void ResetSys(int boardid, Addr4882_t laddrs[]);
extern void FindRQS(int boardid, Addr4882_t taddrs[], short *dev_stat);
extern void AllSpoll(int boardid, Addr4882_t taddrs[], Addr4882_t res[]);
extern void FindLstn(int boardid, Addr4882_t pads[], Addr4882_t results[], int limit);
extern void TestSys(int boardid, Addr4882_t addrs[], Addr4882_t result[]);

#else /*__STDC__*/

extern int ibbna();
extern int ibcac();
extern int ibclr();
extern int iblock();
extern int ibunlock();
extern int ibcmd();
extern int ibdev();
extern int ibdma();
extern int ibeos();
extern int ibeot();
extern int ibfind();
extern int ibgts();
extern int ibist();
extern int iblines();
extern int ibln();
extern int ibloc();
extern int ibllo();
extern int ibonl();
extern int ibpad();
extern int ibpct();
extern int ibppc();
extern int ibrd();
extern int ibrda();
extern int ibrdkey();
extern int ibdiag();
extern int ibrdf();
extern int ibrpp();
extern int ibrsc();
extern int ibrsp();
extern int ibrsv();
extern int ibsad();
extern int ibsgnl();
extern int ibsic();
extern int ibsre();
extern int ibtmo();
extern int ibtrg();
extern int ibwait();
extern int ibwrt();
extern int ibwrta();
extern int ibwrtkey();
extern int ibwrtf();
extern int ibpoke();
extern int ibconfig();
extern int ibask();

/* 488.2 extentions */
extern void SendCmds();
extern void SendSetup();
extern void SendDataBytes();
extern void Send();
extern void SendList();
extern void ReceiveSetup();
extern void RcvRespMsg();
extern void Receive();
extern void SendIFC();
extern void DevClear();
extern void DevClearList();
extern void EnableLocal();
extern void EnableRemote();
extern void SetRWLS();
extern void SendLLO();
extern void PassControl();
extern void ReadStatusByte();
extern void Trigger();
extern void TriggerList();
extern void PPollConfig();
extern void PPollUnconfig();
extern void PPoll();
extern void TestSRQ();
extern void WaitSRQ();
extern void ResetSys();
extern void FindRQS();
extern void AllSpoll();
extern void FindLstn();
extern void TestSys();
#endif /*_ANSI_C_*/
#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif /* UGPIB_INCLUDED */
