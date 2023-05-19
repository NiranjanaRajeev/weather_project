import unittest
import sys
from unittest.mock import MagicMock, patch

# Add the path to the folder containing the program script
sys.path.append('/home/niranjana/Projet_Final/python_scripts')

from weather import fetch_weather_data


class FetchWeatherDataTestCase(unittest.TestCase):

    @patch('weather.requests.get')
    def test_fetch_weather_data_success(self, mock_get):
        # Prepare mock response
        response_data = {
            "main": {
                "temp": 25.0,
                "temp_min": 20.0,
                "temp_max": 30.0,
                "humidity": 70
            }
        }
        mock_response = MagicMock()
        mock_response.status_code = 200
        mock_response.json.return_value = response_data
        mock_get.return_value = mock_response

        # Call the function
        temperature, temp_min, temp_max, humidity, timestamp = fetch_weather_data("api_url", "api_key", "city")

        # Assert the values returned by the function
        self.assertEqual(temperature, 25.0)
        self.assertEqual(temp_min, 20.0)
        self.assertEqual(temp_max, 30.0)
        self.assertEqual(humidity, 70)
        self.assertIsNotNone(timestamp)

    @patch('weather.requests.get')
    def test_fetch_weather_data_failure(self, mock_get):
        # Prepare mock response
        mock_response = MagicMock()
        mock_response.status_code = 404
        mock_response.reason = "Not Found"
        mock_get.return_value = mock_response

        # Call the function
        temperature, temp_min, temp_max, humidity, timestamp = fetch_weather_data("api_url", "api_key", "city")

        # Assert that None is returned for all values
        self.assertIsNone(temperature)
        self.assertIsNone(temp_min)
        self.assertIsNone(temp_max)
        self.assertIsNone(humidity)
        self.assertIsNone(timestamp)


if __name__ == '__main__':
    unittest.main()

