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
    
    
    int previous_version = 0;
    while(1) {
    	if(is_database_updated(&db,&previous_version)) {
    	   clock_t start = clock();
    	   char *sql = malloc(strlen(config.table_name) + 20);
           sprintf(sql, "SELECT * FROM %s", config.table_name);
           char *err_msg = 0; 
           city_data cities[config.num_cities];  // Array of city_data structures
           int value = 0;  

           // Create the callback data structure
           callback_data cb_data;
           cb_data.cities = cities;
           cb_data.param = &value;
           int rc = sqlite3_exec(db, sql, callback, &cb_data, &err_msg);
    

           if (rc != SQLITE_OK ) {
        
             sprintf(message, "Failed to select data\n");
             log_action(message);
             sprintf(message, "SQL error: %s\n", err_msg);
             log_action(message);
             sqlite3_free(err_msg);
             sqlite3_close(db);
        
             return 1;
            } 
           
           pthread_t threads[5];
           thread_data data_thread;
           data_thread.cities = cities;
           data_thread.num_cities = config.num_cities;
           data_thread.current_city = 0;
           pthread_mutex_init(&data_thread.mutex, NULL);
           
           for (int i = 0; i < 4 ; i++) {
           	pthread_create(&threads[i], NULL, generate_files_thread, &data_thread);
           }
           
           for (int i = 0; i < 4; i++) {
           	pthread_join(threads[i], NULL);
           }
           pthread_mutex_destroy(&data_thread.mutex);
           clock_t end = clock();
           double execution_time = (double)(end - start) / CLOCKS_PER_SEC;
           printf("Execution Time: %.4f seconds\n", execution_time);
         }
         sleep(120);
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
