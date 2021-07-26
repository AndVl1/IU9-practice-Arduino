/*
 * File: bcm.c
 *
 * Code generated for Simulink model 'bcm'.
 *
 * Model version                  : 7.27
 * Simulink Coder version         : 9.4 (R2020b) 29-Jul-2020
 * C/C++ source code generated on : Mon Jul 26 03:17:42 2021
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Atmel->AVR (8-bit)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "bcm.h"

/* Named constants for Chart: '<S1>/Chart' */
#define bcm_IN_NO_ACTIVE_CHILD         ((uint8_T)0U)
#define bcm_IN_StateHigh               ((uint8_T)1U)
#define bcm_IN_StateLow                ((uint8_T)2U)

/* Block states (default storage) */
DW_bcm_T bcm_DW;

/* External inputs (root inport signals with default storage) */
ExtU_bcm_T bcm_U;

/* External outputs (root outports fed by signals with default storage) */
ExtY_bcm_T bcm_Y;

/* Real-time model */
static RT_MODEL_bcm_T bcm_M_;
RT_MODEL_bcm_T *const bcm_M = &bcm_M_;

/* Model step function */
void bcm_step(void)
{
  uint8_T rtb_Switch3;
  boolean_T rtb_Compare;

  /* RelationalOperator: '<S3>/Compare' incorporates:
   *  Constant: '<S3>/Constant'
   *  Inport: '<Root>/stop_signal_input'
   */
  rtb_Compare = (bcm_U.stop_signal_input >= 307U);

  /* Switch: '<Root>/Switch2' incorporates:
   *  Constant: '<Root>/Constant1'
   *  Constant: '<Root>/Constant4'
   *  Inport: '<Root>/running_switch'
   *  Switch: '<Root>/Switch'
   */
  if (rtb_Compare) {
    rtb_Switch3 = 0U;
  } else if (bcm_U.running_switch) {
    /* Switch: '<Root>/Switch' incorporates:
     *  Constant: '<Root>/Constant'
     */
    rtb_Switch3 = 180U;
  } else {
    rtb_Switch3 = MAX_uint8_T;
  }

  /* End of Switch: '<Root>/Switch2' */

  /* Outport: '<Root>/running_LED_1' */
  bcm_Y.running_LED_1 = rtb_Switch3;

  /* Outport: '<Root>/running_LED_2' */
  bcm_Y.running_LED_2 = rtb_Switch3;

  /* Outport: '<Root>/stop_LED' incorporates:
   *  Logic: '<Root>/Logical Operator2'
   */
  bcm_Y.stop_LED = !rtb_Compare;

  /* Logic: '<Root>/Logical Operator' incorporates:
   *  Inport: '<Root>/emergence_switch1'
   *  Inport: '<Root>/turn_left_switch'
   */
  rtb_Compare = (bcm_U.turn_left_switch || bcm_U.emergence_switch1);

  /* Outputs for Enabled SubSystem: '<Root>/Blink_Generator ' incorporates:
   *  EnablePort: '<S1>/Enable'
   */
  /* Chart: '<S1>/Chart' */
  if (bcm_DW.temporalCounter_i1_j < 63U) {
    bcm_DW.temporalCounter_i1_j++;
  }

  if (bcm_DW.is_active_c3_bcm == 0U) {
    bcm_DW.is_active_c3_bcm = 1U;
    bcm_DW.is_c3_bcm = bcm_IN_StateHigh;
    bcm_DW.temporalCounter_i1_j = 0U;
    rtb_Switch3 = 1U;
  } else if (bcm_DW.is_c3_bcm == bcm_IN_StateHigh) {
    rtb_Switch3 = 1U;
    if (rtb_Compare && (bcm_DW.temporalCounter_i1_j >= 50)) {
      bcm_DW.is_c3_bcm = bcm_IN_StateLow;
      bcm_DW.temporalCounter_i1_j = 0U;
      rtb_Switch3 = 0U;
    }
  } else {
    /* case IN_StateLow: */
    rtb_Switch3 = 0U;
    if (bcm_DW.temporalCounter_i1_j >= 50) {
      bcm_DW.is_c3_bcm = bcm_IN_StateHigh;
      bcm_DW.temporalCounter_i1_j = 0U;
      rtb_Switch3 = 1U;
    }
  }

  /* End of Chart: '<S1>/Chart' */
  /* End of Outputs for SubSystem: '<Root>/Blink_Generator ' */

  /* Switch: '<Root>/Switch1' */
  if (rtb_Compare) {
    /* Outport: '<Root>/turning_LED_1' */
    bcm_Y.turning_LED_1 = rtb_Switch3;
  } else {
    /* Outport: '<Root>/turning_LED_1' incorporates:
     *  Constant: '<Root>/Constant3'
     */
    bcm_Y.turning_LED_1 = 1U;
  }

  /* End of Switch: '<Root>/Switch1' */

  /* Logic: '<Root>/Logical Operator1' incorporates:
   *  Inport: '<Root>/emergence_switch1'
   *  Inport: '<Root>/turn_right_switch'
   */
  rtb_Compare = (bcm_U.emergence_switch1 || bcm_U.turn_right_switch);

  /* Outputs for Enabled SubSystem: '<Root>/Blink_Generator 1' incorporates:
   *  EnablePort: '<S2>/Enable'
   */
  /* Chart: '<S2>/Chart' */
  if (bcm_DW.temporalCounter_i1 < 63U) {
    bcm_DW.temporalCounter_i1++;
  }

  if (bcm_DW.is_active_c1_bcm == 0U) {
    bcm_DW.is_active_c1_bcm = 1U;
    bcm_DW.is_c1_bcm = bcm_IN_StateHigh;
    bcm_DW.temporalCounter_i1 = 0U;
    rtb_Switch3 = 1U;
  } else if (bcm_DW.is_c1_bcm == bcm_IN_StateHigh) {
    rtb_Switch3 = 1U;
    if (rtb_Compare && (bcm_DW.temporalCounter_i1 >= 50)) {
      bcm_DW.is_c1_bcm = bcm_IN_StateLow;
      bcm_DW.temporalCounter_i1 = 0U;
      rtb_Switch3 = 0U;
    }
  } else {
    /* case IN_StateLow: */
    rtb_Switch3 = 0U;
    if (bcm_DW.temporalCounter_i1 >= 50) {
      bcm_DW.is_c1_bcm = bcm_IN_StateHigh;
      bcm_DW.temporalCounter_i1 = 0U;
      rtb_Switch3 = 1U;
    }
  }

  /* End of Chart: '<S2>/Chart' */
  /* End of Outputs for SubSystem: '<Root>/Blink_Generator 1' */

  /* Switch: '<Root>/Switch3' */
  if (rtb_Compare) {
    /* Outport: '<Root>/turning_LED_2' */
    bcm_Y.turning_LED_2 = rtb_Switch3;
  } else {
    /* Outport: '<Root>/turning_LED_2' incorporates:
     *  Constant: '<Root>/Constant3'
     */
    bcm_Y.turning_LED_2 = 1U;
  }

  /* End of Switch: '<Root>/Switch3' */
}

