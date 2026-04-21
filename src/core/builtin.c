#include "../dependency/shell.h"

int shell_exit(char **args){
    (void)args;
    const char *charging[] = {
        "[            ]",
        "[=           ]",
        "[==          ]",
        "[===         ]",
        "[====        ]",
        "[=====       ]",
        "[======      ]",
        "[=======     ]",
        "[========    ]",
        "[=========   ]",
        "[==========  ]",
        "[=========== ]",
        "[=============]",
    };
    const int frames = sizeof(charging) / sizeof(charging[0]);

    printf(G"Shutting down...\n"RST);

    // Loop through the "charging" animation for 3 seconds
    for (int i = 0; i < frames; i++) {
        printf("\r" Y "%s" RST, charging[i]);
        fflush(stdout);  // Force update the console
        usleep(421337);  
    }
    printf(C"\n EXIT \n"RST);
    return EX_OK;
}

