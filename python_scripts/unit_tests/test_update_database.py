import sqlite3
import unittest
import sys
import tempfile
from unittest.mock import patch
from datetime import datetime
# Add the path to the folder containing the program script
sys.path.append('/home/niranjana/Projet_Final/python_scripts')

from weather import update_database

class DatabaseUpdateTestCase(unittest.TestCase):
    def setUp(self):
        self.db_file = tempfile.NamedTemporaryFile()
        self.db_filepath = self.db_file.name
        self.table_name = "weather_data"
        self.city = "New York"
        self.temperature = 20.5
        self.temp_min = 15.2
        self.temp_max = 25.8
        self.humidity = 70
        self.timestamp = int(datetime.now().timestamp())

        conn = sqlite3.connect(self.db_filepath)
        cursor = conn.cursor()
        cursor.execute(f"CREATE TABLE IF NOT EXISTS {self.table_name} (city TEXT, timestamp INTEGER, time TEXT, temperature REAL, temp_min REAL, temp_max REAL, humidity INTEGER, PRIMARY KEY (city, timestamp))")
        conn.commit()
        conn.close()

    def tearDown(self):
        self.db_file.close()

    def test_update_database(self):
        update_database(self.db_filepath, self.table_name, self.city, self.temperature, self.temp_min, self.temp_max, self.humidity, self.timestamp)

        conn = sqlite3.connect(self.db_filepath)
        cursor = conn.cursor()
        cursor.execute(f"SELECT * FROM {self.table_name} WHERE city = ? AND timestamp = ?", (self.city, self.timestamp))
        result = cursor.fetchone()
        conn.close()

        self.assertIsNotNone(result)
        self.assertEqual(result[0], self.city)
        self.assertEqual(result[1], self.timestamp)
        self.assertEqual(result[2], datetime.fromtimestamp(self.timestamp).strftime('%H:%M:%S %d-%m-%Y '))
        self.assertEqual(result[3], self.temperature)
        self.assertEqual(result[4], self.temp_min)
        self.assertEqual(result[5], self.temp_max)
        self.assertEqual(result[6], self.humidity)
    
    def test_insert_new_data(self):
        # Insert new data for a city that doesn't exist in the database
        new_city = "London"
        new_temperature = 18.9
        new_temp_min = 13.2
        new_temp_max = 22.6
        new_humidity = 65
        new_timestamp = self.timestamp + 1

        update_database(self.db_filepath, self.table_name, new_city, new_temperature, new_temp_min, new_temp_max, new_humidity, new_timestamp)

        conn = sqlite3.connect(self.db_filepath)
        cursor = conn.cursor()
        cursor.execute(f"SELECT * FROM {self.table_name} WHERE city = ? AND timestamp = ?", (new_city, new_timestamp))
        result = cursor.fetchone()
        conn.close()

        self.assertIsNotNone(result)
        self.assertEqual(result[0], new_city)
        self.assertEqual(result[1], new_timestamp)
        self.assertEqual(result[2], datetime.fromtimestamp(new_timestamp).strftime('%H:%M:%S %d-%m-%Y '))
        self.assertEqual(result[3], new_temperature)
        self.assertEqual(result[4], new_temp_min)
        self.assertEqual(result[5], new_temp_max)
        self.assertEqual(result[6], new_humidity)

if __name__ == '__main__':
    unittest.main()