/* Model initialize function */
void bcm_initialize(void)
{
  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatus(bcm_M, (NULL));

  /* states (dwork) */
  (void) memset((void *)&bcm_DW, 0,
                sizeof(DW_bcm_T));

  /* external inputs */
  (void)memset(&bcm_U, 0, sizeof(ExtU_bcm_T));

  /* external outputs */
  (void) memset((void *)&bcm_Y, 0,
                sizeof(ExtY_bcm_T));

  /* SystemInitialize for Enabled SubSystem: '<Root>/Blink_Generator ' */
  /* SystemInitialize for Chart: '<S1>/Chart' */
  bcm_DW.temporalCounter_i1_j = 0U;
  bcm_DW.is_active_c3_bcm = 0U;
  bcm_DW.is_c3_bcm = bcm_IN_NO_ACTIVE_CHILD;

  /* End of SystemInitialize for SubSystem: '<Root>/Blink_Generator ' */

  /* SystemInitialize for Enabled SubSystem: '<Root>/Blink_Generator 1' */
  /* SystemInitialize for Chart: '<S2>/Chart' */
  bcm_DW.temporalCounter_i1 = 0U;
  bcm_DW.is_active_c1_bcm = 0U;
  bcm_DW.is_c1_bcm = bcm_IN_NO_ACTIVE_CHILD;

  /* End of SystemInitialize for SubSystem: '<Root>/Blink_Generator 1' */
}

/* Model terminate function */
void bcm_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
