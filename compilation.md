# Packet Sniffer Module - Compilation & Usage Guide

## 📌 Introduction
This guide explains how to compile, install, and use a custom **packet sniffer** kernel module on a Linux system.

---

## 🛠 Prerequisites
Ensure you have the following installed on your system:

- **Linux Kernel Headers** (Matching your kernel version)
- **GCC Compiler**
- **Make Utility**

### Install Required Dependencies
```bash
sudo apt update && sudo apt install build-essential linux-headers-$(uname -r)
```

---

## 🚀 Compilation Steps

### 1️⃣ **Write the Kernel Module (packet_sniffer.c)**
Ensure your `packet_sniffer.c` file contains the correct logic to sniff packets.

### 2️⃣ **Create a Makefile**
Create a `Makefile` in the same directory as `packet_sniffer.c` with the following content:
```makefile
obj-m += packet_sniffer.o

all:
  make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
  make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
```

### 3️⃣ **Compile the Module**
Run the following command to compile the module:
```bash
make
```
If compilation is successful, you will see a file named **packet_sniffer.ko** in the directory.

---

## 📥 Loading & Using the Module

### 4️⃣ **Insert the Kernel Module**
```bash
sudo insmod packet_sniffer.ko
```
Verify it is loaded:
```bash
lsmod | grep packet_sniffer
```

### 5️⃣ **Check Kernel Logs for Packet Capture**
```bash
sudo dmesg | tail -20
```

---

## 🔍 Testing the Packet Sniffer
Open a **second terminal** and run these commands to generate network traffic:

- **Ping Test (ICMP Traffic)**
  ```bash
  ping -c 5 google.com
  ```
  Expected Output in `dmesg`:
  ```
  [ICMP] Src: <Your IP> -> Dest: 8.8.8.8
  ```

- **HTTP Request (TCP Traffic)**
  ```bash
  curl http://example.com
  ```
  Expected Output in `dmesg`:
  ```
  [TCP] Src: <Your IP>:<port> -> Dest: 93.184.216.34:80
  ```

- **DNS Query (UDP Traffic)**
  ```bash
  dig google.com
  ```
  Expected Output in `dmesg`:
  ```
  [UDP] Src: <Your IP>:<port> -> Dest: 8.8.8.8:53
  ```

---

## 📤 Unloading the Module
If you want to remove the module:
```bash
sudo rmmod packet_sniffer
```
Check logs to confirm removal:
```bash
dmesg | tail -10
```

---
