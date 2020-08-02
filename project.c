/**************************************************************************/
/* CVI Project - Yuval Shahhar and Miki Finkelstein			              */
/* Afeka College of Engineering											  */
/* School of Electrical Engineering										  */
/* GUi for temp sensor connected to Arduino								  */
/* July 2020				                                              */
/**************************************************************************/

#include "excelreport.h"
#include "outlook2000.h"
#include <utility.h>
#include <advanlys.h>
#include <tcpsupp.h>
#include <cvintwrk.h>
#include <rs232.h>
#include <ansi_c.h>
#include <cvirte.h>		
#include <userint.h>
#include "project.h"
#include <dll.h>
#define SIZE 100000

static int panelHandle,graph_panelHandle,Statistics__Panel,Set_Alert_Panel,Password_Panel,About_Panel;
static char ALARMpassword[] = "alarm"; //PASSWORD to stop the Fire Alarm
static double maxTemp,maxTemp_Time,minTemp=15,minTemp_Time;
static CAObjHandle workbookHandle;
static CAObjHandle applicationHandle;
static CAObjHandle rawDataWorkSheetHandle;
static CAObjHandle chartsheetHandle;
static int flag;
static int connect =0;
static double temp_arr[SIZE],dt,t[SIZE];
static int i=0;
static int threadId1;
static int flagthread;
static int COM_PORT;
static int CVICALLBACK thread1(void *funData)
{
	while(flagthread==0)
	{
	Delay (1);
	ReadDataFromComPort(temp_arr,t,dt,i,COM_PORT);
	writedata(temp_arr,t,i);
	SetCtrlVal (panelHandle, PANEL_Temprature, temp_arr[i]); //plot temp_arrature
	}
	return 0;
}
int main (int argc, char *argv[])
{
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;	/* out of memory */
	if ((panelHandle = LoadPanel (0, "project.uir", PANEL)) < 0)
		return -1;
	if ((graph_panelHandle = LoadPanel (0, "project.uir", PANEL_2)) < 0)
		return -1;
	if ((Statistics__Panel = LoadPanel (0, "project.uir", PANEL_3)) < 0)
		return -1;
	if ((Set_Alert_Panel = LoadPanel (0, "project.uir", PANEL_4)) < 0)
		return -1;
	if ((About_Panel = LoadPanel (0, "project.uir", PANEL_5)) < 0)
		return -1;
	if ((Password_Panel = LoadPanel (0, "project.uir", PANEL_6)) < 0)
		return -1;
	DisplayPanel (panelHandle);
	RunUserInterface ();
	DiscardPanel (panelHandle);
	//Close the open COM port before exiting//
	CloseCom (COM_PORT);
	return 0;
}

int CVICALLBACK QuitFunc (int panel, int control, int event,
						  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			QuitUserInterface (0);
			break;
	}
	return 0;
}

int CVICALLBACK ConnectFunc (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
			int Error;
		case EVENT_COMMIT:
			GetCtrlVal (panelHandle, PANEL_COM, &COM_PORT);
			Error = OpenComConfig (COM_PORT, "", 9600, 0, 8, 1, 512, 512);
			if (Error < 0) //error occurred 
            {  
				MessagePopup ("RS232 Error Message",GetRS232ErrorString (Error)); //RS232 Error message
				SetCtrlAttribute (panelHandle, PANEL_LED_OFF, ATTR_VISIBLE, 1); //Enable black led
				SetCtrlAttribute (panelHandle, PANEL_LED_ON, ATTR_VISIBLE, 0); //Disable red led
				
				return 0;
            }
			else //connection succeed
			{
				SetCtrlAttribute (panelHandle, PANEL_LED_ON, ATTR_VISIBLE, 1); //Enable red led
				SetCtrlAttribute (panelHandle, PANEL_LED_OFF, ATTR_VISIBLE, 0); //Disable black led
				FlushInQ (COM_PORT); //Removes all characters from the input COM port queue
				InstallComCallback (COM_PORT, LWRS_RXFLAG, 0, 0, 0, 0);
				MessagePopup ("RS232 succsess Message", "Connection Succeed"); //Connection Pop-up Message
				SetCtrlAttribute (panelHandle, PANEL_TIMER, ATTR_ENABLED, 1); //Enable timer
				GetCtrlAttribute (panelHandle, PANEL_TIMER, ATTR_INTERVAL, &dt); //Time interval
				SetCtrlAttribute (panelHandle, PANEL_take_data, ATTR_DIMMED, 0); //Enable Take data
				SetCtrlAttribute (panelHandle, PANEL_DISCONNECT, ATTR_DIMMED, 0); //Enable Disconnect
				SetCtrlAttribute (panelHandle, PANEL_CONNECT, ATTR_DIMMED, 1); //Disable connect
				file();
				connect=1;
			}
			break;
	}
	return 0;
}

