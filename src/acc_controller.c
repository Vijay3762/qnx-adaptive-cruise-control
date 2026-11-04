#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sched.h>
#include <unistd.h>

/*
 * ============================================================
 * QNX ACC Task Priorities
 * ============================================================
 *
 * Higher numerical value = higher priority.
 *
 * Controller Task : Highest
 * Safety Monitor  : Highest
 * Radar Task      : High
 * Tracking Task   : High
 * Logger          : Low
 *
 * Safety and Controller are currently assigned the same
 * highest priority tier.
 * ============================================================
 */

#define CONTROLLER_PRIORITY     30
#define SAFETY_PRIORITY         30
#define RADAR_PRIORITY          25
#define TRACKING_PRIORITY       25
#define LOGGER_PRIORITY         10


/*
 * ============================================================
 * Lead Vehicle Simulator Thread
 * ============================================================
 */

static void *lead_vehicle_task(void *arg)
{
    (void)arg;

    printf("[LEAD] Lead Vehicle Simulator started\n");
    printf("[LEAD] Priority = 20\n");

    while (1)
    {
        /*
         * Lead vehicle simulation will be integrated here.
         *
         * This task will update:
         *     position
         *     speed
         *     acceleration
         *
         * It will later use the existing lead_vehicle.c
         * simulation functions.
         */

        usleep(100000);
    }

    return NULL;
}


/*
 * ============================================================
 * Radar Task
 * ============================================================
 */

static void *radar_task(void *arg)
{
    (void)arg;

    printf("[RADAR] Radar Task started\n");
    printf("[RADAR] Priority = %d\n", RADAR_PRIORITY);

    while (1)
    {
        /*
         * Radar processing will be implemented here.
         *
         * Later this task will:
         *
         * 1. Obtain radar measurements
         * 2. Check validity
         * 3. Process distance
         * 4. Process relative speed
         * 5. Send data to Tracking Task
         */

        usleep(100000);
    }

    return NULL;
}


/*
 * ============================================================
 * Tracking Task
 * ============================================================
 */

static void *tracking_task(void *arg)
{
    (void)arg;

    printf("[TRACKING] Tracking Task started\n");
    printf("[TRACKING] Priority = %d\n", TRACKING_PRIORITY);

    while (1)
    {
        /*
         * Tracking algorithm will be implemented here.
         *
         * Later this task will:
         *
         * 1. Receive radar data
         * 2. Filter measurements
         * 3. Track the lead vehicle
         * 4. Produce a stable target state
         */

        usleep(100000);
    }

    return NULL;
}


/*
 * ============================================================
 * ACC Controller Task
 * ============================================================
 */

static void *controller_task(void *arg)
{
    (void)arg;

    printf("[CONTROLLER] ACC Controller Task started\n");
    printf("[CONTROLLER] Priority = %d\n", CONTROLLER_PRIORITY);

    while (1)
    {
        /*
         * ACC control algorithm will be implemented here.
         *
         * Later this task will receive:
         *
         *     distance
         *     relative speed
         *     ego speed
         *
         * and calculate:
         *
         *     desired acceleration
         *     desired deceleration
         */

        usleep(100000);
    }

    return NULL;
}


/*
 * ============================================================
 * Safety Monitor Task
 * ============================================================
 */

static void *safety_task(void *arg)
{
    (void)arg;

    printf("[SAFETY] Safety Monitor started\n");
    printf("[SAFETY] Priority = %d\n", SAFETY_PRIORITY);

    while (1)
    {
        /*
         * Safety monitoring will be implemented here.
         *
         * Later this task will monitor:
         *
         *     radar validity
         *     communication timeout
         *     controller output
         *     critical distance
         *     task deadlines
         *
         * and can override an unsafe command.
         */

        usleep(100000);
    }

    return NULL;
}


/*
 * ============================================================
 * Logger Task
 * ============================================================
 */

