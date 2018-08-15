#pragma once

#include "stdafx.h"

//#using <Winmm.dll>

#include <Windows.h>
#include <MMSystem.h>
#include <iostream>
#include "Mockup.h"

#include "AudioInput.h"
/*
typedef struct measurement {
	float magnitude;
	float phase;
	float reference;
} measurementType;
*/
measurementType measured[1024*100];
volatile measurementType actualMeasurement;
int measurementCount[1100];
int measurementIndex[1100];
int lastMeasurement;
int maxMeasurement;


float decoded[1024][2];
volatile int nextDecoded = 0;

//volatile float magSig;
//volatile float phaseSig;
//volatile float volSig;

double audio_volume_reflection;
double audio_phase_reflection;
double audio_volume_transmission;
double audio_phase_transmission;
bool audio_simulation = false;
int audio_delay;

int simMode = 0;
int	simPoint = 0;
int	simMaxPoint = 0;
int	simDuration = 3;
int	simStep = 0;
long simStartF;
long simStepF;
int simBefore;
int simAfter;
int simDirection;
long simS = 0;

int audioPower = false;

#define DEBUGAUDIO

#ifdef DEBUGAUDIO
short temp_audio[NUMPTS];
#endif
HWAVEIN      hWaveIn;

int sampleRate = 44100;
short int waveIn[WAVEHDRBUFFER][NUMPTS];   // 'short int' is a 16-bit type; I request 16-bit samples below
WAVEHDR      WaveInHdr[WAVEHDRBUFFER];
MMRESULT result;

 // Specify recording parameters
 WAVEFORMATEX pFormat;


 //const 
	 short sincos_tbl[48][2] = {
/* 5 khz 48000 s/s
  { 10533,  31029 }, { 27246,  18205 }, { 32698,  -2143 }, { 24636, -21605 },
  {  6393, -32138 }, {-14493, -29389 }, {-29389, -14493 }, {-32138,   6393 },
  {-21605,  24636 }, { -2143,  32698 }, { 18205,  27246 }, { 31029,  10533 },
  { 31029, -10533 }, { 18205, -27246 }, { -2143, -32698 }, {-21605, -24636 },
  {-32138,  -6393 }, {-29389,  14493 }, {-14493,  29389 }, {  6393,  32138 },
  { 24636,  21605 }, { 32698,   2143 }, { 27246, -18205 }, { 10533, -31029 },
  {-10533, -31029 }, {-27246, -18205 }, {-32698,   2143 }, {-24636,  21605 },
  { -6393,  32138 }, { 14493,  29389 }, { 29389,  14493 }, { 32138,  -6393 },
  { 21605, -24636 }, { 2143,  -32698 }, {-18205, -27246 }, {-31029, -10533 },
  {-31029,  10533 }, {-18205,  27246 }, {  2143,  32698 }, { 21605,  24636 },
  { 32138,   6393 }, { 29389, -14493 }, { 14493, -29389 }, { -6393, -32138 },
  {-24636, -21605 }, {-32698,  -2143 }, {-27246,  18205 }, {-10533,  31029 }
*/
/*	 // 5128 Hz in 44.1kHz
  { -30605, 11706 } ,
  { -14982, 29141 } ,
  { 8289, 31701 } ,
  { 27328, 18079 } ,
  { 32418, -4773 } ,
  { 20958, -25188 } ,
  { -1200, -32745 } ,
  { -22745, -23587 } ,
  { -32680, -2388 } ,
  { -25932, 20030 } ,
  { -5947, 32223 } ,
  { 17074, 27967 } ,
  { 31379, 9435 } ,
  { 29666, -13913 } ,
  { 12810, -30159 } ,
  { -10586, -31010 } ,
  { -28578, -16031 } ,
  { -31981, 7132 } ,
  { -19059, 26654 } ,
  { 3592, 32570 } ,
  { 24410, 21859 } ,
  { 32767, -9 } ,
  { 24397, -21873 } ,
  { 3574, -32572 } ,
  { -19074, -26643 } ,
  { -31985, -7114 } ,
  { -28569, 16047 } ,
  { -10569, 31016 } ,
  { 12827, 30152 } ,
  { 29674, 13897 } ,
  { 31374, -9453 } ,
  { 17058, -27977 } ,
  { -5966, -32219 } ,
  { -25944, -20015 } ,
  { -32678, 2407 } ,
  { -22732, 23600 } ,
  { -1181, 32746 } ,
  { 20973, 25176 } ,
  { 32420, 4754 } ,
  { 27318, -18094 } ,
  { 8271, -31706 } ,
  { -14998, -29133 } ,
  { -30611, -11688 } ,
  { -30598, 11723 } ,
*/
	 
//5khz 44100 s/s

  { 10529, 31029 } ,   { 28251, 16600 } ,  { 32231, -5904 } ,  { 20534, -25536 } ,
  { -1150, -32749 } ,  { -22276, -24034 } ,  { -32568, -3629 } ,  { -27019, 18540 } ,
  { -8330, 31691 } ,  { 14411, 29428 } ,  { 30142, 12851 } ,  { 31212, -9977 } ,
  { 17100, -27953 } ,  { -5329, -32333 } ,  { -25166, -20988 } ,  { -32764, 565 } ,
  { -24426, 21843 } ,  { -4209, 32496 } ,  { 18056, 27343 } ,  { 31538, 8891 } ,
  { 29680, -13886 } ,  { 13386, -29910 } ,  { -9420, -31386 } ,  { -27644, -17597 } ,
  { -32423, 4750 } ,  { -21433, 24787 } ,  { -18, 32767 } ,  { 21404, 24810 } ,
  { 32416, 4785 } ,  { 27660, -17568 } ,  { 9451, -31376 } ,  { -13356, -29924 } ,
  { -29667, -13918 } ,  { -31549, 8857 } ,  { -18087, 27324 } ,  { 4172, 32500 } ,
  { 24401, 21869 } ,  { 32761, 600 } ,  { 25187, -20961 } ,  { 5361, -32327 } ,
  { -17072, -27971 } ,  { -31203, -10010 } ,  { -30157, 12819 } ,  { -14444, 29412 } ,
  { 8294, 31700 } ,  { 26997, 18569 } ,  { 32569, -3595 } ,  { 22300, -24010 }

/*
  // 5khz 44100 s/s scale by div 16
  { 658, 1939 } ,   { 1766, 1038 } ,  { 2014, -369 } ,  { 1283, -1596 } ,
  { -72, -2047 } ,  { -1392, -1502 } ,  { -2035, -227 } ,  { -1689, 1159 } ,
  { -521, 1981 } ,  { 901, 1839 } ,  { 1884, 803 } ,  { 1951, -623 } ,
  { 1069, -1747 } ,  { -333, -2021 } ,  { -1573, -1312 } ,  { -2048, 35 } ,
  { -1527, 1365 } ,  { -263, 2031 } ,  { 1129, 1709 } ,  { 1971, 556 } ,
  { 1855, -868 } ,  { 837, -1869 } ,  { -589, -1962 } ,  { -1728, -1100 } ,
  { -2026, 297 } ,  { -1339, 1549 } ,  { -1, 2048 } ,  { 1338, 1551 } ,
  { 2026, 299 } ,  { 1729, -1098 } ,  { 591, -1961 } ,  { -835, -1870 } ,
  { -1854, -870 } ,  { -1972, 554 } ,  { -1130, 1708 } ,  { 261, 2031 } ,
  { 1525, 1367 } ,  { 2048, 38 } ,  { 1574, -1310 } ,  { 335, -2020 } ,
  { -1067, -1748 } ,  { -1950, -626 } ,  { -1885, 801 } ,  { -903, 1838 } ,
  { 518, 1981 } ,  { 1687, 1161 } ,  { 2036, -225 } ,  { 1394, -1501 }
*/
};

