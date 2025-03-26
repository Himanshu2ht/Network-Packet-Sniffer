# Network Packet Sniffer (Kernel-Space)

## Introduction
A **Network Packet Sniffer** is a tool used to **monitor and analyze network traffic** at a low level. This project aims to implement a **Kernel-Space Packet Sniffer** that captures and logs network packets in a Linux system. The implementation will use **Binary Search Trees (BSTs) and Doubly Linked Lists (DLLs)** for efficient data storage and retrieval.

## Objectives
- Capture **incoming and outgoing network packets** at the kernel level.
- Classify packets based on protocol (TCP, UDP, ICMP, etc.) using a **Binary Search Tree (BST)**.
- Maintain a **Doubly Linked List (DLL)** for recent packet history.
- Provide a **lightweight and efficient** logging mechanism.

## Real-World Applications
- **Network Security Monitoring**: Detect unusual or malicious traffic.
- **Intrusion Detection Systems (IDS)**: Identify unauthorized access.
- **Traffic Analysis**: Optimize network performance.
- **Performance Debugging**: Debug network-related application issues.

## System Architecture
### Components:
1. **Kernel Module**:
   - Hooks into **network stack** to capture packets.
   - Stores packets in **BST (for classification)**.
   - Uses **DLL (for recent history tracking)**.
2. **User-Space Interface**:
   - Communicates with the kernel module to retrieve logged packets.
   - Displays logs in a readable format.

### Data Structures Used
- **Binary Search Tree (BST)**: Efficient packet classification and lookup.
- **Doubly Linked List (DLL)**: Fast insertion/deletion of recent packets.
- **Structures (struct)**: To store packet metadata (source, destination, protocol, timestamp).

## Implementation Steps
1. **Set Up Kernel Module**
   - Loadable Kernel Module (LKM) to hook into the network stack.
   - Use `netfilter` hooks to capture packets.
   
2. **Implement Packet Storage**
   - **BST** for classifying packets by protocol.
   - **DLL** for maintaining a cache of recent packets.
   
3. **Logging Mechanism**
   - Write logs to **/var/log/sniffer.log**.
   - Expose data via `/proc/sniffer_info`.
   
4. **User-Space Interaction**
   - Implement a simple command (`cat /proc/sniffer_info`) to retrieve logs.
   
5. **Testing and Debugging**
   - Test using **Wireshark** and `tcpdump` for validation.
   - Monitor performance impact.

## Safety Considerations
- **Kernel Stability**: Ensure memory is managed properly.
- **Security**: Prevent unauthorized access to logs.
- **Performance**: Optimize packet processing to avoid system slowdowns.

## Future Enhancements
- **Filtering by IP or Port**.
- **Live User-Space Monitoring Tool**.
- **Machine Learning for Anomaly Detection**.

## Conclusion
This **Kernel-Space Network Packet Sniffer** provides a powerful tool for **network analysis and security monitoring** while leveraging efficient **BST and DLL data structures** for real-time performance. It lays the groundwork for advanced **network security applications** and **traffic monitoring solutions**.

