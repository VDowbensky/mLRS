//------------------------------
// The fastMavlink library
// (c) OlliW, OlliW42, www.olliw.eu
//------------------------------

#pragma once
#ifndef FASTMAVLINK_MSG_RADIO_LINK_STATS_MLRS_H
#define FASTMAVLINK_MSG_RADIO_LINK_STATS_MLRS_H


//----------------------------------------
//-- Message RADIO_LINK_STATS_MLRS
//----------------------------------------

// fields are ordered, as they appear on the wire
FASTMAVLINK_PACK(
typedef struct _fmav_radio_link_stats_mlrs_t {
    float frequency1;
    float frequency2;
    uint8_t target_system;
    uint8_t target_component;
    uint8_t flags;
    uint8_t rx_LQ_rc;
    uint8_t rx_LQ_ser;
    uint8_t rx_rssi1;
    int8_t rx_snr1;
    uint8_t rx_rssi2;
    int8_t rx_snr2;
    uint8_t tx_LQ_ser;
    uint8_t tx_rssi1;
    int8_t tx_snr1;
    uint8_t tx_rssi2;
    int8_t tx_snr2;
    uint8_t rx_receive_antenna;
    uint8_t rx_transmit_antenna;
    uint8_t tx_receive_antenna;
    uint8_t tx_transmit_antenna;
}) fmav_radio_link_stats_mlrs_t;


#define FASTMAVLINK_MSG_ID_RADIO_LINK_STATS_MLRS  60045

#define FASTMAVLINK_MSG_RADIO_LINK_STATS_MLRS_PAYLOAD_LEN_MAX  26
#define FASTMAVLINK_MSG_RADIO_LINK_STATS_MLRS_CRCEXTRA  185

#define FASTMAVLINK_MSG_RADIO_LINK_STATS_MLRS_FLAGS  3
#define FASTMAVLINK_MSG_RADIO_LINK_STATS_MLRS_TARGET_SYSTEM_OFS  8
#define FASTMAVLINK_MSG_RADIO_LINK_STATS_MLRS_TARGET_COMPONENT_OFS  9

#define FASTMAVLINK_MSG_RADIO_LINK_STATS_MLRS_FRAME_LEN_MAX  51



#define FASTMAVLINK_MSG_RADIO_LINK_STATS_MLRS_FIELD_FREQUENCY1_OFS  0
#define FASTMAVLINK_MSG_RADIO_LINK_STATS_MLRS_FIELD_FREQUENCY2_OFS  4
#define FASTMAVLINK_MSG_RADIO_LINK_STATS_MLRS_FIELD_TARGET_SYSTEM_OFS  8
#define FASTMAVLINK_MSG_RADIO_LINK_STATS_MLRS_FIELD_TARGET_COMPONENT_OFS  9
#define FASTMAVLINK_MSG_RADIO_LINK_STATS_MLRS_FIELD_FLAGS_OFS  10
#define FASTMAVLINK_MSG_RADIO_LINK_STATS_MLRS_FIELD_RX_LQ_RC_OFS  11
#define FASTMAVLINK_MSG_RADIO_LINK_STATS_MLRS_FIELD_RX_LQ_SER_OFS  12
#define FASTMAVLINK_MSG_RADIO_LINK_STATS_MLRS_FIELD_RX_RSSI1_OFS  13
#define FASTMAVLINK_MSG_RADIO_LINK_STATS_MLRS_FIELD_RX_SNR1_OFS  14
#define FASTMAVLINK_MSG_RADIO_LINK_STATS_MLRS_FIELD_RX_RSSI2_OFS  15
#define FASTMAVLINK_MSG_RADIO_LINK_STATS_MLRS_FIELD_RX_SNR2_OFS  16
#define FASTMAVLINK_MSG_RADIO_LINK_STATS_MLRS_FIELD_TX_LQ_SER_OFS  17
#define FASTMAVLINK_MSG_RADIO_LINK_STATS_MLRS_FIELD_TX_RSSI1_OFS  18
#define FASTMAVLINK_MSG_RADIO_LINK_STATS_MLRS_FIELD_TX_SNR1_OFS  19
#define FASTMAVLINK_MSG_RADIO_LINK_STATS_MLRS_FIELD_TX_RSSI2_OFS  20
#define FASTMAVLINK_MSG_RADIO_LINK_STATS_MLRS_FIELD_TX_SNR2_OFS  21
#define FASTMAVLINK_MSG_RADIO_LINK_STATS_MLRS_FIELD_RX_RECEIVE_ANTENNA_OFS  22
#define FASTMAVLINK_MSG_RADIO_LINK_STATS_MLRS_FIELD_RX_TRANSMIT_ANTENNA_OFS  23
#define FASTMAVLINK_MSG_RADIO_LINK_STATS_MLRS_FIELD_TX_RECEIVE_ANTENNA_OFS  24
#define FASTMAVLINK_MSG_RADIO_LINK_STATS_MLRS_FIELD_TX_TRANSMIT_ANTENNA_OFS  25


