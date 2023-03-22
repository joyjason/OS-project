#!/usr/bin/env python
# coding: utf-8

# In[1]:


import threading
import time
import multiprocessing 
import queue

INPUT_T = '你要分成幾份thread? :'
INPUT_P = '你要分成幾分process? :'
INPUT_F = '你要分成幾份file? :'

class BSTNode:

	def __init__( self ):
		self.key   = None
		self.left  = None
		self.right = None

def BubbleSort(_list, q):
    Listlen = len(_list)
    for i in range(Listlen):
        for j in range(Listlen-1-i):
            if _list[j] > _list[j+1]:
                _list[j], _list[j+1] = _list[j+1], _list[j] # swap
    q.put(_list)



def _Find_Maximum_Subarray( A, low, high ):
	if high == low:
		return low, high, A[low]
	else:
		mid = ( low + high ) // 2 
		
		left_low, left_high, left_sum    = _Find_Maximum_Subarray( A, low, mid )
		right_low, right_high, right_sum = _Find_Maximum_Subarray( A, mid + 1, high )		
		cross_low, cross_high, cross_sum = _Find_Max_Crossing_Subarray( A, low, mid, high )
		
		if ( left_sum > right_sum and left_sum >= cross_sum ):
			return left_low, left_high, left_sum
		elif ( right_sum >= left_sum and right_sum >= cross_sum ):
			return right_low, right_high, right_sum
		else:
			return cross_low, cross_high, cross_sum
def MergeSort(_ll, _rl, q): # both _ll and _rl are lists
    l, r = 0, 0
    lenOf_ll = len(_ll)
    lenOf_rl = len(_rl)
    items = []# sorted list
    
    while l < lenOf_ll and r < lenOf_rl: # breaks if one of the list is empty !
        if _ll[l] < _rl[r]:
            items.append(_ll[l])
            l += 1
        else : # _ll[l] > _rl[r]
            items.append(_rl[r])
            r += 1

    # after the comparison, concat the rest of the ll or rl
    if l == lenOf_ll:
        items.extend(_rl[r:lenOf_rl])
    else: # r == lenOf_rl
        items.extend(_ll[l:lenOf_ll])

    q.put(items)# put the sorted list into the queue


def Process_bubble_merge(_list, q):# doing bubblesort and mergesort in single process
    for l in _list:
        BubbleSort(l, q)

    while q.qsize() != 1:
        ll = q.get()
        rl = q.get()
        MergeSort(ll, rl, q)

class BinarySearchTree:

	def __init__( self ):
		self.root = None
		self.n = 0

	def Insert( self, key ):
		ptr = BSTNode()
		ptr.key = key
		ptr.left = None
		ptr.right = None

		if ( self.root == None ):
			self.root = ptr
		else:
			parent = None
			current = self.root
			while ( current != None ):
				parent = current
				if ( key < current.key ):
					current = current.left
				else:
					current = current.right
			if ( key < parent.key ):
				parent.left = ptr
			else:
				parent.right = ptr
		self.n += 1

	def Delete( self, key ):
		parent = None
		current = self.root	
		while ( current != None ):			
			if ( key == current.key ):
				break
			parent = current
			if ( key < current.key ):
				current = current.left
			else:
				current = current.right

		if ( current == None ):
			print( "Deleted node is not found." )
		else:
			if ( current.left == None and current.right == None ):  # Leaf node
				if ( current == self.root ):
					self.root = None
				else:
					if ( current.key < parent.key ):
						parent.left = None
					else:
						parent.right = None
			elif ( current.left != None and current.right == None ):  # Left subtree is not empty
				if ( current == self.root ):
					self.root = current.left
				else:
					if ( current.key < parent.key ):
						parent.left = current.left
					else:
						parent.right = current.left
			elif ( current.left == None and current.right != None ):  # Right subtree is not empty
				if ( current == self.root ):
					self.root = current.right
				else:
					if ( current.key < parent.key ):
						parent.left = current.right
					else:
						parent.right = current.right
			else:                                        # Both left & right subtrees are not empty
				prev = current
				ptr = current.right
				while ( ptr.left != None ):
					prev = ptr
					ptr = ptr.left

				if ( ptr.key < prev.key ):
					prev.left = ptr.right
				else:
					prev.right = ptr.right

				current.key = ptr.key

			self.n -= 1				

	def Preorder( self ):
		if ( self.root == None ):
			print( "No keys in the binary search tree." )
		else:
			print( "Binary Search Tree (Preoder):" )
			self._Preorder( self.root )
			print()


def GetList(fileName, f):
    content = f.read() # read the rest of the data
    content_ls = content.split()# seprate the content by ' ', a space
    int_con_ls = list(map(int, content_ls)) # convert all content from String type to Integer type
    return int_con_ls
          
def func(x): return x*x
def dfunc(x): return 2 * x
            
def WriteFile(fileName, list, perf_time): # just write list into output file
    fileName = fileName[0:len(fileName) - 4]
    file = open(fileName + '_output.txt', "w")
    
    file.write('Sorted:\n')
    for index in list:
        file.write(str(index) + ' ')
    file.write('\ntotal time : {:.5f} seconds'.format(perf_time))
    file.close()

    
    
def mission1(fileName,f):
    _list = GetList(fileName,f)
    q = queue.Queue(len(_list))

    start = time.perf_counter() # clock start

    BubbleSort(_list,q) # Start bubblesort function

    process_time = time.perf_counter() - start # clock end
    print('Time: ' + str(process_time))
    WriteFile(fileName, q.get(), process_time)


def mission4(fileName, f):
    sepNum = ''
    while not sepNum.isdigit():
        sepNum = input(INPUT_F)
    sepNum = int(sepNum)
    sep_list = GetSepList(fileName, sepNum, f) # get the processed sepratedly list
    manager = multiprocessing.Manager()
    q = manager.Queue(sepNum) # a queue to store several lists which are sorted by Bubblesort

    start = time.perf_counter() # clock start

    # just put the separated list into the Process_bubble_merge function as a process
    pbm = multiprocessing.Process(target = Process_bubble_merge, args = (sep_list, q))
    pbm.start()
    pbm.join()

    process_time = time.perf_counter() - start # clock end

    print('Time: ' + str(process_time))
    WriteFile(fileName, q.get(), process_time)

if __name__ == '__main__':
    fileName = input('請輸入檔名: ')
    f = open(fileName , "r")
    #if f == NULL : print('找不到檔案，請確認你的input是否正確')
    missionNum = f.read(1)
    
    if missionNum == '1':
        mission1(fileName, f)
    elif missionNum == '4':
        mission4(fileName, f)
    else :
        print('你的檔案格式錯誤，請使用格式相容的檔案')


    print('任務結束')
    input('請輸入任意input結束')





