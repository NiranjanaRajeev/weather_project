#include <stdio.h>
#include <sqlite3.h>
#include <jansson.h>
#include <string.h>

typedef struct {
    const char *db_filename;
    const char *table_name;
    // Add more parameters as needed
} Config;

int load_config(const char *filename, Config *config);
int callback(void *NotUsed, int argc, char **argv, char **azColName);
int connect_to_database(const Config *config, sqlite3 **db);
