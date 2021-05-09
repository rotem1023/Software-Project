#input-filepath, file is a matrix
#output-the matrix
import sys

#import from file
def fromFile():
    arr=fromFile2()
    return [split2(x.split(",")) for x in arr];

def fromFile2():
    temp=[]
    c=input()
    while (True):
        try:
            temp.append(c)
            c = input()
        except EOFError as e:
            break;
    return temp


def split2(arr):
    for i in range (len(arr)):
        arr[i]=float(arr[i]);
    return arr;



# add vector to is cluster
def add_group(vec, mean):
    for i in range(len(vec)):
        mean.append(vec[i])

# checking the distance from the mean
def distanceFromMean(n, vec, mean):
    
    d = 0
    x = 0
    distance = 0
    for i in range(n):
        meani = mean[i]
        x = vec[i]
        distance = (x - meani) * (x - meani)
        d = d + distance
    return d

# update the mean according to the last iteration
def update_mean(n, vec, mean, numOfVec):
    if numOfVec > 0:

        for i in range(n):
            meani = mean[i]
            summ = meani * numOfVec + vec[i]
            mean[i] = summ / (numOfVec + 1)
    else:
   
        for j in range(n):

            mean[j]=(vec[j])
           


def update_check(n, vec, vec2):
    for i in range(n):
        vec[i] = vec2[i]

# help function to check if we need to stop the function from runing
def to_stop(n, vec, mean):
    for i in range(n):
        if vec[i] != mean[i]:
            return False
    return True

# help function to check if we need to stop the function from runing
def to_stop_v2(d, n, a1, a2):
    for i in range(n):
        if not to_stop(d, a1[i], a2[i]):
            return False
    return True


def copyVecOfMeans(d, n, a1, a2):
    for i in range(n):
        for j in range(d):
            a2[i][j] = a1[i][j]


def mainFuncV2(k, max_iter):
    yaeri_vec= fromFile();
    iterr = 0
    d = len(yaeri_vec[0])
    number_of_vec_per_group = [0 for i in range(k)]
    vec_of_means_old = [[0 for j in range(d)] for i in range(k)]
    vec_of_means_new = [[0 for j in range(d)] for i in range(k)]
    boolean = False
    assert (k > 0)
    assert (k < len(yaeri_vec))
    assert (max_iter > 0)
    ##// initialize
    for t in range(k):
        for t1 in range(d):
            vec_of_means_old[t][t1] = yaeri_vec[t][t1]
    while iterr < max_iter:
        # distance=0
        # place=0
        cur_distance = 0
        for i in range(len(yaeri_vec)):
            distance = 0
            place = 0
            cur_distance = 0
            for j in range(k):
                vec= yaeri_vec[i]
                cur_distance = distanceFromMean(d, vec, vec_of_means_old[j])
                if j == 0:
                    distance = cur_distance
                if cur_distance < distance:
                    distance = cur_distance
                    place = j
            update_mean(d, vec, vec_of_means_new[place], number_of_vec_per_group[place])
            number_of_vec_per_group[place] = number_of_vec_per_group[place] + 1
        if to_stop_v2(d, k, vec_of_means_old, vec_of_means_new):
            boolean = True
            break
        copyVecOfMeans(d, k, vec_of_means_new, vec_of_means_old)
        number_of_vec_per_group = [0 for i in range(k)]
        iterr = iterr + 1
    for a in range(k):
        for b in range(d):
            vec_of_means_old[a][b]=format(vec_of_means_old[a][b],'.4f')
    return vec_of_means_old

def printSpecial (mat):
    for i in mat:
        for j in range(len(i)):
            print(i[j],end="")
            if (j!=len(i)-1):
                print(",",end="")
        print("\n",end="")

arr= sys.argv
if (len(arr)==2):
    x0 =int (arr[1])
    printSpecial(mainFuncV2(x0, 200))
if (len(arr)==3):
    x0=int (arr[1])
    x1= int (arr[2])
    printSpecial(mainFuncV2(x0, x1))
if (len(arr)<2):
    assert (1<0)
if (len(arr)>3):
    assert (1<0)

