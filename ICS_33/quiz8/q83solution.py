from   bag import Bag
import unittest  # use unittest.TestCase
import random    # use random.shuffle,random.randint

#random.shuffle(alist) mutates its alist argument to be a random permutation
#random.randint(1,10)  returns a random number in the range 1-10 inclusive


class Test_Bag(unittest.TestCase):
    
    def setUp(self):
        self.alist = ['d','a','b','d','c','b','d']
        self.bag = Bag(self.alist)
        
    def test_len(self):
        self.assertEqual(len(self.bag), 7)
        expected = 6
        random.shuffle(self.alist)
        for v in self.alist:
            self.bag.remove(v)
            self.assertEqual(len(self.bag), expected)
            expected -= 1
        
    def test_unique(self):
        self.assertEqual(self.bag.unique(), 4)
        random.shuffle(self.alist)
        for v in self.alist:
            self.bag.remove(v)
            self.assertEqual(self.bag.unique(), len(self.bag.counts))
        
    def test_contains(self):
        for s in 'abcd':
            self.assertIn(s, self.bag)
        self.assertNotIn('x', self.bag)
        
    def test_count(self):
        self.assertEqual(self.bag.count('a'), 1)
        self.assertEqual(self.bag.count('b'), 2)
        self.assertEqual(self.bag.count('c'), 1)
        self.assertEqual(self.bag.count('d'), 3)
        self.assertEqual(self.bag.count('x'), 0)
        random.shuffle(self.alist)
        expected = 6
        for v in self.alist:
            self.bag.remove(v)
            self.assertEqual(sum([self.bag.count(s) for s in 'abcd']), expected)
            expected -= 1
            
    def test_equal(self):
        test = [random.randint(1,10) for _ in range(1000)]
        bag1 = Bag(test)
        random.shuffle(test)
        bag2 = Bag(test)
        self.assertEqual(bag1, bag2)
        bag1.remove(test[0])
        self.assertNotEqual(bag1, bag2)
        
    def test_add(self):
        test = [random.randint(1,10) for _ in range(1000)]
        bag1 = Bag(test)
        bag2 = Bag()
        random.shuffle(test)
        for v in test:
            bag2.add(v)
        self.assertEqual(bag1, bag2)
        
    def test_remove(self):
        test = [random.randint(1,10) for _ in range(1000)]
        bag1 = Bag(test)
        self.assertRaises(ValueError, bag1.remove, 86)
        
        bag2 = Bag(test)
        random.shuffle(test)
        test1 = [random.randint(1,10) for _ in range(1000)]
        for v in test1:
            bag2.add(v)
        for v in test1:
            bag2.remove(v)
        self.assertEqual(bag1, bag2)
            
        