#include <lrpc.h>
#include <led.h>
#include <tock.h>

// This service returns the number of led on the board.
// ok to assume that client knows service name, number assoc. w procedures
// goal is to write manual "auto generated" code
uint8_t *set_led_a_stack;
uint8_t *get_led_count_a_stack;
int set_led_num_calls = 2;
int get_led_count_num_calls = 2;
int set_led_arg_size = 1;
int get_led_count_arg_size = 1; // No argument required but service has to return a value, so arg size is 1.

static uint8_t get_led_count()
{
  int count = led_count();
  printf("PI: server number of LED is %d", count);
  return count;
}

static void set_led(uint8_t led_state, uint8_t led_id)
{
  if (led_state == 0)
  {
    led_off(led_id);
  }
  else
  {
    led_on(led_id);
  }
}


void set_led_clerk(__attribute__((unused)) int pid,
                   __attribute__((unused)) int len,
                   __attribute__((unused)) int arg2,
                   __attribute__((unused)) void *ud)
{
}

// This function corresponds to the binding clerk.
// responds to `bind_interface`.
void get_led_count_clerk(int clientPid,
                         __attribute__((unused)) int arg2,
                         __attribute__((unused)) int arg3,
                         __attribute__((unused)) void *ud)
{
  // Allocate A-stack.
  /*
    allow(driver: u32, allow_number: u32, pointer: usize, size: u32) -> ReturnCode as u32
        Arguments
        driver: An integer specifying which driver should be granted access.
        allow_number: A driver-specific integer specifying the purpose of this buffer.
        pointer: A pointer to the start of the buffer in the process memory space.
        size: An integer number of bytes specifying the length of the buffer.
    command(driver: u32, command_number: u32, argument1: u32, argument2: u32) -> ReturnCode as u32
        Arguments
        driver: An integer specifying which driver to call.
        command_number: An integer specifying the requested command.
        argument1: A command-specific argument.
        argument2: A command-specific argument.
    */
  int a_stack_size = get_led_count_arg_size * get_led_count_num_calls;
  // TODO: should be statically alloc
  char a_stack[a_stack_size];
  // Share an a_stack with a client
  allow(IPC_DRIVER_NUM, clientPid, a_stack, a_stack_size);
  // Notify client that it is ready
  // QUESTION: How does client know where a-stack is alloc?
  command(IPC_DRIVER_NUM, clientPid, 0, 0);
}

int main(void)
{
  printf("HELLO led LRPC\n");
  procedure_description pds[1];
  // pds[0].clerk = set_led_clerk;
  // pds[0].arg_size = set_led_arg_size;
  // pds[0].num_calls = set_led_num_calls;
  pds[0].clerk = get_led_count_clerk;
  pds[0].arg_size = get_led_count_arg_size;
  pds[0].num_calls = get_led_count_num_calls;

  export_interface(pds, 1);
  return 0;
}
