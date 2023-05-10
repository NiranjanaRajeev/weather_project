import requests

api_url = 'http://api.openweathermap.org/data/2.5/weather'
appid = '1ab917e7eee961089f0c045f3f7a026b'

r = requests.get(url=api_url, params={"q": "Toulouse", "appid": appid, "units": "metric"})

print(r.content.strip())
