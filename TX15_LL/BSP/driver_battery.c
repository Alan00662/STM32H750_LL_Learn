
#include "driver_battery.h"
#include "hal.h"
#include "adc.h"

enum {
  ADC_INPUT_MAIN=0, // gimbals / wheel + throttle
  ADC_INPUT_FLEX,
  ADC_INPUT_VBAT,
  ADC_INPUT_RTC_BAT,
  ADC_INPUT_ALL,
};

typedef struct  {
  const char* name;
  const char* label;
  const char* short_label;
}etx_hal_adc_input_t;

typedef struct  {
  uint8_t                    n_inputs;
  uint8_t                    offset;
  const etx_hal_adc_input_t* inputs;
}etx_hal_adc_inputs_t;

const etx_hal_adc_inputs_t* _hal_adc_inputs = NULL;

void adcInit(void)
{
	MX_ADC1_Init();
		MX_ADC3_Init();
}
uint8_t adcGetMaxInputs(uint8_t type)
{
  if (type > ADC_INPUT_ALL) return 0;
  return _hal_adc_inputs[type].n_inputs;
}

// used by diaganas
uint32_t s_anaFilt[14];
#define ANALOG_MULTIPLIER (1 << 1)
#define JITTER_FILTER_STRENGTH  4
#define JITTER_ALPHA            (1<<JITTER_FILTER_STRENGTH)

#define ANA_FILT(chan)    (s_anaFilt[chan] / (JITTER_ALPHA * ANALOG_MULTIPLIER))

uint16_t anaIn(uint8_t chan)
{
  if (chan >= 14) return 0;
  return ANA_FILT(chan);
}

uint8_t adcGetInputOffset(uint8_t type)
{
  if (type > ADC_INPUT_ALL) return 0;
  return _hal_adc_inputs[type].offset;
}

uint16_t getBatteryVoltage(void)
{
  // using filtered ADC value on purpose
  if (adcGetMaxInputs(ADC_INPUT_VBAT) < 1) return 0;
  int32_t instant_vbat = anaIn(adcGetInputOffset(ADC_INPUT_VBAT));
	
//  return (uint16_t)((instant_vbat * (1000 + g_eeGeneral.txVoltageCalibration)) /
//                    BATTERY_DIVIDER);
}
