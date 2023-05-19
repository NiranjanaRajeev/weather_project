#include "unity.h"
#include "../functions.h"

void setUp() {
    // Initialize any necessary resources before each test case
}

void tearDown() {
    // Clean up any allocated resources after each test case
}

void test_connect_to_database_success() {
    // Arrange
    Config config;
    config.db_filename = "test_weather.db";

    sqlite3 *db;
    
    // Act
    int result = connect_to_database(&config, &db);
    
    // Assert
    TEST_ASSERT_EQUAL_INT(0, result);
    TEST_ASSERT_NOT_NULL(db);
    
    // Clean up
    sqlite3_close(db);
}

void test_connect_to_database_invalid_db_filename() {
    // Arrange
    Config config;
    config.db_filename = "nonexistent.db"; // Invalid filename

    sqlite3 *db;
    
    // Act
    int result = connect_to_database(&config, &db);
    
    // Assert
    TEST_ASSERT_NOT_EQUAL_INT(0, result);
    TEST_ASSERT_NULL(db);
}

int main() {
    UNITY_BEGIN();
    
    RUN_TEST(test_connect_to_database_success);
    RUN_TEST(test_connect_to_database_invalid_db_filename);
    
    return UNITY_END();
}

