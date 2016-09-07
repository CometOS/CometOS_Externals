/*
 ***************************************************************************
 *
 * Author: Teunis van Beelen
 *
 * Copyright (C) 2005, 2006, 2007, 2008, 2009 Teunis van Beelen
 *
 * teuniz@gmail.com
 *
 ***************************************************************************
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 ***************************************************************************
 *
 * This version of GPL is at http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt
 *
 ***************************************************************************
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rs232.h"
//#include "palLocalTime.h"

#ifdef __linux__   /* Linux */

static struct termios new_port_settings;

#include <stdlib.h>

int OpenComport(const char* port, int baudrate) {
	int baudr;

	switch (baudrate) {
	case 50:
		baudr = B50;
		break;
	case 75:
		baudr = B75;
		break;
	case 110:
		baudr = B110;
		break;
	case 134:
		baudr = B134;
		break;
	case 150:
		baudr = B150;
		break;
	case 200:
		baudr = B200;
		break;
	case 300:
		baudr = B300;
		break;
	case 600:
		baudr = B600;
		break;
	case 1200:
		baudr = B1200;
		break;
	case 1800:
		baudr = B1800;
		break;
	case 2400:
		baudr = B2400;
		break;
	case 4800:
		baudr = B4800;
		break;
	case 9600:
		baudr = B9600;
		break;
	case 19200:
		baudr = B19200;
		break;
	case 38400:
		baudr = B38400;
		break;
	case 57600:
		baudr = B57600;
		break;
	case 115200:
		baudr = B115200;
		break;
	case 230400:
		baudr = B230400;
		break;
	case 460800:
		baudr = B460800;
		break;
	case 500000:
		baudr = B500000;
		break;
	case 576000:
		baudr = B576000;
		break;
	case 921600:
		baudr = B921600;
		break;
	case 1000000:
		baudr = B1000000;
		break;
	default:
		printf("invalid baudrate\n");
		return (-1);
		break;
	}

	int descr = open(port, O_RDWR | O_NOCTTY | O_NDELAY);
	if (descr == -1) {
		perror("unable to open comport ");
		return (-1);
	}

	memset(&new_port_settings, 0, sizeof(new_port_settings)); /* clear the new struct */

	new_port_settings.c_cflag = baudr | CS8 | CLOCAL | CREAD;
	new_port_settings.c_iflag = IGNPAR;
	new_port_settings.c_oflag = 0;
	new_port_settings.c_lflag = 0;
	new_port_settings.c_cc[VMIN] = 0; /* block untill n bytes are received */
	new_port_settings.c_cc[VTIME] = 0; /* block untill a timer expires (n * 100 mSec.) */

	if (tcsetattr(descr, TCSANOW, &new_port_settings) == -1) {
		close(descr);
		perror("unable to adjust portsettings ");
		return (-1);
	}

	return descr;
}

int PollComport(int descr, unsigned char *buf, int size) {
	int n;

#ifndef __STRICT_ANSI__                       /* __STRICT_ANSI__ is defined when the -ansi option is used for gcc */
	if (size > SSIZE_MAX)
		size = (int) SSIZE_MAX; /* SSIZE_MAX is defined in limits.h */
#else
	if(size>4096) size = 4096;
#endif

//	struct timeval end;
//	struct timeval start;

 //   gettimeofday(&start, NULL);

	n = read(descr, buf, size);

//	gettimeofday(&end, NULL);

 //   long sec = end.tv_sec - start.tv_sec;
 //   long usec = (end.tv_usec) - (start.tv_usec);

//    printf("%ld\n", sec * 1000000 + usec);

	return (n);
}

int SendByte(int descr, unsigned char byte) {
	int n;

	n = write(descr, &byte, 1);
	if (n < 0)
		return (1);

	return (0);
}

int SendBuf(int descr, unsigned char *buf, int size) {
	return (write(descr, buf, size));
}

void CloseComport(int descr) {
	close(descr);
}

/*
 Constant  Description
 TIOCM_LE  DSR (data set ready/line enable)
 TIOCM_DTR DTR (data terminal ready)
 TIOCM_RTS RTS (request to send)
 TIOCM_ST  Secondary TXD (transmit)
 TIOCM_SR  Secondary RXD (receive)
 TIOCM_CTS CTS (clear to send)
 TIOCM_CAR DCD (data carrier detect)
 TIOCM_CD  Synonym for TIOCM_CAR
 TIOCM_RNG RNG (ring)
 TIOCM_RI  Synonym for TIOCM_RNG
 TIOCM_DSR DSR (data set ready)
 */

int IsCTSEnabled(int descr) {
	int status;

	status = ioctl(descr, TIOCMGET, &status);

	if (status & TIOCM_CTS)
		return (1);
	else
		return (0);
}

#else         /* windows */

// TODO commeted stuff contains attempt to use blocking calls to ReadFile
//      and WriteFile. For some reason, ReadFile never returned with
//      ReadIntervalTimeout = 3 (other two set to 0)