int CVICALLBACK take_data_func (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			flagthread=0;
			CmtScheduleThreadPoolFunction (DEFAULT_THREAD_POOL_HANDLE, thread1, NULL, &threadId1); //create thread
			break;
	}
	return 0;
}



int CVICALLBACK DisconnectFunc (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		int RS232CloseError;
		case EVENT_COMMIT:
			if(connect==1)
			{
				flagthread=1;
				Delay(1);
				CmtReleaseThreadPoolFunctionID (DEFAULT_THREAD_POOL_HANDLE, threadId1); //relese thread
				SetCtrlAttribute (panelHandle, PANEL_take_data, ATTR_DIMMED, 1); //Disable Take data
				SetCtrlAttribute (panelHandle, PANEL_DISCONNECT, ATTR_DIMMED, 1); //Disable Disconnect
				SetCtrlAttribute (panelHandle, PANEL_CONNECT, ATTR_DIMMED, 0); //Enable connect
				FlushInQ (COM_PORT); //Removes all characters from the input COM port queue
				SetCtrlAttribute (panelHandle, PANEL_TIMER, ATTR_ENABLED, 0); //Disable timer
				SetCtrlAttribute (Set_Alert_Panel, PANEL_4_TIMER1, ATTR_ENABLED, 0); //Disable timer_panel_4
				RS232CloseError=CloseCom (COM_PORT); //Closes the COM port
				if (RS232CloseError < 0) //error occurred 
	            {  
					MessagePopup ("RS232 Error Message",GetRS232ErrorString (RS232CloseError)); //RS232 Error message
					return 0;
	            }
				else //End connection succeed
				{
					
				
					SetCtrlVal (panelHandle, PANEL_Temprature, 0.00); //Temprature Reset
					MessagePopup ("", "Connection Ended");
					i,maxTemp,maxTemp_Time,minTemp,minTemp_Time=0;
					SetCtrlAttribute (panelHandle, PANEL_LED_ON, ATTR_VISIBLE, 0); //Disablered led
					SetCtrlAttribute (panelHandle, PANEL_LED_OFF, ATTR_VISIBLE, 1); //Enable black led
					//statistic Values Reset//
					SetCtrlVal (graph_panelHandle, PANEL_3_Recorded_min, 0);
					SetCtrlVal (graph_panelHandle, PANEL_3_Recorded_max, 0);
					SetCtrlVal (graph_panelHandle, PANEL_3_StdDev, 0);
					SetCtrlVal (graph_panelHandle, PANEL_3_Mean_2, 0);
					SetCtrlVal (graph_panelHandle, PANEL_3_Max_Temp, maxTemp);
					SetCtrlVal (graph_panelHandle, PANEL_3_Min_Temp, minTemp);
					DeleteGraphPlot (graph_panelHandle, PANEL_2_GRAPH_TEMP, -1, VAL_IMMEDIATE_DRAW); //Delete Current graph
					connect=0;
					
				}
			}
			break;
	}
	return 0;
}




