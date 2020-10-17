#ifndef OPERATIONFIELD_H
#define OPERATIONFIELD_H

#define No_Operation          0
#define Video_Start           1
#define Video_Stop            2
#define Manual_Play           3
#define Photo_Graph           4
#define Set_Plus_True         5
#define Set_Plus_False        6
#define Denoise_Not           7
#define Denoise_One           8
#define Global_Info_Hide      9
#define Global_Info_Show      10
#define Global_Point_Hide     11
#define Global_Point_Show     12
#define Gear_One              13
#define Gear_Two              14
#define Image_Thaw            15
#define Image_Free            16
#define Infrared_Iron         17
#define Infrared_Ironinv      18
#define Infrared_Rainbow      19
#define Infrared_Feather      20
#define Infrared_Greyinv      21
#define Infrared_Grey         22
#define Save_Model_Data       23
#define Set_Fid               24
#define Set_Gsk               25
#define Set_Gain              26
#define Set_Int               27
#define Save_Arg              28
#define Auto_Shutter_On       29
#define Auto_Shutter_Off      30
#define Auto_Shutter_Time     31
#define Serial_Number         32
#define Set_Fac_Year          33
#define Set_Fac_Month         34
#define Set_Fac_Day           35
#define BadPoint_Query        36
#define BadPoint_SetPos       37
#define BadPoint_Cal          38
#define Save_KTable           39
#define Set_Window_Normal     40
#define Set_Window_BadPoint   41
#define Set_Window_Collect    42
#define Collect1_SetPos       43
#define Collect2_SetPos       44
#define Adjust_On             45
#define Adjust_Off            46
#define Clear_KTable          47
#define Adjust_LowTemp        48
#define Adjust_HighTemp       49
#define Shutter_Inside        50
#define Shutter_Outside       51
#define Center_Info_Hide      52
#define Center_Info_Show      53
#define Update_TempAd_Table   54
#define Effect_TempAd_Table   55
#define Table_To_SD           56
#define SD_To_Table           57
#define Area_Indicator_On     58
#define Area_Indicator_Off    59
#define Laser_On              60
#define Laser_Off             61
#define Set_Schema            62
#define AutoInt_On            63
#define AutoInt_Off           64

#define Set_Dis               65
#define Set_Emiss             66
#define Set_EnvTemp           67
#define Set_RelHum            68
#define Set_RefTemp           69
#define Set_CorTemp           70



#define Set_RecordArg_On      71
#define Set_RecordArg_Off     72


#define Set_SavePhotoTime     73
#define Set_SavePhotoSign_On  79
#define Set_SavePhotoSign_Off 80

#define Reset_Param           74

#define Set_Length_Meter      75
#define Set_Length_Foot       76
#define Set_Temp_Celsius      77
#define Set_Temp_Fahrenheit   78

#define ShutDown              81
#define Save_Param            82
#define Read_Param            83
#define Backup_App            84
#define Update_App            85
#define Recovery_App          86

#define Set_UpdateAppState    87


#define Open_Correct_Widget   100



//==========更新程序界面的状态标记===========


#define Update_App_State_Hide              1000  /*提示界面不显示*/
#define Update_App_State_Backuping         1001  /*正在备份*/
#define Update_App_State_Backup_Success    1002  /*备份成功*/
#define Update_App_State_Backup_Failure    1003  /*备份失败*/
#define Update_App_State_Updating          1004  /*正在更新*/
#define Update_App_State_Update_Failure    1005  /*更新失败*/
#define Update_App_State_Update_Reboot     1006  /*更新成功，重启*/
#define Update_App_State_Recoverying       1007  /*正在恢复备份版本*/
#define Update_App_State_Recovery_Failure  1008  /*恢复失败（无备份版本、恢复中出错）*/
#define Update_App_State_Recovery_Success  1009  /*恢复成功，重启*/
















#endif // OPERATIONFIELD_H
