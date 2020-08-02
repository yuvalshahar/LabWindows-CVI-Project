/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/*                                                                        */
/* WARNING: Do not add to, delete from, or otherwise modify the contents  */
/*          of this include file.                                         */
/**************************************************************************/

#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

     /* Panels and Controls: */

#define  PANEL                            1
#define  PANEL_QUITBUTTON                 2       /* control type: command, callback function: QuitFunc */
#define  PANEL_CONNECT                    3       /* control type: command, callback function: ConnectFunc */
#define  PANEL_Temprature                 4       /* control type: scale, callback function: (none) */
#define  PANEL_LED_ON                     5       /* control type: LED, callback function: (none) */
#define  PANEL_LED_OFF                    6       /* control type: LED, callback function: (none) */
#define  PANEL_Hot                        7       /* control type: LED, callback function: (none) */
#define  PANEL_Comfortable                8       /* control type: LED, callback function: (none) */
#define  PANEL_Cold                       9       /* control type: LED, callback function: (none) */
#define  PANEL_Export_To_Excel            10      /* control type: command, callback function: Export_To_Excel_Func */
#define  PANEL_take_data                  11      /* control type: command, callback function: take_data_func */
#define  PANEL_DISCONNECT                 12      /* control type: command, callback function: DisconnectFunc */
#define  PANEL_PICTURE                    13      /* control type: picture, callback function: (none) */
#define  PANEL_COM                        14      /* control type: numeric, callback function: (none) */
#define  PANEL_TIMER                      15      /* control type: timer, callback function: TimerFunc */

#define  PANEL_2                          2
#define  PANEL_2_GRAPH_TEMP               2       /* control type: graph, callback function: (none) */
#define  PANEL_2_PLOT_GRAPH               3       /* control type: command, callback function: PlotGraphFunc */
#define  PANEL_2_DELETEGRAPH              4       /* control type: command, callback function: DeleteGraphFunc */
#define  PANEL_2_COMMANDBUTTON            5       /* control type: command, callback function: BackFunc */
#define  PANEL_2_SAVEGRAPH                6       /* control type: command, callback function: SaveGraphFunc */
#define  PANEL_2_FREEZE                   7       /* control type: command, callback function: FreezeFunc */
#define  PANEL_2_DISPLAY_Y                8       /* control type: numeric, callback function: (none) */
#define  PANEL_2_DISPLAY_X                9       /* control type: numeric, callback function: (none) */
#define  PANEL_2_TIMER1                   10      /* control type: timer, callback function: TimerGraphFunc */

#define  PANEL_3                          3
#define  PANEL_3_COMMANDBUTTON            2       /* control type: command, callback function: Back1Func */
#define  PANEL_3_GetStats                 3       /* control type: command, callback function: GetStats_Func */
#define  PANEL_3_Recorded_min             4       /* control type: numeric, callback function: (none) */
#define  PANEL_3_Recorded_max             5       /* control type: numeric, callback function: (none) */
#define  PANEL_3_StdDev                   6       /* control type: numeric, callback function: (none) */
#define  PANEL_3_Mean_2                   7       /* control type: numeric, callback function: (none) */
#define  PANEL_3_Min_Temp                 8       /* control type: numeric, callback function: (none) */
#define  PANEL_3_Max_Temp                 9       /* control type: numeric, callback function: (none) */

#define  PANEL_4                          4
#define  PANEL_4_TO                       2       /* control type: string, callback function: (none) */
#define  PANEL_4_Set_Alert                3       /* control type: command, callback function: Set_Alert_Func */
#define  PANEL_4_Back                     4       /* control type: command, callback function: Back2Func */
#define  PANEL_4_WarningTemp              5       /* control type: numeric, callback function: (none) */
#define  PANEL_4_TIMER1                   6       /* control type: timer, callback function: TimeCheckFunc */
#define  PANEL_4_STRING                   7       /* control type: string, callback function: (none) */

#define  PANEL_5                          5
#define  PANEL_5_Back3                    2       /* control type: command, callback function: Back3Func */
#define  PANEL_5_TEXTBOX                  3       /* control type: textBox, callback function: (none) */
#define  PANEL_5_PICTURE_2                4       /* control type: picture, callback function: (none) */
#define  PANEL_5_PICTURE_3                5       /* control type: picture, callback function: (none) */
#define  PANEL_5_PICTURE                  6       /* control type: picture, callback function: (none) */

#define  PANEL_6                          6
#define  PANEL_6_PASSWORD                 2       /* control type: string, callback function: Password_Func */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

#define  MENUBAR                          1
#define  MENUBAR_Graph                    2       /* callback function: Graph */
#define  MENUBAR_ITEM1                    3       /* callback function: Statistics */
#define  MENUBAR_Send_Email               4       /* callback function: Set_Alert */
#define  MENUBAR_MENU1                    5       /* callback function: About */


     /* Callback Prototypes: */

void CVICALLBACK About(int menubar, int menuItem, void *callbackData, int panel);
int  CVICALLBACK Back1Func(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Back2Func(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Back3Func(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK BackFunc(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK ConnectFunc(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK DeleteGraphFunc(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK DisconnectFunc(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Export_To_Excel_Func(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK FreezeFunc(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK GetStats_Func(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
void CVICALLBACK Graph(int menubar, int menuItem, void *callbackData, int panel);
int  CVICALLBACK Password_Func(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK PlotGraphFunc(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK QuitFunc(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SaveGraphFunc(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
void CVICALLBACK Set_Alert(int menubar, int menuItem, void *callbackData, int panel);
int  CVICALLBACK Set_Alert_Func(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
void CVICALLBACK Statistics(int menubar, int menuItem, void *callbackData, int panel);
int  CVICALLBACK take_data_func(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK TimeCheckFunc(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK TimerFunc(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK TimerGraphFunc(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif