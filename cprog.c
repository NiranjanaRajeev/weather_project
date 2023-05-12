#include <stdio.h>
#include <jansson.h>

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

    return 0;
}

