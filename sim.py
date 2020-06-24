import numpy as np
import matplotlib.pyplot as plt # Core plotting support



# Possible states:
EMPTY = 0 # not occupied by a vehicle in a cell
SHOULDER = 1 # left shoulder and right shoulder just next to travel lanes
OCCUPIED = 2 # the cell occupied by a vehicle
ACCIDENT = 3 # the cell where an accident happens

def create_world (n, m):
    G = EMPTY * np.ones ((n+2, m), dtype=int)
    G[0, :] = 1
    G[6, :] = 1

    return G

def show_peeps (G, Lane_flow, file, file_acc, vmin=EMPTY, vmax=ACCIDENT, values="states"):
    # visualize a 2-D world

    # Set color range
    assert values in ["states", "bool"]
    if values == "states":
        vticks = range (vmin, vmax+1)
        vlabels = ['Empty', 'Shoulder', 'Occupied', 'Accident']
    else:
        vticks = [0, 1]
        vlabels = ['False (0)', 'True (1)']
    
    m, n = G.shape[0], G.shape[1]

    # Set visualization plot of CA
    plt.subplot(2, 1, 1)
    plt.pcolor (G, vmin=vmin, vmax=vmax, edgecolor='black')
    cb = plt.colorbar (shrink=0.25)
    cb.set_ticks (vticks)
    cb.set_ticklabels (vlabels)
    plt.axis ('square')
    plt.axis ([0, n, 0, m])
    plt.title("Traffic movement "+file.split('.txt')[0] + "_time "+str(time))


    # Set flow-time chart of CA
    x1 = []
    y1 = [[],[],[],[],[]]

    for tt in range(time+1):

        x1.append(tt)
        for yy in range(5):
            y1[yy].append(Lane_flow[tt][yy])


    plt.subplot(2, 1, 2)
    plt.plot(x1, y1[0], 'b-', label='lane 1')
    plt.plot(x1, y1[1], 'g-', label='lane 2')
    plt.plot(x1, y1[2], 'r-', label='lane 3')
    plt.plot(x1, y1[3], 'c-', label='lane 4')
    plt.plot(x1, y1[4], 'm-', label='lane 5')


    plt.title('Time-flow diagrams_time '+ str(time))
    plt.ylabel('Flow')
    plt.xlabel('time (s)')
    plt.xlim(0,500)
    plt.ylim(0,5)
    plt.legend(loc='upper left',  prop={'size': 5})

    #plt.canvas.draw()
    plt.pause(0.1)
    times = [58,59,60,61]
    #times = [3, 37, 38, 499]
    if time in times:
        #plt.show()
        plt.savefig('simulation_'+str(time)+'.png', dpi=1000)



def filereader (G, File, File_Acc, Time):
    # file reader

    G[1:6, :] = EMPTY
    f = open(File, 'r')
    f_a = open(File_Acc, 'r')
    lane_flow_cell = [0, 0, 0, 0, 0]
    total = [0,0,0,0,0]
    A = total
    for i in f:
        i = i.split()

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
file = 'den_0.2_acc_0.000100.txt'
file_acc = 'den_0.2_acc_0.000100_accident.txt'
lane_flow = []

for time in range(500):

    timeandlane, cell = filereader (peeps_0, file, file_acc, time)
    lane_flow.append(cell)
    show_peeps (peeps_0, lane_flow, file, file_acc)
    plt.clf()


