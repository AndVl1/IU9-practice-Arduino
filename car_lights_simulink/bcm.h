/*
 * File: bcm.h
 *
 * Code generated for Simulink model 'bcm'.
 *
 * Model version                  : 7.42
 * Simulink Coder version         : 9.4 (R2020b) 29-Jul-2020
 * C/C++ source code generated on : Fri Jul 30 01:55:50 2021
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Atmel->AVR (8-bit)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_bcm_h_
#define RTW_HEADER_bcm_h_
#include <string.h>
#include <stddef.h>
#ifndef bcm_COMMON_INCLUDES_
#define bcm_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* bcm_COMMON_INCLUDES_ */

/* Model Code Variants */

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* Forward declaration for rtModel */
typedef struct tag_RTM_bcm_T RT_MODEL_bcm_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  uint16_T temporalCounter_i1;         /* '<S1>/Chart' */
  uint8_T is_active_c2_bcm;            /* '<S1>/Chart' */
  uint8_T is_c2_bcm;                   /* '<S1>/Chart' */
} DW_bcm_T;

/* External inputs (root inport signals with default storage) */
typedef struct {
  boolean_T running_switch;            /* '<Root>/running_switch' */
  boolean_T emergence_switch1;         /* '<Root>/emergence_switch1' */
  uint16_T stop_signal_input;          /* '<Root>/stop_signal_input' */
  boolean_T turn_left_switch;          /* '<Root>/turn_left_switch' */
  boolean_T turn_right_switch;         /* '<Root>/turn_right_switch' */
  uint16_T stop_min_value;             /* '<Root>/stop_min_value' */
  uint16_T intensivity;                /* '<Root>/intensivity' */
  uint8_T running_intensivity;         /* '<Root>/running_intensivity' */
} ExtU_bcm_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  uint8_T running_LED_1;               /* '<Root>/running_LED_1' */
  uint8_T running_LED_2;               /* '<Root>/running_LED_2' */
  uint8_T turning_LED_1;               /* '<Root>/turning_LED_1' */
  uint8_T turning_LED_2;               /* '<Root>/turning_LED_2' */
  boolean_T stop_LED;                  /* '<Root>/stop_LED' */
} ExtY_bcm_T;

/* Real-time Model Data Structure */
struct tag_RTM_bcm_T {
  const char_T * volatile errorStatus;
};

/* Block states (default storage) */
extern DW_bcm_T bcm_DW;

/* External inputs (root inport signals with default storage) */
extern ExtU_bcm_T bcm_U;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY_bcm_T bcm_Y;

/* Model entry point functions */
extern void bcm_initialize(void);
extern void bcm_step(void);
extern void bcm_terminate(void);

/* Real-time Model object */
extern RT_MODEL_bcm_T *const bcm_M;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'bcm'
 * '<S1>'   : 'bcm/Blink_Generator 2'
 * '<S2>'   : 'bcm/Enabled Subsystem1'
 * '<S3>'   : 'bcm/Blink_Generator 2/Chart'
 * '<S4>'   : 'bcm/Enabled Subsystem1/If Action Subsystem'
 * '<S5>'   : 'bcm/Enabled Subsystem1/If Action Subsystem1'
 * '<S6>'   : 'bcm/Enabled Subsystem1/If Action Subsystem2'
 * '<S7>'   : 'bcm/Enabled Subsystem1/If Action Subsystem3'
 * '<S8>'   : 'bcm/Enabled Subsystem1/If Action Subsystem4'
 * '<S9>'   : 'bcm/Enabled Subsystem1/If Action Subsystem5'
 */
#endif                                 /* RTW_HEADER_bcm_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