//----------------------------------------
//-- Message RADIO_LINK_STATS_MLRS pack,encode routines, for sending
//----------------------------------------

FASTMAVLINK_FUNCTION_DECORATOR uint16_t fmav_msg_radio_link_stats_mlrs_pack(
    fmav_message_t* _msg,
    uint8_t sysid,
    uint8_t compid,
    uint8_t target_system, uint8_t target_component, uint8_t flags, uint8_t rx_LQ_rc, uint8_t rx_LQ_ser, uint8_t rx_rssi1, int8_t rx_snr1, uint8_t rx_rssi2, int8_t rx_snr2, uint8_t tx_LQ_ser, uint8_t tx_rssi1, int8_t tx_snr1, uint8_t tx_rssi2, int8_t tx_snr2, uint8_t rx_receive_antenna, uint8_t rx_transmit_antenna, uint8_t tx_receive_antenna, uint8_t tx_transmit_antenna, float frequency1, float frequency2,
    fmav_status_t* _status)
{
    fmav_radio_link_stats_mlrs_t* _payload = (fmav_radio_link_stats_mlrs_t*)_msg->payload;

    _payload->frequency1 = frequency1;
    _payload->frequency2 = frequency2;
    _payload->target_system = target_system;
    _payload->target_component = target_component;
    _payload->flags = flags;
    _payload->rx_LQ_rc = rx_LQ_rc;
    _payload->rx_LQ_ser = rx_LQ_ser;
    _payload->rx_rssi1 = rx_rssi1;
    _payload->rx_snr1 = rx_snr1;
    _payload->rx_rssi2 = rx_rssi2;
    _payload->rx_snr2 = rx_snr2;
    _payload->tx_LQ_ser = tx_LQ_ser;
    _payload->tx_rssi1 = tx_rssi1;
    _payload->tx_snr1 = tx_snr1;
    _payload->tx_rssi2 = tx_rssi2;
    _payload->tx_snr2 = tx_snr2;
    _payload->rx_receive_antenna = rx_receive_antenna;
    _payload->rx_transmit_antenna = rx_transmit_antenna;
    _payload->tx_receive_antenna = tx_receive_antenna;
    _payload->tx_transmit_antenna = tx_transmit_antenna;


    _msg->sysid = sysid;
    _msg->compid = compid;
    _msg->msgid = FASTMAVLINK_MSG_ID_RADIO_LINK_STATS_MLRS;
    _msg->target_sysid = target_system;
    _msg->target_compid = target_component;
    _msg->crc_extra = FASTMAVLINK_MSG_RADIO_LINK_STATS_MLRS_CRCEXTRA;
    _msg->payload_max_len = FASTMAVLINK_MSG_RADIO_LINK_STATS_MLRS_PAYLOAD_LEN_MAX;

    return fmav_finalize_msg(_msg, _status);
}


FASTMAVLINK_FUNCTION_DECORATOR uint16_t fmav_msg_radio_link_stats_mlrs_encode(
    fmav_message_t* _msg,
    uint8_t sysid,
    uint8_t compid,
    const fmav_radio_link_stats_mlrs_t* _payload,
    fmav_status_t* _status)
{
    return fmav_msg_radio_link_stats_mlrs_pack(
        _msg, sysid, compid,
        _payload->target_system, _payload->target_component, _payload->flags, _payload->rx_LQ_rc, _payload->rx_LQ_ser, _payload->rx_rssi1, _payload->rx_snr1, _payload->rx_rssi2, _payload->rx_snr2, _payload->tx_LQ_ser, _payload->tx_rssi1, _payload->tx_snr1, _payload->tx_rssi2, _payload->tx_snr2, _payload->rx_receive_antenna, _payload->rx_transmit_antenna, _payload->tx_receive_antenna, _payload->tx_transmit_antenna, _payload->frequency1, _payload->frequency2,
        _status);
}


