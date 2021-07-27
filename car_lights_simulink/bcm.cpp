/*
 * File: bcm.c
 *
 * Code generated for Simulink model 'bcm'.
 *
 * Model version                  : 7.38
 * Simulink Coder version         : 9.4 (R2020b) 29-Jul-2020
 * C/C++ source code generated on : Wed Jul 28 02:39:46 2021
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
  boolean_T rtb_Merge1;

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

  /* Outputs for Enabled SubSystem: '<Root>/Enabled Subsystem1' incorporates:
   *  EnablePort: '<S4>/Enable'
   */
  /* Outputs for IfAction SubSystem: '<S4>/If Action Subsystem3' incorporates:
   *  ActionPort: '<S10>/Action Port'
   */
  /* Outputs for IfAction SubSystem: '<S4>/If Action Subsystem2' incorporates:
   *  ActionPort: '<S9>/Action Port'
   */
  /* If: '<S4>/If1' incorporates:
   *  Inport: '<Root>/emergence_switch1'
   *  Inport: '<Root>/turn_left_switch'
   *  Inport: '<S10>/In1'
   *  Inport: '<S9>/In1'
   */
  rtb_Merge1 = ((!bcm_U.emergence_switch1) && bcm_U.turn_left_switch);

  /* End of Outputs for SubSystem: '<S4>/If Action Subsystem2' */
  /* End of Outputs for SubSystem: '<S4>/If Action Subsystem3' */

  /* Logic: '<S4>/Logical Operator' incorporates:
   *  Inport: '<Root>/emergence_switch1'
   */
  rtb_Compare = (bcm_U.emergence_switch1 || rtb_Merge1);

  /* If: '<S4>/If2' incorporates:
   *  Inport: '<Root>/emergence_switch1'
   *  Inport: '<Root>/turn_right_switch'
   *  Logic: '<S4>/Logical Operator1'
   */
  rtb_Merge1 = (bcm_U.emergence_switch1 || ((!rtb_Merge1) &&
    bcm_U.turn_right_switch));

  /* End of Outputs for SubSystem: '<Root>/Enabled Subsystem1' */

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
    if (rtb_Merge1 && (bcm_DW.temporalCounter_i1 >= 50)) {
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
  if (rtb_Merge1) {
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