//long acc_samp_s;
//long acc_samp_c;
//long acc_ref_s;
//long acc_ref_c;


#define PI	3.14159265358979

#include "Constants.h"

#define todb(X) (20.0f * log10 ((float(X)/(float)32768)))


float max_rr = 0;
float min_rr = (float)1e+30;
float factor = 1;
int reference_signal_level=0;
int prev_ref_signal = 0;


//#pragma STDC FP_CONTRACT ON

void dsp_process(short *capture, long length)
{
  short *p = capture;
  int len = length / 2;
  int i;
  long long samp_s = 0;
  long long samp_c = 0;
  long long ref_s = 0;
  long long ref_c = 0;
  double ref_mag;
    double samp_mag;

  for (i = 0; i < len; i++) {
    long long smp = (*p++ );
    long long ref = (*p++ );
    long s = sincos_tbl[i][0];
    long c = sincos_tbl[i][1];

 
	if (audioPower) {
		samp_s += smp*smp;
		samp_c += smp;
	} else {
		samp_s += smp * s;
	    samp_c += smp * c;
	}
	ref_s += ref * s;
	ref_c += ref * c;

  }
//  acc_samp_s = samp_s;
//  acc_samp_c = samp_c;
//  acc_ref_s = ref_s;
//  acc_ref_c = ref_c;

	ref_mag = sqrt((ref_s*(float)ref_s)+ref_c*(float)ref_c);
  if (audioPower) {
//	samp_mag = samp_s - abs(samp_c);
	  samp_mag = sqrt(((float)samp_s)/len - ((float)samp_c)*samp_c/len/len);
//	  samp_phase = 0;
	  actualMeasurement.magnitude = todb(samp_mag); 
	  actualMeasurement.phase = (float)0.0;
  } else {
#ifdef FAST_DSP	
	  double fast_mag, v0,v1;
	double fast_phase;
	 v0 = (samp_c*(float)ref_c + samp_s*(float)ref_s) / ((ref_s*(float)ref_s)+ref_c*(float)ref_c);
	v1 = (samp_s*(float)ref_c - samp_c*(float)ref_s) / ((ref_s*(float)ref_s)+ref_c*(float)ref_c);

	fast_mag = sqrt(v0*v0+v1*v1);
	fast_phase =360.0f / 2 / PI  * atan2(v1, v0);
	actualMeasurement.magnitude = todb(fast_mag*32760);
	actualMeasurement.phase = (float)fast_phase;
#else
	double ref_phase;
    double samp_phase;

	samp_mag = sqrt((samp_s*(float)samp_s)+samp_c*(float)samp_c);
	ref_phase = 360.0f / 2 / PI  * atan2((float)ref_c, (float)ref_s);
	samp_phase = 360.0f / 2 / PI  * atan2((float)samp_c, (float)samp_s);
	actualMeasurement.magnitude = todb((samp_mag / ref_mag )*32760);
	actualMeasurement.phase = (float)ref_phase - (float)samp_phase;
#endif
  }

	if (audioPower) {
	} else {
	}



  while (actualMeasurement.phase >= 180.0f) actualMeasurement.phase-= 360.0;
  while (actualMeasurement.phase <= -180.0f) actualMeasurement.phase += 360.0;
  actualMeasurement.reference =  todb(ref_mag / 32760 / 20);
}