FASTMAVLINK_FUNCTION_DECORATOR uint16_t fmav_msg_radio_link_stats_mlrs_pack_to_frame_buf(
    uint8_t* _buf,
    uint8_t sysid,
    uint8_t compid,
    uint8_t target_system, uint8_t target_component, uint8_t flags, uint8_t rx_LQ_rc, uint8_t rx_LQ_ser, uint8_t rx_rssi1, int8_t rx_snr1, uint8_t rx_rssi2, int8_t rx_snr2, uint8_t tx_LQ_ser, uint8_t tx_rssi1, int8_t tx_snr1, uint8_t tx_rssi2, int8_t tx_snr2, uint8_t rx_receive_antenna, uint8_t rx_transmit_antenna, uint8_t tx_receive_antenna, uint8_t tx_transmit_antenna, float frequency1, float frequency2,
    fmav_status_t* _status)
{
    fmav_radio_link_stats_mlrs_t* _payload = (fmav_radio_link_stats_mlrs_t*)(&_buf[FASTMAVLINK_HEADER_V2_LEN]);

    _payload->frequency1 = frequency1;
    _payload->frequency2 = frequency2;
    _payload->target_system = target_system;
    _payload->target_component = target_component;
    _payload->flags = flags;
    _payload->rx_LQ_rc = rx_LQ_rc;
    _payload->rx_LQ_ser = rx_LQ_ser;
    _payload->rx_rssi1 = rx_rssi1;
    _payload->rx_snr1 = rx_snr1;
    _payload->rx_rssi2 = rx_rssi2;
    _payload->rx_snr2 = rx_snr2;
    _payload->tx_LQ_ser = tx_LQ_ser;
    _payload->tx_rssi1 = tx_rssi1;
    _payload->tx_snr1 = tx_snr1;
    _payload->tx_rssi2 = tx_rssi2;
    _payload->tx_snr2 = tx_snr2;
    _payload->rx_receive_antenna = rx_receive_antenna;
    _payload->rx_transmit_antenna = rx_transmit_antenna;
    _payload->tx_receive_antenna = tx_receive_antenna;
    _payload->tx_transmit_antenna = tx_transmit_antenna;


    _buf[5] = sysid;
    _buf[6] = compid;
    _buf[7] = (uint8_t)FASTMAVLINK_MSG_ID_RADIO_LINK_STATS_MLRS;
    _buf[8] = ((uint32_t)FASTMAVLINK_MSG_ID_RADIO_LINK_STATS_MLRS >> 8);
    _buf[9] = ((uint32_t)FASTMAVLINK_MSG_ID_RADIO_LINK_STATS_MLRS >> 16);

    return fmav_finalize_frame_buf(
        _buf,
        FASTMAVLINK_MSG_RADIO_LINK_STATS_MLRS_PAYLOAD_LEN_MAX,
        FASTMAVLINK_MSG_RADIO_LINK_STATS_MLRS_CRCEXTRA,
        _status);
}


FASTMAVLINK_FUNCTION_DECORATOR uint16_t fmav_msg_radio_link_stats_mlrs_encode_to_frame_buf(
    uint8_t* _buf,
    uint8_t sysid,
    uint8_t compid,
    const fmav_radio_link_stats_mlrs_t* _payload,
    fmav_status_t* _status)
{
    return fmav_msg_radio_link_stats_mlrs_pack_to_frame_buf(
        _buf, sysid, compid,
        _payload->target_system, _payload->target_component, _payload->flags, _payload->rx_LQ_rc, _payload->rx_LQ_ser, _payload->rx_rssi1, _payload->rx_snr1, _payload->rx_rssi2, _payload->rx_snr2, _payload->tx_LQ_ser, _payload->tx_rssi1, _payload->tx_snr1, _payload->tx_rssi2, _payload->tx_snr2, _payload->rx_receive_antenna, _payload->rx_transmit_antenna, _payload->tx_receive_antenna, _payload->tx_transmit_antenna, _payload->frequency1, _payload->frequency2,
        _status);
}


