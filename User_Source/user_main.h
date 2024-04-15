
/*----------------------------------------------------------------------------
 *    ADORNE SOFTAP 4-WIRE DIMMER
 *----------------------------------------------------------------------------
 *    File Name: user_main.h
 *    Description: Compilation options, global variables, constants, enums, 
 *       typedefs, and prototypes for public functions in user_main.c.  
 *----------------------------------------------------------------------------
 *    Notes:
 *    1. 
 *----------------------------------------------------------------------------
 *    This code is the property of P&S Division of Legrand Corporation.
 *    Copyright (c) 2013 - 2014 Legrand Corp. All rights reserved.
 *---------------------------------------------------------------------------*/   
//#include "RL78G12.h"    // maps pltform independent macros to RL78 G12 hardware
#include <cytypes.h>
#include <CY8C4124.h>
#include <project.h>


/*----------------------------------------------------------------------------
 *    Compilation options
 *---------------------------------------------------------------------------*/  
//#define FACTORY_DEFAULT // load eeprom with default values every power up
//#define DIM_PH_DEF   FWD   // default dimming mode from enum phases
//#define UL  // implements quicker fade on/off for compatibility with UL 
            // test equipment, comment out to compile for standard production       
 
#define SofTap                  1 // softTap = (1) or Touch = (0)
#define OvrldEndurance          0 // Overload & Endurance Testing = (1) or Production = (0)
#define Wdog_Enable             1 // Enable Watchdog = (1) Disable Watchdog = (0)

/*----------------------------------------------------------------------------
 *    Constants, Macros, Enums
 *---------------------------------------------------------------------------*/  
#define FOREVER                 1

#define TRUE                    1
#define FALSE                   0

#define HIGH                    1
#define LOW                     0

#define LOW_8BIT                0x00

#define SET                     1
#define CLEAR                   0

#define SW_RELEASED             1
#define SW_PRESSED              0

//Display stuff
#define UI_MTRX_LIMIT           9  // 9 comes from the 3x3 matrix of LEDs

#define zc_test_min           308  //
#define zc_test_max           362  //


#define pushbutton_interval   200  //number of 1.11mS timer ticks required before the pushbuttons are read
#if(OvrldEndurance == 1)
#define fade_interval           1  //number of pushbutton intervals (11.1mS) used to change PWM_Value toward target
#else
#define fade_interval           7  //number of pushbutton intervals (11.1mS) used to change PWM_Value toward target
#endif
#define autorepeat              2  //number of 100mS intervals need to autorepeat
#define dimmer_adjust_interval  5  //number of pushbutton intervals (11.1mS) used to change the PWM_Value when up/down button held_on

#define gotobed_interval        2  //number of 100mS timer intervals used to qualify the 'goto bed' state
#define pwm_100mS_count      2000  //number of pwm iterations needed to reach 100mS of time
#define gotobed_totaltime      25  //time in seconds over which the fade for "gotobed" occurs
#define gotobed_scalefactor    10  //this is 100mS timer frequency
#define flash_threshold         3  //number of 100mS timer intervals used to flash the top LED when entering Gotobed mode
#define one_second_interval    60  //number of zero crosses that equals one second of time

#if(SofTap == 1)
#define pb_debounce_press       5  // button must be pressed for at least these number of tick counts
#define pb_debounce_release     5  // button must be released for at least 5 tick counts
#else
#define pb_debounce_press       1  // CapSense does debounce
#define pb_debounce_release     1  // CapSense does debounce
#endif

#define LED_upper_limit        10  // LED's are 1-9
#define LED_lower_limit         0  // LED's are 1-9
#define LED_plus                8  // Plus is always on when any one of 1-7 are on
#define LED_minus               9  // Minus is always on when any one of 1-7 are on
#define desired_dim_levels     32  // number of desired dimming levels 
#define ui_limit               11  // number of PWM intervals needed to make the User Interface interrupt; not sure this will be used
#define user_interface_levels   8  // user interface can vary from 0 - 7; therefore 8 levels
#define translation_factor      5  // used in the computation to translate the dim levels (32) to user interface levels (8)

#define full_cycle_count      300  // Maximum number of complete PWM iterations in a full cycle; 16.667mS/1mS ~ 16.7 -> round down to 15
#define half_cycle_count        7  // Number of complete PWM iterations in a half cycle; 8.333mS/1mS ~ 8.33 -> round down to 7
#define i_sense_threshold      40  // Number of Zero Crosses counted before dimmer is deemed "on"
#define max_current_sense       8  // Max number the current sense can be (measured in neg half cycle only every 1mS)
#define i_sense_off             0  // Off threshold for i_sense_acc
#define i_presence_threshold_hi 1  // this threshold determines whether load current is present or not; it is compared to a counter that increment 
                                   // every 1.11mS only if current is present, the comparison is made at every zero cross
