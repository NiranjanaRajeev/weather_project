#include <stdio.h>
#include <sqlite3.h>
#include <jansson.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>
#include <mosquitto.h>

typedef struct {
    const char *db_filename;
    const char *table_name;
    const char **city_array;
    int num_cities;       
    // Add more parameters as needed
} Config;

typedef struct {
    char *name;
    long int timestamp;
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

typedef struct {
    city_data* cities;
    int num_cities;
    int current_city;
    pthread_mutex_t mutex;
} thread_data;

typedef struct {
    city_data* cities;
    int num_cities;
} publish_thread_data;

char message[200];
// MQTT publisher variables
struct mosquitto *mqtt_client;

int load_config(const char *filename, Config *config);
int callback(void *data, int argc, char **argv, char **column_names);
int connect_to_database(const Config *config, sqlite3 **db);
bool is_database_updated(sqlite3 **db, int *previous_version);
void* generate_files_thread(void* arg);
void log_action(char* message);

void on_connect(struct mosquitto *mosq, void *userdata, int rc);
void on_publish(struct mosquitto *mosq, void *userdata, int mid);
//void publish_data(city_data *cities,Config config);
void* publish_data_thread(void* arg);
