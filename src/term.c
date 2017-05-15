#include <term.h>
#include <API.h>
#include <input.h>
#include <string.h>

void term_thread(void* x)
{
    char read[256];
    while(true)
    {
        if(fread(read, 1, 256, stdin) > 0) {
            if(strcmp(read, "record") == 0)
    	    {
    		    printf("Starting recording!");
    		    start_recording();
    	    }
    	    else if(strcmp(read, "stop") == 0)
    	    {
    		    printf("Stopping recording!");
    		    stop_recording();
    	    }
            else if(strcmp(read, "save ") == 0)
            {
                char filename[strlen(read) - 4];
    		    memcpy(&filename[0], &read[strlen(read) - 4], strlen(read) - 4);

                autonomous_save(filename);
            }
            else if(strcmp(read, "load ") == 0)
            {
                char filename[strlen(read) - 4];
    		    memcpy(&filename[0], &read[strlen(read) - 4], strlen(read) - 4);

                autonomous_load(filename);
            }
        }
    }
}

void term_init()
{
    taskCreate(term_thread, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
}
