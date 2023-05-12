import requests
import json
import sqlite3
import time
import datetime

def read_config(config_file):
    # Read the JSON config file
    with open(config_file) as f:
        config = json.load(f)

    # Read the configuration parameters
    api_url = config['weather_map']['api_url']
    api_key = config['weather_map']['api_key']
    db_filename = config['database']['db_filename']
    table_name = config['database']['table_name']
    cities = config['general']['cities']

    return api_url, api_key, db_filename, table_name, cities

def create_table(db_filename, table_name):
    conn = sqlite3.connect(db_filename)
    cursor = conn.cursor()
    cursor.execute(f"CREATE TABLE IF NOT EXISTS {table_name} (city TEXT, timestamp INTEGER, temperature REAL, temp_min REAL, temp_max REAL, humidity INTEGER, PRIMARY KEY (city, timestamp))")
    conn.close()

def fetch_weather_data(api_url, api_key, city):
    response = requests.get(api_url, params={"q": city, "appid": api_key, "units": "metric"})
    if response.status_code == 200:
        data = response.json()
        temperature = data["main"]["temp"]
        temp_min = data["main"]["temp_min"]
        temp_max = data["main"]["temp_max"]
        humidity = data["main"]["humidity"]
        timestamp = int(time.time())
        return temperature, temp_min, temp_max, humidity, timestamp
    else:
        print(f"Error fetching weather data for {city}: {response.status_code} - {response.reason}")
        return None, None, None, None, None

def update_database(db_filename, table_name, city, temperature, temp_min, temp_max, humidity, timestamp):
    conn = sqlite3.connect(db_filename)
    cursor = conn.cursor()
    cursor.execute(f"SELECT * FROM {table_name} WHERE city = ? ORDER BY timestamp DESC LIMIT 1", (city,))
    existing_data = cursor.fetchone()
    if existing_data:
        existing_timestamp = existing_data[1]
        if timestamp > existing_timestamp:
            cursor.execute(f"UPDATE {table_name} SET timestamp = ?, temperature = ?, temp_min = ?, temp_max = ?, humidity = ? WHERE city = ? AND timestamp = ?", (timestamp, temperature,temp_min,temp_max, humidity, city, existing_data[1]))
            conn.commit()
    else:
        cursor.execute(f"INSERT INTO {table_name} (city, timestamp, temperature,temp_min, temp_max, humidity) VALUES (?, ?, ?, ?, ?, ?)", (city, timestamp, temperature,temp_min, temp_max, humidity))
        conn.commit()
    conn.close()

def main():
    api_url, api_key, db_filename, table_name, cities = read_config('config.json')
    create_table(db_filename, table_name)

    while True:
        for city in cities:
            temperature,temp_min,temp_max, humidity, timestamp = fetch_weather_data(api_url, api_key, city)
            if temperature is not None and temp_min is not None and temp_max is not None and humidity is not None and timestamp is not None:
                update_database(db_filename, table_name, city, temperature, temp_min, temp_max, humidity, timestamp)
        time.sleep(60)

if __name__ == '__main__':
    main()

