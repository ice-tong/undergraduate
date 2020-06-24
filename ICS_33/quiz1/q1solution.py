# Submitter: kfarsany(Farsany, Kian)

def solve_root(f : callable, error : float) -> callable:
    if error <= 0:
        raise AssertionError
    
    def result_func(negf: float, posf: float) -> float:
        if f(negf) >= 0 or f(posf) <= 0:
            raise AssertionError
        while True:
            midpoint = (posf + negf) / 2
            if f(midpoint) < 0:
                negf = midpoint
            elif f(midpoint) > 0:
                posf = midpoint
                
            if abs(posf - negf) <= error:
                return midpoint
    
    return result_func



UCI = {'A+': 4.0, 'A': 4.0, 'A-': 3.7,
       'B+': 3.3, 'B': 3.0, 'B-': 2.7,
       'C+': 2.3, 'C': 2.0, 'C-': 1.7,
       'D+': 1.3, 'D': 1.0, 'D-': 0.7,
       'F' : 0.0}


# To write small function bodies I used the following abbreviations
# c for a course; s for a student; g for a grade; feel free to use
# these abbreviations for use longer/more descriptive names

def enrollments(db : {str:{(str,str)}}) -> [(str,int)]:
    return sorted([(course, len(db[course])) for course in db], key = (lambda x: -x[1]))
    

def hardness(db : {str:{(str,str)}}) -> [str]:
    return sorted([course for course in db], key = lambda x: ( sum([UCI[student[1]] for student in db[x]]) / len(db[x]), -len(db[x]) ) )


def honors(db : {str:{(str,str)}}, gpa : float) -> {str: [str]}:
    return {course: sorted([student[0] for student in db[course] if UCI[student[1]] >= gpa]) for course in db}


def honors2(db : {str:{(str,str)}}, gpa : float) -> {str: [str]}:
    return {course: [student[0] for student in sorted(list(db[course]), key = lambda x: -UCI[x[1]]) if UCI[student[1]] >= gpa] for course in db}


def grade_view(db : {str:{(str,str)}}) -> {str: {str : {str}}}:
    outer_dict = dict()
    for course in db:
        for student in db[course]:
            grade = student[1][0]
            if grade not in outer_dict:
                outer_dict[grade] = {course: {student[0]}}
            elif course not in outer_dict[grade]:
                outer_dict[grade][course] = {student[0]}
            else:
                outer_dict[grade][course].add(student[0])
    return outer_dict
                