/*
void reset_dsp_accumerator(void)
{
  acc_ref_s = 0;
  acc_ref_c = 0;
  acc_samp_s = 0;
  acc_samp_c = 0;
}
*/

typedef enum audioStates { AS_NOCHANGE, AS_ARMED, AS_STARTED, AS_SIGNAL, AS_SILENCE, AS_STOPPING, AS_FINISHED };
audioStates audioState = AS_ARMED;
audioStates nextState = AS_NOCHANGE;

#define UPCOUNT 0
#define DOWNCOUNT	1
int maxPoints = 0;

void ArmAudio(int mP)
{
	audioState = AS_ARMED;
	maxMeasurement = mP;
	lastMeasurement = 0;
	nextDecoded = 0;
}

int lastI=-1;
int lastJ=-1;
bool lastRefl = false;

bool RetreiveData(int i, int d, float& m, float& p, float& tm, float& tp, float& r)
{
	if (i < lastMeasurement-1 && i < maxMeasurement) {
		if (i != lastI ) {
			lastI = i;
			lastJ = 0;
		}
		r = measured[measurementIndex[i] + 1 + lastJ].reference;
		m = measured[measurementIndex[i] + 1 + lastJ].magnitude;
		p = measured[measurementIndex[i] + 1 + lastJ].phase;
		tm = measured[measurementIndex[i] + 1 + d + lastJ].magnitude;
		tp = measured[measurementIndex[i] + 1 + d + lastJ].phase;
//		if (i > 4 && m > -20)
//			m = m;
		lastJ++;
		return true;
	} 
	return (false);
}

