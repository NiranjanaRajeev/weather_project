#include "unity.h"
#include "../functions.h"

void setUp() {
    // Initialize any necessary resources before each test case
}

void tearDown() {
    // Clean up any allocated resources after each test case
}

void test_callback() {
    // Arrange
    callback_data cb_data;
    city_data cities[2]; // Assuming we have an array of city_data with two elements
    int param = 0;
    cb_data.cities = cities;
    cb_data.param = &param;

    // Test case 1
    char* argv1[] = {"New York", "16873774747", "12:00", "25.5", "20.2", "30.7", "80"};
    char* column_names1[] = {"city", "timestamp", "time", "temperature", "temp_min", "temp_max", "humidity"};
    int argc1 = sizeof(argv1) / sizeof(argv1[0]);

    // Act
    int result1 = callback(&cb_data, argc1, argv1, column_names1);

    // Assert
    TEST_ASSERT_EQUAL_INT(0, result1);
    TEST_ASSERT_EQUAL_STRING("New York", cities[0].name);
    TEST_ASSERT_EQUAL_INT(16873774747, cities[0].timestamp);
    TEST_ASSERT_EQUAL_STRING("12:00", cities[0].time);
    TEST_ASSERT_FLOAT_WITHIN(0.001, 25.5f, cities[0].temperature);
    TEST_ASSERT_FLOAT_WITHIN(0.001, 20.2f, cities[0].temp_min);
    TEST_ASSERT_FLOAT_WITHIN(0.001, 30.7f, cities[0].temp_max);
    TEST_ASSERT_FLOAT_WITHIN(0.001, 80.0f, cities[0].humidity);
    TEST_ASSERT_EQUAL_INT(1, param);

    // Test case 2
    char* argv2[] = {"Paris", "16873774747", "18:30", "22.8", "18.5", "26.7", "75"};
    char* column_names2[] = {"city", "timestamp", "time", "temperature", "temp_min", "temp_max", "humidity"};
    int argc2 = sizeof(argv2) / sizeof(argv2[0]);

    // Act
    int result2 = callback(&cb_data, argc2, argv2, column_names2);

    // Assert
    TEST_ASSERT_EQUAL_INT(0, result2);
    TEST_ASSERT_EQUAL_STRING("Paris", cities[1].name);
    TEST_ASSERT_EQUAL_INT(16873774747, cities[1].timestamp);
    TEST_ASSERT_EQUAL_STRING("18:30", cities[1].time);
    TEST_ASSERT_FLOAT_WITHIN(0.001, 22.8f, cities[1].temperature);
    TEST_ASSERT_FLOAT_WITHIN(0.001, 18.5f, cities[1].temp_min);
    TEST_ASSERT_FLOAT_WITHIN(0.001, 26.7f, cities[1].temp_max);
    TEST_ASSERT_FLOAT_WITHIN(0.001, 75.0f, cities[1].humidity);
    TEST_ASSERT_EQUAL_INT(2, param);
}

void test_callback_invalid_column_name() {
    // Arrange
    callback_data cb_data;
    city_data cities[1];
    int param = 0;
    cb_data.cities = cities;
    cb_data.param = &param;

    char* argv[] = {"New York", "16873774747", "12:00", "25.5", "20.2", "30.7", "80"};
    char* column_names[] = {"city", "timestamp", "time", "temperature", "unknown_column", "temp_max", "humidity"};
    int argc = sizeof(argv) / sizeof(argv[0]);

    // Act
    int result = callback(&cb_data, argc, argv, column_names);

    // Assert
    TEST_ASSERT_EQUAL_INT(0, result);
    TEST_ASSERT_EQUAL_STRING("New York", cities[0].name);
    TEST_ASSERT_EQUAL_INT(16873774747, cities[0].timestamp);
    TEST_ASSERT_EQUAL_STRING("12:00", cities[0].time);
    TEST_ASSERT_FLOAT_WITHIN(0.001, 25.5f, cities[0].temperature);
    TEST_ASSERT_FLOAT_WITHIN(0.001, 0.0f, cities[0].temp_min); // Unknown column, default value
    TEST_ASSERT_FLOAT_WITHIN(0.001, 30.7f, cities[0].temp_max);
    TEST_ASSERT_FLOAT_WITHIN(0.001, 80.0f, cities[0].humidity);
    TEST_ASSERT_EQUAL_INT(1, param);
}

int main() {
    UNITY_BEGIN();

    RUN_TEST(test_callback);
    RUN_TEST(test_callback_invalid_column_name);

    return UNITY_END();
}

