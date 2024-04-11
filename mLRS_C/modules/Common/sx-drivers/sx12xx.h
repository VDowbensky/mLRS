//*******************************************************
// Copyright (c) MLRS project
// GPL3
// https://www.gnu.org/licenses/gpl-3.0.de.html
// OlliW @ www.olliw.eu
//*******************************************************
// SX12XX shim
//*******************************************************
#ifndef SX12XX_H
#define SX12XX_H

#include "common_conf.h"
#include "device_conf.h"

#if defined DEVICE_HAS_SX126x || defined DEVICE_HAS_DUAL_SX126x_SX126x
#include "sx126x.h"
#elif defined DEVICE_HAS_SX127x
#include "sx127x.h"
#elif defined DEVICE_HAS_DUAL_SX126x_SX128x
#include "sx126x.h"
#include "sx128x.h"
#else
#include "sx128x.h"
#endif


#endif // SX12XX_H
