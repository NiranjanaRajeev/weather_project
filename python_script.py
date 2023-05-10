import requests
import json
import sqlite3
import time
import datetime

# Read the JSON config file
with open('config.json') as f:
    config = json.load(f)
    
# Read the configuration parameters
API_URL = config['Python_script']['api_url']
API_KEY = config['Python_script']['api_key']
DB_FILENAME = config['Python_script']['db_filename']
TABLE_NAME = config['Python_script']['table_name']
cities = config['Python_script']['cities']

conn = sqlite3.connect(DB_FILENAME)
cursor = conn.cursor()
cursor.execute(f"CREATE TABLE IF NOT EXISTS {TABLE_NAME} (city TEXT, time TEXT, temperature REAL, humidity INTEGER, PRIMARY KEY (city, time))")

while True:
    for city in cities:
        response = requests.get(API_URL, params={"q": city, "appid": API_KEY, "units": "metric"})
        if response.status_code == 200:
            data = response.json()
            temperature = data["main"]["temp"]
            humidity = data["main"]["humidity"]
            timestamp = int(time.time())
            
            # Check if an entry exists for this city in the database
            cursor.execute(f"SELECT * FROM {TABLE_NAME} WHERE city = ? ORDER BY time DESC LIMIT 1", (city,))
            existing_data = cursor.fetchone()

            # If an entry exists, update it with the latest weather data
            if existing_data:
                existing_timestamp = existing_data[1]
                if timestamp > existing_timestamp:
                    dt_string = datetime.datetime.fromtimestamp(timestamp).strftime('%H:%M:%S %d-%m-%Y ')
                    cursor.execute(f"UPDATE {TABLE_NAME} SET time = ?, temperature = ?, humidity = ? WHERE city = ? AND timestamp = ?", (dt_string, temperature, humidity, city, existing_timestamp))
                    conn.commit()
            # Otherwise, insert a new entry for the city with the latest weather data
            else:
                dt_string = datetime.datetime.fromtimestamp(timestamp).strftime('%H:%M:%S %d-%m-%Y ')
                cursor.execute(f"INSERT INTO {TABLE_NAME} (city, time, temperature, humidity) VALUES (?, ?, ?, ?)", (city, dt_string, temperature, humidity))
                conn.commit()
        else:
            print(f"Error fetching weather data for {city}: {response.status_code} - {response.reason}")
    time.sleep(60)

conn.close()
