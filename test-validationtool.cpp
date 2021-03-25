#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "sensor-validate.h"


/*----------------------------------------------------------------------------------
 * SoC Sensor Tests
 */
TEST_CASE("reports error when soc jumps abruptly - Upward Spike") {
  double socReadings[] = {0.0, 0.01, 0.5, 0.51};
  int numOfSocReadings = sizeof(socReadings) / sizeof(socReadings[0]);
  REQUIRE(validateSOCreadings(socReadings, numOfSocReadings) == false);
}

TEST_CASE("reports error when soc jumps abruptly - Downward Spike") {
  double socReadings[] = {0.51, 0.01, 0.5, 0.1};
  int numOfSocReadings = sizeof(socReadings) / sizeof(socReadings[0]);
  REQUIRE(validateSOCreadings(socReadings, numOfSocReadings) == false);
}

TEST_CASE("reports error when empty SOC data is sent") {
  double socReadings[] = {};
  REQUIRE(validateSOCreadings(socReadings, 0) == false);
}

TEST_CASE("reports no error when single SoC reading is passed") {
  double socReadings[] = {0.01};
  int numOfSocReadings = sizeof(socReadings) / sizeof(socReadings[0]);
  REQUIRE(validateSOCreadings(socReadings, numOfSocReadings) == true);
}

/*----------------------------------------------------------------------------------
 *  Current Sensor Tests
 */

TEST_CASE("reports error when current jumps abruptly - Upward Spike") {
  double currentReadings[] = {0.03, 0.03, 0.03, 0.33};
  int numOfCurReadings = sizeof(currentReadings) / sizeof(currentReadings[0]);
  REQUIRE(validateCurrentreadings(currentReadings, numOfCurReadings) == false);
}

TEST_CASE("reports error when current jumps abruptly - Downward Spike") {
  double currentReadings[] = {0.03, 0.03, 0.03, 0.33};
  int numOfCurReadings = sizeof(currentReadings) / sizeof(currentReadings[0]);
  REQUIRE(validateCurrentreadings(currentReadings, numOfCurReadings) == false);
}

TEST_CASE("reports error when empty current data is sent") {
  double currentReadings[] = {};
  REQUIRE(validateCurrentreadings(currentReadings, 0) == false);
}

TEST_CASE("reports no error when single Current reading is passed") {
  double currentReadings[] = {0.03};
  int numOfCurReadings = sizeof(currentReadings) / sizeof(currentReadings[0]);
  REQUIRE(validateCurrentreadings(currentReadings, numOfCurReadings) == true);
}





