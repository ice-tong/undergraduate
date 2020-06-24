#
# Kian Farsany 55375951
# Project 3
# output_classes.py
#

import mapquest_api

#
# All output classes have a function which takes the proper
# locations-tuple as a parameter and prints its output in the
# proper format.
#

class Steps:
    def generate_output(self, locations: (str, [str])) -> None:
        url = mapquest_api.make_directions_query(locations[0], locations[1])
        json = mapquest_api.get_json(url)

        print('DIRECTIONS')
        
        for leg in json['route']['legs']:
            for step in leg['maneuvers']:
                print(step['narrative'])

class TotalDistance:
    def generate_output(self, locations: (str, [str])) -> None:
        url = mapquest_api.make_directions_query(locations[0], locations[1])
        json = mapquest_api.get_json(url)
        
        distance = json['route']['distance']
        rounded_distance = int(distance)
        
        print('TOTAL DISTANCE: {} miles'.format(rounded_distance))
        
class TotalTime:
    def generate_output(self, locations: (str, [str])) -> None:
        url = mapquest_api.make_directions_query(locations[0], locations[1])
        json = mapquest_api.get_json(url)
        
        seconds = json['route']['time']
        minutes = (int(seconds/60))
        
        print('TOTAL TIME: {} minutes'.format(minutes))

class LatLong:
    def generate_output(self, locations: (str, [str])) -> None:
        url = mapquest_api.make_directions_query(locations[0], locations[1])
        json = mapquest_api.get_json(url)

        print('LATLONGS')

        for location in json['route']['locations']:
            
            lat = location['latLng']['lat']
            lat_letter = ''
            if lat >= 0:
                lat_letter = 'N'
            else:
                lat_letter = 'S'
                
            lng = location['latLng']['lng']
            lng_letter = ''
            if lng >= 0:
                lng_letter = 'E'
            else:
                lng_letter = 'W'
                
            print('{:.2f}{} {:.2f}{}'.format(abs(lat),lat_letter, abs(lng), lng_letter))

class Elevation:
    def generate_output(self, locations: (str, [str])) -> None:
        urls = mapquest_api.make_elevation_query(locations[0], locations[1])

        print('ELEVATIONS')

        for url in urls:
            json = mapquest_api.get_json(url)
            print(int(json['elevationProfile'][0]['height']))


        
