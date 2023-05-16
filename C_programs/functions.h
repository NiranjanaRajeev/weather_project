#include <stdio.h>
#include <sqlite3.h>
#include <jansson.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

typedef struct {
    const char *db_filename;
    const char *table_name;
    const char **city_array;
    int num_cities;       
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
int callback(void *data, int argc, char **argv, char **column_names);
int connect_to_database(const Config *config, sqlite3 **db);
void generate_files(const city_data* cities, int no_cities, const char* output_dir);
bool is_database_updated(sqlite3 **db, int *previous_version);
