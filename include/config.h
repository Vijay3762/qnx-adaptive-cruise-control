#ifndef CONFIG_H
#define CONFIG_H

/* ============================================================
 * Simulation Configuration
 * ============================================================ */

#define SIMULATION_DURATION       60.0
#define SIMULATION_DT             0.1


/* ============================================================
 * Ego Vehicle Initial State
 * ============================================================ */

#define INITIAL_EGO_POSITION      0.0
#define INITIAL_EGO_SPEED         15.0
#define INITIAL_EGO_ACCELERATION  0.0

#define MAX_EGO_SPEED             35.0


/* ============================================================
 * Lead Vehicle Initial State
 * ============================================================ */

#define INITIAL_LEAD_POSITION     50.0
#define INITIAL_LEAD_SPEED        15.0
#define INITIAL_LEAD_ACCELERATION 0.0

#define MAX_LEAD_SPEED            30.0
#define MIN_LEAD_SPEED             0.0


/* ============================================================
 * Lead Vehicle Scenarios
 * ============================================================ */

/*
 *  0 - 10 s : Constant speed
 * 10 - 20 s : Acceleration
 * 20 - 30 s : Constant speed
 * 30 - 35 s : Deceleration
 * 35 - 40 s : Constant speed
 * 40 - 43 s : Sudden braking
 * 43 - 50 s : Slow movement
 * 50 - 60 s : Stop
 */

#define ACCELERATION_START_TIME       10.0
#define ACCELERATION_END_TIME         20.0

#define DECELERATION_START_TIME       30.0
#define DECELERATION_END_TIME         35.0

#define SUDDEN_BRAKING_START_TIME     40.0
#define SUDDEN_BRAKING_END_TIME       43.0

#define STOP_START_TIME               50.0


/* ============================================================
 * Lead Vehicle Accelerations
 * ============================================================ */

#define LEAD_ACCELERATION              2.0
#define LEAD_DECELERATION            -2.0
#define LEAD_SUDDEN_BRAKING          -5.0


/* ============================================================
 * Ego Vehicle Test Profile
 *
 * Temporary only.
 * Eventually the ACC controller will generate
 * the ego acceleration command.
 * ============================================================ */

#define EGO_ACCELERATION_START_TIME   10.0
#define EGO_ACCELERATION_END_TIME     20.0

#define EGO_DECELERATION_START_TIME   30.0
#define EGO_DECELERATION_END_TIME     35.0

#define EGO_ACCELERATION               1.0
#define EGO_DECELERATION              -1.5


/* ============================================================
 * Radar Configuration
 * ============================================================ */

#define RADAR_MAX_RANGE               300.0
#define RADAR_MIN_RANGE                 0.5

#define RADAR_NOISE_DISTANCE            0.05
#define RADAR_NOISE_RELATIVE_SPEED      0.05

#define RADAR_DELAY                     0.2


/* ============================================================
 * Radar Failure Scenario
 *
 * 45 - 47 s : simulated radar failure
 * ============================================================ */

#define RADAR_FAILURE_START_TIME       45.0
#define RADAR_FAILURE_END_TIME         47.0

#endif
