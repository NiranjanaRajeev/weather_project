#include "unity.h"
#include "../functions.h"

void setUp(void) {
    // Set up any necessary resources before each test
}

void tearDown(void) {
    // Clean up any resources after each test
}

void test_load_config(void) {
    const char *filename = "test_config.json";
    Config config;

    // Test loading a valid configuration file
    TEST_ASSERT_EQUAL_INT(0, load_config(filename, &config));
    TEST_ASSERT_EQUAL_STRING("weather.db", config.db_filename);
    TEST_ASSERT_EQUAL_STRING("weather_data", config.table_name);
    TEST_ASSERT_EQUAL_INT(7, config.num_cities);
    TEST_ASSERT_EQUAL_STRING("Toulouse", config.city_array[0]);
    TEST_ASSERT_EQUAL_STRING("Nantes", config.city_array[1]);
    TEST_ASSERT_EQUAL_STRING("Nice", config.city_array[2]);

    // Test loading a non-existent configuration file
    TEST_ASSERT_EQUAL_INT(1, load_config("nonexistent.json", &config));

    // Test loading an invalid configuration file
    TEST_ASSERT_EQUAL_INT(1, load_config("invalid_config.json", &config));
}

void test_invalid_config_num_cities(void) {
    const char *filename = "invalid_num_cities.json";
    Config config;

    // Test loading an invalid configuration file with empty cities array
    TEST_ASSERT_EQUAL_INT(1, load_config(filename, &config));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_load_config);
    RUN_TEST(test_invalid_config_num_cities);
    return UNITY_END();
}