int CVICALLBACK TimerFunc (int panel, int control, int event,
						   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_TIMER_TICK:
			SetCtrlVal (panelHandle, PANEL_Temprature, temp_arr[i]); //plot temp
			if(t[i]>50)
			{
				SetCtrlAttribute (panelHandle, PANEL_Export_To_Excel, ATTR_DIMMED, 0);
			}
			if(temp_arr[i]>30)
			{
				SetCtrlAttribute (panelHandle, PANEL_Hot, ATTR_VISIBLE, 1);
				SetCtrlAttribute (panelHandle, PANEL_Comfortable, ATTR_VISIBLE, 0);
				SetCtrlAttribute (panelHandle, PANEL_Cold, ATTR_VISIBLE, 0);
			}
			else if(20<temp_arr[i]<30)
			{
				SetCtrlAttribute (panelHandle, PANEL_Comfortable, ATTR_VISIBLE, 1);
				SetCtrlAttribute (panelHandle, PANEL_Cold, ATTR_VISIBLE, 0);
				SetCtrlAttribute (panelHandle, PANEL_Hot, ATTR_VISIBLE, 0);
			}
			else if(temp_arr[i]<5)
			{
				SetCtrlAttribute (panelHandle, PANEL_Cold, ATTR_VISIBLE, 1);
				SetCtrlAttribute (panelHandle, PANEL_Hot, ATTR_VISIBLE, 0);
				SetCtrlAttribute (panelHandle, PANEL_Comfortable, ATTR_VISIBLE, 0);
			}
			if(temp_arr[i]>maxTemp) //Max Temprature and Time 
			{
				maxTemp=temp_arr[i];
				maxTemp_Time=i*dt;
			}
			if(temp_arr[i]<minTemp) //min Temprature and Time 
			{
				minTemp=temp_arr[i];
				minTemp_Time=i*dt;
			}
			i++;
			break;
	}
	return 0;
}
////////////////////////////////////////////////////// activx excel ////////////////////////////////////////////////

int CVICALLBACK Export_To_Excel_Func (int panel, int control, int event,
									  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
			
		case EVENT_COMMIT:
			HRESULT error = 0;
			int R_CH_ATTR_CHART_TYPE=0;
			error =ExcelRpt_ApplicationNew(VTRUE,&applicationHandle);
			 if (error<0) 
			{
        		MessagePopup ("Error"," An error occurred trying to launch Excel 2000");
				error = 0;
                goto Error1;
			}
			ExcelRpt_WorkbookNew(applicationHandle,&workbookHandle);
			//Get the worksheet handle. You can also get the worksheet handle by the name of the worksheet using ExcelRpt_GetWorksheetFromName()
			ExcelRpt_GetWorksheetFromIndex(workbookHandle,1,&rawDataWorkSheetHandle);
			//Rename the worksheet to “Analysis Data”
			ExcelRpt_SetWorksheetAttribute(rawDataWorkSheetHandle,ER_WS_ATTR_NAME,"Temp Data");
			 //define the channel header text.
			char* channelHeaders[] = {"Time","Temp"};
			ExcelRpt_WriteData (rawDataWorkSheetHandle,"A1:B1",ExRConst_dataString ,1,2,channelHeaders);
			//data is a 1250x2 array of doubles. DATASIZE = 1250
			ExcelRpt_WriteData (rawDataWorkSheetHandle, "B2:B50",ExRConst_dataDouble, 50, 1, &temp_arr[10]);
			ExcelRpt_WriteData (rawDataWorkSheetHandle, "A2:A50",ExRConst_dataDouble, 50, 1, t);
			//Create a new chart with its own worksheet
			ExcelRpt_ChartNew(workbookHandle,-1,&chartsheetHandle);

			//Create a XY scatter chart using the data we wrote to the worksheet as its data source.
			ExcelRpt_ChartWizard (chartsheetHandle, rawDataWorkSheetHandle, "B2:B50", ExRConst_GalleryXYScatter, ExRConst_Columns, 0, 0, 0, 0,
								  "Temperature Graph", "time", "temp", NULL);
			//Change the plot lines to not display markers and smooth out the plot lines. This is one of the plot styles available in Excel.
			ExcelRpt_SetChartAttribute (chartsheetHandle, R_CH_ATTR_CHART_TYPE,
			ExRConst_XYScatterSmoothNoMarkers);
			ExcelRpt_WorkbookSave (workbookHandle, "excel report", ExRConst_DefaultFileFormat); //save in documents folder	
			break;
	}
Error1:
	return 0;
}


////////////////////////////////////////////////////// graph panel ////////////////////////////////////////////////

void CVICALLBACK Graph (int menuBar, int menuItem, void *callbackData,int panel)
{
	DisplayPanel(graph_panelHandle); //Show graph PANEL
}

int CVICALLBACK BackFunc (int panel, int control, int event,
						  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			HidePanel(graph_panelHandle); //back to the conrol_panel	
			break;
	}
	return 0;
}


int CVICALLBACK PlotGraphFunc (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			SetCtrlAttribute (graph_panelHandle, PANEL_2_TIMER1, ATTR_ENABLED, 1); //Enable Timer
			break;
	}
	return 0;
}

