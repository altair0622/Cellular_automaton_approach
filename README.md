# Project1

## Group members

Han Gyol Kim / hkim857@gatech.edu

Ruxu Zhang / zhangruxu@gatech.edu

Ciyuan Yu / cyu338@gatech.edu

## Code Files Description

application.c file: system building file to extract data

sim.py: input data and visulize data


### Installation

For C:

```
gcc application.c -o main
```

### Execution

For C:

```
./main <density> <accident_possibility> <data_file_name.txt> <accident_file_name.txt>
```

For Python:

```
python sim.py
```

## General idea

When it comes to traffic congestion, a car accident is an unignorable factor. In highways, due to high driving speed and relative high density of vehicles, car accidents always cause more serious consequences than accidents on normal roads do. This would definitely lead to large impact to the traffic flow on the highways.
  
Our simulation model will focus on this topic, the final model is a five-lane traffic flow model with lane changing and accidents happen with certain possibility, and the whole model is based on the cellular traffic model.