#define SIGNAL_THRESHOLD -30
void StoreMeasurement()
{
	int lowmatch = 0;
	int highmatch = 0;
//	if (lastMeasurement >= maxMeasurement)
//		return;
	if (nextDecoded < 1024*100) {
		measured[nextDecoded].magnitude = actualMeasurement.magnitude;
		measured[nextDecoded].phase = actualMeasurement.phase;
		measured[nextDecoded++].reference = actualMeasurement.reference;
	}
	if (nextDecoded > 10  && (lastMeasurement == 0 || (measurementIndex[lastMeasurement-1] + 10 < nextDecoded )) ) {
//		if ( measured[nextDecoded-10].reference < SIGNAL_THRESHOLD ) lowmatch++;
//		if ( measured[nextDecoded-9].reference < SIGNAL_THRESHOLD ) lowmatch++;
//		if ( measured[nextDecoded-8].reference < SIGNAL_THRESHOLD ) lowmatch++;
		if ( measured[nextDecoded-7].reference < SIGNAL_THRESHOLD ) lowmatch++;
		if ( measured[nextDecoded-6].reference < SIGNAL_THRESHOLD ) lowmatch++;
		if ( measured[nextDecoded-5].reference > SIGNAL_THRESHOLD ) highmatch++;
		if ( measured[nextDecoded-4].reference > SIGNAL_THRESHOLD ) highmatch++;
		if ( measured[nextDecoded-3].reference > SIGNAL_THRESHOLD ) highmatch++;
		if ( measured[nextDecoded-2].reference > SIGNAL_THRESHOLD ) highmatch++;
		if ( measured[nextDecoded-1].reference > SIGNAL_THRESHOLD ) highmatch++;
		if (lowmatch >= 1 && highmatch >= 5) {
			 if (measured[nextDecoded-6].reference > SIGNAL_THRESHOLD) 
				 measurementIndex[lastMeasurement++] = nextDecoded - 6;
			 else if (measured[nextDecoded-5].reference > SIGNAL_THRESHOLD) 
				 measurementIndex[lastMeasurement++] = nextDecoded - 5;
			 else if (measured[nextDecoded-4].reference > SIGNAL_THRESHOLD) 
				 measurementIndex[lastMeasurement++] = nextDecoded - 4;
			 else if (measured[nextDecoded-3].reference > SIGNAL_THRESHOLD) 
				 measurementIndex[lastMeasurement++] = nextDecoded - 3;
			 else 
				 measurementIndex[lastMeasurement++] = nextDecoded - 2;
			if (lastMeasurement > 5 &&
				(measurementIndex[lastMeasurement-1] - measurementIndex[lastMeasurement - 2]) * 2 > 
					(measurementIndex[lastMeasurement-2] - measurementIndex[lastMeasurement - 3]) * 3
				) {
					 lowmatch = lastMeasurement; // probably skipped one measurement, just for having a breakpoint location for debugging
			}
		}
		if ( measured[nextDecoded-9].reference > SIGNAL_THRESHOLD &&
			 measured[nextDecoded-8].reference > SIGNAL_THRESHOLD &&
			 measured[nextDecoded-7].reference > SIGNAL_THRESHOLD &&
			 measured[nextDecoded-6].reference > SIGNAL_THRESHOLD &&
			 measured[nextDecoded-4].reference < SIGNAL_THRESHOLD &&
			 measured[nextDecoded-3].reference < SIGNAL_THRESHOLD &&
			 measured[nextDecoded-2].reference < SIGNAL_THRESHOLD &&
			 measured[nextDecoded-1].reference < SIGNAL_THRESHOLD   ) {
			 if (measurementIndex[lastMeasurement-1] + 15 > nextDecoded - 5 )
				nextDecoded = nextDecoded; // probably skipped one measurement, just for having a breakpoint location for debugging
		}
	}
}

#include <complex>
using namespace std;  

complex <double> modelLoadRefl(long freq, double res)
{
	if (res < 50.0) {
		return (polar(- (50.0-res)/50.0, 0.0));
	} else if (res == 50.0) {
		return (polar(- 0.0001, 0.0));
	}
	return( polar( (res-50.0) / (res+50.0), 0.0) ); 
}

complex <double> modelLoadTran(long freq, double res)
{
	if (res < 50.0) {
		return ( polar(1 - (50.0-res)/50.0, 0.0) );
	}
	if (res == 50.0) {
		return ( polar(1 - (50.0-res)/50.0, 0.0) );
	}
	return( polar(1 -(res-50.0) / (res+50.0), 0.0) ); 
}

	complex <double> debugC;
