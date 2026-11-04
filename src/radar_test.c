#include <stdio.h>
#include "vehicle_state.h"
#include "radar_data.h"
#include "config.h"

/* Radar simulator function */
void generate_radar_data(
    const VehicleState *ego,
    const VehicleState *lead,
    double timestamp,
    RadarData *radar
);

int main(void)
{
    VehicleState ego = {0};
    VehicleState lead = {0};
    RadarData radar = {0};

    double dt = 0.1;
    double time = 0.0;

    /* Initialize ego vehicle */
    ego.position = 0.0;
    ego.speed = 15.0;
    ego.acceleration = 0.0;

    /* Initialize lead vehicle */
    lead.position = 50.0;
    lead.speed = 15.0;
    lead.acceleration = 0.0;

    printf("\n");
    printf("============================================\n");
    printf("       RADAR SIMULATOR INDEPENDENT TEST\n");
    printf("============================================\n\n");

    printf("Time | Ego Pos | Lead Pos | Distance | Rel Speed | Status\n");
    printf("------------------------------------------------------------\n");

    while (time <= 60.0)
    {
        /*
         * Update vehicle positions.
         * These are test inputs, not ACC control commands.
         */

        ego.position += ego.speed * dt;
        lead.position += lead.speed * dt;

        /*
         * Lead vehicle test scenario:
         * Sudden braking at 10 seconds.
         */
        if (time >= 10.0 && time < 12.0)
        {
            lead.speed -= 2.0 * dt;

            if (lead.speed < 0.0)
                lead.speed = 0.0;
        }

        /*
         * Generate radar measurements.
         */
        generate_radar_data(
            &ego,
            &lead,
            time,
            &radar
        );

        /*
         * Display radar output.
         */
        if (radar.valid)
        {
            printf("%4.1f | %7.2f | %8.2f | %8.2f | %9.2f | VALID\n",
                   time,
                   ego.position,
                   lead.position,
                   radar.distance,
                   radar.relative_speed);
        }
        else
        {
            printf("%4.1f | %7.2f | %8.2f |    ---   |    ---    | INVALID\n",
                   time,
                   ego.position,
                   lead.position);
        }

        time += dt;
    }

    printf("\nRadar simulation test completed.\n");

    return 0;
}
