#ifndef VEHICLE_STATE_H
#define VEHICLE_STATE_H

typedef struct
{
    double position;       /* metres */
    double speed;          /* m/s */
    double acceleration;   /* m/s^2 */
} VehicleState;

#endif
