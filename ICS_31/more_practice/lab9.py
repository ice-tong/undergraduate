#  Kian Farsany 55375951 and Anna Zhang 44332211.  ICS 31 Lab sec 8.  Lab asst 9.

#
# Part (c)
#
print('-----Part (c)-----\n\n')

from random import *

NUMBER_OF_STUDENTS = 200
NUMBER_OF_QUESTIONS = 20
NUMBER_OF_CHOICES = 4

# Part (c.1)
def generate_answers() -> str:
    '''Return random answers to a multiple choice test'''
    result = ''
    for i in range(NUMBER_OF_QUESTIONS):
        result += choice('ABCD')
    return result

ANSWERS = generate_answers()


# Part (c.2) and (c.3)
print('-----Part (c.2) and (c.3)-----\n')

from collections import namedtuple
Student = namedtuple('Student', 'id answers scores total')

def Student_total(S: Student) -> int:
    '''Return a Student's total'''
    return S.total

def check_answers(A: str) -> [int]:
    '''Returns a list with 1s and 0s according to correct answers'''
    result = []
    for i in range(len(A)):
        if A[i] == ANSWERS[i]:
            result.append(1)
        else:
            result.append(0)
    return result

def one_student() -> Student:
    '''Generates one random Student'''
    student_answers = generate_answers()
    student_scores = check_answers(student_answers)
    return Student(randrange(10000000, 100000000), student_answers, student_scores, sum(student_scores)) 

def random_students() -> [Student]:
    '''Return a list of random Students'''
    result = []
    for i in range(NUMBER_OF_STUDENTS):
        result.append(one_student())
    return result

students = random_students()
students.sort(key=Student_total, reverse = True)
print(students[:10])

print('\n\n')

average_total = 0
for S in students:
    average_total += Student_total(S)
print(average_total/NUMBER_OF_STUDENTS)
print('\n\n')


# Part (c.4)
print('-----Part (c.4)-----\n')

def generate_weighted_student_answer(s: str) -> str:
    '''Returns a student's answer when weighted by the correct answer'''
    answer_choices = 'ABCD' + (randrange(0, 9) * s)
    return choice(answer_choices)

def one_student2() -> Student:
    '''Generates one random Student with weighted answers'''
    student_answers = ''
    for A in ANSWERS:
        student_answers += generate_weighted_student_answer(A)
    student_scores = check_answers(student_answers)
    return Student(randrange(10000000, 100000000), student_answers, student_scores, sum(student_scores))

def random_students2() -> [Student]:
    '''Return a list of random Students with weighted answers'''
    result = []
    for i in range(NUMBER_OF_STUDENTS):
        result.append(one_student2())
    return result

students2 = random_students2()
students2.sort(key=Student_total, reverse = True)
print(students2[:10])

print('\n\n')

average_total2 = 0
for S in students2:
    average_total2 += Student_total(S)
print(average_total2
      /NUMBER_OF_STUDENTS)
print('\n\n')


# Part (c.5)
print('-----Part (c.5)-----\n')

def count_incorrect(L: [Student], n: int) -> int:
    '''Return the number of incorrect answers for one question given the nth question'''
    result = 0
    for S in L:
        if S.answers[n] != ANSWERS[n]:
            result += 1
    return result
            
def question_weights(L: [Student]) -> [int]:
    '''Return a list of numbers representing the amount of incorrect answers'''
    result = []
    for i in range(NUMBER_OF_QUESTIONS):
        result.append(count_incorrect(L, i))
    return result

WEIGHTS = question_weights(students2)

def Student_weighted_score(S: Student, W: [int]) -> Student:
    '''Return the same Student with its total field changed by W'''
    new_total = 0
    for i in range(NUMBER_OF_QUESTIONS):
        new_total += (S.scores[i] * W[i])
    return S._replace(total=new_total)

students3 = []
for S in students2:
    students3.append(Student_weighted_score(S, WEIGHTS))
students3.sort(key=Student_total, reverse = True)
print(students3[:10])

print('\n\n')

average_total3 = 0
for S in students3:
    average_total3 += Student_total(S)
print(average_total3
      /NUMBER_OF_STUDENTS)
print('\n\n')


#
# Part (d)
#
print('-----Part (d)-----\n\n')


