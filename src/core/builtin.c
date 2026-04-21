#include "../dependency/shell.h"

int shell_cd(char **args)
{
    char    *path;
    char    oldpwd[BUFSIZ];
    char    newpwd[BUFSIZ];

    if (args[1] != NULL && args[2] != NULL)
    {
        fprintf(stderr, "cd: too many arguments\n");
        return (EX_USAGE);
    }
    if (Getcwd(oldpwd, sizeof(oldpwd)) == NULL)
        oldpwd[0] = '\0';
    if (args[1] == NULL)
    {
        path = getenv("HOME");
        if (path == NULL || *path == '\0')
        {
            fprintf(stderr, "cd: HOME not set\n");
            return (EX_USAGE);
        }
    }
    else if (strcmp(args[1], "-") == 0)
    {
        path = getenv("OLDPWD");
        if (path == NULL || *path == '\0')
        {
            fprintf(stderr, "cd: OLDPWD not set\n");
            return (EX_USAGE);
        }
        printf("%s\n", path);
    }
    else
        path = args[1];
    if (chdir(path) != 0)
    {
        perror("cd");
        return (errno);
    }
    if (oldpwd[0] != '\0')
        setenv("OLDPWD", oldpwd, 1);
    if (Getcwd(newpwd, sizeof(newpwd)) != NULL)
        setenv("PWD", newpwd, 1);
    return (EX_OK);
}

int shell_fetch(char **args)
{
    struct utsname  info;
    char            cwd[BUFSIZ];
    char            host[256];
    const char      *user;
    const char      *home;
    const char      *shell_name;

    if (args[1] != NULL)
    {
        fprintf(stderr, "fetch: too many arguments\n");
        return (EX_USAGE);
    }
    user = getenv("USER");
    if (user == NULL || *user == '\0')
        user = "unknown";
    home = getenv("HOME");
    if (home == NULL || *home == '\0')
        home = "unknown";
    if (shell_name == NULL || *shell_name == '\0')
        shell_name = "c-shell";
    if (Getcwd(cwd, sizeof(cwd)) == NULL)
        strcpy(cwd, "unknown");
    if (gethostname(host, sizeof(host)) != 0)
        strcpy(host, "unknown");
    else
        host[sizeof(host) - 1] = '\0';
    if (uname(&info) != 0)
    {
        perror("fetch");
        return (errno);
    }
    printf(C "      ____      " RST "%s@%s\n", user, host);
    printf(C "   .-' __ '-.   " RST "OS: %s\n", info.sysname);
    printf(C "  / .'    '. \\  " RST "Kernel: %s\n", info.release);
    printf(C "  | |  __  | |  " RST "Machine: %s\n", info.machine);
    printf(C "  | | |  | | |  " RST "Shell: %s\n", shell_name);
    printf(C "  | | |__| | |  " RST "Home: %s\n", home);
    printf(C "  \\ '.____.' /  " RST "PWD: %s\n", cwd);
    printf(C "   '-.____.-'   " RST "\n");
    return (EX_OK);
}

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
    exit(EX_OK);
}