#ifdef FASTMAVLINK_SERIAL_WRITE_CHAR

FASTMAVLINK_FUNCTION_DECORATOR uint16_t fmav_msg_radio_link_stats_mlrs_pack_to_serial(
    uint8_t sysid,
    uint8_t compid,
    uint8_t target_system, uint8_t target_component, uint8_t flags, uint8_t rx_LQ_rc, uint8_t rx_LQ_ser, uint8_t rx_rssi1, int8_t rx_snr1, uint8_t rx_rssi2, int8_t rx_snr2, uint8_t tx_LQ_ser, uint8_t tx_rssi1, int8_t tx_snr1, uint8_t tx_rssi2, int8_t tx_snr2, uint8_t rx_receive_antenna, uint8_t rx_transmit_antenna, uint8_t tx_receive_antenna, uint8_t tx_transmit_antenna, float frequency1, float frequency2,
    fmav_status_t* _status)
{
    fmav_radio_link_stats_mlrs_t _payload;

    _payload.frequency1 = frequency1;
    _payload.frequency2 = frequency2;
    _payload.target_system = target_system;
    _payload.target_component = target_component;
    _payload.flags = flags;
    _payload.rx_LQ_rc = rx_LQ_rc;
    _payload.rx_LQ_ser = rx_LQ_ser;
    _payload.rx_rssi1 = rx_rssi1;
    _payload.rx_snr1 = rx_snr1;
    _payload.rx_rssi2 = rx_rssi2;
    _payload.rx_snr2 = rx_snr2;
    _payload.tx_LQ_ser = tx_LQ_ser;
    _payload.tx_rssi1 = tx_rssi1;
    _payload.tx_snr1 = tx_snr1;
    _payload.tx_rssi2 = tx_rssi2;
    _payload.tx_snr2 = tx_snr2;
    _payload.rx_receive_antenna = rx_receive_antenna;
    _payload.rx_transmit_antenna = rx_transmit_antenna;
    _payload.tx_receive_antenna = tx_receive_antenna;
    _payload.tx_transmit_antenna = tx_transmit_antenna;


    return fmav_finalize_serial(
        sysid,
        compid,
        (uint8_t*)&_payload,
        FASTMAVLINK_MSG_ID_RADIO_LINK_STATS_MLRS,
        FASTMAVLINK_MSG_RADIO_LINK_STATS_MLRS_PAYLOAD_LEN_MAX,
        FASTMAVLINK_MSG_RADIO_LINK_STATS_MLRS_CRCEXTRA,
        _status);
}


FASTMAVLINK_FUNCTION_DECORATOR uint16_t fmav_msg_radio_link_stats_mlrs_encode_to_serial(
    uint8_t sysid,
    uint8_t compid,
    const fmav_radio_link_stats_mlrs_t* _payload,
    fmav_status_t* _status)
{
    return fmav_finalize_serial(
        sysid,
        compid,
        (uint8_t*)_payload,
        FASTMAVLINK_MSG_ID_RADIO_LINK_STATS_MLRS,
        FASTMAVLINK_MSG_RADIO_LINK_STATS_MLRS_PAYLOAD_LEN_MAX,
        FASTMAVLINK_MSG_RADIO_LINK_STATS_MLRS_CRCEXTRA,
        _status);
}
#endif


//----------------------------------------
//-- Message RADIO_LINK_STATS_MLRS decode routines, for receiving
//----------------------------------------
// For these functions to work correctly, the msg payload must be zero-filled.
// Call the helper fmav_msg_zerofill() if needed, or set FASTMAVLINK_ALWAYS_ZEROFILL to 1
// Note that the parse functions do zero-fill the msg payload, but that message generator functions
// do not. This means that for the msg obtained from parsing the below functions can safely be used,
// but that this is not so for the msg obtained from pack/encode functions.

