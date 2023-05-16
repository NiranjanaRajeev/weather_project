#include <stdio.h>
#include <jansson.h>
#include <sqlite3.h>
#include <string.h>
#include "functions.h"

int main() {
    const char *config_filename = "../config.json";
    Config config;
    
    if (load_config(config_filename, &config) != 0) {
        return 1; // Error loading configuration
    }
    
    printf("db_filename: %s\n", config.db_filename);
    printf("table_name: %s\n", config.table_name);
     printf("Cities:\n");
    for (int i = 0; i < config.num_cities; i++) {
         printf("- %s\n", config.city_array[i]);
    }
    printf("number of cities: %d \n", config.num_cities);
    
    // Connect to the database
    sqlite3 *db;
    if (connect_to_database(&config, &db) != 0) {
        return 1; // Error connecting to the database
    }
    city_data cities[config.num_cities];  // Array of city_data structures
    int value = 0;   

    // Create the callback data structure
    callback_data cb_data;
    cb_data.cities = cities;
    cb_data.param = &value;

    char *sql = malloc(strlen(config.table_name) + 20);
    sprintf(sql, "SELECT * FROM %s", config.table_name);
    char *err_msg = 0; 
        
    int rc = sqlite3_exec(db, sql, callback, &cb_data, &err_msg);
    

    if (rc != SQLITE_OK ) {
        
        fprintf(stderr, "Failed to select data\n");
        fprintf(stderr, "SQL error: %s\n", err_msg);

        sqlite3_free(err_msg);
        sqlite3_close(db);
        
        return 1;
    } 
    for (int i = 0; i < config.num_cities; i++) {
        printf("City: %s\n", cities[i].name);
        printf("Time: %s\n", cities[i].time);
        printf("Temperature: %.2f\n", cities[i].temperature);
        printf("Temp Min: %.2f\n", cities[i].temp_min);
        printf("Temp Max: %.2f\n", cities[i].temp_max);
        printf("Humidity: %.2f\n", cities[i].humidity);
        printf("\n");
    }
    sqlite3_close(db);
    // Free allocated memory for config parameters
    free((void *)config.db_filename);
    free((void *)config.table_name);
    for (size_t i = 0; i < config.num_cities; i++) {
        free((void *)config.city_array[i]);
    }
    free(config.city_array);
    
    return 0;
}
