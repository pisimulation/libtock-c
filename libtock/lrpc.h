#include "ipc.h"

#define IPC_DRIVER_NUM 0x10000

typedef struct procedure_description
{
    subscribe_cb *clerk;
    uint8_t num_calls;
    uint8_t arg_size;
} procedure_description;

typedef struct a_stack_info
{
    uint8_t *a_stack;
    uint8_t arg_size;
} a_stack_info;

int **export_interface(procedure_description pds[], int len);
int bind_interface(int svc_id);