FASTMAVLINK_FUNCTION_DECORATOR void fmav_msg_radio_link_stats_mlrs_decode(fmav_radio_link_stats_mlrs_t* payload, const fmav_message_t* msg)
{
#if FASTMAVLINK_ALWAYS_ZEROFILL
    if (msg->len < FASTMAVLINK_MSG_RADIO_LINK_STATS_MLRS_PAYLOAD_LEN_MAX) {
        memcpy(payload, msg->payload, msg->len);
        // ensure that returned payload is zero-filled
        memset(&(((uint8_t*)payload)[msg->len]), 0, FASTMAVLINK_MSG_RADIO_LINK_STATS_MLRS_PAYLOAD_LEN_MAX - msg->len);
    } else {
        // note: msg->len can be larger than PAYLOAD_LEN_MAX if the message has unknown extensions
        memcpy(payload, msg->payload, FASTMAVLINK_MSG_RADIO_LINK_STATS_MLRS_PAYLOAD_LEN_MAX);
    }
#else
    // this requires that msg payload had been zero-filled before
    memcpy(payload, msg->payload, FASTMAVLINK_MSG_RADIO_LINK_STATS_MLRS_PAYLOAD_LEN_MAX);
#endif
}


FASTMAVLINK_FUNCTION_DECORATOR float fmav_msg_radio_link_stats_mlrs_get_field_frequency1(const fmav_message_t* msg)
{
    float r;
    memcpy(&r, &(msg->payload[0]), sizeof(float));
    return r;
}


FASTMAVLINK_FUNCTION_DECORATOR float fmav_msg_radio_link_stats_mlrs_get_field_frequency2(const fmav_message_t* msg)
{
    float r;
    memcpy(&r, &(msg->payload[4]), sizeof(float));
    return r;
}


FASTMAVLINK_FUNCTION_DECORATOR uint8_t fmav_msg_radio_link_stats_mlrs_get_field_target_system(const fmav_message_t* msg)
{
    uint8_t r;
    memcpy(&r, &(msg->payload[8]), sizeof(uint8_t));
    return r;
}


FASTMAVLINK_FUNCTION_DECORATOR uint8_t fmav_msg_radio_link_stats_mlrs_get_field_target_component(const fmav_message_t* msg)
{
    uint8_t r;
    memcpy(&r, &(msg->payload[9]), sizeof(uint8_t));
    return r;
}


FASTMAVLINK_FUNCTION_DECORATOR uint8_t fmav_msg_radio_link_stats_mlrs_get_field_flags(const fmav_message_t* msg)
{
    uint8_t r;
    memcpy(&r, &(msg->payload[10]), sizeof(uint8_t));
    return r;
}


FASTMAVLINK_FUNCTION_DECORATOR uint8_t fmav_msg_radio_link_stats_mlrs_get_field_rx_LQ_rc(const fmav_message_t* msg)
{
    uint8_t r;
    memcpy(&r, &(msg->payload[11]), sizeof(uint8_t));
    return r;
}


FASTMAVLINK_FUNCTION_DECORATOR uint8_t fmav_msg_radio_link_stats_mlrs_get_field_rx_LQ_ser(const fmav_message_t* msg)
{
    uint8_t r;
    memcpy(&r, &(msg->payload[12]), sizeof(uint8_t));
    return r;
}


FASTMAVLINK_FUNCTION_DECORATOR uint8_t fmav_msg_radio_link_stats_mlrs_get_field_rx_rssi1(const fmav_message_t* msg)
{
    uint8_t r;
    memcpy(&r, &(msg->payload[13]), sizeof(uint8_t));
    return r;
}


FASTMAVLINK_FUNCTION_DECORATOR int8_t fmav_msg_radio_link_stats_mlrs_get_field_rx_snr1(const fmav_message_t* msg)
{
    int8_t r;
    memcpy(&r, &(msg->payload[14]), sizeof(int8_t));
    return r;
}


FASTMAVLINK_FUNCTION_DECORATOR uint8_t fmav_msg_radio_link_stats_mlrs_get_field_rx_rssi2(const fmav_message_t* msg)
{
    uint8_t r;
    memcpy(&r, &(msg->payload[15]), sizeof(uint8_t));
    return r;
}


