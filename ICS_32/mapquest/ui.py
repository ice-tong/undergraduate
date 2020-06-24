#
# Kian Farsany 55375951
# Project 3
# ui.py
#

import output_classes
import mapquest_api

def _read_locations() -> (str, [str]):
    '''Read the locations and return them as a tuple
    where the str is the "from" location and the
    list is the "to" location(s)'''
    
    number_of_locations = int(input())
    result = (input(), [])
    
    for i in range(number_of_locations-1):
        result[1].append(input())
        
    return result

def _read_outputs() -> [str]:
    '''Read the desired outputs from the user'''
    
    number_of_outputs = int(input())
    result = []
    
    for i in range(number_of_outputs):
        result.append(input())
        
    return result

def _make_output_list(outputs: [str]) -> ['output']:
    '''Take the list of outputs from the user and turn
    them into the proper output classes'''
    result = []
    for output in outputs:
        if output == 'STEPS':
            result += [output_classes.Steps()]
        elif output == 'TOTALDISTANCE':
            result += [output_classes.TotalDistance()]
        elif output == 'TOTALTIME':
            result += [output_classes.TotalTime()]
        elif output == 'LATLONG':
            result += [output_classes.LatLong()]
        elif output == 'ELEVATION':
            result += [output_classes.Elevation()]
            
    return result

        
if __name__ == '__main__':
    try:
        locations = _read_locations()
        user_outputs = _read_outputs()

        print()

        output_classes = _make_output_list(user_outputs)
        for output in output_classes:
            output.generate_output(locations)
            print()

    except mapquest_api.NoRouteFound:
        print('\nNO ROUTE FOUND')

    except:
        print('\nMAPQUEST ERROR')
               
    else:
        print('Directions Courtesy of MapQuest; Map Data Copyright OpenStreetMap Contributors')
    
