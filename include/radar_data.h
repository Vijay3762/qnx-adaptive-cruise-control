#ifndef RADAR_DATA_H
#define RADAR_DATA_H

typedef struct
{
    double timestamp;        /* seconds */
    double distance;         /* metres */
    double relative_speed;   /* m/s */

    int valid;               /* 1 = valid, 0 = invalid */
    int delayed;             /* 1 = delayed measurement */
    int target_detected;     /* 1 = target detected */
} RadarData;

#endif
