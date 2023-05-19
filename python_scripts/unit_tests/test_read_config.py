import unittest
import json
import os
import sys

# Add the path to the folder containing  program script
sys.path.append('/home/niranjana/Projet_Final/python_scripts')

from weather import read_config

class TestWeatherScript(unittest.TestCase):
    def test_read_config_with_valid_config(self):
        # Define a sample config dictionary
        sample_config = {
            "weather_map": {
                "api_url": "http://api.openweathermap.org/data/2.5/weather",
                "api_key": "1ab917e7eee961089f0c045f3f7a026b"
            },
            "database": {
                "db_filename": "weather.db",
                "table_name": "weather_data",
                "db_location": "/home/niranjana/Projet_Final"
            },
            "general": {
                "cities": ["London", "New York", "Tokyo"]
            }
        }

        # Create a temporary JSON file with the sample config
        with open("temp_config.json", "w") as f:
            f.write(json.dumps(sample_config))

        # Call the read_config function with the temporary config file
        api_url, api_key, db_filepath, table_name, cities = read_config("temp_config.json")

        # Assert that the returned values match the sample config
        self.assertEqual(api_url, "http://api.openweathermap.org/data/2.5/weather")
        self.assertEqual(api_key, "1ab917e7eee961089f0c045f3f7a026b")
        self.assertEqual(db_filepath, "/home/niranjana/Projet_Final/weather.db")
        self.assertEqual(table_name, "weather_data")
        self.assertEqual(cities, ["London", "New York", "Tokyo"])

        # Remove the temporary config file
        os.remove("temp_config.json")

    def test_read_config_with_missing_value(self):
        # Test with missing config values
        sample_config = {
            "weather_map": {
                "api_url": "http://api.openweathermap.org/data/2.5/weather"
                # Missing "api_key" key
            },
            "database": {
                "db_filename": "weather.db",
                "table_name": "weather_data",
                "db_location": "/home/niranjana/Projet_Final"
            },
            "general": {
                "cities": ["London", "New York", "Tokyo"]
            }
        }

        with open("temp_config.json", "w") as f:
            f.write(json.dumps(sample_config))

        # Ensure that an exception is raised when a required value is missing
        with self.assertRaises(KeyError):
            read_config("temp_config.json")

        os.remove("temp_config.json")

    def test_read_config_with_empty_cities(self):
        # Test with an empty cities list
        sample_config = {
            "weather_map": {
                "api_url": "http://api.openweathermap.org/data/2.5/weather",
                "api_key": "1ab917e7eee961089f0c045f3f7a026b"
            },
            "database": {
                "db_filename": "weather.db",
                "table_name": "weather_data",
                "db_location": "/home/niranjana/Projet_Final"
            },
            "general": {
                "cities": []
            }
        }

        with open("temp_config.json", "w") as f:
            f.write(json.dumps(sample_config))

        api_url, api_key, db_filepath, table_name, cities = read_config("temp_config.json")

        self.assertEqual(api_url, "http://api.openweathermap.org/data/2.5/weather")
        self.assertEqual(api_key, "1ab917e7eee961089f0c045f3f7a026b")
        self.assertEqual(db_filepath, "/home/niranjana/Projet_Final/weather.db")
        self.assertEqual(table_name, "weather_data")
        self.assertEqual(cities, [])  # Ensure that the cities list is empty

        os.remove("temp_config.json")

if __name__ == '__main__':
    unittest.main()


