#include "lrpc.h"

int **export_interface(procedure_description pds[], int len)
{
    printf("exporting interface");
    for (int i = 0; i < len; i++)
    {
        /*
    subscribe(driver: u32, subscribe_number: u32, callback: u32, userdata: u32) -> ReturnCode as u32
        Arguments
        driver: An integer specifying which driver to call.
        subscribe_number: An integer index for which function is being subscribed.
        callback: A pointer to a callback function to be executed when this event occurs. All callbacks conform to the C-style function signature: void callback(int arg1, int arg2, int arg3, void* data).
        userdata: A pointer to a value of any type that will be passed back by the kernel as the last argument to callback.
    */
        subscribe(IPC_DRIVER_NUM, 0, pds[i].clerk, NULL);
    }
    return 0;
}

int bind_interface(int svc_id)
{

    // use `command` to invoke binding / notify server
    /*
    command(driver: u32, command_number: u32, argument1: u32, argument2: u32) -> ReturnCode as u32
        Arguments
        driver: An integer specifying which driver to call.
        command_number: An integer specifying the requested command.
        argument1: A command-specific argument.
        argument2: A command-specific argument.
    */
    return command(IPC_DRIVER_NUM, svc_id, 0, 0);
    // Also subscribes to service to know where to continue when done.
    // subscribe(IPC_DRIVER_NUM, svc_id, client_cb, NULL);
    // give client A stack info
    //return 0;
}

// int lrpc_call(const char *procedure_name, )
// {
// }