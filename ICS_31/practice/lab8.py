#  Kian Farsany 55375951 and Andrew Severt 27644841.  ICS 31 Lab sec 8.  Lab asst 8c-d.

#
# Part (c)
#
from collections import namedtuple
Dish = namedtuple('Dish', 'name price calories')
print('-----Part (c)-----\n\n')
# Part (c.1)
def read_menu_with_count(file_name: str) -> [Dish]:
    '''Returns a list of the Dishes in the file after the count'''
    result = []
    file = open(file_name, 'r')
    dishes = file.readlines()[1:]
    file.close()
    for dish in dishes:
        dish_line = dish.split('\t')
        result.append(Dish(dish_line[0], float(dish_line[1][1:]), int(dish_line[2])))
    return result
print('-----Part (c.1)-----')
print(read_menu_with_count('menu1.txt'))
print()
print(read_menu_with_count('menu2.txt'))

print()

# Part (c.2)
def read_menu(file_name: str) -> [Dish]:
    '''Returns a list of the Dishes in the file'''
    result = []
    file = open(file_name, 'r')
    dishes = file.readlines()
    file.close()
    for dish in dishes:
        dish_line = dish.split('\t')
        result.append(Dish(dish_line[0], float(dish_line[1][1:]), int(dish_line[2])))
    return result
print('-----Part (c.2)-----')
#print(read_menu('menu3.txt'))

print()

# Part (c.3)
def write_menu(L: [Dish], file_name: str) -> None:
    '''Write a file with the given Dishes in txt'''
    outfile = open(file_name, 'w')
    outfile.write(str(len(L)) + '\n')
    for dish in L:
        outfile.write('{}\t${:4.2f}\t{}\n'.format(dish.name, dish.price, dish.calories))
        
#
# Part (d)
#
print('\n-----Part (d)-----\n\n')
Course = namedtuple('Course', 'dept num title instr units')
# Each field is a string except the number of units
ics31 = Course('ICS', '31', 'Intro to Programming', 'Kay', 4.0)
ics32 = Course('ICS', '32', 'Programming with Libraries', 'Thornton', 4.0)
wr39a = Course('Writing', '39A', 'Intro Composition', 'Alexander', 4.0)
wr39b = Course('Writing', '39B', 'Intermediate Composition', 'Gross', 4.0)
bio97 = Course('Biology', '97', 'Genetics', 'Smith', 4.0)
mgt1  = Course('Management', '1', 'Intro to Management', 'Jones', 2.0)
  
Student = namedtuple('Student', 'ID name level major studylist')
# All are strings except studylist, which is a list of Courses.
sT = Student('59203792', 'Student, Again', 'FR', 'PSB', [ics31, wr39b])
sU = Student('19402749', 'Student, Another', 'FR', 'CSE', [ics31, wr39a, bio97, mgt1])
sV = Student('18394729', 'Student, Random', 'SR', 'INFX', [ics31, ics32, mgt1])
sW = Student('11223344', 'Anteater, Peter', 'FR', 'PSB', [ics31, wr39a, bio97, mgt1])
sX = Student('21223344', 'Anteater, Andrea', 'SO', 'CS', [ics31, wr39b, bio97, mgt1])
sY = Student('31223344', 'Programmer, Paul', 'FR', 'COG SCI', [ics32, wr39a, bio97])
sZ = Student('41223344', 'Programmer, Patsy', 'SR', 'PSB', [ics32, mgt1])

StudentBody = [sT, sU, sV, sW, sX, sY, sZ]

# Part (d.1)
def Students_at_level(L: [Student], s: str) -> [Student]:
    '''Returns a list of Students with the given class level'''
    result = []
    for i in L:
        if i.level == s:
            result.append(i)
    return result
assert Students_at_level(StudentBody, 'FR') == [sT, sU, sW, sY]
assert Students_at_level(StudentBody, 'SO') == [sX]

# Part (d.2)
def Students_in_majors(L: [Student], s: [str]) -> [Student]:
    '''Return a list of the Students with the gievn majors'''
    result = []
    for i in L:
        if i.major in s:
            result.append(i)
    return result
assert Students_in_majors(StudentBody, ['COG SCI', 'CS']) == [sX, sY]
assert Students_in_majors(StudentBody, ['PSB']) == [sT, sW, sZ]

# Part (d.3)
def Course_equals(c1: Course, c2: Course) -> bool:
    ''' Return True if the department and number of c1 match the department and
	     number of c2 (and False otherwise)'''
    return c1.dept == c2.dept and c1.num == c2.num

def Course_on_studylist(c: Course, SL: 'list of Course') -> bool:
    ''' Return True if the course c equals any course on the list SL (where equality
	     means matching department name and course number) and False otherwise.'''
    for i in SL:
        if Course_equals(c, i):
            return True
    return False

def Student_is_enrolled(S: Student, department: str, coursenum: str) -> bool:
    ''' Return True if the course (department and course number) is on the student's
	     studylist (and False otherwise)'''
    for c in S.studylist:
        if c.dept == department and c.num == coursenum:
            return True
    return False

def Students_in_class(L: [Student], department: str, course: str) -> [Student]:
    '''Return the Students with the given class'''
    result = []
    for S in L:
        if Student_is_enrolled(S, department, course):
            result.append(S)
    return result
assert Students_in_class(StudentBody, 'ICS', '31') == [sT, sU, sV, sW, sX]
assert Students_in_class(StudentBody, 'Writing', '39A') == [sU, sW, sY]

# Part (d.4)
def Student_names(L: [Student]) -> [str]:
    '''Return the list of the names of the Students'''
    result = []
    for S in L:
        result.append(S.name)
    return result
assert Student_names(StudentBody) == ['Student, Again',
                                      'Student, Another',
                                      'Student, Random',
                                      'Anteater, Peter',
                                      'Anteater, Andrea',
                                      'Programmer, Paul',
                                      'Programmer, Patsy']
# Part (d.5)
print('-----Part (d.5)-----\n')

Students_in_ICS_major = Students_in_majors(StudentBody, ['CS', 'CSE', 'BIM', 'INFX', 'CGS', 'SE', 'ICS'])
seniors_in_ICS_major = Students_at_level(Students_in_ICS_major, 'SR')
freshmen_in_ICS_major = Students_at_level(Students_in_ICS_major, 'FR')
freshmen_in_ICS31 = Students_in_class(Students_at_level(StudentBody, 'FR'), 'ICS', '31')

print(Students_in_ICS_major)

print()

print(Student_names(Students_in_ICS_major))

print()

print(len(Students_in_ICS_major))

print()

print(Student_names(seniors_in_ICS_major))

print()

print(len(seniors_in_ICS_major))

print()

print(str((len(seniors_in_ICS_major)/len(Students_in_ICS_major)) * 100) + '%')

print()

print(len(Students_in_class(freshmen_in_ICS_major, 'ICS', '31')))

print()

total = 0
for F in freshmen_in_ICS31:
    for C in F.studylist:
        total += C.units
print(total/len(freshmen_in_ICS31))
