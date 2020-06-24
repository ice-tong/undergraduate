#
# Project 1
# Kian Farsany 55375951
# Nomin Amgalan 11249291
#

from pathlib import Path
import shutil



def print_list(L: [Path]) -> None:
    '''Prints the list of paths'''
    for p in L:
        print(p)




def D_input(p: Path) -> [Path]:
    '''Return all files (not subdirectories) in the given directory'''
    result = []
    for i in p.iterdir():
        if i.is_file():
            result += [i]
    return result

def R_input(p: Path) -> [Path]:
    '''Return all of the files in the directory
       including its subdirectories' files'''
    result = []
    for i in p.iterdir():
        if i.is_file():
            result += [i]
    for i in p.iterdir():
        if i.is_dir():
            result += R_input(i)
    return result




def A_input(files: [Path]) -> [Path]:
    '''Return all files in the list of Paths'''
    return files

def N_input(files: [Path], file_name: str) -> [Path]:
    '''Return all files with given name'''
    result = []
    for path in files:
        if file_name == path.name:
            result += [path]
    return result

def E_input(files: [Path], extension: str) -> [Path]:
    '''Return files with the given extension'''
    result = []
    for path in files:
        if extension.startswith('.'):
            if extension == path.suffix:
                result += [path]
        elif ('.' + extension) == path.suffix:
            result += [path]
    return result           

def T_input(files: [Path], text: str) -> [Path]:
    '''Return files with the given text; if they are not
       readable files, then skip them'''
    result = []
    for path in files:
        try:
            file = path.open('r')
            file_text = file.read()
            file.close()
            if text in file_text:
                result += [path]
        except:
            pass
    return result
            
def less_than_input(files: [Path], size: float) -> [Path]:
    '''Return the files with size lower than the given bytes'''
    result = []
    for p in files:
        if p.stat().st_size < size:
            result += [p]
    return result

def more_than_input(files: [Path], size: float) -> [Path]:
    '''Return the files with size lower than the given bytes'''
    result = []
    for p in files:
        if p.stat().st_size > size:
            result += [p]
    return result



def F_input(files: [Path]) -> None:
    '''Print the first line of text from text files,
       print NOT TEXT if not a text file'''
    for path in files:
        try:
            file = path.open('r')
            text = file.readline()
            file.close()
            print(text.strip("\n"))
        except:
            print('NOT TEXT')
    
def dup_input(files: [Path]) -> None:
    '''Store a duplicate copy of each file in the same directory
       as the original with .dup added'''
    for path in files:
        path_dup = path.with_suffix(path.suffix+'.dup')
        shutil.copy(path, path_dup)
        
def touch_input(files: [Path]) -> None:
    '''Touch the files'''
    for path in files:
        path.touch()



def read_first_input(path_list: [Path]) -> [Path]:
    '''Read first input, either D or R, print
       error otherwise'''
    while True:
        text = input()

        try:
            command = text[:1]
            p = Path(text[2:])
            if p != Path(''):
                if command == 'D':
                    path_list = D_input(p)
                    print_list(path_list)
                elif command == 'R':
                    path_list = R_input(p)
                    print_list(path_list)
                else:
                    print('ERROR')
                    continue
            else:
                print('ERROR')
                continue
        except:
            print('ERROR')
            continue
        return path_list

def read_second_input(path_list: [Path]) -> [Path]:
    '''Read second input, either A, N, E, T, <, or >,
       print error otherwise'''
    while True:
        text = input()

        try:
            command = text[:1]
            s = text[2:]
            if s != '':
                if command == 'N':
                    path_list = N_input(path_list, s)
                    print_list(path_list)                   
                elif command == 'E':
                    path_list = E_input(path_list, s)
                    print_list(path_list)
                elif command == 'T':
                    path_list = T_input(path_list, s)
                    print_list(path_list)
                elif command == '<':
                    path_list = less_than_input(path_list, float(s))
                    print_list(path_list)
                elif command == '>':
                    path_list = more_than_input(path_list, float(s))
                    print_list(path_list)
                else:
                    print('ERROR')
                    continue
            elif len(text) == 1 and command == 'A' :
                path_list = A_input(path_list)
                print_list(path_list)
            else:
                print('ERROR')
                continue
            if path_list == []:
                return path_list
        except:
                print('ERROR')
                continue
        return path_list
            
def read_third_input() -> None:
    '''Read third input, F, D, or T,
       print error otherwise'''
    while True:
        command = input()
 
        if len(command) == 1:
            if command == 'F':
                F_input(path_list)
            elif command == 'D':
                dup_input(path_list)
            elif command == 'T':
                touch_input(path_list)
            else:
                print('ERROR')
                continue
        else:
            print('ERROR')
            continue
        break
            
                

if __name__ == '__main__':
    
    path_list = []
    
    path_list = read_first_input(path_list)

    path_list = read_second_input(path_list)
    
    path_list = read_third_input()
    

            





