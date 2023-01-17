# JIT-SW
This repository includes Linux driver and software. [JIT-HW](https://github.com/Leo-Cheung-CUHK/JIT-HW) repository has the FPGA design. This repository is based on the original [Openwifi repository](https://github.com/open-sdr/openwifi). This readme only describes the new features provided in JIT-SW. To see more detail about the original design of openwifi-HW, please check the README_Openwifi.md.

# New Feature 
## Hybrid TDMA/CSMA Channel Access Mechanism
In the JIT system, time is divided into frames. Each frame consists of three sections: 

1) Section 1 - Time-slotted TDMA section: Each TDMA user use its assigned time slots for its transmission. This section is suitable for time-sensitive application. 
2) Section 2 - CSMA-based control-information section: This section is for control-information transmission needed in section 1. The control-information includes message of time-slot allocation and message for time synchronization among TDMA user. 
3) Section 3 - Gneral-purpose CSMA section: This section is for general traffic. 

# Timestamping Mechanism
Whenever sending a packet from driver to hardware, a timestamp is needed to be generated by the driver and this tiemstamp is further delivered to the hardware. 

1) For the packet of sections 2 & 3, its timestamp is ignored in JIT-HW anyway, and hence it is set to a random value.
2) For the packet of section 1, its timestamp is its scheduled transmission time according to the time-slot allocation in the JIT network. 

# Time Slot Allocation
1) The time slot alloaction is determined by the TDMA server and is transmitted to TDMA clients. 
2) The information of time slot allocation is a type of control information which is transmitted in section 2. 

# PTP synchronziation mechanism
Time synchronization is needed to calibrate the timestamp that is assoicated to a packet. In the JIT network, precise-time-protocol synchronization mechanism is deployed. Details of the basic concept can be found in this [paper](https://ieeexplore.ieee.org/stamp/stamp.jsp?arnumber=9480604). 

# JIT Paper
This is the source code of the paper ["A Just-In-Time Networking Framework for Minimizing Request-Response Latency of Wireless Time-Sensitive Applications"](https://arxiv.org/pdf/2109.03032.pdf).

Please cite our publication if you intened to use this repo.

@article{zhang2021just, title={A Just-In-Time Networking Framework for Minimizing Request-Response Latency of Wireless Time-Sensitive Applications}, author={Zhang, Lihao and Liew, Soung Chang and Chen, He}, journal={arXiv preprint arXiv:2109.03032}, year={2021} }