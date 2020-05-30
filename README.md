# TDMA Simulator built in C#
Implemented the random TDMA simulator in C#.

## Random TDMA
### Protocol Description
Each node follows a slot transmission schedule trans, with trans[i] determining the channel on which node i will be allowed to transmit. If node i is not scheduled for transmission, trans[i] = 0. 
At the beginning of each slot, a busy node i with trans[i] = k > 0 is given permission to gransmit on channel k to any of the nodes in the set Bk(the set of nodes that receive on channel k).
Node i can choose from its buffer any of the packets whose destination is in the set Bk, and it will transmit successfully if is has such a packet.
