#  Kian Farsany 55375951 and Anna Zhang 27644841.  ICS 31 Lab sec 8.  Lab asst 9e.

import datetime
from collections import namedtuple
Reservation = namedtuple('Reservation', 'room arrive depart name confirmation')
# confirmation being a number; room, arrive, depart, and name being strings

bedrooms = []
reservations = []
confirmations = []

def BandB() -> None:
    '''Main command function'''
    command_file = open(str(input('Enter the command file name: ')), 'r')
    command_lines = command_file.readlines()
    command_file.close
    for line in command_lines:
        line = line.strip()
        if line[0:2].lower() == 'nb':
            add_new_bedroom(line)
        if line[0:2].lower() == 'lb':
            print_bedrooms(bedrooms)
        if line[0:2].lower() == 'pl':
            print_line(line)
        if line[0:2].lower() == 'db':
            delete_bedroom(line)
        if line[0:2].lower() == 'rr':
            reserve_room(line)
        if line[0:2].lower() == 'lr':
            print_reservations(reservations)
        if line[0:2].lower() == 'dr':
            delete_reservation(line)

def add_new_bedroom(s: str) -> None:
    '''Add a bedroom to the list of bedrooms'''
    split_words = s.split()
    if split_words[1] not in bedrooms:
        bedrooms.append(split_words[1])
    else:
        print("Sorry, can't add room", split_words[1], "again; it's already on the list.")

def print_bedrooms(L: list) -> None:
    '''Print the current list of bedrooms'''
    print('Number of bedrooms in service: ', len(bedrooms))
    print('------------------------------------')
    for B in bedrooms:
        print(B)

def print_line(s: str) -> None:
    '''Print the entire command line excluding PL'''
    PL_removed = s.strip()[2:]
    print(PL_removed.strip())

def delete_bedroom(s: str) -> None:
    '''Delete a bedroom from the list,
    give an error if it is not in the list'''
    split_words = s.split()
    room = split_words[1]
    removeR=[]
    if room in bedrooms:
        bedrooms.remove(room)
        for i in range(len(reservations)):
            if reservations[i].room == room:   
                print('Deleting room', room, 'forces cancellation of this reservation:')
                print('\t{} arriving {} and departing  {} (Conf. #{})'.format(reservations[i].name, reservations[i].arrive, reservations[i].depart, reservations[i].confirmation))
                reservations[i]= None
        while None in reservations:
            reservations.remove(None)
    else:
        print("Sorry, can't delete room {}; it is not in service now.".format(split_words[1]))

def format_date(s: str) -> str:
    '''Format a date string into a date'''
    split_numbers = s.split('/')
    return '{:2s}/{:2s}/{:4s}'.format(split_numbers[0], split_numbers[1], split_numbers[2])

def make_name(L: list) -> str:
    '''Combine separate names in a list into one string'''
    result = ''
    for s in L:
        result = result +  s + ' '
    return result

def str_to_date(s: str) -> 'date':
    '''Convert a date string to a date'''
    split_dates = s.split('/')
    return datetime.date(int(split_dates[2]), int(split_dates[0]), int(split_dates[1]))

def arrival_before_departure(a: 'date', d: 'date') -> bool:
    '''Return True if arrival date is before departure date'''
    return a < d

def arrival_on_departure(a: 'date', d: 'date') -> bool:
    '''Return True if arrival date is on departure date'''
    return a == d

def dates_dont_overlap(a_new: 'date', d_new: 'date', a_old: 'date', d_old: 'date') -> bool:
    '''Check scheduling conflicts for a room'''
    if a_new > a_old and a_new < d_old:
        return False
    elif d_new > a_old and d_new < d_old:
        return False
    elif a_new < a_old and d_new > d_old:
        return False
    elif a_new == a_old or d_new == d_old:
        return False
    return True

def reserve_room(s: str) -> None:
    '''Add a reservation for a room'''
    split_words = s.split()
    name = split_words[4:]
    arrive_date = str_to_date(split_words[2])
    depart_date = str_to_date(split_words[3])
    room_is_usable = True
    if split_words[1] in bedrooms:
        if arrival_before_departure(arrive_date, depart_date):
            for R in reservations:
                if not dates_dont_overlap(arrive_date, depart_date, str_to_date(R.arrive), str_to_date(R.depart)):
                    print("Sorry, can't reserve room {} ({} to  {});".format(R.room, R.arrive, R.depart))
                    print("\tit's already booked (Conf. #{})".format(R.confirmation))
                    room_is_usable = False
                    break
            if room_is_usable:
                confirmations.append(len(confirmations)+1)
                reserve = Reservation(split_words[1], split_words[2], split_words[3], make_name(name), confirmations[-1])
                reservations.append(reserve)
                print('Reserving room {} for {} -- Confirmation #{}'.format(reserve.room, reserve.name, reserve.confirmation))
                print('\t(arriving {}, departing {})'.format(reserve.arrive, reserve.depart))
        elif arrival_on_departure(arrive_date, depart_date):
            print("Sorry, can't reserve room {} ({} to {});".format(split_words[1], split_words[2], split_words[3]))
            print("\tcan't arrive and leave on the same day.")
        else:
            print("Sorry, can't reserve room {} ({} to {});".format(split_words[1], split_words[2], split_words[3]))
            print("\tcan't leave before you arrive.")
    else:
        print("Sorry; can't reserve room {}; room not in service".format(split_words[1]))

def print_reservations(L: list) -> None:
    '''Print all of the current reservations'''
    print('Number of reservations:', len(L))
    print('No. Rm. Arrive     Depart     Guest')
    print('------------------------------------------------')
    for R in L:
        print('{:3d} {:3s} {} {} {}'.format(R.confirmation, R.room, format_date(R.arrive), format_date(R.depart), R.name))

def delete_reservation(s: str) -> None:
    '''Deletes a reservation from the list given its confirmation number'''
    confirmation = int(s.split()[1])
    found_room = False
    for R in reservations:
        if R.confirmation == confirmation:
            reservations.remove(R)
            found_room = True
    if not found_room:
        print("Sorry, can't cancel reservation; no confirmation number", confirmation)


BandB()
