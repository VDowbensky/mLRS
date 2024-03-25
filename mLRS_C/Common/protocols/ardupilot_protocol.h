//*******************************************************
// Copyright (c) MLRS project
// GPL3
// https://www.gnu.org/licenses/gpl-3.0.de.html
// OlliW @ www.olliw.eu
//*******************************************************
// ArduPilot Protocol Stuff
//*******************************************************
#ifndef ARDUPILOT_PROTOCOL_H
#define ARDUPILOT_PROTOCOL_H

//-------------------------------------------------------
// ArduPilot flight modes
//-------------------------------------------------------
// this we got from ArduCopter/mode.h
typedef enum {
    AP_COPTER_FLIGHTMODE_STABILIZE =     0,  // manual airframe angle with manual throttle
    AP_COPTER_FLIGHTMODE_ACRO =          1,  // manual body-frame angular rate with manual throttle
    AP_COPTER_FLIGHTMODE_ALT_HOLD =      2,  // manual airframe angle with automatic throttle
    AP_COPTER_FLIGHTMODE_AUTO =          3,  // fully automatic waypoint control using mission commands
    AP_COPTER_FLIGHTMODE_GUIDED =        4,  // fully automatic fly to coordinate or fly at velocity/direction using GCS immediate commands
    AP_COPTER_FLIGHTMODE_LOITER =        5,  // automatic horizontal acceleration with automatic throttle
    AP_COPTER_FLIGHTMODE_RTL =           6,  // automatic return to launching point
    AP_COPTER_FLIGHTMODE_CIRCLE =        7,  // automatic circular flight with automatic throttle
    AP_COPTER_FLIGHTMODE_LAND =          9,  // automatic landing with horizontal position control
    AP_COPTER_FLIGHTMODE_DRIFT =        11,  // semi-autonomous position, yaw and throttle control
    AP_COPTER_FLIGHTMODE_SPORT =        13,  // manual earth-frame angular rate control with manual throttle
    AP_COPTER_FLIGHTMODE_FLIP =         14,  // automatically flip the vehicle on the roll axis
    AP_COPTER_FLIGHTMODE_AUTOTUNE =     15,  // automatically tune the vehicle's roll and pitch gains
    AP_COPTER_FLIGHTMODE_POSHOLD =      16,  // automatic position hold with manual override, with automatic throttle
    AP_COPTER_FLIGHTMODE_BRAKE =        17,  // full-brake using inertial/GPS system, no pilot input
    AP_COPTER_FLIGHTMODE_THROW =        18,  // throw to launch mode using inertial/GPS system, no pilot input
    AP_COPTER_FLIGHTMODE_AVOID_ADSB =   19,  // automatic avoidance of obstacles in the macro scale - e.g. full-sized aircraft
    AP_COPTER_FLIGHTMODE_GUIDED_NOGPS = 20,  // guided mode but only accepts attitude and altitude
    AP_COPTER_FLIGHTMODE_SMART_RTL =    21,  // SMART_RTL returns to home by retracing its steps
    AP_COPTER_FLIGHTMODE_FLOWHOLD  =    22,  // FLOWHOLD holds position with optical flow without rangefinder
    AP_COPTER_FLIGHTMODE_FOLLOW    =    23,  // follow attempts to follow another vehicle or ground station
    AP_COPTER_FLIGHTMODE_ZIGZAG    =    24,  // ZIGZAG mode is able to fly in a zigzag manner with predefined point A and point B
    AP_COPTER_FLIGHTMODE_SYSTEMID  =    25,  // System ID mode produces automated system identification signals in the controllers
    AP_COPTER_FLIGHTMODE_AUTOROTATE =   26,  // Autonomous autorotation
    AP_COPTER_FLIGHTMODE_AUTO_RTL =     27,  // Auto RTL, this is not a true mode, AUTO will report as this mode if entered to perform a DO_LAND_START Landing sequence
    AP_COPTER_FLIGHTMODE_TURTLE =       28,  // Flip over after crash
} AP_COPTER_FLIGHTMODE_ENUM;

