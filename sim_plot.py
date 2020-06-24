import numpy as np
import matplotlib.pyplot as plt # Core plotting support
'''
file1 = 'flows_den_0.2_acc_0.01.txt'
file2 = 'flows_den_0.2_acc_0.001.txt'
file3 = 'flows_den_0.2_acc_0.0001.txt'
file4 = 'flows_den_0.2_acc_0.00001.txt'
file5 = 'flows_den_0.2_acc_0.000001.txt'

f1 = open(file1, 'r')
x1 = []
y1 = []
for i in f1:
    i = i.split()
    x1.append(float(i[0]))
    y1.append(float(i[1]))
plt.plot(x1, y1, 'b-', label='den_0.2_acc_0.01')


f2 = open(file2, 'r')
x2 = []
y2 = []
for i in f2:
    i = i.split()
    x2.append(i[0])
    y2.append(float(i[1]))
plt.plot(x1, y2, 'g-', label='den_0.2_acc_0.001')


f3 = open(file3, 'r')
x3 = []
y3 = []
for i in f3:
    i = i.split()
    x3.append(i[0])
    y3.append(float(i[1]))
plt.plot(x1, y3, 'r-', label='den_0.2_acc_0.0001')


f4 = open(file4, 'r')
x4 = []
y4 = []
for i in f4:
    i = i.split()
    x4.append(i[0])
    y4.append(float(i[1]))
plt.plot(x1, y4, 'c-', label='den_0.2_acc_0.00001')

f5 = open(file5, 'r')
x5 = []
y5 = []
for i in f5:
    i = i.split()
    x5.append(i[0])
    y5.append(float(i[1]))
plt.plot(x1, y5, 'm-', label='den_0.2_acc_0.000001')



plt.title('Time-flow by different accident rates')
plt.ylabel('Flow')
plt.xlabel('time (s)')
#plt.xlim(0,500)
plt.legend(loc='upper left',  prop={'size': 5})


plt.savefig('simulation_acc.png', dpi=1000)

'''
file1 = 'flows_den_0.2_acc_0.0001.txt'
file2 = 'flows_den_0.4_acc_0.0001.txt'
file3 = 'flows_den_0.6_acc_0.0001.txt'
file4 = 'flows_den_0.8_acc_0.0001.txt'

f1 = open(file1, 'r')
x1 = []
y1 = []
for i in f1:
    i = i.split()
    x1.append(float(i[0]))
    y1.append(float(i[1]))
plt.plot(x1, y1, 'b-', label='den_0.2_acc_0.001')


f2 = open(file2, 'r')
x2 = []
y2 = []
for i in f2:
    i = i.split()
    x2.append(i[0])
    y2.append(float(i[1]))
plt.plot(x1, y2, 'g-', label='den_0.4_acc_0.001')


f3 = open(file3, 'r')
x3 = []
y3 = []
for i in f3:
    i = i.split()
    x3.append(i[0])
    y3.append(float(i[1]))
plt.plot(x1, y3, 'r-', label='den_0.6_acc_0.001')


f4 = open(file4, 'r')
x4 = []
y4 = []
for i in f4:
    i = i.split()
    x4.append(i[0])
    y4.append(float(i[1]))
plt.plot(x1, y4, 'c-', label='den_0.8_acc_0.001')





plt.title('Time-flow by different density rates')
plt.ylabel('Flow')
plt.xlabel('time (s)')
#plt.xlim(0,500)
plt.legend(loc='upper left',  prop={'size': 5})


plt.savefig('simulation_den.png', dpi=1000)


'''
def filereader (G, File, File_Acc, Time):
    # file reader

    G[1:6, :] = EMPTY

    lane_flow_cell = [0, 0, 0, 0, 0]
    total = [0,0,0,0,0]
    A = total


        if i[0]==str(Time):
            G[int(i[1]),int(i[4])]= OCCUPIED
            total[int(i[1])-1]+=1
            lane_flow_cell[int(i[1])-1]+=int(i[3])

    for j in range(5):
        A[j] = float(lane_flow_cell[j])/total[j]
    for fa in f_a:
        fa = fa.split()

        if fa[0]==str(Time):
            G[int(fa[1]),int(fa[2])]= ACCIDENT

    return G, A


# set # of lanes and # of cells each lane
N = 5
M = 100



peeps_0 = create_world (N, M)

lane_flow = []

for time in range(500):

    timeandlane, cell = filereader (peeps_0, file, file_acc, time)
    lane_flow.append(cell)
    show_peeps (peeps_0, lane_flow, file, file_acc)
    plt.clf()

'''
