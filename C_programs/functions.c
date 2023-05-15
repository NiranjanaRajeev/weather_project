#include "functions.h"

int callback(void *NotUsed, int argc, char **argv, 
                    char **azColName) {
    
    NotUsed = 0;
    
    for (int i = 0; i < argc; i++) {

        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    
    printf("\n");
    
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
    // Load more parameters as needed

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
