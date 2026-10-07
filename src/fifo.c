#include "fifo.h"

void fifo_worker_handler(QueueHandle_t requests, QueueHandle_t results, int id)
{
    struct request_msg work;

    // This is the body of the worker thread; it should always be available to accept work and never return
    while (1)
    {
        // Wait for work to be assigned, then obtain a copy of the requested work
        xQueueReceive(requests, &work, portMAX_DELAY);
        // 'long-running work'
        work.output = work.input + 5;
        work.handled_by = id;
        // Copy results out; this worker will now be available to receive more work
        xQueueSend(results, &work, portMAX_DELAY);
    }
}