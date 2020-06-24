#
# Kian Farsany 55375951
# Project 3
# mapquest_api.py
#

import json
import urllib.request
import urllib.parse

MAPQUEST_API_KEY = 'uxqbGaRaBJjZLszDUbYug3fK56c0KweA'

BASE_MAPQUEST_URL = 'http://open.mapquestapi.com'



class NoRouteFound(Exception):
    pass



def make_directions_query(from_location: str, to_locations: [str]) -> str:
    '''Make a directions query with the given locations'''
    query_parameters = [
        ('key', MAPQUEST_API_KEY), ('from', from_location),
    ]
    
    for location in to_locations:
        query_parameters.append(('to', location))

    return BASE_MAPQUEST_URL + '/directions/v2/route?' + urllib.parse.urlencode(query_parameters)

def make_elevation_query(from_location: str, to_locations: [str]) -> [str]:
    '''Make elevation queries for each location so as to avoid
    distance errors when the route is greater than 250 miles.
    Return those query urls as a list of strings.'''
    urls = []
    for latlong_pair in _get_latlong_collection(from_location, to_locations):
        latlong_pair_string = str(latlong_pair[0]) + ',' + str(latlong_pair[1])
        
        query_parameters = [
        ('key', MAPQUEST_API_KEY),
        ('latLngCollection', latlong_pair_string)
        ]
        urls.append(BASE_MAPQUEST_URL + '/elevation/v1/profile?' + urllib.parse.urlencode(query_parameters))
        
    return urls

def get_json(url: str) -> dict:
    '''Get the JSON response for the sent URL'''
    response = None

    try:
        response = urllib.request.urlopen(url)
        json_text = response.read().decode(encoding = 'utf-8')

        json_dict = json.loads(json_text)
        _check_json(json_dict)
        return json_dict

    finally:
        if response != None:
            response.close()

def _check_json(json: dict) -> None:
    '''Raise an exception if there is a route error'''
    if 'route' in json:
        if json['route']['routeError']['errorCode'] == 2:
            raise NoRouteFound()

def _get_latlong_collection(from_location: str, to_locations: [str]) -> [(float, float)]:
    '''Get a LatLng collection with all of the locations' latlongs
    as tuples so they can be iterated through so each pair has its own
    elevation query'''
    result = []
    
    json = get_json(make_directions_query(from_location, to_locations))
    for location in json['route']['locations']:
        result.append((location['latLng']['lat'], location['latLng']['lng']))
        
    return result


