#include "vehicle_state.h"
#include "config.h"


/*
 * Initialize the ego vehicle.
 */
void initialize_ego_vehicle(VehicleState *ego)
{
    if (ego == 0)
        return;

    ego->position = INITIAL_EGO_POSITION;
    ego->speed = INITIAL_EGO_SPEED;
    ego->acceleration = INITIAL_EGO_ACCELERATION;
}


/*
 * Limit ego vehicle speed.
 */
static void limit_ego_speed(VehicleState *ego)
{
    if (ego->speed < 0.0)
        ego->speed = 0.0;

    if (ego->speed > MAX_EGO_SPEED)
        ego->speed = MAX_EGO_SPEED;
}


/*
 * Update ego vehicle using the supplied acceleration.
 *
 * This acceleration will eventually come from the
 * ACC controller.
 */
void update_ego_vehicle(VehicleState *ego,
                        double acceleration,
                        double dt)
{
    if (ego == 0)
        return;


    /*
     * Store the requested acceleration.
     */
    ego->acceleration = acceleration;


    /*
     * Vehicle dynamics:
     *
     * v(k+1) = v(k) + a(k) * dt
     */
    ego->speed +=
        ego->acceleration * dt;


    /*
     * Prevent physically impossible speed.
     */
    limit_ego_speed(ego);


    /*
     * Position dynamics:
     *
     * x(k+1) = x(k) + v(k+1) * dt
     */
    ego->position +=
        ego->speed * dt;
}
