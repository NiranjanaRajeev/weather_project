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
    
    // Connect to the database
    sqlite3 *db;
    if (connect_to_database(&config, &db) != 0) {
        return 1; // Error connecting to the database
    }
    
    
    char *sql = malloc(strlen(config.table_name) + 20);
    sprintf(sql, "SELECT * FROM %s", config.table_name);
    char *err_msg = 0; 
        
    int rc = sqlite3_exec(db, sql, callback, 0, &err_msg);
    
    if (rc != SQLITE_OK ) {
        
        fprintf(stderr, "Failed to select data\n");
        fprintf(stderr, "SQL error: %s\n", err_msg);

        sqlite3_free(err_msg);
        sqlite3_close(db);
        
        return 1;
    } 
    
    sqlite3_close(db);
    // Free allocated memory for config parameters
    free((void *)config.db_filename);
    free((void *)config.table_name);
    
    return 0;
}