complex <double> modelRefl(long freq, double bef, double res, double aft)
{
	double del1 = bef/10./160e6, del2 = aft/10./160e6;
	complex <double> r = polar(1.,del1*freq*2*PI) * modelLoadRefl(freq,res) * polar(1.,del1*freq*2*PI) ;
	debugC = r;
	return(r);
}

complex <double> modelTran(long freq, double bef, double res, double aft)
{
	double del1 = bef/10./160e6, del2 = aft/10./160e6;
	complex <double> r = polar(1.,del1*freq*2*PI) * modelLoadTran(freq,res) * polar(1.,del2*freq*2*PI) ;
	return(r);
}

VOID ProcessHeader(WAVEHDR * pHdr)
{
	MMRESULT mRes=0;
	short *audio;
	static int state = 0;
	int i;
	int remaining;
	double temp;
	float sigLevel = (float)1;
	complex <double> tran;
	complex <double> refl;
	double v,a;
	double pi = 3.14159265359;

	//	TRACE("%d",pHdr->dwUser);
	if(WHDR_DONE==(WHDR_DONE &pHdr->dwFlags))
	{

		audio = (short *)pHdr->lpData;


		remaining = NUMPTS / 2 / SAMP;
		while (remaining-- > 0) {

			//for (i = 0; i < 48; i++) {
			//			sincos_tbl[i][0] = (short)(32000 * sin(3.1416 * 2  * i * IFFREQ / 44100));
			//			sincos_tbl[i][1] = (short)(32000 * cos(3.1416 * 2  * i * IFFREQ / 44100));
			//}
//#define DEBUGSIM
#ifdef DEBUGSIM
			if (simMode == 0) {
	simMode = M_SHORT;
	simPoint = 0;
	simMaxPoint = 100;
	simDuration = 3;
	simStep = 0;
	simStartF = 20000000;
	simStepF = 1000000;
	simDirection = 0;
	simS = 0;
	simBefore = 5;
	simAfter = 3;
			}
#endif
			if (simMode) {
				audio = waveIn[0];
				if (simStartF > MAXCALFREQ * 3)
					sigLevel = sigLevel / 16;
				else if (simStartF > MAXCALFREQ)
					sigLevel = sigLevel / 4;

				//if (simPoint < simMaxPoint ) {

				audio_simulation = false;
				if (simMode == M_SHORT) {
					tran = modelTran(simStartF, simBefore, 1.0, simAfter);
					refl = modelRefl(simStartF, simBefore, 1.0, simAfter);
					audio_volume_transmission = 0.00001 * sigLevel;
					audio_phase_transmission = 0.0;
					audio_phase_reflection = -180.0 +  (2 * simBefore) * simStartF / 1000000.;
					audio_volume_reflection = 0.9 * sigLevel;
					audio_simulation = true;
				}
				if (simMode == M_OPEN) {
					tran = modelTran(simStartF, simBefore, 20000.0, simAfter);
					refl = modelRefl(simStartF, simBefore, 20000.0, simAfter);
					audio_volume_transmission = 0.0000001 * sigLevel;
					audio_phase_transmission = 0.0;
					audio_phase_reflection = 0.0 +  (2 * simBefore) * simStartF / 1000000.;
					audio_volume_reflection = 0.9 * sigLevel;
					audio_simulation = true;
				}
				if (simMode == M_LOAD) {
					tran = modelTran(simStartF, simBefore, 0.01, simAfter);
					refl = modelRefl(simStartF, simBefore, 50.0, simAfter);
					audio_volume_transmission = 0.0001 * sigLevel;
					audio_phase_transmission = 0.0;
					audio_phase_reflection = 0.0;
					audio_volume_reflection = 0.0001 * sigLevel;
					audio_simulation = true;
				}
				if (simMode == M_THROUGH) {
					tran = modelTran(simStartF, simBefore, 50.0, simAfter);
					refl = modelRefl(simStartF, simBefore, 50.0, simAfter);
					audio_volume_transmission = 0.9 * sigLevel;
					audio_phase_transmission = 0.0 + (simBefore + simAfter) * simStartF / 1000000.;
					while (audio_phase_transmission >= +180.0) audio_phase_transmission -= 360.0;
					while (audio_phase_transmission <= -180.0) audio_phase_transmission += 360.0;
					audio_phase_reflection = 0.0;
					audio_volume_reflection = 0.0001 * sigLevel;
					audio_simulation = true;
				}
				if (simMode == M_ATTN) {
					tran = modelTran(simStartF, simBefore, 0.5, simAfter);
					refl = modelRefl(simStartF, simBefore, 50.0, simAfter);
					audio_volume_transmission = 0.9 * sigLevel / 100; // /100 = -40dB
 					audio_phase_transmission = 0.0 + (simBefore + simAfter) * simStartF / 1000000.;
					while (audio_phase_transmission >= +180.0) audio_phase_transmission -= 360.0;
					while (audio_phase_transmission <= -180.0) audio_phase_transmission += 360.0;
					audio_phase_reflection = 0.0;
					audio_volume_reflection = 0.0001 * sigLevel;
					audio_simulation = true;
				}


#define SILENCE_GAP	2
				if (simDirection) {
					temp = audio_volume_reflection;
					audio_volume_reflection = audio_volume_transmission;
					audio_volume_reflection = temp;
					temp = audio_phase_reflection;
					audio_phase_reflection = audio_phase_transmission;
					audio_phase_transmission = temp;
				}
				// simS = 0;
#ifdef DEBUGSIM
				//simS = 0;
				for (i = 0; i < SAMP; i++) {
					a = abs(refl);
					v = arg(refl);
					audio [i*2+0] = 0+(short)(32600 * abs(real(refl)) * cos(PI *2 * simS * IFFREQ / 44100 + v ));
					audio [i*2+1] = 0+(short)(32600 * 0.1 * cos(PI *2 * (simS) * IFFREQ / 44100)); // Reference
					simS++;
					simStartF += simStepF;
				}
#else
				if (simPoint < simMaxPoint && simStep >= SILENCE_GAP + simDuration*2 ) {
					simPoint += 1;
					if (simPoint < simMaxPoint) {
						simStep = 0;
						simStartF += simStepF;
					}
				}
				if (simStep < SILENCE_GAP ) { // Initial silence
					for (i = 0; i < SAMP; i++) {
						audio [i*2+0] = 0+(short)(32600 * 0.0000000000000000000001 * sin(PI * 2 * ((simS+0) + audio_phase_reflection * 1 / 360)  * IFFREQ / 44100));
						audio [i*2+1] = 0+(short)(32600 * 0.0000000000000000000001 * sin(PI * 2 * (simS) * IFFREQ / 44100)); // Reference
						simS++;
					}
				} else if (simStep < SILENCE_GAP + simDuration ) { // Reflection
					for (i = 0; i < SAMP; i++) {
//						audio [i*2+0] = 0+(short)(32600 * audio_volume_reflection * (1 - (rand() % 1000)/1000.0*0.00001) * sin(PI * 2 * ((simS+0) + audio_phase_reflection * 1 / 360)  * IFFREQ / 44100));
//						audio [i*2+1] = 0+(short)(32600 * 0.1 * sigLevel * (1 - (rand() % 1000)/1000.0*0.00001) * sin(PI * 2 * (simS) * IFFREQ / 44100)); // Reference

						a = abs(refl);
						v = arg(refl);
						audio [i*2+0] = 0+(short)(32600 * abs(refl) * (1 - (rand() % 1000)/1000.0*0.00001) * cos(PI * 2 * simS * IFFREQ / 44100 + arg(refl) ));
						audio [i*2+1] = 0+(short)(32600 * 1.0 *  (1 - (rand() % 1000)/1000.0*0.00001) * cos(PI * 2 * simS * IFFREQ / 44100)); // Reference
						simS++;
					}
				} else { // Transmission
					for (i = 0; i < SAMP; i++) {
//						audio [i*2+0] = 0+(short)(32600 * audio_volume_transmission * (1 - (rand() % 1000)/1000.0*0.00001) * sin(PI * 2 * ((simS+0) + audio_phase_transmission * 1/ 360)  * IFFREQ / 44100));
//						audio [i*2+1] = 0+(short)(32600 * 0.1 * sigLevel * (1 - (rand() % 1000)/1000.0*0.00001) * sin(PI * 2 * (simS) * IFFREQ / 44100)); // Reference
						a = abs(tran);
						v = arg(tran);
						audio [i*2+0] = 0+(short)(32600 * abs(tran) * (1 - (rand() % 1000)/1000.0*0.00001) * cos(PI *2 * simS * IFFREQ / 44100 + arg(tran)));
						audio [i*2+1] = 0+(short)(32600 * 1.0 * (1 - (rand() % 1000)/1000.0*0.00001) * cos(PI *2 * (simS) * IFFREQ / 44100)); // Reference
						simS++;
					}
				}
#endif
				//				if ((rand() % 20) < 19) // add uncertainty on timing
				simStep += 1; 
				//}
			}
			//float measured[1024][100];
			//int measurementCount[1024];
			//int lastMeasurement;

			//if (!simMode || simPoint < simMaxPoint ) {
			dsp_process(audio, SAMP*2);
			StoreMeasurement();
			audio = & (audio[SAMP*2]);
			//}
		}
		mRes=waveInAddBuffer(hWaveIn,pHdr,sizeof(WAVEHDR));
	}
}