//static OVERLAPPED olRx = {0};
//static OVERLAPPED olTx = {0};
static __int64 freqMs;

void usleep(int waitTime) {
	int waitfor = (waitTime + 500) / 1000;
	Sleep(waitfor == 0 ? 1 : waitfor);
}

#include <windows.h>
//
//void usleep(int waitTime) {
//    __int64 time1 = 0, time2 = 0, freq = 0;
//
//    QueryPerformanceCounter((LARGE_INTEGER *) &time1);
//    QueryPerformanceFrequency((LARGE_INTEGER *)&freq);
//
//    do {
//        QueryPerformanceCounter((LARGE_INTEGER *) &time2);
//    } while((time2-time1) < waitTime);
//
//}


char baudr[64];

int OpenComport(const char* port, int baudrate)
{
    __int64 freq;
    QueryPerformanceFrequency((LARGE_INTEGER *)&freq);
    freqMs = freq / 1000;

	switch(baudrate)
	{
		case 110 : strcpy(baudr, "baud=110 data=8 parity=N stop=1");
		break;
		case 300 : strcpy(baudr, "baud=300 data=8 parity=N stop=1");
		break;
		case 600 : strcpy(baudr, "baud=600 data=8 parity=N stop=1");
		break;
		case 1200 : strcpy(baudr, "baud=1200 data=8 parity=N stop=1");
		break;
		case 2400 : strcpy(baudr, "baud=2400 data=8 parity=N stop=1");
		break;
		case 4800 : strcpy(baudr, "baud=4800 data=8 parity=N stop=1");
		break;
		case 9600 : strcpy(baudr, "baud=9600 data=8 parity=N stop=1");
		break;
		case 19200 : strcpy(baudr, "baud=19200 data=8 parity=N stop=1");
		break;
		case 38400 : strcpy(baudr, "baud=38400 data=8 parity=N stop=1");
		break;
		case 57600 : strcpy(baudr, "baud=57600 data=8 parity=N stop=1");
		break;
		case 115200 : strcpy(baudr, "baud=115200 data=8 parity=N stop=1");
		break;
		case 128000 : strcpy(baudr, "baud=128000 data=8 parity=N stop=1");
		break;
		case 256000 : strcpy(baudr, "baud=256000 data=8 parity=N stop=1");
		break;
		default : printf("invalid baudrate\n");
		return(-1);
		break;
	}

//	HANDLE descr = CreateFileA(port,
//			GENERIC_READ|GENERIC_WRITE,
//			0, /* no share  */
//			NULL, /* no security */
//			OPEN_EXISTING,
//			FILE_FLAG_OVERLAPPED,
//			NULL); /* no templates */

	HANDLE descr = CreateFileA(port,
            GENERIC_READ|GENERIC_WRITE,
            0, /* no share  */
            NULL, /* no security */
            OPEN_EXISTING,
            0, /* no threads */
            NULL); /* no template */

	if(descr==INVALID_HANDLE_VALUE)
	{
		printf("unable to open comport\n");
		return(-1);
	}

	printf("opened COM port %s\n", port);

	DCB port_settings;
	memset(&port_settings, 0, sizeof(port_settings)); /* clear the new struct  */
	port_settings.DCBlength = sizeof(port_settings);

	if(!BuildCommDCBA(baudr, &port_settings))
	{
		printf("unable to set comport dcb settings\n");
		CloseHandle(descr);
		return(-1);
	}

	if(!SetCommState(descr, &port_settings))
	{
		printf("unable to set comport cfg settings\n");
		CloseHandle(descr);
		return(-1);
	}

	COMMTIMEOUTS Cptimeouts;

	Cptimeouts.ReadIntervalTimeout = MAXDWORD;
	Cptimeouts.ReadTotalTimeoutMultiplier = 0;
	Cptimeouts.ReadTotalTimeoutConstant = 0;
	Cptimeouts.WriteTotalTimeoutMultiplier = 0;
	Cptimeouts.WriteTotalTimeoutConstant = 0;

//	Cptimeouts.ReadIntervalTimeout = MAXDWORD;
//    Cptimeouts.ReadTotalTimeoutMultiplier = MAXDWORD;
//    Cptimeouts.ReadTotalTimeoutConstant = 1000;
//    Cptimeouts.WriteTotalTimeoutMultiplier = 0;
//    Cptimeouts.WriteTotalTimeoutConstant = 0;

	if(!SetCommTimeouts(descr, &Cptimeouts))
	{
		printf("unable to set comport time-out settings\n");
		CloseHandle(descr);
		return(-1);
	}

//	// create event for "asynchronous" completion
//	olRx.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
//	olTx.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
////
//	if (olRx.hEvent == NULL || olTx.hEvent == NULL) {
//	    printf("Event creation for rx/tx failed\n");
//	    exit(-1);
//	}

	return (int)(descr);
}