int CVICALLBACK DeleteGraphFunc (int panel, int control, int event,
								 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			SetCtrlAttribute (graph_panelHandle, PANEL_2_TIMER1, ATTR_ENABLED, 0);//Disable Timer
			DeleteGraphPlot (graph_panelHandle, PANEL_2_GRAPH_TEMP, -1, VAL_IMMEDIATE_DRAW);//Delete graph
			break;
	}
	return 0;
}

int CVICALLBACK TimerGraphFunc (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_TIMER_TICK:
			int activeCursor;
			double xCurs,yCurs;
			PlotXY (graph_panelHandle, PANEL_2_GRAPH_TEMP, t, temp_arr, i, VAL_DOUBLE, VAL_DOUBLE, VAL_THIN_LINE, VAL_EMPTY_SQUARE, VAL_SOLID, 1, VAL_RED); //Plot graph
			GetActiveGraphCursor (graph_panelHandle, PANEL_2_GRAPH_TEMP, &activeCursor);//activeCursor
			GetGraphCursor (graph_panelHandle, PANEL_2_GRAPH_TEMP, 1, &xCurs, &yCurs); //get the point on the graph
			SetCtrlVal (graph_panelHandle, PANEL_2_DISPLAY_X, xCurs); //show  the x point
			SetCtrlVal (graph_panelHandle, PANEL_2_DISPLAY_Y, yCurs); //show  the y point
			break;
	}
	return 0;
}


int CVICALLBACK SaveGraphFunc (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
			int Bitmap;
		case EVENT_COMMIT:
			GetCtrlDisplayBitmap (graph_panelHandle, PANEL_2_GRAPH_TEMP, 1, &Bitmap);
			SaveBitmapToPNGFile (Bitmap, "Graph.PNG");//save photo of the graph
			DiscardBitmap (Bitmap);
			break;
	}
	return 0;
}

int CVICALLBACK FreezeFunc (int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			SetCtrlAttribute (graph_panelHandle, PANEL_2_TIMER1, ATTR_ENABLED, 0);//stop the plot
			break;
	}
	return 0;
}


/////////////////////////////////// Statistics__Panel ///////////////////////////////////////////////////
void CVICALLBACK Statistics (int menuBar, int menuItem, void *callbackData,int panel)
{
	DisplayPanel (Statistics__Panel); //Statistics__Panel
}


int CVICALLBACK Back1Func (int panel, int control, int event,
						   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			HidePanel(Statistics__Panel); //back to the conrol_panel
			break;
	}
	return 0;
}


int CVICALLBACK GetStats_Func (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		double Mean,Standard_Deviation;	
		case EVENT_COMMIT:
			
			StdDev (temp_arr, i, &Mean, &Standard_Deviation);//plot Mean and StdDev
			SetCtrlVal (Statistics__Panel, PANEL_3_Max_Temp, maxTemp);//plot max_temp
			SetCtrlVal (Statistics__Panel, PANEL_3_Recorded_max, maxTemp_Time);//plot max_temp_Time
			SetCtrlVal (Statistics__Panel, PANEL_3_Min_Temp, minTemp);//plot min_temp
			SetCtrlVal (Statistics__Panel, PANEL_3_Recorded_min, minTemp_Time);//plot min_temp_Time
			SetCtrlVal (Statistics__Panel, PANEL_3_Mean_2, Mean);//Mean
			SetCtrlVal (Statistics__Panel, PANEL_3_StdDev, Standard_Deviation);//StdDev
	
			break;
	}
	return 0;
}

/////////////////////////////////// Set_Alert_Panel ///////////////////////////////////////////////////

void CVICALLBACK Set_Alert (int menuBar, int menuItem, void *callbackData,int panel)
{
	DisplayPanel (Set_Alert_Panel); //Set_Alert_Panel
}


int CVICALLBACK Set_Alert_Func (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			SetCtrlAttribute (Set_Alert_Panel, PANEL_4_TIMER1, ATTR_ENABLED, 1);
			flag=0;
			break;
	}
	return 0;
}



