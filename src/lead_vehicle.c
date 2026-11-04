#include "vehicle_state.h"
#include "config.h"


/*
 * Initialize the lead vehicle.
 */
void initialize_lead_vehicle(VehicleState *lead)
{
    if (lead == 0)
        return;

    lead->position = INITIAL_LEAD_POSITION;
    lead->speed = INITIAL_LEAD_SPEED;
    lead->acceleration = INITIAL_LEAD_ACCELERATION;
}


/*
 * Limit vehicle speed to physically meaningful values.
 */
static void limit_lead_speed(VehicleState *lead)
{
    if (lead->speed > MAX_LEAD_SPEED)
        lead->speed = MAX_LEAD_SPEED;

    if (lead->speed < MIN_LEAD_SPEED)
        lead->speed = MIN_LEAD_SPEED;
}


/*
 * Determine the current driving scenario.
 */
static double determine_acceleration(double simulation_time)
{
    /*
     * --------------------------------------------------------
     * Scenario 1: Constant speed
     * 0 - 10 seconds
     * --------------------------------------------------------
     */
    if (simulation_time < ACCELERATION_START_TIME)
    {
        return 0.0;
    }


    /*
     * --------------------------------------------------------
     * Scenario 2: Acceleration
     * 10 - 20 seconds
     * --------------------------------------------------------
     */
    if (simulation_time < ACCELERATION_END_TIME)
    {
        return LEAD_ACCELERATION;
    }


    /*
     * --------------------------------------------------------
     * Scenario 3: Constant speed
     * 20 - 30 seconds
     * --------------------------------------------------------
     */
    if (simulation_time < DECELERATION_START_TIME)
    {
        return 0.0;
    }


    /*
     * --------------------------------------------------------
     * Scenario 4: Deceleration
     * 30 - 35 seconds
     * --------------------------------------------------------
     */
    if (simulation_time < DECELERATION_END_TIME)
    {
        return LEAD_DECELERATION;
    }


    /*
     * --------------------------------------------------------
     * Scenario 5: Constant speed
     * 35 - 40 seconds
     * --------------------------------------------------------
     */
    if (simulation_time < SUDDEN_BRAKING_START_TIME)
    {
        return 0.0;
    }


    /*
     * --------------------------------------------------------
     * Scenario 6: Sudden / emergency braking
     * 40 - 43 seconds
     * --------------------------------------------------------
     */
    if (simulation_time < SUDDEN_BRAKING_END_TIME)
    {
        return LEAD_SUDDEN_BRAKING;
    }


    /*
     * --------------------------------------------------------
     * Scenario 7: Slow movement
     * 43 - 50 seconds
     * --------------------------------------------------------
     */
    if (simulation_time < STOP_START_TIME)
    {
        return 0.0;
    }


    /*
     * --------------------------------------------------------
     * Scenario 8: Vehicle stops
     * 50 seconds onward
     * --------------------------------------------------------
     */
    return -5.0;
}


/*
 * Update the lead vehicle.
 */
void update_lead_vehicle(VehicleState *lead,
                         double simulation_time,
                         double dt)
{
    double acceleration;

    if (lead == 0)
        return;

    /*
     * Determine the scenario.
     */
    acceleration =
        determine_acceleration(simulation_time);

    lead->acceleration = acceleration;


    /*
     * Update speed.
     *
     * v(k+1) = v(k) + a * dt
     */
    lead->speed +=
        lead->acceleration * dt;


    /*
     * Prevent negative speed.
     */
    limit_lead_speed(lead);


    /*
     * Update position.
     *
     * x(k+1) = x(k) + v(k+1) * dt
     */
    lead->position +=
        lead->speed * dt;
}
