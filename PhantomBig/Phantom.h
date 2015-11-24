#include "Winsock2.h"
#include <HD/hd.h>
#include <HDU/hduError.h>
#include <HDU/hduVector.h>
#include <Eigen/Dense>

#include <boost/shared_ptr.hpp>
#include <cstdlib>

#include <windows.h>
#include <winbase.h>

#include <random>

#include <sstream>

#define K_FEEDBACK		0.2
#define DEVICE_NAME_1 "BIG"

typedef struct _PACK{
	hduVector3Dd position;
	hduVector3Dd force;
	hduVector3Dd prev;
}PACK;

HHD phantomId_1;

hduVector3Dd init_position,init_angles,position;
bool Phantom_Started;
LARGE_INTEGER sPos, ePos, freq;
__int64 ms_interval = 0;
int omni_cnt;
int m1Buttons;
PACK mst;


bool animation_flag;
bool first_bnt;
bool button_flag;
bool positioning_flag;
double init_positioning[3];
int target_count;

HDCallbackCode HDCALLBACK DeviceCalibrate(void *pUserData);
HDCallbackCode HDCALLBACK PhantomDevice(void *pUserData);
inline void Phantom1();
void Omni_Calibrate(void);
void Omni_Init(void);
void Omni_Start(void);
void LogData();

void Omni_Init(void)
{
	phantomId_1 = hdInitDevice(DEVICE_NAME_1);
    hdEnable(HD_FORCE_OUTPUT);

    hdStartScheduler();
    hdMakeCurrentDevice(phantomId_1);

    for (int i = 0; i < 3; ++i)
    {
    	init_position[i] = 0.0;
    	init_angles[i] = 0.0;
    	mst.position[i] = 0.0;
    	mst.prev[i] = 0.0;
    	mst.force[i] = 0.0;
    	position[i] = 0.0;
    }

    omni_cnt = 0;
    Phantom_Started = false;
    animation_flag = false;
    first_bnt = false;
    button_flag = false;
    target_count = 0;

	positioning_flag = false;
	init_positioning[0] = -400;
	init_positioning[1] = 200;
	init_positioning[2] = -250;
}

void Omni_Calibrate(void)
{
	if (!Phantom_Started){

		hdScheduleSynchronous(DeviceCalibrate, position, HD_MIN_SCHEDULER_PRIORITY);
	}
}

void Omni_Start(void) 
{
	if (!Phantom_Started){	
		Phantom_Started=true;
		hdScheduleAsynchronous(PhantomDevice, position, HD_DEFAULT_SCHEDULER_PRIORITY);
	}
}

HDCallbackCode HDCALLBACK DeviceCalibrate(void *pUserData)
{
   hdBeginFrame(phantomId_1);
   hdGetDoublev(HD_CURRENT_POSITION,init_position);
   hdGetDoublev(HD_CURRENT_GIMBAL_ANGLES, init_angles);
   hdEndFrame(hdGetCurrentDevice());
   
   return HD_CALLBACK_DONE;
}

HDCallbackCode HDCALLBACK PhantomDevice(void *pUserData)
{   
	if (omni_cnt <2000)
	{
		omni_cnt++;
	} 
	else{
		QueryPerformanceFrequency(&freq); 
		omni_cnt++;
		QueryPerformanceCounter(&sPos);
		ms_interval = (sPos.QuadPart - ePos.QuadPart)/(freq.QuadPart/1000000);
		ePos = sPos;
			
		//master
		Phantom1();
	}
	return HD_CALLBACK_CONTINUE;
}

inline void Phantom1(){
	hdBeginFrame(phantomId_1);
		
	hdGetIntegerv(HD_CURRENT_BUTTONS, &m1Buttons);

	if (m1Buttons && HD_DEVICE_BUTTON_1)
	{
		if (!button_flag)
		{	
			button_flag = true;

			animation_flag = true;
			target_count++;
			if (target_count > 8)
			{
				target_count = 1;
			}
			if (!first_bnt)
			{
				first_bnt = true;
				positioning_flag = false;
				for (int i = 0; i < 3; ++i)	init_position[i] = mst.position[i];
			}
		}
	}
	else
	{
		if (button_flag)
		{
			button_flag = false;
		}
	}

	for (int i = 0; i < 3; ++i)	mst.prev[i]=mst.position[i];
					
	hdGetDoublev(HD_CURRENT_POSITION,mst.position);

	for (int i = 0; i < 3; ++i)	mst.position[i]-=init_position[i];

	if (first_bnt)
	{
		mst.force[0] = 0;
		mst.force[1] = 0;
		mst.force[2] = -K_FEEDBACK*mst.position[2];
		hdSetDoublev(HD_CURRENT_FORCE, mst.force);
	}else if(positioning_flag)
	{
		mst.force[0] = K_FEEDBACK*(init_positioning[0]-mst.position[0]);
		mst.force[1] = K_FEEDBACK*(init_positioning[1]-mst.position[1]);
		mst.force[2] = K_FEEDBACK*(init_positioning[2]-mst.position[2]);
		hdSetDoublev(HD_CURRENT_FORCE, mst.force);
	}


	hdEndFrame(hdGetCurrentDevice());
}

