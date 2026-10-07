#include "signal.h"

void signal_handle_calculation(SemaphoreHandle_t request, SemaphoreHandle_t response, struct signal_data *data)
{
    // Wait until data is available to work on
    xSemaphoreTake(request, portMAX_DELAY);
    // 'long-running work'
    data->output = data->input + 5;
    // Indicate that the work has been performed and is ready
    xSemaphoreGive(response);
}

BaseType_t signal_request_calculate(SemaphoreHandle_t request, SemaphoreHandle_t response, struct signal_data *data)
{
    // Indicate that work is available and then wait for a reasonable amount of time for the work to be completed
    // Return the status of whether the work was performed; short-circuit fail if the worker didn't respond to a prior request
    return xSemaphoreGive(request) && xSemaphoreTake(response, 10);
}