# Part (d.1a)
def calculate_GPA(L: [str]) -> float:
    '''Return the GPA given a list of letter grades'''
    total = 0
    for s in L:
        if s == 'A':
            total += 4
        elif s == 'B':
            total += 3
        elif s == 'C':
            total += 2
        elif s == 'D':
            total += 1
    return total/len(L)
assert calculate_GPA(['A', 'C', 'A', 'B', 'A', 'F', 'D']) == 2.5714285714285716


# Part (d.1b)
def calculate_GPA2(L: [str]) -> float:
    '''Return the GPA given a list of letter grades using a dictionary'''
    D = {'A+': 4, 'A': 4, 'A-': 3.7,
         'B+': 3.3, 'B': 3, 'B-': 2.7,
         'C+': 2.3, 'C': 2, 'C-': 1.7,
         'D+': 1.3, 'D': 1, 'D-': 0.7,
         'F+': 0.3, 'F': 0, 'F-': 0}
    total = 0
    for s in L:
        total += D[s]
    return total/len(L)
assert calculate_GPA2(['A', 'C', 'A', 'B', 'A', 'F', 'D']) == 2.5714285714285716


# Part (d.2)
def flatten_2D_list(L: '2D list') -> list:
    '''Turn a 2D list of int into a single list of int'''
    result = []
    for row in L:
        for i in row:
            result.append(i)
    return result
assert flatten_2D_list([[1, 3, 2],
                        [3, 5, 1],
                        [7, 5, 1],
                        [3, 2],
                        [9, 4]]) == [1, 3, 2, 3, 5, 1, 7, 5, 1, 3, 2, 9, 4]

# Part (d.3a)
print('-----Part (d.3a)-----\n')
def skip_every_third_item(L: list) -> None:
    '''Print each item in the list, skipping every third item'''
    count = 0
    for i in L:
        if count == 2:
            count = 0
        else:
            print(i)
            count += 1
L = ['If', 'you', '432234', 'did', 'the', '9834234', 'exercise', 'correctly', '534523423', 
		 'this', 'should', '1044323', 'be', 'readable']
skip_every_third_item(L)

print('\n\n')


# Part (d.3b)
print('-----Part (d.3b)-----\n')
def skip_every_nth_item(L: list, n: int) -> None:
    '''Print each item in the list, skipping every nth item'''
    count = 0
    for i in L:
        if count == n-1:
            count = 0
        else:
            print(i)
            count += 1
skip_every_nth_item(L, 3)

print('\n\n')


# Part (d.4a)
print('-----Part (d.4a)-----\n')
def tally_days_worked(L: list) -> dict:
    '''Return a dict with each employee's names and days worked'''
    result = {}
    for i in L:
        if i not in result:
            result.update({i: 1})
        else:
            result[i] += 1
    return result
work_week = ['Bob', 'Jane', 'Kyle', 'Larry', 'Brenda', 'Samantha', 'Bob', 
             'Kyle', 'Larry', 'Jane', 'Samantha', 'Jane', 'Jane', 'Kyle', 
             'Larry', 'Brenda', 'Samantha']
workers = tally_days_worked(work_week)
print(workers)

print('\n\n')


# Part (d.4b)
print('-----Part (d.4b)-----\n')
hourly_wages = {'Kyle': 13.50, 'Brenda': 8.50, 'Jane': 15.50, 'Bob': 30.00, 'Samantha': 8.50, 'Larry': 8.50}
def pay_employees(days_worked: dict, wages: dict) -> None:
    '''Prints each employees amount earned from work'''
    for i in wages:
        hours = days_worked[i] * 8
        rate = wages[i]
        total = rate * hours
        print('{} will be paid ${:6.2f} for {} hours of work at ${:4.2f} per hour.'.format(i, total, hours, rate))
pay_employees(workers, hourly_wages)


# Part (d.5)
def reverse_dict(D: dict) -> dict:
    '''Flips a dict's keys and values'''
    result = {}
    for i in D:
        result.update({D[i]: i})
    return result
assert reverse_dict({'a': 'one',
                    'b': 'two',
                    'c': 'three',
                    'd': 'four',
                    'e': 'five',
                    'f': 'six'}) == {'one': 'a', 'three': 'c', 'five': 'e', 'six': 'f', 'two': 'b', 'four': 'd'}
