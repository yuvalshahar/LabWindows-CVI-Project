#include <cviauto.h>
#include "project.h"
#include <userint.h>
#include <rs232.h>
#include <ansi_c.h>
//#include "function.h"
#include <stdlib.h>
#include <stdio.h>
#include <dll.h>
FILE *fp;

void ReadDataFromComPort(double temp_arr[],double t[],double dt,int i) 
{
	int 	strLen; //Queue Data Len
	char 	readBuf[200] = {0}; //Data
	strLen = GetInQLen (9);
	ComRd (3, readBuf, strLen);//Reading data
	temp_arr[i] = strtod (readBuf, NULL);//string to double
	t[i]=i*dt;//time interval
}

void file()
{
fp=fopen("file.txt","w+");
fputs("Temp[C]\t Time(sec)\n", fp);
}       						  						 						   					



void writedata(double temp_arr[],double t[],int i)
{			
	//fprintf(fp,"%f               %f\n",temp_arr[i],t[i]);
	fprintf(fp,"%f\t%f\n",temp_arr[i],t[i]);
}




void ProcessActiveXError(int error)
{
	char errorMessage[500], errorText[500];
	
	CA_GetAutomationErrorString (error, errorText, 500);
	strcpy (errorMessage, "Outlook ActiveX Error:  ");
	strcat(errorMessage, errorText);
	MessagePopup ("ActiveX Error", errorMessage);
}




