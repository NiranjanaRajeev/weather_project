#include "unity.h"
#include "../functions.h"

void setUp() {
    // Initialize any necessary resources before each test case
}

void tearDown() {
    // Clean up any allocated resources after each test case
}

void test_generate_files_thread_valid_data() {
    // Create a mock thread data with city information
    thread_data data_thread;
    data_thread.num_cities = 2;
    data_thread.current_city = 0;
    pthread_mutex_init(&data_thread.mutex, NULL);

    city_data cities[2];
    cities[0].name = "New York";
    cities[0].timestamp = 1621440000;
    cities[0].time = "12:00 PM";
    cities[0].temperature = 25.5;
    cities[0].temp_min = 20.0;
    cities[0].temp_max = 30.0;
    cities[0].humidity = 70.0;
    cities[1].name = "London";
    cities[1].timestamp = 1621440000;
    cities[1].time = "5:00 PM";
    cities[1].temperature = 18.9;
    cities[1].temp_min = 15.0;
    cities[1].temp_max = 20.0;
    cities[1].humidity = 65.0;

    data_thread.cities = cities;

    // Act
    generate_files_thread(&data_thread);

    // Assert
    // Check if the output files were generated
    FILE* file1 = fopen("output/New York.csv", "r");
    FILE* file2 = fopen("output/London.csv", "r");

    TEST_ASSERT_NOT_NULL(file1);
    TEST_ASSERT_NOT_NULL(file2);

    fclose(file1);
    fclose(file2);

    // Clean up
    remove("output/New York.csv");
    remove("output/London.csv");
}

int main() {
    UNITY_BEGIN();

    RUN_TEST(test_generate_files_thread_valid_data);

    return UNITY_END();
}


