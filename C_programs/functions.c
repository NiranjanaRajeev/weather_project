#include "functions.h"

int callback(void *data, int argc, char **argv, 
                    char **columnNames) {
    
    callback_data* cb_data = (callback_data*)data;
    city_data* cities = cb_data->cities;
    int* param = cb_data->param;

    for (int i = 0; i < argc; i++) {
        if (strcmp(columnNames[i], "city") == 0) {
            cities[*param].name = malloc(strlen(argv[i]) + 1);
            strcpy(cities[*param].name, argv[i]);
        } else if (strcmp(columnNames[i], "time") == 0) {
            cities[*param].time = malloc(strlen(argv[i]) + 1);
            strcpy(cities[*param].time, argv[i]);
        } else if (strcmp(columnNames[i], "temperature") == 0) {
            cities[*param].temperature = atof(argv[i]);
        } else if (strcmp(columnNames[i], "temp_min") == 0) {
            cities[*param].temp_min = atof(argv[i]);
        } else if (strcmp(columnNames[i], "temp_max") == 0) {
            cities[*param].temp_max = atof(argv[i]);
        } else if (strcmp(columnNames[i], "humidity") == 0) {
            cities[*param].humidity = atof(argv[i]);
        }
    }
    (*param)++;
    
    return 0;
}

int load_config(const char *filename, Config *config) {
    json_t *root;
    json_error_t error;

    // Open and parse the config file
    root = json_load_file(filename, 0, &error);
    if (!root) {
        fprintf(stderr, "Error: %s\n", error.text);
        return 1;
    }

    // Get the values from the JSON object
    json_t *db_obj = json_object_get(root, "database");
    config->db_filename = strdup(json_string_value(json_object_get(db_obj, "db_filename")));
    config->table_name = strdup(json_string_value(json_object_get(db_obj, "table_name")));
    
     // Get the "cities" array from the JSON object
    json_t *cities_array = json_object_get(json_object_get(root, "general"), "cities");
    if (!json_is_array(cities_array)) {
        fprintf(stderr, "Error: 'cities' is not an array.\n");
        return 1;
    }

    // Store the city names in the Config structure
    config->num_cities = json_array_size(cities_array);
    config->city_array = (const char **)malloc(config->num_cities * sizeof(const char *));
    for (size_t i = 0; i < config->num_cities; i++) {
        json_t *city_value = json_array_get(cities_array, i);
        config->city_array[i] = strdup(json_string_value(city_value));
    }
    json_decref(root);
    return 0;
}

int connect_to_database(const Config *config, sqlite3 **db) {
    char db_path[100]; 
    snprintf(db_path, sizeof(db_path), "../%s", config->db_filename);

    int rc = sqlite3_open(db_path, db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(*db));
        sqlite3_close(*db);
        return 1;
    }

    return 0;
}




