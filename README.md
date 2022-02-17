# can-for-omnet

## What's this

- OMNeT++ is an extensible, modular, component-based C++ simulation library and framework, primarily for building network simulators.
- However OMNeT++ does not include simulation model to simulate automotive control networks. 
- Here, we have distributed source code of a simulation model for Controller Area Network (CAN) for OMNeT++ as an open-source.
- Anyone can download the source code at Github and simulate the CAN network. However, the distributed source code is a beta version that may include some bugs.
- We have also distributed a CAN-Ethernet GW model as an experimental version. It can be found Github.

## Features

- A simulation model for CAN (Controller Area Network) for OMNeT++. This is the only one found in the world so far.
- A simulation model for CAN message router is included. By using this model, CAN-CAN gateway can be simulated easily.
- Error frame of the CAN protocol is not supported in the current version. It may be supported if there are any requests.

## Environment

- OMNeT++ 4.4.1 or later (We confirmed on 4.4.1 and 4.6. Unfortunately, 5.x are not supported.)
- INET-Framework 2.3.0 or 2.5 (We found some errors when compiling with INET 2.6 or 3.x.) 

## Installation Instructions

1. Download and Install OMNeT++ and INET-Framework in your computer (usually ~/program/). If you install them for the first time, please refer to their install guides.

2. Extract the downloaded zip file and copy all source files into your inet directory (usually ~/program/omnetpp-4.4.1/inet/) as follows.

- 0.1.0/src/* -> ~/program/omnetpp-4.4.1/inet/src/
- 0.1.0/example/* -> ~/program/omnetpp-4.4.1/inet/example/

```
$ cp -r 0.1.0/src/* ~/program/omnetpp-4.4.1/inet/src
$ cp -r 0.1.0/example/* ~/program/omnetpp-4.4.1/inet/example/
```

3. Change to the root directory(e.g. ~/program/omnetpp-4.4.1) of OMNeT++.

```
$ cd ~/program/omnetpp-4.4.1
$ . setenv
```

4. This should generate the makefiles for you automatically.

```
$ ./configure
```
5. Type "make" to build the CAN executable.

```
$ cd inet
$ make clean
$ make makefiles
$ make
```

6. We implemented the following examples for CAN. These examples are located in omnetpp-4.4.1/inet/examples/can/. You can run specific examples by changing into the example's directory and executing "./run". If the run file has not permission of execution, type "chmod +x run".
- bus1
- bus2
- messagerouter1
- messagerouter2

## Publication
- Keigo Kawahara, Yutaka Matsubara and Hiroaki Takada, "A Simulation Environment and Preliminary Evaluation for Automotive CAN-Ethernet AVB Networks", Proceedings of the 1st OMNeT++ Community Summit (Successor of the International Workshop on OMNeT++), pp. xx-xx, Hamburg, Germany, Sep 2014.
- Jun Matsumura, Yutaka Matsubara, Hiroaki Takada, Masaya Oi, Masumi Toyoshima and Akihito Iwai, "A Simulation Environment based on OMNeT++ for Automotive CAN–Ethernet Networks", Proceedings of the 4th International Workshop on Analysis Tools and Methodologies for Embedded and Real-time Systems (WATERS2013), pp.1-6, Paris, France, Jul 2013. [PDF]

## Contacts
- We welcome feedback from users of our simulation model.
- If you have any questions, please feel free to ask us by e-mail. You can find our contact information here.
