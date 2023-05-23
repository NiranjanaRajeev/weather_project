import requests
import json
import sqlite3
import time
import datetime
import os

def read_config(config_file):
    # Read the JSON config file
    with open(config_file) as f:
        config = json.load(f)

    # Read the configuration parameters
    api_url = config['weather_map']['api_url']
    api_key = config['weather_map']['api_key']
    db_filename = config['database']['db_filename']
    db_location = config['database']['db_location']
    table_name = config['database']['table_name']
    cities = config['general']['cities']
    
    # The path where the database has to be created is in the config file, so we join the location with the filename
    db_filepath = os.path.join(db_location, db_filename)   

    return api_url, api_key, db_filepath, table_name, cities

def create_table(db_filepath, table_name):
    # Create a connection to the database
    conn = sqlite3.connect(db_filepath)
    cursor = conn.cursor()
    
    # Create the table if it doesn't exist
    cursor.execute(f"CREATE TABLE IF NOT EXISTS {table_name} (city TEXT,timestamp INTEGER, time TEXT, temperature REAL, temp_min REAL, temp_max REAL, humidity INTEGER, PRIMARY KEY (city, timestamp))")
    
    # Close the connection
    conn.close()

def fetch_weather_data(api_url, api_key, city):
    # Sending GET request to the weather API
    response = requests.get(api_url, params={"q": city, "appid": api_key, "units": "metric"})
    if response.status_code == 200:
        data = response.json()
        
        # Extract the relevant weather data from the API response
        temperature = data["main"]["temp"]
        temp_min = data["main"]["temp_min"]
        temp_max = data["main"]["temp_max"]
        humidity = data["main"]["humidity"]
        timestamp = int(time.time())
        return temperature, temp_min, temp_max, humidity, timestamp
    else:
        # Display an error message if the API request fails
        print(f"Error fetching weather data for {city}: {response.status_code} - {response.reason}")
        return None, None, None, None, None

def update_database(db_filepath, table_name, city, temperature, temp_min, temp_max, humidity, timestamp):
    # Create a connection to the database
    conn = sqlite3.connect(db_filepath)
    cursor = conn.cursor()
    
    # Check if there is existing data for the city
    cursor.execute(f"SELECT * FROM {table_name} WHERE city = ? ORDER BY time DESC LIMIT 1", (city,))
    existing_data = cursor.fetchone()
    if existing_data:
        existing_time = existing_data[1]
        # Getting time in qpecific format from Unix Timestamp
        dt_string = datetime.datetime.fromtimestamp(timestamp).strftime('%H:%M:%S %d-%m-%Y ')
        # Update the existing data in the database
        cursor.execute(f"UPDATE {table_name} SET timestamp = ?, time = ?, temperature = ?, temp_min = ?, temp_max = ?, humidity = ? WHERE city = ? AND timestamp = ?", (timestamp,dt_string, temperature,temp_min,temp_max, humidity, city, existing_time))
        conn.commit()
    else:
        dt_string = datetime.datetime.fromtimestamp(timestamp).strftime('%H:%M:%S %d-%m-%Y ')
        # Insert new data into the database
        cursor.execute(f"INSERT INTO {table_name} (city,timestamp, time, temperature,temp_min, temp_max, humidity) VALUES (?, ?, ?, ?, ?, ?, ?)", (city,timestamp, dt_string, temperature,temp_min, temp_max, humidity))
        conn.commit()
    # Close the connection
    conn.close()

def main():
    api_url, api_key, db_filepath, table_name, cities = read_config('../config.json')
    create_table(db_filepath, table_name)

    while True:
        for city in cities:
            temperature,temp_min,temp_max, humidity, timestamp = fetch_weather_data(api_url, api_key, city)
            if temperature is not None and temp_min is not None and temp_max is not None and humidity is not None and timestamp is not None:
                update_database(db_filepath, table_name, city, temperature, temp_min, temp_max, humidity, timestamp)
        # Pause added so that data is fetched every 10 minutes only (600 seconds)
        time.sleep(600)

if __name__ == '__main__':
    main()