// the higher the max, the lower the output transistor resistance
#define PWM_upper_min_limit   545  // highest value the PWM_MIN can be set in calibration
#define PWM_min_default       545  // default, minimum value that the PWM can be
#define PWM_lower_min_limit   257  // lowest value the PWM_MIN can be set in calibration
#define PWM_min_cal_chg        32  // amount each main button press changes the output

// the lower the min, the higher the output transistor resistance
#define PWM_upper_max_limit   225  // highest value the PWM_MAX can be set in calibration
#define PWM_max_fine_mode      70  // below this threshold the cal change is fine mode
#define PWM_max_default         1  // default, maximum value that the PWM can be
#define PWM_lower_max_limit     1  // lowest value the PWM_MAX can be set in calibration
#define PWM_max_cal_chg        32  // amount each main button press changes the output
#define PWM_max_cal_chg_fine    8  // amount each main button press changes the output in fine mode

#define PWM_chg_default         8  // default, single press of up or down will result in this change
#define cal_key_value          27  // when read from the EEPROM, this means that the EEPROM has been written
#define PWM_cal_count_limit    10  // number of seconds required before calibration can be entered
#define PWM_cal_count_release  10  // number of seconds (of inactivity) required before calibration is released

#define PWM_display_interval  100  // number of PWM counts used to attentuate the display

#if(SofTap == 1)
#define PWM_display_on_off      5  // number of PWM counts for the on/off display; sofTap value 
#define PWM_display_bargraph    40  // number of PWM counts for the dimmer display; sofTap value
#define PWM_display_plusminus   40  // number of PWM counts for the dimmer display; sofTap value
#else
#define PWM_display_on_off      5  // number of PWM counts for the on/off display; touch value
#define PWM_display_bargraph    4  // number of PWM counts for the bargraph
#define PWM_display_plusminus   75  // number of PWM counts for the plus and minus
#endif

#define relay_delay_1p         50  // this is the on-time (measured in iterations of a 50uS timer) for the relay coils
#define relay_delay_3w         55  // this is the on-time (measured in iterations of a 50uS timer) for the relay coils
#define dead_zone               3  // number of 100mS periods used to prohibit relay triggers after a previous relay fire
#define pwm_multiple_1         19  //
#define pwm_multiple_2         39  //
#define pwm_multiple_3         59  //
#define pwm_multiple_4         79  //
#define pwm_multiple_5         99  //

#define Relay_coil_active     500  // number of Timer2 iterations that the coil will be powered

#if(OvrldEndurance == 1)
#define double_tap_interval   200  //number of pushbutton intervals (11.1mS) used to change PWM_Value toward target
#else
#define double_tap_interval   750  //number of pushbutton intervals (11.1mS) used to change PWM_Value toward target
#endif

   
// nonvolatile calibration values - index into nonvolatile buffer array
enum non_vol_vals {
        Cal_Key,
        PWM_Min_Low,   
        PWM_Min_High,
        PWM_Max_Low,
        PWM_Max_High,
        PWM_Trgt_Low,
        PWM_Trgt_High
};
// pushbuttons
enum pushbuttons {PB_MAIN, PB_UP, PB_DOWN};

/*----------------------------------------------------------------------------
 *    Typedefs
 *---------------------------------------------------------------------------*/

typedef struct pushbutton_status {
   uint8_t switched_on:     1;    //
   uint8_t held_on:         1;    //a push button is pressed for a time greater than a predetermined interval
   uint8_t switched_off:    1;    //nothing is pressed
   uint8_t held_off:        1;
} pb_status_t;    

typedef struct timer_status {
   uint8_t tick:            1;    //SET in every iteration of the tick timer, cleared in main loop when tick timer tasks are complete
   uint8_t pwmtick:         1;    //Set in every PWM timer iteration
   uint8_t second:          1;    //SET every second
   uint8_t zc_tick:         1;    //SET every zero cross
   uint8_t gp_100mS_tick:   1;    //SET every 100mS
   uint8_t single_tap:      1;
   uint8_t pos_half:        1;
   uint8_t neg_half:        1;
   uint8_t ovldend_bug:     1;
} tmr_status;

typedef struct dmr_status {
   uint16_t on:             1;    //SET when dimmer is on
   uint16_t off:            1;    //SET when dimmer is off
   uint16_t fade_on:        1;    //SET when transitioning from off to on
   uint16_t fade_off:       1;    //SET when transitioning from on to off
   uint16_t goto_bed:       1;    //SET when main button held for more than 4s, then fades off over a 25s period
   uint16_t flash:          1;    //Part of the goto_bed routine where the top LED flashes
   uint16_t single_pole:    1;    //An arbitrary assignment of relay position to the single-pole throw
   uint16_t three_way:      1;    //An arbitrary assignment of relay position to the three-way throw
   uint16_t coilactive:     1;
   uint16_t throwrelay:     1;    //SET when a request to throw the relay is made
   uint16_t store_status:   1;    //SET when an important value changes and needs to be stored in EEprom
   uint16_t mincalibration: 1;
   uint16_t maxcalibration: 1;
   uint16_t min_cal_adjust: 1;    //SET when cal mode is entered and button is released
   uint16_t max_cal_adjust: 1;    //SET when cal mode is entered and button is released
} dimmer_status;

