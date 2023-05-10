import requests
import json

# Read the JSON config file
with open('config.json') as f:
    config = json.load(f)
    
# Read the configuration parameters
API_URL = config['Python_script']['api_url']
API_KEY = config['Python_script']['api_key']

r = requests.get(url=API_URL, params={"q": "Toulouse", "appid": API_KEY, "units": "metric"})

print(r.content.strip())