void CALLBACK waveInProc(HWAVEIN hwi,UINT uMsg,DWORD dwInstance,DWORD dwParam1,DWORD dwParam2)
{
	WAVEHDR *pHdr=NULL;
	switch(uMsg)
	{
	case WIM_CLOSE:
		break;

	case WIM_DATA:
		{
			ProcessHeader((WAVEHDR *)dwParam1);
		}
		break;

	case WIM_OPEN:
		break;

	default:
		break;
	}
}



int OpenAudio (void) {
	int i;
	pFormat.wFormatTag=WAVE_FORMAT_PCM;     // simple, uncompressed format
	pFormat.nChannels=2;                    //  1=mono, 2=stereo
	pFormat.nSamplesPerSec=sampleRate;      // 44100
	pFormat.nAvgBytesPerSec=sampleRate*4;   // = nSamplesPerSec * n.Channels * wBitsPerSample/8
	pFormat.nBlockAlign=4;                  // = n.Channels * wBitsPerSample/8
	pFormat.wBitsPerSample=16;              //  16 for high quality, 8 for telephone-grade
	pFormat.cbSize=0;
	/*
	WAVEINCAPS stWIC={0};
	MMRESULT mRes;

	ZeroMemory(&stWIC,sizeof(WAVEINCAPS));
	mRes=waveInGetDevCaps(nSel,&stWIC,sizeof(WAVEINCAPS));
	*/

	result = waveInOpen(&hWaveIn, WAVE_MAPPER,&pFormat,
		(DWORD_PTR)waveInProc,0L,CALLBACK_FUNCTION);
	//            0L, 0L, WAVE_FORMAT_DIRECT);
	if (result)
	{
		// wchar_t fault[256];
		//waveInGetErrorText(result, fault, 256);
		//Application->MessageBox(fault, "Failed to open waveform input device.",
		//            MB_OK | MB_ICONEXCLAMATION);
		return(result);
	}

	for (i=0; i<WAVEHDRBUFFER ; i++) {
		// Set up and prepare header for input
		WaveInHdr[i].lpData = (LPSTR)(waveIn[i]);
		WaveInHdr[i].dwBufferLength = NUMPTS*2;
		WaveInHdr[i].dwBytesRecorded=0;
		WaveInHdr[i].dwUser = 0L;
		WaveInHdr[i].dwFlags = 0L;
		WaveInHdr[i].dwLoops = 0L;
		waveInPrepareHeader(hWaveIn, &WaveInHdr[i], sizeof(WAVEHDR));
		// Insert a wave input buffer
		result = waveInAddBuffer(hWaveIn, &WaveInHdr[i], sizeof(WAVEHDR));
		if (result)
		{
			//  MessageBox(Application->Handle, "Failed to read block from device",
			//                   NULL, MB_OK | MB_ICONEXCLAMATION);
			return(result);
		}
	}

	// Commence sampling input
	result = waveInStart(hWaveIn);
	if (result)
	{
		//  MessageBox(Application->Handle, "Failed to start recording",
		//                   NULL, MB_OK | MB_ICONEXCLAMATION);
		return(result);

	}
	audio_delay = -1;
	return(0);
}

void StartAudioSimulation(int mode, int numPoints, int duration, long startF, long stepF, int cable_before, int cable_after, int direction)
{
	simMode = mode;
	simPoint = 0;
	simMaxPoint = numPoints;
	simDuration = duration;
	simStep = 0;
	simStartF = startF;
	simStepF = stepF;
	simBefore = cable_before;
	simAfter = cable_after;
	simDirection = direction;
	simS = 0;
}

void SetAudioPower(int power)
{
	audioPower = power;
}