if __name__ == '__main__':
    # This code is useful for debugging your functions, especially
    #   when they raise exceptions: better than using driver.driver().
    # Feel free to add more tests (including tests showing in the bsc.txt file)
    # Use the driver.driver() code only after you have removed any bugs
    #   uncovered by these test cases.
    
    from goody import irange
    import math
    
    print('\nTesting solve_root')
    def f(x):
        return 3*x**4 + 3*x**3 - 1 
    rooter = solve_root(f, .0001)
    r1,r2 = rooter(0,1),rooter(-1,-2)
    print(f'root 1 is approximately {r1} where f({r1}) ={f(r1)}')
    print(f'root 2 is approximately {r2} where f({r2}) ={f(r2)}')
    root = solve_root(lambda x : 23*math.sqrt(x) - (10*math.log2(x)**2+1000), .1)(10000,20000)
    print(f'root is approximately {root}')


    print('\nTesting enrollments')
    db = {'ICS-31': {('Bob', 'A'), ('David', 'C'), ('Carol', 'B')}, 'Math-3A': {('Bob', 'B'), ('Alice', 'A')}}
    print(enrollments(db))
    db = {'ICS-31':  {('Carol', 'B+'), ('Debbie','B-')},
          'ICS-32':  {('Alan', 'B')},
          'ICS-33':  {('Fran', 'A+'),('Herb','C'),('Erin','B')},
          'Math-3A': {('Bob', 'B+'), ('Alan', 'A')},
          'Math-3B': {('Bob', 'C'), ('Alan', 'B+')}}
    print(enrollments(db))

    print('\nTesting hardness')
    db = {'ICS-31': {('Bob', 'A'), ('David', 'C'), ('Carol', 'B')}, 'Math-3A': {('Bob', 'B'), ('Alice', 'A')}}
    print(hardness(db))
    db = {'ICS-31':  {('Carol', 'B+'), ('Debbie','B-')},
          'ICS-32':  {('Alan', 'B')},
          'ICS-33':  {('Fran', 'A+'),('Herb','C'),('Erin','B')},
          'Math-3A': {('Bob', 'B+'), ('Alan', 'A')},
          'Math-3B': {('Bob', 'C'), ('Alan', 'B+')}}
    print(hardness(db))

    print('\nTesting honors')
    db = {'ICS-31': {('Bob', 'A'), ('David', 'C'), ('Carol', 'B')}, 'Math-3A': {('Bob', 'B'), ('Alice', 'A')}}
    print(honors(db,2.7))
    db = {'ICS-31':  {('Carol', 'B+'), ('Debbie','B-')},
          'ICS-32':  {('Alan', 'B')},
          'ICS-33':  {('Fran', 'A+'),('Herb','C'),('Erin','B')},
          'Math-3A': {('Bob', 'B+'), ('Alan', 'A')},
          'Math-3B': {('Bob', 'C'), ('Alan', 'B+')}}
    print(honors(db,3.3))

    print('\nTesting honors2')
    db = {'ICS-31': {('Bob', 'A'), ('David', 'C'), ('Carol', 'B')}, 'Math-3A': {('Bob', 'B'), ('Alice', 'A')}}
    print(honors2(db,2.7))
    db = {'ICS-31':  {('Carol', 'B+'), ('Debbie','B-')},
          'ICS-32':  {('Alan', 'B')},
          'ICS-33':  {('Fran', 'A+'),('Herb','C'),('Erin','B')},
          'Math-3A': {('Bob', 'B+'), ('Alan', 'A')},
          'Math-3B': {('Bob', 'C'), ('Alan', 'B+')}}
    print(honors2(db,2.7))

    print('\nTesting grade_view')
    db = {'ICS-31': {('Bob', 'A'), ('David', 'C'), ('Carol', 'B')}, 'Math-3A': {('Bob', 'B'), ('Alice', 'A')}}
    print(grade_view(db)) 
    db = {'ICS-31':  {('Carol', 'B+'), ('Debbie','B-')},
          'ICS-32':  {('Alan', 'B')},
          'ICS-33':  {('Fran', 'A+'),('Herb','C'),('Erin','B')},
          'Math-3A': {('Bob', 'B+'), ('Alan', 'A')},
          'Math-3B': {('Bob', 'C'), ('Alan', 'B+')}}
    print(grade_view(db))

    
    print('\ndriver testing with batch_self_check:')
    import driver
    driver.default_file_name = "bscq1W18.txt"
#     driver.default_show_traceback = True
#     driver.default_show_exception = True
#     driver.default_show_exception_message = True
    driver.driver()           



# What script should print (before driver executed)
#
# Testing solve_root
# root 1 is approximately 0.593597412109375 where f(0.593597412109375) =-5.556624596381177e-05
# root 2 is approximately -1.195220947265625 where f(-1.195220947265625) =-1.782591557120128e-05
# root is approximately 16630.05828857422
# 
# Testing enrollments
# [('ICS-31', 3), ('Math-3A', 2)]
# [('ICS-33', 3), ('ICS-31', 2), ('Math-3A', 2), ('Math-3B', 2), ('ICS-32', 1)]
# 
# Testing hardness
# ['ICS-31', 'Math-3A']
# ['Math-3B', 'ICS-31', 'ICS-32', 'ICS-33', 'Math-3A']
# 
# Testing honors
# {'ICS-31': ['Bob', 'Carol'], 'Math-3A': ['Alice', 'Bob']}
# {'ICS-31': ['Carol'], 'ICS-32': [], 'ICS-33': ['Fran'], 'Math-3A': ['Alan', 'Bob'], 'Math-3B': ['Alan']}
# 
# Testing honors2
# {'ICS-31': ['Bob', 'Carol'], 'Math-3A': ['Alice', 'Bob']}
# {'ICS-31': ['Carol', 'Debbie'], 'ICS-32': ['Alan'], 'ICS-33': ['Fran', 'Erin'], 'Math-3A': ['Alan', 'Bob'], 'Math-3B': ['Alan']}
# 
# Testing grade_view
# {'C': {'ICS-31': {'David'}}, 'B': {'ICS-31': {'Carol'}, 'Math-3A': {'Bob'}}, 'A': {'ICS-31': {'Bob'}, 'Math-3A': {'Alice'}}}
# {'B': {'ICS-31': {'Carol', 'Debbie'}, 'ICS-32': {'Alan'}, 'ICS-33': {'Erin'}, 'Math-3A': {'Bob'}, 'Math-3B': {'Alan'}}, 'C': {'ICS-33': {'Herb'}, 'Math-3B': {'Bob'}}, 'A': {'ICS-33': {'Fran'}, 'Math-3A': {'Alan'}}}