FASTMAVLINK_FUNCTION_DECORATOR int8_t fmav_msg_radio_link_stats_mlrs_get_field_rx_snr2(const fmav_message_t* msg)
{
    int8_t r;
    memcpy(&r, &(msg->payload[16]), sizeof(int8_t));
    return r;
}


FASTMAVLINK_FUNCTION_DECORATOR uint8_t fmav_msg_radio_link_stats_mlrs_get_field_tx_LQ_ser(const fmav_message_t* msg)
{
    uint8_t r;
    memcpy(&r, &(msg->payload[17]), sizeof(uint8_t));
    return r;
}


FASTMAVLINK_FUNCTION_DECORATOR uint8_t fmav_msg_radio_link_stats_mlrs_get_field_tx_rssi1(const fmav_message_t* msg)
{
    uint8_t r;
    memcpy(&r, &(msg->payload[18]), sizeof(uint8_t));
    return r;
}


FASTMAVLINK_FUNCTION_DECORATOR int8_t fmav_msg_radio_link_stats_mlrs_get_field_tx_snr1(const fmav_message_t* msg)
{
    int8_t r;
    memcpy(&r, &(msg->payload[19]), sizeof(int8_t));
    return r;
}


FASTMAVLINK_FUNCTION_DECORATOR uint8_t fmav_msg_radio_link_stats_mlrs_get_field_tx_rssi2(const fmav_message_t* msg)
{
    uint8_t r;
    memcpy(&r, &(msg->payload[20]), sizeof(uint8_t));
    return r;
}


FASTMAVLINK_FUNCTION_DECORATOR int8_t fmav_msg_radio_link_stats_mlrs_get_field_tx_snr2(const fmav_message_t* msg)
{
    int8_t r;
    memcpy(&r, &(msg->payload[21]), sizeof(int8_t));
    return r;
}


FASTMAVLINK_FUNCTION_DECORATOR uint8_t fmav_msg_radio_link_stats_mlrs_get_field_rx_receive_antenna(const fmav_message_t* msg)
{
    uint8_t r;
    memcpy(&r, &(msg->payload[22]), sizeof(uint8_t));
    return r;
}


FASTMAVLINK_FUNCTION_DECORATOR uint8_t fmav_msg_radio_link_stats_mlrs_get_field_rx_transmit_antenna(const fmav_message_t* msg)
{
    uint8_t r;
    memcpy(&r, &(msg->payload[23]), sizeof(uint8_t));
    return r;
}


FASTMAVLINK_FUNCTION_DECORATOR uint8_t fmav_msg_radio_link_stats_mlrs_get_field_tx_receive_antenna(const fmav_message_t* msg)
{
    uint8_t r;
    memcpy(&r, &(msg->payload[24]), sizeof(uint8_t));
    return r;
}


FASTMAVLINK_FUNCTION_DECORATOR uint8_t fmav_msg_radio_link_stats_mlrs_get_field_tx_transmit_antenna(const fmav_message_t* msg)
{
    uint8_t r;
    memcpy(&r, &(msg->payload[25]), sizeof(uint8_t));
    return r;
}





//----------------------------------------
//-- Pymavlink wrappers
//----------------------------------------
#ifdef FASTMAVLINK_PYMAVLINK_ENABLED

#define MAVLINK_MSG_ID_RADIO_LINK_STATS_MLRS  60045

#define mavlink_radio_link_stats_mlrs_t  fmav_radio_link_stats_mlrs_t

#define MAVLINK_MSG_ID_RADIO_LINK_STATS_MLRS_LEN  26
#define MAVLINK_MSG_ID_RADIO_LINK_STATS_MLRS_MIN_LEN  26
#define MAVLINK_MSG_ID_60045_LEN  26
#define MAVLINK_MSG_ID_60045_MIN_LEN  26

#define MAVLINK_MSG_ID_RADIO_LINK_STATS_MLRS_CRC  185
#define MAVLINK_MSG_ID_60045_CRC  185




#if MAVLINK_COMM_NUM_BUFFERS > 0