#if(SofTap == 0)
typedef struct captouch_status {
   uint8_t ON_SWCPS:          1;    // On/Off key status - CapTouch detection
   uint8_t UP_SWCPS:          1;    // Up key status - CapTouch detection
   uint8_t DN_SWCPS:          1;    // Down key status - CapTouch detection
} ct_status_t;
#endif

   
/*----------------------------------------------------------------------------
 *  Global Variables
 *---------------------------------------------------------------------------*/ 
#ifdef _MAIN_C // global variable declarations will be included in main.c
#define var_loc
#else          // extern declarations will be included in other modules
#define var_loc  extern
#endif

var_loc uint8_t  UI_CNTR;         // counts the strobe iteration user interface LEDs
var_loc uint16_t UI_VAL;          // counts the strobe iteration user interface LEDs
var_loc uint16_t ZC_TEST;         // counts the strobe iteration user interface LEDs
var_loc uint8_t  MCU_OSC_ACC;     // counts the strobe iteration user interface LEDs

var_loc uint8_t  PB_INTERVAL_TICK;// counts the ticks of Timer2 (1.111mS timer period)
var_loc uint8_t  ZC_CNTR;         // counts the ticks of Timer3 (100mS timer period)
var_loc uint8_t  SECOND_CNTR;     // counts the ticks of Timer2 (1.111mS timer period)
var_loc uint8_t  UI_TICK_CNT;     // counts the ticks of Timer3 (100mS timer period)
var_loc uint8_t  FADE_CNT;        // increments every time the tick counter reaches the pushbutton_interval
var_loc uint8_t  DMR_ADJ_CNT;     // increments every 10th iteration of Timer2 ticks when a button is held_on

var_loc uint16_t TICK_CNT;       // increments every iteration of Timer2 interrupt is serviced and is reset at the zero cross interrupt
var_loc uint16_t TICK_CNT_100mS; // counts the # of PWM iterations up to 100, then resets
var_loc uint16_t TICK_DBL_TAP;   // counts the # of PWM iterations to form a double tap interval
var_loc uint8_t  TICK_CNT_Display; // counts PWM iterations to attentuate the display

var_loc uint8_t  I_SENSE_CNT;    // increments every time I_Sense input is high every ZC period (min = 0/1; max = 7/8)
var_loc uint16_t I_SENSE_ACC;    // accummulates presence of current using the I_SENSE_CNT measurements

var_loc uint16_t RELAY_CNT;      // counts the Timer2 interrupts used to 'pulse' the latching relay
var_loc uint8_t  RELAY_OFFSET;   // holds the offset from zero cross at which time the latching relay is activated
var_loc uint8_t  Nuisance_Trigger; // counts 100mS periods to create a dead_zone after any relay trigger

var_loc uint8_t  GOTO_BED_INTERVAL;  //holds the goto bed interval based on the PWM_Value at the time of state entry
var_loc uint8_t  FLASH_CNT;       // counts 100mS intervals to create the 2Hz flash rate

var_loc uint16_t PWM_CURRENT;     // Maximum PWM value
var_loc uint16_t PWM_MAX;         // Maximum PWM value
var_loc uint16_t PWM_CHG;         // Given that the range of PWM can change, so might the 
                                  // the amount of change need to adjust to keep the number
                                  // of steps from MIN to MAX constant
var_loc uint16_t PWM_MIN;         // Minimum PWM value
var_loc uint16_t PWM_TARGET;      // Actual preset target, this is the value that the dimmer will fade from/to
var_loc uint16_t PWM_CAL_CNT;     // Counts the seconds that 
var_loc uint8_t volatile  NON_VOL_A[A_SIZE];

var_loc uint8_t  RELAY_STATE;            // stores state of latching relay 
// Note: Two switch times are needed, one for each relay throw

// pushbutton status  
var_loc pb_status_t   PB_Status[3];    
var_loc tmr_status    TMR_Status;
var_loc dimmer_status DMR_Status;

#if(SofTap == 0)
    var_loc ct_status_t CT_Status;
#endif

/*----------------------------------------------------------------------------
 *  Function Prototypes
 *---------------------------------------------------------------------------*/ 
int main(void);
void init_dimmer_status(void);
void gp_100mS_timer(void);

#if (SofTap == 0)
    void CapTouch_Scan(void);
#endif
    