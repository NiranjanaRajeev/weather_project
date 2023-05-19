#include "unity.h"
#include "../functions.h"

void setUp() {
    // Initialize any necessary resources before each test case
}

void tearDown() {
    // Clean up any allocated resources after each test case
}

void test_is_database_updated_no_database_file() {
    // Arrange
    Config config;
    config.db_filename = "test_update_weather.db";

    sqlite3* db = NULL;
    int previous_version = 0;

    // Act
    bool result = is_database_updated(&db, &previous_version);

    // Assert
    TEST_ASSERT_FALSE(result);

    // Clean up
    sqlite3_close(db);
}

void test_is_database_updated_empty_database_file() {
    // Arrange
    Config config;
    config.db_filename = "test_update_weather.db";

    // Create an empty database file
    FILE* db_file = fopen("test_update_weather.db", "w");
    fclose(db_file);

    sqlite3* db = NULL;
    int previous_version = 0;

    // Act
    bool result = is_database_updated(&db, &previous_version);

    // Assert
    TEST_ASSERT_FALSE(result);

    // Clean up
    sqlite3_close(db);
    remove("test_update_weather.db");
}

void test_is_database_updated_with_records() {
    // Arrange
    Config config;
    config.db_filename = "test_update_weather.db";

    sqlite3* db = NULL;
    int previous_version = 0;

    // Open the database
    int rc = sqlite3_open("test_update_weather.db", &db);
    TEST_ASSERT_EQUAL_INT(SQLITE_OK, rc);

    // Execute a query to create a table and insert a record
    char* create_table_query = "CREATE TABLE weather_data (city TEXT, timestamp INTEGER)";
    char* insert_record_query = "INSERT INTO weather_data (city, timestamp) VALUES ('New York', 1621440000)";
    rc = sqlite3_exec(db, create_table_query, 0, 0, 0);
    TEST_ASSERT_EQUAL_INT(SQLITE_OK, rc);
    rc = sqlite3_exec(db, insert_record_query, 0, 0, 0);
    TEST_ASSERT_EQUAL_INT(SQLITE_OK, rc);

    // Act
    bool result = is_database_updated(&db, &previous_version);

    // Assert
    TEST_ASSERT_TRUE(result);

    // Clean up
    sqlite3_close(db);
    remove("test_update_weather.db");
}

void test_is_database_updated_no_updates() {
    // Arrange
    Config config;
    config.db_filename = "test_update_weather.db";

    sqlite3* db = NULL;
    int previous_version = 1;  // Set the previous version to the same value as the current version

    // Open the database
    int rc = sqlite3_open("test_update_weather.db", &db);
    TEST_ASSERT_EQUAL_INT(SQLITE_OK, rc);

    // Act
    bool result = is_database_updated(&db, &previous_version);

    // Assert
    TEST_ASSERT_FALSE(result);

    // Clean up
    sqlite3_close(db);
    remove("test_update_weather.db");
}

int main() {
    UNITY_BEGIN();

    RUN_TEST(test_is_database_updated_no_database_file);
    RUN_TEST(test_is_database_updated_empty_database_file);
    RUN_TEST(test_is_database_updated_with_records);
    RUN_TEST(test_is_database_updated_no_updates);

    return UNITY_END();
}