FASTMAVLINK_FUNCTION_DECORATOR uint16_t mavlink_msg_radio_link_stats_mlrs_pack(
    uint8_t sysid,
    uint8_t compid,
    mavlink_message_t* _msg,
    uint8_t target_system, uint8_t target_component, uint8_t flags, uint8_t rx_LQ_rc, uint8_t rx_LQ_ser, uint8_t rx_rssi1, int8_t rx_snr1, uint8_t rx_rssi2, int8_t rx_snr2, uint8_t tx_LQ_ser, uint8_t tx_rssi1, int8_t tx_snr1, uint8_t tx_rssi2, int8_t tx_snr2, uint8_t rx_receive_antenna, uint8_t rx_transmit_antenna, uint8_t tx_receive_antenna, uint8_t tx_transmit_antenna, float frequency1, float frequency2)
{
    fmav_status_t* _status = mavlink_get_channel_status(MAVLINK_COMM_0);
    return fmav_msg_radio_link_stats_mlrs_pack(
        _msg, sysid, compid,
        target_system, target_component, flags, rx_LQ_rc, rx_LQ_ser, rx_rssi1, rx_snr1, rx_rssi2, rx_snr2, tx_LQ_ser, tx_rssi1, tx_snr1, tx_rssi2, tx_snr2, rx_receive_antenna, rx_transmit_antenna, tx_receive_antenna, tx_transmit_antenna, frequency1, frequency2,
        _status);
}


FASTMAVLINK_FUNCTION_DECORATOR uint16_t mavlink_msg_radio_link_stats_mlrs_encode(
    uint8_t sysid,
    uint8_t compid,
    mavlink_message_t* _msg,
    const mavlink_radio_link_stats_mlrs_t* _payload)
{
    return mavlink_msg_radio_link_stats_mlrs_pack(
        sysid,
        compid,
        _msg,
        _payload->target_system, _payload->target_component, _payload->flags, _payload->rx_LQ_rc, _payload->rx_LQ_ser, _payload->rx_rssi1, _payload->rx_snr1, _payload->rx_rssi2, _payload->rx_snr2, _payload->tx_LQ_ser, _payload->tx_rssi1, _payload->tx_snr1, _payload->tx_rssi2, _payload->tx_snr2, _payload->rx_receive_antenna, _payload->rx_transmit_antenna, _payload->tx_receive_antenna, _payload->tx_transmit_antenna, _payload->frequency1, _payload->frequency2);
}

#endif


FASTMAVLINK_FUNCTION_DECORATOR uint16_t mavlink_msg_radio_link_stats_mlrs_pack_txbuf(
    char* _buf,
    fmav_status_t* _status,
    uint8_t sysid,
    uint8_t compid,
    uint8_t target_system, uint8_t target_component, uint8_t flags, uint8_t rx_LQ_rc, uint8_t rx_LQ_ser, uint8_t rx_rssi1, int8_t rx_snr1, uint8_t rx_rssi2, int8_t rx_snr2, uint8_t tx_LQ_ser, uint8_t tx_rssi1, int8_t tx_snr1, uint8_t tx_rssi2, int8_t tx_snr2, uint8_t rx_receive_antenna, uint8_t rx_transmit_antenna, uint8_t tx_receive_antenna, uint8_t tx_transmit_antenna, float frequency1, float frequency2)
{
    return fmav_msg_radio_link_stats_mlrs_pack_to_frame_buf(
        (uint8_t*)_buf,
        sysid,
        compid,
        target_system, target_component, flags, rx_LQ_rc, rx_LQ_ser, rx_rssi1, rx_snr1, rx_rssi2, rx_snr2, tx_LQ_ser, tx_rssi1, tx_snr1, tx_rssi2, tx_snr2, rx_receive_antenna, rx_transmit_antenna, tx_receive_antenna, tx_transmit_antenna, frequency1, frequency2,
        _status);
}


FASTMAVLINK_FUNCTION_DECORATOR void mavlink_msg_radio_link_stats_mlrs_decode(const mavlink_message_t* msg, mavlink_radio_link_stats_mlrs_t* payload)
{
    fmav_msg_radio_link_stats_mlrs_decode(payload, msg);
}

#endif // FASTMAVLINK_PYMAVLINK_ENABLED


#endif // FASTMAVLINK_MSG_RADIO_LINK_STATS_MLRS_H
