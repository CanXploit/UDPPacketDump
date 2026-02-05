
---
# UDPPacketDump

**UDPPacketDump** is a simple C program that captures **UDP packets** from a network interface and prints their source and destination IP addresses and ports in real time. It uses the **libpcap** library for packet capturing and is intended to run on Linux systems.

## Features

* Captures **UDP traffic only**.
* Displays source IP, source port, destination IP, and destination port for each packet.
* Allows users to select the network interface from the command line.
* Lightweight and easy to use for monitoring and analyzing UDP traffic.

## Requirements

* Linux system (Ubuntu or similar).
* `libpcap-dev` library installed.
* Root privileges to access network interfaces.

## Installation

1. Install the required library:

```bash
sudo apt update
sudo apt install libpcap-dev build-essential
```

2. Clone or copy the code into a file called `udpdump.c`.

3. Compile the program:

```bash
gcc udpdump.c -lpcap -o udpdump
```

## Usage

Run the program with root privileges and specify the network interface to monitor:

```bash
sudo ./udpdump <interface>
```

Example:

```bash
sudo ./udpdump eth0
```

This will start capturing UDP packets on the `eth0` interface and print each packet’s source and destination information.

## Example Output

```
192.168.1.10:12345 -> 192.168.1.20:80
10.0.0.5:5678 -> 10.0.0.8:53
```

## Notes

* Make sure to run the program with `sudo` to allow access to network interfaces.
* The program captures only **IPv4 UDP packets**.
* For systems with multiple network interfaces, specify the correct interface to capture the desired traffic.

## License

This project is free to use for learning and educational purposes.

---