static void *logger_task(void *arg)
{
    (void)arg;

    printf("[LOGGER] Logger Task started\n");
    printf("[LOGGER] Priority = %d\n", LOGGER_PRIORITY);

    while (1)
    {
        /*
         * Logging functionality will be implemented here.
         *
         * Later this task will record:
         *
         *     timestamp
         *     ego speed
         *     lead speed
         *     distance
         *     relative speed
         *     controller command
         *     safety events
         *     deadline information
         */

        usleep(100000);
    }

    return NULL;
}


/*
 * ============================================================
 * Configure Thread Attributes
 * ============================================================
 */

static int configure_thread_attributes(
        pthread_attr_t *attr,
        int priority)
{
    struct sched_param param;

    /*
     * Initialize attributes.
     */
    if (pthread_attr_init(attr) != 0)
    {
        return -1;
    }

    /*
     * Use explicitly supplied scheduling parameters.
     */
    if (pthread_attr_setinheritsched(
            attr,
            PTHREAD_EXPLICIT_SCHED) != 0)
    {
        pthread_attr_destroy(attr);
        return -1;
    }

    /*
     * Use FIFO real-time scheduling.
     */
    if (pthread_attr_setschedpolicy(
            attr,
            SCHED_FIFO) != 0)
    {
        pthread_attr_destroy(attr);
        return -1;
    }

    /*
     * Set task priority.
     */
    param.sched_priority = priority;

    if (pthread_attr_setschedparam(
            attr,
            &param) != 0)
    {
        pthread_attr_destroy(attr);
        return -1;
    }

    return 0;
}


/*
 * ============================================================
 * Main
 * ============================================================
 */

