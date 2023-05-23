#include "functions.h"

void log_action(char* message) {
    FILE* logfile;
    logfile = fopen("log.txt", "a");
    
    time_t currentTime;
    struct tm *timeInfo;
    char timeString[30];

 // Get the current time
    currentTime = time(NULL);

 // Convert the current time to the local time
    timeInfo = localtime(&currentTime);

 // Format the time as "At %H:%M:%S %d-%m-%Y"
    strftime(timeString, sizeof(timeString), "At %H:%M:%S %d-%m-%Y", timeInfo);

 // Write the formatted time and message to the file
    fprintf(logfile, "%s %s\n", timeString, message);
    fclose(logfile);
}
int callback(void *data, int argc, char **argv, 
                    char **column_names) {
    
    callback_data* cb_data = (callback_data*)data;
    city_data* cities = cb_data->cities;
    int* param = cb_data->param;

    for (int i = 0; i < argc; i++) {
        if (strcmp(column_names[i], "city") == 0) {
            cities[*param].name = malloc(strlen(argv[i]) + 1);
            strcpy(cities[*param].name, argv[i]);
        }
          else if (strcmp(column_names[i], "timestamp") == 0) {
            cities[*param].timestamp = atof(argv[i]);
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
        sprintf(message, "Error: %s\n", error.text);
        log_action(message);
        return 1;
    }

    // Get the values from the JSON object
    json_t *db_obj = json_object_get(root, "database");
    config->db_filename = strdup(json_string_value(json_object_get(db_obj, "db_filename")));
    config->table_name = strdup(json_string_value(json_object_get(db_obj, "table_name")));
    
     // Get the "cities" array from the JSON object
    json_t *cities_array = json_object_get(json_object_get(root, "general"), "cities");
    if (!json_is_array(cities_array)) {
        sprintf(message, "Error: 'cities' is not an array.\n");
        log_action(message);
        json_decref(root);
        return 1;
    }
    // Check if cities array is NULL
    if (json_array_size(cities_array) == 0) {
        sprintf(message, "Error: 'cities' array is NULL.\n");
        log_action(message);
        json_decref(root);
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
    
     // Check if the database file exists
    FILE *file = fopen(db_path, "r");
    if (file == NULL) {
        fprintf(stderr, "Database file does not exist: %s\n", db_path);
        *db = NULL;
        return 1;
    }
    fclose(file);

    int rc = sqlite3_open(db_path, db);
    if (rc != SQLITE_OK) {
        sprintf(message, "Cannot open database: %s\n", sqlite3_errmsg(*db));
        log_action(message);
        sqlite3_close(*db);
        *db = NULL;
        return 1;
    }
    sprintf(message,"Connected to database");
    log_action(message);
    return 0;
}
bool is_database_updated(sqlite3 **db, int *previous_version) {
    sqlite3_stmt *statement;
    int result = sqlite3_prepare_v2(*db, "PRAGMA data_version;", -1, &statement, NULL);
    if (result != SQLITE_OK) {
        sprintf(message, "Failed to execute PRAGMA data_version: %s\n", sqlite3_errmsg(*db));
        log_action(message);
        return false;
    }
    int current_version = 0;
    result = sqlite3_step(statement);
    if (result == SQLITE_ROW) {
        current_version = sqlite3_column_int(statement, 0);
    }
    
    bool updated = false;
    if(current_version != *previous_version) {
    	sprintf(message,"Database updated");
    	log_action(message);
    	updated = true;
    	*previous_version = current_version;
    }
    else {
    	sprintf(message,"Database not updated");
    	log_action(message);
    }
    
    sqlite3_finalize(statement);
    
    return updated;

}
void* generate_files_thread(void* arg) {
    thread_data* data_thread = (thread_data*)arg;
    
    while(1) {
    	int current_city;
    	char city_message[100];
    	pthread_mutex_lock(&data_thread->mutex);
    	current_city = data_thread->current_city++;
    	pthread_mutex_unlock(&data_thread->mutex);
    	
    	if (current_city >= data_thread->num_cities) {
    	    break;
    	}
    	
    	city_data* city = &data_thread->cities[current_city];
    	
    	 // Create file for the current city
        char filename[100];
        snprintf(filename, sizeof(filename), "output/%s.csv", city->name);
        FILE* file = fopen(filename, "a");
        if (file == NULL) {
            sprintf(message, "Failed to create file for city: %s\n", city->name);
            log_action(message);
            continue;
        }
        
        long file_size;
        fseek(file, 0, SEEK_END);
        file_size = ftell(file);
        
        if(file_size == 0) {
            fprintf(file, "Name,Timestamp,Time,Temperature,Temp Min,Temp Max,Humidity\n");
        }    
        fprintf(file, "%s,%ld,%s,%.2f,%.2f,%.2f,%.2f\n",
                city->name,city->timestamp,city->time, city->temperature, city->temp_min, city->temp_max, city->humidity);
        sprintf(city_message,"Weather data updated for %s in %s.csv",city->name,city->name);
        log_action(city_message);
        // Close the file
        fclose(file);
    }
    
    return NULL;

}

// Function to handle MQTT connection status
void on_connect(struct mosquitto *mosq, void *userdata, int rc) {
    if (rc == MOSQ_ERR_SUCCESS) {
        printf("MQTT connection successful.\n");
        // Publish initial weather data here if needed
    } else {
        printf("MQTT connection failed: %s\n", mosquitto_strerror(rc));
    }
}

// Function to handle MQTT message delivery
void on_publish(struct mosquitto *mosq, void *userdata, int mid) {
    printf("MQTT message published (mid: %d)\n", mid);
}

void* publish_data_thread(void* arg) {
    publish_thread_data *publish_args = (publish_thread_data *)arg;
    city_data* copy_cities = publish_args->cities;
    int num_cities = publish_args->num_cities;
    

    // Publish data for each city
    for (int i = 0; i < num_cities; i++) {
        city_data city = copy_cities[i];
        char topic[100];
        snprintf(topic, sizeof(topic), "weather/%s", city.name);

        // Format the payload as JSON or any other desired format
        char payload[200];
        snprintf(payload, sizeof(payload), "{\"name\": \"%s\", \"timestamp\": %ld, \"time\": \"%s\", \"temperature\": %.2f, \"temp_min\": %.2f, \"temp_max\": %.2f, \"humidity\": %.2f}",
         city.name, city.timestamp, city.time, city.temperature, city.temp_min, city.temp_max, city.humidity);


        // Publish the data to the MQTT broker
        mosquitto_publish(mqtt_client, NULL, topic, strlen(payload), payload, 0, false);
    }

    return NULL;
}
/*void publish_data(city_data *cities,Config config) {
    

    // Publish data for each city
    for (int i = 0; i < config.num_cities; i++) {
        city_data city = cities[i];
        char topic[100];
        snprintf(topic, sizeof(topic), "weather/%s", city.name);

        // Format the payload as JSON or any other desired format
        char payload[200];
        snprintf(payload, sizeof(payload), "{\"name\": \"%s\", \"timestamp\": %ld, \"time\": \"%s\", \"temperature\": %.2f, \"temp_min\": %.2f, \"temp_max\": %.2f, \"humidity\": %.2f}",
         city.name, city.timestamp, city.time, city.temperature, city.temp_min, city.temp_max, city.humidity);


        // Publish the data to the MQTT broker
        mosquitto_publish(mqtt_client, NULL, topic, strlen(payload), payload, 0, false);
    }
}*/
