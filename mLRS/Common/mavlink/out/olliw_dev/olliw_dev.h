//------------------------------
// The fastMavlink library
// (c) OlliW, OlliW42, www.olliw.eu
//------------------------------

#pragma once
#ifndef FASTMAVLINK_OLLIW_DEV_H
#define FASTMAVLINK_OLLIW_DEV_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef FASTMAVLINK_BUILD_DATE
#define FASTMAVLINK_BUILD_DATE  "Wed Mar 27 2024"
#endif

#ifndef FASTMAVLINK_DIALECT_VERSION
#define FASTMAVLINK_DIALECT_VERSION  0  // this is the version specified in the dialect xml file
#endif


//------------------------------
//-- Message credentials
//-- The values of msg_entry_t for all messages in the dialect.
//-- msgid, extra crc, max length, flag, target sysid offset, target compid offset
//------------------------------

#include "olliw_dev_msg_entries.h"

#ifndef FASTMAVLINK_MESSAGE_CRCS
#define FASTMAVLINK_MESSAGE_CRCS  FASTMAVLINK_MSG_ENTRIES
#endif


//------------------------------
//-- FastMavlink lib
//------------------------------

#include "../lib/fastmavlink.h"

#ifdef FASTMAVLINK_PYMAVLINK_ENABLED
#include "../lib/fastmavlink_pymavlink.h"
#endif


//------------------------------
//-- Enum definitons
//------------------------------

#ifndef FASTMAVLINK_TEST_EXCLUDE_ENUMS

#ifndef FASTMAVLINK_HAS_ENUM_RADIO_LINK_STATS_FLAGS_DEV
#define FASTMAVLINK_HAS_ENUM_RADIO_LINK_STATS_FLAGS_DEV
typedef enum RADIO_LINK_STATS_FLAGS_DEV {
    RADIO_LINK_STATS_FLAGS_RSSI_DBM_DEV = 1,  // Rssi values are in negative dBm. Values 0..253 corresponds to 0..-253 dBm. 254 represents no link connection. 
    RADIO_LINK_STATS_FLAGS_DEV_ENUM_END = 2,  // end marker
} RADIO_LINK_STATS_FLAGS_DEV;
#endif


#ifndef FASTMAVLINK_HAS_ENUM_RADIO_LINK_TYPE_DEV
#define FASTMAVLINK_HAS_ENUM_RADIO_LINK_TYPE_DEV
typedef enum RADIO_LINK_TYPE_DEV {
    RADIO_LINK_TYPE_GENERIC_DEV = 0,  // Unknown radio link type. 
    RADIO_LINK_TYPE_HERELINK_DEV = 1,  // Radio link is HereLink. 
    RADIO_LINK_TYPE_DRAGONLINK_DEV = 2,  // Radio link is Dragon Link. 
    RADIO_LINK_TYPE_RFD900_DEV = 3,  // Radio link is RFD900. 
    RADIO_LINK_TYPE_CROSSFIRE_DEV = 4,  // Radio link is Crossfire. 
    RADIO_LINK_TYPE_EXPRESSLRS_DEV = 5,  // Radio link is ExpressLRS. 
    RADIO_LINK_TYPE_MLRS_DEV = 6,  // Radio link is mLRS. 
    RADIO_LINK_TYPE_DEV_ENUM_END = 7,  // end marker
} RADIO_LINK_TYPE_DEV;
#endif

#endif // FASTMAVLINK_DO_NOT_INCLUDE_ENUMS


//------------------------------
//-- Message definitions
//------------------------------

#ifdef FASTMAVLINK_IGNORE_WADDRESSOFPACKEDMEMBER
  #if defined __GNUC__ && __GNUC__ >= 9
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Waddress-of-packed-member"
  #endif
#endif

#include "./mavlink_msg_autopilot_state_for_gimbal_device_ext.h"
#include "./mavlink_msg_radio_link_flow_control.h"
#include "./mavlink_msg_radio_link_stats_mlrs.h"
#include "./mavlink_msg_radio_link_stats_dev.h"
#include "./mavlink_msg_radio_link_information_dev.h"

#ifdef FASTMAVLINK_IGNORE_WADDRESSOFPACKEDMEMBER
  #if defined __GNUC__ && __GNUC__ >= 9
    #pragma GCC diagnostic pop
  #endif
#endif


//------------------------------
//-- Dialect includes
//------------------------------




#ifdef __cplusplus
}
#endif

#endif // FASTMAVLINK_OLLIW_DEV_H
