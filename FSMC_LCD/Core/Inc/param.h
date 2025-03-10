/*
 * param.h
 *
 *  Created on: Mar 7, 2025
 *      Author: compro
 */

#ifndef INC_PARAM_H_
#define INC_PARAM_H_

typedef struct
{
	uint32_t ParamVer;
	uint8_t ucBackLight;

	uint16_t usAdcX1;
	uint16_t usAdcY1;
	uint16_t usAdcX2;
	uint16_t usAdcY2;
	uint16_t usAdcX3;
	uint16_t usAdcY3;
	uint16_t usAdcX4;
	uint16_t usAdcY4;
	uint16_t XYChange;

	uint8_t uip_ip[4];
	uint8_t uip_net_mask[4];
	uint8_t uip_net_gate[4];

	uint8_t lwip_ip[4];
	uint8_t lwip_net_mask[4];
	uint8_t lwip_net_gate[4];

	uint8_t ucRadioMode;
	uint8_t ucRadioListType;
	uint8_t ucIndexFM;
	uint8_t ucIndexAM;
	uint8_t ucRadioVolume;
	uint8_t ucSpkOutEn;
}
PARAM_T;

extern PARAM_T g_tParam;

#endif /* INC_PARAM_H_ */
