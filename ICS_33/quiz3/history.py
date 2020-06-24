from collections import defaultdict


class History:
    def __init__(self):
        pass

    
    def __getattr__(self,name):
        pass


    def __getitem__(self,index):
        pass

    
    def __setattr__(self,name,value):
        pass





if __name__ == '__main__':
    #Simple tests before running driver
    #Put your own test code here to test History before doing bsc tests

    print('Start simple testing')

    
    import driver
    driver.default_file_name = 'bsc2.txt'
#     driver.default_show_traceback =True
#     driver.default_show_exception =True
#     driver.default_show_exception_message =True
    driver.driver()
