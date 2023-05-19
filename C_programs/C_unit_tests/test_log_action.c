#include "unity.h"
#include "../functions.h"

void setUp() {
    // Initialize any necessary resources before each test case
}

void tearDown() {
    // Clean up any allocated resources after each test case
}

void test_log_action_success() {
    // Arrange
    char *message = "Action logged successfully";

    // Act
    log_action(message);

    // Assert
    // Check if the log file contains the expected message
    FILE* logfile = fopen("../log.txt", "r");
    char line[100];
    int found = 0;
    while (fgets(line, sizeof(line), logfile)) {
        if (strstr(line, message) != NULL) {
            found = 1;
            break;
        }
    }
    fclose(logfile);

    TEST_ASSERT_TRUE(found);
}

int main() {
    UNITY_BEGIN();

    RUN_TEST(test_log_action_success);

    return UNITY_END();
}

