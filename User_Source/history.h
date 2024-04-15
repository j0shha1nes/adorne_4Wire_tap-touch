
/*----------------------------------------------------------------------------
 *    ADORNE SOFTAP 4-WIRE DIMMER
 *----------------------------------------------------------------------------
 *    File Name: history.h
 *    Description: list of program modifications/updates/compile configurations 
 *     
 *----------------------------------------------------------------------------
 *    Notes:

12/8/2015
 Combined SoftTap (Switch) & Touch (CapSense) programs using conditional compile definiton of "SofTap"
 "SofTap" == 1 then Soft Tap interface else "SofTap" == 0 then Touch interface
 Setting is in file "history.h" in User_Source folder

SOFTAP PROCEDURE:
    Step1: If "SofTap" == 1 do the following changes
        Update the Schematic:
            1. Right click on CapSense module & select Disable (grayed out)
            2. Right click on Switch Inputs Main, Plus & Minue & select Enable (bold)
            
    Step2: then update the Drawing:
        a. Select & move SW_Main to P3.5
        b. Select & move SW_Plus to P3.6
        c. Select & move SW_Minus to P3.7
            
    NOTE:  The references to CapSense Buttons are greyed out in the drawing
    
    Step3: Save & Compile
 
TOUCH PROCEDURE:
    Step1: If "SofTap" == 0 do the following schematic changes
        a. Update the Schematic:
        b. Right click on CapSense module & select Enable (bold)
        c. Right click on Switch Inputs Main, Plus & Minus & select Disable (grayed out)
            
    Step2:  then update the Drawing:
        a. Select & move CapSense_1:Sns[0]\Button0_BTN to P3.5
        b. Select & move CapSense_1:Sns[1]\Button1_BTN to P3.6
        c. Select & move CapSense_1:Sns[2]\Button2_BTN to P3.7
            
    NOTE:  The references to Pushbutton digital inputs are greyed out in the drawing
    
    Step3: Save & Compile
        
 Optimize Program for size:
        Menu bar => Project => Building Settings => Compiler => Optimization
        select "SIZE" for minimal program code
          >> added *(volatile uint8_t *) to line 43 of CY8C4124.c to allow size optimization for touch design
        select "NONE" for debug that allows breakpoints/step thru
        
 Device Selection:
        In Workspace Explorer window, right click on the "Project" with the device in [######...#]
        then click on "device selector" & then select target device to program
        
 Added Git database for software revision control/change documentation "Git"
        Used only in folder "User_Source" to track user created files

        
May 17, 2016:
  
  LED Brightness 
        - added PWM using the relay offset timer changed to 50µS interval

  Minus Key Bug
        - Single press of the minus key when the Dimmer is in OFF mode results in Last Dimmer Level 
        (rather than minimum dimmer level)
        
  Current Measurement
        - Adjusted current measurement algorithm to respond to current observed only in the negative half cycle
        this was needed because at high current levels (2A < i < 10A) the sensor becomes saturated and the signal
        reduces significantly.
        
  Zero Cross Interrupt
        - Observed a failure of the Zero Cross interrupt to exist at the correct time of the AC wave consistently
        contacted Carl Finke to help with this error
        Conclusion: This ended up being a unique hardware issue that was not a software.
        
*/