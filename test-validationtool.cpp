#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "sensor-validate.h"


/*----------------------------------------------------------------------------------
 * SoC Sensor Tests
 */
TEST_CASE("Reports ERROR when SoC readings JUMP ABRUPBTLY - Upward Spike")
{
  double socReadings[] = {0.0, 0.01, 0.5, 0.51, 0.6};
  int numOfSocReadings = sizeof(socReadings) / sizeof(socReadings[0]);

  REQUIRE(isSOCReadingsValid(socReadings, numOfSocReadings) == false);
}

TEST_CASE("Reports ERROR when SoC readings JUMP ABRUPBTLY - Downward Spike")
{
  double socReadings[] = {0.51, 0.01, 0.5, 0.1};
  int numOfSocReadings = sizeof(socReadings) / sizeof(socReadings[0]);

  REQUIRE(isSOCReadingsValid(socReadings, numOfSocReadings) == false);
}

TEST_CASE("Reports ERROR when SoC readings are EMPTY")
{
  double socReadings[] = {};

  REQUIRE(isSOCReadingsValid(socReadings, 0) == false);
}


TEST_CASE("Reports ERROR when SoC Readings are passed as NULL")
{

  REQUIRE(isSOCReadingsValid(NULL, 0) == false);
}


TEST_CASE("Reports NO ERROR when ONLY ONE SoC reading is passed")
{
  double socReadings[] = {0.01};
  int numOfSocReadings = sizeof(socReadings) / sizeof(socReadings[0]);

  REQUIRE(isSOCReadingsValid(socReadings, numOfSocReadings) == true);
}

TEST_CASE("Reports NO ERROR when VALID SoC readings are passed")
{
  double socReadings[] = {0.01, 0.02, 0.03, 0.04};
  int numOfSocReadings = sizeof(socReadings) / sizeof(socReadings[0]);

  REQUIRE(isSOCReadingsValid(socReadings, numOfSocReadings) == true);
}


/*----------------------------------------------------------------------------------
 *  Current Sensor Tests
 */

TEST_CASE("Reports ERROR when Current readings JUMP ABRUPBTLY - Upward Spike")
{
  double currentReadings[] = {0.03, 0.03, 0.03, 0.33};
  int numOfCurReadings = sizeof(currentReadings) / sizeof(currentReadings[0]);

  REQUIRE(isCurrentReadingsValid(currentReadings, numOfCurReadings) == false);
}

TEST_CASE("Reports ERROR when Current readings JUMP ABRUPBTLY - Downward Spike")
{
  double currentReadings[] = {0.33, 0.03, 0.03};
  int numOfCurReadings = sizeof(currentReadings) / sizeof(currentReadings[0]);

  REQUIRE(isCurrentReadingsValid(currentReadings, numOfCurReadings) == false);
}

TEST_CASE("Reports ERROR when Empty Current reading is passed")
{
  double currentReadings[] = {};

  REQUIRE(isCurrentReadingsValid(currentReadings, 0) == false);
}

TEST_CASE("Reports ERROR when NULL Current reading is passed") {

  REQUIRE(isCurrentReadingsValid(NULL, 0) == false);
}

TEST_CASE("Reports NO ERROR when ONLY ONE Current reading is passed")
{
  double currentReadings[] = {0.03};
  int numOfCurReadings = sizeof(currentReadings) / sizeof(currentReadings[0]);

  REQUIRE(isCurrentReadingsValid(currentReadings, numOfCurReadings) == true);
}

TEST_CASE("Reports NO ERROR when VALID Current readings are passed")
{
  double currentReadings[] = {0.03, 0.04, 0.05, 0.06};
  int numOfCurReadings = sizeof(currentReadings) / sizeof(currentReadings[0]);

  REQUIRE(isCurrentReadingsValid(currentReadings, numOfCurReadings) == true);
}





