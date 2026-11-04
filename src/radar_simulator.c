#include <stdlib.h>
#include <math.h>

#include "vehicle_state.h"
#include "radar_data.h"
#include "config.h"


/*
 * Generate a small pseudo-random noise value.
 *
 * Output range:
 *
 * -1.0 to +1.0
 */
static double generate_noise(void)
{
    return ((double)rand() / (double)RAND_MAX) * 2.0 - 1.0;
}


/*
 * Simulate radar measurement.
 */
void generate_radar_data(const VehicleState *ego,
                         const VehicleState *lead,
                         double timestamp,
                         RadarData *radar)
{
    double true_distance;
    double true_relative_speed;

    if (ego == 0 || lead == 0 || radar == 0)
        return;


    /*
     * --------------------------------------------------------
     * Initialize radar structure
     * --------------------------------------------------------
     */

    radar->timestamp = timestamp;
    radar->distance = 0.0;
    radar->relative_speed = 0.0;

    radar->valid = 0;
    radar->delayed = 0;
    radar->target_detected = 0;


    /*
     * --------------------------------------------------------
     * Calculate ground-truth distance
     * --------------------------------------------------------
     */

    true_distance =
        lead->position - ego->position;


    /*
     * --------------------------------------------------------
     * Calculate ground-truth relative speed
     * --------------------------------------------------------
     */

    true_relative_speed =
        lead->speed - ego->speed;


    /*
     * --------------------------------------------------------
     * Check radar operating range
     * --------------------------------------------------------
     */

    if (true_distance < RADAR_MIN_RANGE ||
        true_distance > RADAR_MAX_RANGE)
    {
        return;
    }


    /*
     * --------------------------------------------------------
     * Simulated radar failure
     * --------------------------------------------------------
     */

    if (timestamp >= RADAR_FAILURE_START_TIME &&
        timestamp < RADAR_FAILURE_END_TIME)
    {
        radar->valid = 0;
        radar->target_detected = 0;

        return;
    }


    /*
     * --------------------------------------------------------
     * Add measurement noise
     * --------------------------------------------------------
     */

    radar->distance =
        true_distance +
        generate_noise() * RADAR_NOISE_DISTANCE;

    radar->relative_speed =
        true_relative_speed +
        generate_noise() * RADAR_NOISE_RELATIVE_SPEED;


    /*
     * --------------------------------------------------------
     * Radar status
     * --------------------------------------------------------
     */

    radar->valid = 1;
    radar->target_detected = 1;


    /*
     * --------------------------------------------------------
     * Indicate simulated sensor delay.
     *
     * Actual delayed-buffer implementation will be added
     * when we implement the radar task.
     * --------------------------------------------------------
     */

    if (RADAR_DELAY > 0.0)
    {
        radar->delayed = 1;
    }
}
