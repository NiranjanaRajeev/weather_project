#include <stdio.h>
#include <jansson.h>
#include <sqlite3.h>
#include <string.h>

int callback(void *NotUsed, int argc, char **argv, 
                    char **azColName) {
    
    NotUsed = 0;
    
    for (int i = 0; i < argc; i++) {

        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    
    printf("\n");
    
    return 0;
}

int main() {
    json_t *root;
    json_error_t error;
    const char *db_filename, *table_name;

    // Open and parse the config file
    root = json_load_file("config.json", 0, &error);
    if (!root) {
        fprintf(stderr, "Error: %s\n", error.text);
        return 1;
    }

    // Get the values from the JSON object

    db_filename = json_string_value(json_object_get(json_object_get(root, "database"), "db_filename"));
    table_name = json_string_value(json_object_get(json_object_get(root, "database"), "table_name"));

    // Print the values to verify that they were correctly assigned

    printf("db_filename: %s\n", db_filename);
    printf("table_name: %s\n", table_name);
    sqlite3 *db;
    char *err_msg = 0;
    int rc = sqlite3_open(db_filename,&db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s \n",sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
        }
    char *sql = malloc(strlen(table_name) + 20); 
    sprintf(sql, "SELECT * FROM %s", table_name); 
        
    rc = sqlite3_exec(db, sql, callback, 0, &err_msg);
    
    if (rc != SQLITE_OK ) {
        
        fprintf(stderr, "Failed to select data\n");
        fprintf(stderr, "SQL error: %s\n", err_msg);

        sqlite3_free(err_msg);
        sqlite3_close(db);
        
        return 1;
    } 
    
    sqlite3_close(db);
    
    return 0;
}

