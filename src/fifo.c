#include "fifo.h"

void fifo_worker_handler(QueueHandle_t requests, QueueHandle_t results, int id)
{
    struct request_msg work;

    while (1)
    {
        xQueueReceive(requests, &work, portMAX_DELAY);
        work.output = work.input + 5;
        work.handled_by = id;
        xQueueSend(results, &work, portMAX_DELAY);
    }
}