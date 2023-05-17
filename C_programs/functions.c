#include "functions.h"

int callback(void *data, int argc, char **argv, 
                    char **column_names) {
    
    callback_data* cb_data = (callback_data*)data;
    city_data* cities = cb_data->cities;
    int* param = cb_data->param;

    for (int i = 0; i < argc; i++) {
        if (strcmp(column_names[i], "city") == 0) {
            cities[*param].name = malloc(strlen(argv[i]) + 1);
            strcpy(cities[*param].name, argv[i]);
        } else if (strcmp(column_names[i], "time") == 0) {
            cities[*param].time = malloc(strlen(argv[i]) + 1);
            strcpy(cities[*param].time, argv[i]);
        } else if (strcmp(column_names[i], "temperature") == 0) {
            cities[*param].temperature = atof(argv[i]);
        } else if (strcmp(column_names[i], "temp_min") == 0) {
            cities[*param].temp_min = atof(argv[i]);
        } else if (strcmp(column_names[i], "temp_max") == 0) {
            cities[*param].temp_max = atof(argv[i]);
        } else if (strcmp(column_names[i], "humidity") == 0) {
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
bool is_database_updated(sqlite3 **db, int *previous_version) {
    sqlite3_stmt *statement;
    int result = sqlite3_prepare_v2(*db, "PRAGMA data_version;", -1, &statement, NULL);
    if (result != SQLITE_OK) {
        fprintf(stderr, "Failed to execute PRAGMA data_version: %s\n", sqlite3_errmsg(*db));
        return false;
    }
    int current_version = 0;
    result = sqlite3_step(statement);
    if (result == SQLITE_ROW) {
        current_version = sqlite3_column_int(statement, 0);
    }
    
    bool updated = false;
    if(current_version != *previous_version) {
    	printf("Database updated \n");
    	updated = true;
    	*previous_version = current_version;
    }
    else {
    	printf("Database not updated \n");
    }
    
    sqlite3_finalize(statement);
    
    return updated;

}
void* generate_files_thread(void* arg) {
    thread_data* data_thread = (thread_data*)arg;
    
    while(1) {
    	int current_city;
    	pthread_mutex_lock(&data_thread->mutex);
    	current_city = data_thread->current_city++;
    	pthread_mutex_unlock(&data_thread->mutex);
    	
    	if (current_city >= data_thread->num_cities) {
    	    break;
    	}
    	
    	city_data* city = &data_thread->cities[current_city];
    	
    	 // Create file for the current city
        char filename[100];
        snprintf(filename, sizeof(filename), "../output/%s.csv", city->name);
        FILE* file = fopen(filename, "a");
        if (file == NULL) {
            fprintf(stderr, "Failed to create file for city: %s\n", city->name);
            continue;
        }
        
        long file_size;
        fseek(file, 0, SEEK_END);
        file_size = ftell(file);
        
        if(file_size == 0) {
            fprintf(file, "Name,Time,Temperature,Temp Min,Temp Max,Humidity\n");
        }    
        fprintf(file, "%s,%s,%.2f,%.2f,%.2f,%.2f\n",
                city->name, city->time, city->temperature, city->temp_min, city->temp_max, city->humidity);

        // Close the file
        fclose(file);
    }
    
    return NULL;

}	

