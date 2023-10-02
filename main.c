#include <stdio.h>
#include <string.h>  // Include the string.h header for strcmp and strcpy
#include <stdlib.h> 

#ifndef CONFIG_H


// Define a structure to store configuration settings
typedef struct {
    char database_host[100];
    int database_port;
    int max_connections;
    int debug_mode;
} Config;

// Function to read configuration values from the config file
int read_config(const char *filename, Config *config);

#endif /* CONFIG_H */


int read_config(const char *filename, Config *config) {
    FILE *config_file = fopen(filename, "r");
    if (config_file == NULL) {
        perror("Error opening config file");
        return 1;
    }

    char line[256];
    while (fgets(line, sizeof(line), config_file)) {
        char key[100];
        char value[100];

        // Parse key-value pairs
        if (sscanf(line, "%99s = %99s", key, value) == 2) {
            if (strcmp(key, "database_host") == 0) {
                strcpy(config->database_host, value);
            } else if (strcmp(key, "database_port") == 0) {
                config->database_port = atoi(value);
            } else if (strcmp(key, "max_connections") == 0) {
                config->max_connections = atoi(value);
            } else if (strcmp(key, "debug_mode") == 0) {
                config->debug_mode = (strcmp(value, "true") == 0);
            }
        }
    }

    fclose(config_file);
    return 0;
}



int main() {
    Config config;

    // Read configuration values from the config file
    if (read_config("config.txt", &config) != 0) {
        printf("Failed to read config file.\n");
        return 1;
    }

    // Use configuration values
    printf("Database Host: %s\n", config.database_host);
    printf("Database Port: %d\n", config.database_port);
    printf("Max Connections: %d\n", config.max_connections);
    printf("Debug Mode: %s\n", config.debug_mode ? "true" : "false");

    return 0;
}