int PollComport(int descr, unsigned char *buf, int size)
{
    int n;

    if(size>4096) size = 4096;

    /* added the void pointer cast, otherwise gcc will complain about */
    /* "warning: dereferencing type-punned pointer will break strict aliasing rules" */

    ReadFile((HANDLE)descr, buf, size, (LPDWORD)((void *)&n), NULL);

    return(n);

//    BOOL waitForRxCompletion = FALSE;
//    int n;
//
//
//    __int64 time1 = 0, time2 = 0;
//	static int count = 0;
//	count++;
//
//
//	if(size>4096) size = 4096;
//
//	/* added the void pointer cast, otherwise gcc will complain about */
//	/* "warning: dereferencing type-punned pointer will break strict aliasing rules" */
//	printf("readfile %u\n", palLocalTime_get());
//	QueryPerformanceCounter((LARGE_INTEGER *) &time1);
//
//	if (!waitForRxCompletion) {
//        if (!ReadFile((HANDLE)descr, buf, size, NULL, &olRx)) {
//            if (GetLastError() != ERROR_IO_PENDING) {
//                printf("RxError: %lu\n", GetLastError());
//                return 0;
//            } else {
//                printf("RxError: %lu\n", GetLastError());
//                waitForRxCompletion = TRUE;
//            }
//        } else {
//            return n;
//        }
//	} else {
//	    return 0;
//	}
//
//	DWORD result;
//
//	if (waitForRxCompletion) {
//	    printf("waiting\n");
//	    result = WaitForSingleObject(olRx.hEvent, INFINITE);
//	    printf("end waiting\n");
//	    QueryPerformanceCounter((LARGE_INTEGER *) &time2);
//	    switch(result) {
//	        case WAIT_OBJECT_0:
//	            waitForRxCompletion = FALSE;
//	            if(!GetOverlappedResult((HANDLE)descr, &olRx, (DWORD*)&n, FALSE)) {
//	                printf("RxError: %lu\n", GetLastError());
//	                return 0;
//	            } else {
//	                printf("rx:%4d|%d|%llu|%u\n", count, n, (time2-time1)/freqMs, palLocalTime_get());
//	                return n;
//	            }
//	            break;
//
//	        case WAIT_TIMEOUT:
//	            waitForRxCompletion = FALSE;
//	            break;
//
//	        default:
//	            printf("WaitError: %lu\n", GetLastError());
//	            break;
//	    }
//	}
//	return n;
}

int SendByte(int descr, unsigned char byte)
{
//	int n;
//
//	__int64 time1 = 0, time2 = 0, freq=0;
//    static int count = 0;
//    count++;
//    QueryPerformanceFrequency((LARGE_INTEGER *)&freq);
//
//
//    QueryPerformanceCounter((LARGE_INTEGER *) &time1);
//
//
//    WriteFile((HANDLE)descr, &byte, 1, (LPDWORD)((void *)&n), NULL);
//    QueryPerformanceCounter((LARGE_INTEGER *) &time2);
//
//    printf("%4d|%d|%llu\n", count, n, (time2-time1)/freq);
//
//
//	if(n<0) return(1);
//
//	return(0);
    int n;

    WriteFile((HANDLE)descr, &byte, 1, (LPDWORD)((void *)&n), NULL);

    if(n<0) return(1);

    return(0);
}

int SendBuf(int descr, unsigned char *buf, int size)
{
    int n;
    __int64 time1 = 0, time2 = 0;
    QueryPerformanceCounter((LARGE_INTEGER *) &time1);

    if(WriteFile((HANDLE)descr, buf, size, (LPDWORD)((void *)&n), NULL))
    {
        QueryPerformanceCounter((LARGE_INTEGER *) &time2);
//        printf("Tx: %d|%llu\n", n, ((time2 - time1) / freqMs));
        return(n);
    } else {
//        printf("TxError: %lu\n", GetLastError());
    }

    return(-1);

//	int n;
//
//	__int64 time1 = 0, time2 = 0, freq=0;
//	static int count = 0;
//	count++;
//    QueryPerformanceFrequency((LARGE_INTEGER *)&freq);
//
//
//    QueryPerformanceCounter((LARGE_INTEGER *) &time1);
//
//
//	if(!WriteFile((HANDLE)descr, buf, size, (LPDWORD)((void *)&n), &olTx)) {
//		if (GetLastError() != ERROR_IO_PENDING) {
//		    return -1;
//		} else {
//            if (!GetOverlappedResult((HANDLE) descr, &olTx, (LPDWORD) &n, TRUE)) {
//                printf("WaitError:%lu\n", GetLastError());
//                return -1;
//            } else {
//                // success
//                QueryPerformanceCounter((LARGE_INTEGER *) &time2);
//                printf("tx:%d|%llu|%lu\n", n, ((time2 - time1) / freq), palLocalTime_get());
//                return n;
//            }
//		}
//	} else {
//	    return n;
//	}
}

void CloseComport(int descr)
{
	CloseHandle((HANDLE)descr);
}

int IsCTSEnabled(int descr)
{
	int status;

	GetCommModemStatus((HANDLE)descr, (LPDWORD)((void *)&status));

	if(status&MS_CTS_ON) return(1);
	else return(0);
}

#endif