// this we got from ArduPlane/mode.h
typedef enum {
    AP_PLANE_FLIGHTMODE_MANUAL        = 0,
    AP_PLANE_FLIGHTMODE_CIRCLE        = 1,
    AP_PLANE_FLIGHTMODE_STABILIZE     = 2,
    AP_PLANE_FLIGHTMODE_TRAINING      = 3,
    AP_PLANE_FLIGHTMODE_ACRO          = 4,
    AP_PLANE_FLIGHTMODE_FLY_BY_WIRE_A = 5,
    AP_PLANE_FLIGHTMODE_FLY_BY_WIRE_B = 6,
    AP_PLANE_FLIGHTMODE_CRUISE        = 7,
    AP_PLANE_FLIGHTMODE_AUTOTUNE      = 8,
    AP_PLANE_FLIGHTMODE_AUTO          = 10,
    AP_PLANE_FLIGHTMODE_RTL           = 11,
    AP_PLANE_FLIGHTMODE_LOITER        = 12,
    AP_PLANE_FLIGHTMODE_TAKEOFF       = 13,
    AP_PLANE_FLIGHTMODE_AVOID_ADSB    = 14,
    AP_PLANE_FLIGHTMODE_GUIDED        = 15,
    AP_PLANE_FLIGHTMODE_INITIALISING  = 16,
    AP_PLANE_FLIGHTMODE_QSTABILIZE    = 17,
    AP_PLANE_FLIGHTMODE_QHOVER        = 18,
    AP_PLANE_FLIGHTMODE_QLOITER       = 19,
    AP_PLANE_FLIGHTMODE_QLAND         = 20,
    AP_PLANE_FLIGHTMODE_QRTL          = 21,
    AP_PLANE_FLIGHTMODE_QAUTOTUNE     = 22,
    AP_PLANE_FLIGHTMODE_QACRO         = 23,
    AP_PLANE_FLIGHTMODE_THERMAL       = 24,
    AP_PLANE_FLIGHTMODE_LOITER_ALT_QLAND = 25,
} AP_PLANE_FLIGHTMODE_ENUM;

// this we got from Rover/mode.h
typedef enum {
    AP_ROVER_FLIGHTMODE_MANUAL       = 0,
    AP_ROVER_FLIGHTMODE_ACRO         = 1,
    AP_ROVER_FLIGHTMODE_STEERING     = 3,
    AP_ROVER_FLIGHTMODE_HOLD         = 4,
    AP_ROVER_FLIGHTMODE_LOITER       = 5,
    AP_ROVER_FLIGHTMODE_FOLLOW       = 6,
    AP_ROVER_FLIGHTMODE_SIMPLE       = 7,
    AP_ROVER_FLIGHTMODE_DOCK         = 8,
    AP_ROVER_FLIGHTMODE_AUTO         = 10,
    AP_ROVER_FLIGHTMODE_RTL          = 11,
    AP_ROVER_FLIGHTMODE_SMART_RTL    = 12,
    AP_ROVER_FLIGHTMODE_GUIDED       = 15,
    AP_ROVER_FLIGHTMODE_INITIALISING = 16,
} AP_ROVER_FLIGHTMODE_ENUM;

// this we got from ArduSub/defines.h
typedef enum {
    AP_SUB_FLIGHTMODE_STABILIZE =     0,  // manual angle with manual depth/throttle
    AP_SUB_FLIGHTMODE_ACRO =          1,  // manual body-frame angular rate with manual depth/throttle
    AP_SUB_FLIGHTMODE_ALT_HOLD =      2,  // manual angle with automatic depth/throttle
    AP_SUB_FLIGHTMODE_AUTO =          3,  // fully automatic waypoint control using mission commands
    AP_SUB_FLIGHTMODE_GUIDED =        4,  // fully automatic fly to coordinate or fly at velocity/direction using GCS immediate commands
    AP_SUB_FLIGHTMODE_CIRCLE =        7,  // automatic circular flight with automatic throttle
    AP_SUB_FLIGHTMODE_SURFACE =       9,  // automatically return to surface, pilot maintains horizontal control
    AP_SUB_FLIGHTMODE_POSHOLD =      16,  // automatic position hold with manual override, with automatic throttle
    AP_SUB_FLIGHTMODE_MANUAL =       19,  // Pass-through input with no stabilization
    AP_SUB_FLIGHTMODE_MOTOR_DETECT = 20   // Automatically detect motors orientation
} AP_SUB_FLIGHTMODE_ENUM;

typedef enum {
    AP_VEHICLE_GENERIC = 0,
    AP_VEHICLE_COPTER,
    AP_VEHICLE_PLANE,
    AP_VEHICLE_ROVER,
    AP_VEHICLE_SUB,
} AP_VEHICLE_ENUM;

// these we find in ArduCopter/mode.h
void ap_copter_flight_mode_name4(char* name4, uint8_t flight_mode);
// these we find in ArduPlane/mode.h
void ap_plane_flight_mode_name4(char* name4, uint8_t flight_mode);
// these we find in Rover/mode.h
void ap_rover_flight_mode_name4(char* name4, uint8_t flight_mode);
// there are these? made them up myself
void ap_sub_flight_mode_name4(char* name4, uint8_t flight_mode);

//-------------------------------------------------------
// ArduPilot vehicles
//-------------------------------------------------------
// this we deduce by searching for MAV_TYPE in ArduPilot code
uint8_t ap_vehicle_from_mavtype(uint8_t mav_type);

//-------------------------------------------------------
// more
//-------------------------------------------------------
void ap_flight_mode_name4(char* name4, uint8_t vehicle, uint8_t flight_mode);

#endif // ARDUPILOT_PROTOCOL_H
