#include <stdio.h>
#include <sqlite3.h>
#include <jansson.h>
#include <string.h>

typedef struct {
    const char *db_filename;
    const char *table_name;
    const char **city_array;  // Array of city names
    int num_cities;       // Number of cities
    // Add more parameters as needed
} Config;

typedef struct {
    char *name;
    char *time;
    float temperature;
    float temp_min;
    float temp_max;
    float humidity;
} city_data;

typedef struct {
    city_data* cities;
    int* param;
} callback_data;



int load_config(const char *filename, Config *config);
int callback(void *data, int argc, char **argv, char **azColName);
int connect_to_database(const Config *config, sqlite3 **db);
