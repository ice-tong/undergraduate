#  Kian Farsany 55375951 and Andrew Severt 27644841.  ICS 31 Lab sec 8.  Lab asst 8f.

bedrooms = []

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

def add_new_bedroom(s: str) -> None:
    '''Add a bedroom to the list of bedrooms'''
    split_words = s.split()
    bedrooms.append(split_words[1])

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

BandB()