int main(void)
{
    pthread_t lead_thread_id;
    pthread_t radar_thread_id;
    pthread_t tracking_thread_id;
    pthread_t controller_thread_id;
    pthread_t safety_thread_id;
    pthread_t logger_thread_id;

    pthread_attr_t lead_attr;
    pthread_attr_t radar_attr;
    pthread_attr_t tracking_attr;
    pthread_attr_t controller_attr;
    pthread_attr_t safety_attr;
    pthread_attr_t logger_attr;

    int ret;


    /*
     * ========================================================
     * Application startup
     * ========================================================
     */

    printf("\n");
    printf("============================================================\n");
    printf("          QNX INTELLIGENT ADAPTIVE CRUISE CONTROL\n");
    printf("============================================================\n\n");

    printf("Initializing QNX real-time task architecture...\n\n");


    /*
     * ========================================================
     * Configure task attributes
     * ========================================================
     */

    /*
     * Lead Vehicle Simulator
     *
     * Priority 20
     */
    if (configure_thread_attributes(
            &lead_attr,
            20) != 0)
    {
        printf("ERROR: Failed to configure Lead Vehicle task\n");
        return EXIT_FAILURE;
    }


    /*
     * Radar Task
     *
     * Priority 25
     */
    if (configure_thread_attributes(
            &radar_attr,
            RADAR_PRIORITY) != 0)
    {
        printf("ERROR: Failed to configure Radar task\n");
        return EXIT_FAILURE;
    }


    /*
     * Tracking Task
     *
     * Priority 25
     */
    if (configure_thread_attributes(
            &tracking_attr,
            TRACKING_PRIORITY) != 0)
    {
        printf("ERROR: Failed to configure Tracking task\n");
        return EXIT_FAILURE;
    }


    /*
     * Controller Task
     *
     * Priority 30
     */
    if (configure_thread_attributes(
            &controller_attr,
            CONTROLLER_PRIORITY) != 0)
    {
        printf("ERROR: Failed to configure Controller task\n");
        return EXIT_FAILURE;
    }


    /*
     * Safety Monitor
     *
     * Priority 30
     */
    if (configure_thread_attributes(
            &safety_attr,
            SAFETY_PRIORITY) != 0)
    {
        printf("ERROR: Failed to configure Safety task\n");
        return EXIT_FAILURE;
    }


    /*
     * Logger
     *
     * Priority 10
     */
    if (configure_thread_attributes(
            &logger_attr,
            LOGGER_PRIORITY) != 0)
    {
        printf("ERROR: Failed to configure Logger task\n");
        return EXIT_FAILURE;
    }


    /*
     * ========================================================
     * Create Lead Vehicle Simulator
     * ========================================================
     */

    ret = pthread_create(
        &lead_thread_id,
        &lead_attr,
        lead_vehicle_task,
        NULL);

    if (ret != 0)
    {
        printf("ERROR: Failed to create Lead Vehicle task\n");
        return EXIT_FAILURE;
    }


    /*
     * ========================================================
     * Create Radar Task
     * ========================================================
     */

    ret = pthread_create(
        &radar_thread_id,
        &radar_attr,
        radar_task,
        NULL);

    if (ret != 0)
    {
        printf("ERROR: Failed to create Radar task\n");
        return EXIT_FAILURE;
    }


    /*
     * ========================================================
     * Create Tracking Task
     * ========================================================
     */

    ret = pthread_create(
        &tracking_thread_id,
        &tracking_attr,
        tracking_task,
        NULL);

    if (ret != 0)
    {
        printf("ERROR: Failed to create Tracking task\n");
        return EXIT_FAILURE;
    }


    /*
     * ========================================================
     * Create ACC Controller Task
     * ========================================================
     */

    ret = pthread_create(
        &controller_thread_id,
        &controller_attr,
        controller_task,
        NULL);

    if (ret != 0)
    {
        printf("ERROR: Failed to create Controller task\n");
        return EXIT_FAILURE;
    }


    /*
     * ========================================================
     * Create Safety Monitor Task
     * ========================================================
     */

    ret = pthread_create(
        &safety_thread_id,
        &safety_attr,
        safety_task,
        NULL);

    if (ret != 0)
    {
        printf("ERROR: Failed to create Safety task\n");
        return EXIT_FAILURE;
    }


    /*
     * ========================================================
     * Create Logger Task
     * ========================================================
     */

    ret = pthread_create(
        &logger_thread_id,
        &logger_attr,
        logger_task,
        NULL);

    if (ret != 0)
    {
        printf("ERROR: Failed to create Logger task\n");
        return EXIT_FAILURE;
    }


    /*
     * ========================================================
     * Attributes no longer required
     * ========================================================
     */

    pthread_attr_destroy(&lead_attr);
    pthread_attr_destroy(&radar_attr);
    pthread_attr_destroy(&tracking_attr);
    pthread_attr_destroy(&controller_attr);
    pthread_attr_destroy(&safety_attr);
    pthread_attr_destroy(&logger_attr);


    /*
     * ========================================================
     * Display architecture
     * ========================================================
     */

    printf("\n");
    printf("QNX TASK ARCHITECTURE\n");
    printf("---------------------\n");

    printf("Controller Task : Priority %d\n",
           CONTROLLER_PRIORITY);

    printf("Safety Monitor  : Priority %d\n",
           SAFETY_PRIORITY);

    printf("Radar Task      : Priority %d\n",
           RADAR_PRIORITY);

    printf("Tracking Task   : Priority %d\n",
           TRACKING_PRIORITY);

    printf("Lead Simulator  : Priority 20\n");

    printf("Logger          : Priority %d\n",
           LOGGER_PRIORITY);

    printf("\nAll tasks created successfully.\n");
    printf("System is running...\n\n");


    /*
     * ========================================================
     * Wait for tasks
     * ========================================================
     *
     * These tasks currently run forever, so the joins keep
     * the main process alive.
     */

    pthread_join(
        lead_thread_id,
        NULL);

    pthread_join(
        radar_thread_id,
        NULL);

    pthread_join(
        tracking_thread_id,
        NULL);

    pthread_join(
        controller_thread_id,
        NULL);

    pthread_join(
        safety_thread_id,
        NULL);

    pthread_join(
        logger_thread_id,
        NULL);


    return EXIT_SUCCESS;
}
