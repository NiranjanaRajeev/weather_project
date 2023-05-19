import unittest
import json
import os
import sys
import sqlite3
import tempfile

# Add the path to the folder containing the program script
sys.path.append('/home/niranjana/Projet_Final/python_scripts')

from weather import create_table

class CreateTableTestCase(unittest.TestCase):
    def setUp(self):
        self.db_file = tempfile.NamedTemporaryFile()  # Create a temporary file for the database
        self.db_filepath = self.db_file.name
        self.table_name = "weather_data"
        self.conn = sqlite3.connect(self.db_filepath)
        self.cursor = self.conn.cursor()

    def tearDown(self):
        self.cursor.close()
        self.conn.close()
        self.db_file.close()

    def test_create_table(self):
        create_table(self.db_filepath, self.table_name)

        # Check if the table exists
        self.cursor.execute(f"SELECT name FROM sqlite_master WHERE type='table' AND name='{self.table_name}'")
        result = self.cursor.fetchone()

        self.assertIsNotNone(result)  # Table should exist
        self.assertEqual(result[0], self.table_name)  # Table name should match
        
    def test_create_table_duplicate(self):
        create_table(self.db_filepath, self.table_name)
        create_table(self.db_filepath, self.table_name)  # Create the table again

        # Check if there are any duplicate tables
        self.cursor.execute(f"SELECT COUNT(name) FROM sqlite_master WHERE type='table' AND name='{self.table_name}'")
        result = self.cursor.fetchone()

        self.assertEqual(result[0], 1)  # There should be only one table with the given name

if __name__ == '__main__':
    unittest.main()