int CVICALLBACK TimeCheckFunc (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
			double temprature;
			int error;
			int Warning;
		case EVENT_TIMER_TICK:
			GetCtrlVal (Set_Alert_Panel, PANEL_4_WarningTemp, &Warning);
			unsigned short int alarm[4]={Warning,0,0,0};
			ComWrt (COM_PORT, (char*)alarm, 6); //send data to the ardouino
			GetCtrlVal (panelHandle, PANEL_Temprature,&temprature);
			if(temprature>Warning)
			{
				if(flag==0)
				{
					char toAddress[200];
		    		GetCtrlVal (Set_Alert_Panel, PANEL_4_TO, toAddress);
					char subject[200]="Temp Alert";
					char emailbody[200]="Dear User, the sensor dedected high temprature! Data file is attached.";
					CAObjHandle messageHandle = 0;
					CAObjHandle outlookHandle = 0;
					VARIANT varPath;
					OutlookObj_Attachments attachments = 0;
					OutlookObj_Attachment Attachment = 0;
					char errortext[500];
					//Start Outlook Application
					error = Outlook_New_Application (NULL, 1, LOCALE_NEUTRAL, 0, &outlookHandle);
					if (error < 0)
					{
	  	 	  			CA_GetAutomationErrorString (error, errortext, 500);
	  		  			MessagePopup ("ActiveX Error", errortext);
	  		 			goto Error;
					}
					//Create a New Mail Item
					Outlook__ApplicationCreateItem (outlookHandle, NULL,OutlookConst_olMailItem,&messageHandle);
					if (error<0)
					{
	  					ProcessActiveXError(error);
	 					goto Error;
					}
					//Set the Mail to Address, Subject, and Standard Text Body of the New Mail
					Outlook_SetProperty (messageHandle, NULL, Outlook__MailItemTo,CAVT_CSTRING, toAddress);
					Outlook_SetProperty (messageHandle, NULL, Outlook__MailItemSubject, CAVT_CSTRING, subject);
					Outlook_SetProperty (messageHandle, NULL, Outlook__MailItemBody,CAVT_CSTRING, emailbody);
		   			//Attachment
		   			CA_VariantSetCString (&varPath, "C:\\Users\\Yuval.sh\\Desktop\\CVI\\file.txt");
		   			Outlook_GetProperty (messageHandle, NULL, Outlook__MailItemAttachments, CAVT_OBJHANDLE,&attachments);
	       			Outlook_AttachmentsAdd (attachments, NULL, varPath, CA_DEFAULT_VAL,CA_DEFAULT_VAL, CA_DEFAULT_VAL, &Attachment);
		   			error = Outlook__MailItemSend (messageHandle, NULL);
					if (error<0)
					{
	  					ProcessActiveXError(error);
	 			 		goto Error;
					}
					MessagePopup ("E-mail Sent", "E-mail report was successfully sent.");
		   			//Send New Mail Item
	       			Outlook__MailItemSend (messageHandle, NULL);
		   			flag=1;
		   			DisplayPanel (Password_Panel);//
		   		Error:
					if (Attachment)
						CA_DiscardObjHandle(Attachment);
					if (attachments)
						CA_DiscardObjHandle(attachments);
					if (messageHandle)
						CA_DiscardObjHandle(messageHandle);
					if (outlookHandle)
						CA_DiscardObjHandle(outlookHandle);
		   		}
		   	}
			break;
	}
	return 0;
}

//back to the conrol_panel
int CVICALLBACK Back2Func (int panel, int control, int event,
						   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			HidePanel(Set_Alert_Panel);//back to the conrol_panel
			break;
	}
	return 0;
}

/////////////////////////////////// PASSWORDÉ_Panel ///////////////////////////////////////////////////

int CVICALLBACK Password_Func (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		char password[20];	
		case EVENT_COMMIT:
			GetCtrlVal (Password_Panel, PANEL_6_PASSWORD, password);
			if(strcmp (password, ALARMpassword)==0) //Check if Valid
			{
				SetCtrlVal (Set_Alert_Panel, PANEL_4_WarningTemp, 50);
				MessagePopup ("", "ALARM OFF");
				HidePanel (Password_Panel); //Exit PANEL
			}
			else
				MessagePopup ("", "WRONG PASSWORD - PLEASE TRY AGAIN"); //Wrong PASSWORD
			break;
	}
	return 0;
}




///////////////////////////////////// about_panel //////////////////////////////////
void CVICALLBACK About(int menuBar, int menuItem, void *callbackData,int panel)
{
	DisplayPanel (About_Panel); //About
}


int CVICALLBACK Back3Func (int panel, int control, int event,
						   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			HidePanel(About_Panel); //back to the About_panel
			break;
	}
	return 0;
}