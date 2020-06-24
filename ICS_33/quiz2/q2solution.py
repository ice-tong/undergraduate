import re

# Before running the driver on the bsc.txt file, ensure you have put a regular
#   expression pattern in the files repattern1a.txt, repattern1b.txt, repattern1c.txt, 
#   and repattern1d.txt. The patterns must be all on the first line, enclosed in ^ and $


def expand_re(pat_dict:{str:str}):
    for rule in pat_dict:
        key = re.compile('#' + rule + '#')
        for other_rule in pat_dict:
            pat_dict[other_rule] = key.sub('(?:' + pat_dict[rule] + ')', 
                                           pat_dict[other_rule])
    

def multiline_search(pat_file : open, text_file : open) -> [(int,[int])]:
    result = []
    
    text_lines = [line.rstrip() for line in text_file]
    
    patterns = []
    for line_number, line in enumerate(pat_file, 1):
        patterns.append((line_number, [re.compile(p) for p in line.rstrip().split('<->')]))
       
    for t in range(len(text_lines)):
        pat_matches = []
        for pat_seq in patterns:
            if t+len(pat_seq[1]) <= len(text_lines):
                match = True
                for p in range(len(pat_seq[1])):
                    if pat_seq[1][p].search(text_lines[t+p]) == None:
                        match = False
                if match:
                    pat_matches.append(pat_seq[0])
        if pat_matches != []:
            result.append((t+1, pat_matches))
    return result
    
if __name__ == '__main__':
    
    p1a = open('repattern1a.txt').readline().rstrip() # Read pattern on first line
    print('Testing the pattern p1a: ',p1a)
    for text in open('bm1a.txt'):
        text = text.rstrip()
        print('Matching against:',text)
        m = re.match(p1a,text)
        print(' ','Matched' if m != None else "Not matched")


    p1b = open('repattern1b.txt').readline().rstrip() # Read pattern on first line
    print('\nTesting the pattern p1b: ',p1b)
    for text in open('bm1b.txt'):
        text = text.rstrip()
        print('Matching against:',text)
        m = re.match(p1b,text)
        print('  ','Matched' if m != None else 'Not matched' )
        
        
    p1c = open('repattern1c.txt').readline().rstrip() # Read pattern on first line
    print('\nTesting the pattern p1c: ',p1c)
    for text in open('bm1c.txt'):                 # Same file as before
        text = text.rstrip()
        print('Matching against:',text)
        m = re.match(p1c,text)
        print('  ','Matched' if m != None else 'Not matched' )
        
        
    p2 = open('repattern1d.txt').read().rstrip() # Read pattern on first line
    print('\nTesting the pattern p2: ',p2)
    for text in open('bm1d.txt'):
        text = text.rstrip()
        print('Matching against:',text)
        m = re.match(p2,text)
        print('  ','Matched with numbered groups ='+ str(m.groups())    if m != None else 'Not matched' )
        print('  ','Matched with named    groups ='+ str(m.groupdict()) if m != None else 'Not matched' )
        
    
    
    print('\nTesting expand_re')
    pd = dict(digit = r'\d', integer = r'[+-]?#digit##digit#*')
    print('  Expanding ',pd)
    expand_re(pd)
    print('  result =',pd)
    # produces/prints the dictionary
    # {'digit': '\\d', 'integer': '[=-]?(?:\\d)(?:\\d)*'}
    
    pd = dict(integer       = r'[+-]?\d+',
              integer_range = r'#integer#(..#integer#)?',
              integer_list  = r'#integer_range#(?,#integer_range#)*',
              integer_set   = r'{#integer_list#?}')
    print('\n  Expanding ',pd)
    expand_re(pd)
    print('  result =',pd)
    # produces/prints the dictionary 
    # {'integer': '[+-]?\\d+',
    #  'integer_range': '(?:[+-]?\\d+)(..(?:[+-]?\\d+))?',
    #  'integer_list': '(?:(?:[+-]?\\d+)(..(?:[+-]?\\d+))?)(?,(?:(?:[+-]?\\d+)(..(?:[+-]?\\d+))?))*',
    #  'integer_set': '{(?:(?:(?:[+-]?\\d+)(..(?:[+-]?\\d+))?)(?,(?:(?:[+-]?\\d+)(..(?:[+-]?\\d+))?))*)?}'
    # }
    
    pd = dict(a='correct',b='#a#',c='#b#',d='#c#',e='#d#',f='#e#',g='#f#')
    print('\n  Expanding ',pd)
    expand_re(pd)
    print('  result =',pd)
    # produces/prints the dictionary 
    # {'a': 'correct',
    #  'b': '(?:correct)',
    #  'c': '(?:(?:correct))',
    #  'd': '(?:(?:(?:correct)))',
    #  'e': '(?:(?:(?:(?:correct))))',
    #  'f': '(?:(?:(?:(?:(?:correct)))))',
    #  'g': '(?:(?:(?:(?:(?:(?:correct))))))'
    # }
    
    
    
    print('\nTesting multiline_search on pats1.txt and texts1.txt')
    print(multiline_search(open("pats1.txt"),open("texts1.txt")))

    print('\nTesting multi_search on pats2.txt and texts2.txt')
    print(multiline_search(open("pats2.txt"),open("texts2.txt")))
    
    
    
    print()
    print()
    import driver
    driver.default_file_name = "bscq2W18.txt"
#     driver.default_show_traceback = True
#     driver.default_show_exception = True
#     driver.default_show_exception_message = True
    driver.driver()
    
    
       
        
        
        
        

