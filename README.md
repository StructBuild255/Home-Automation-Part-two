# Taking Back Control of Home Automation (Part 2)

This repository contains the code for **Part 2** of my home automation series. In this video, we move from the device firmware (Sonoff) to the backend controller. We build a C program for Linux that communicates with our smart devices over a TCP network socket.

## Project Overview

The goal of this specific application (`HomeAuto_Act1`) is to act as a command-line controller. It connects to the WiFi-enabled Sonoff device and sends simple text commands (`ON`, `OFF`, `TOGGLE`) to control the relay.

**Key Features:**
* **Custom TCP Client:** Connects directly to the device IP.
* **Menu Interface:** Simple terminal-based UI for manual control.
* **Dependency:** Built using my custom `easy_socket` library.

## Dependencies

This project relies on the **Easy Socket** library from my shared libraries repository. You must install that library before this code will compile.

1.  **Download the Library:**
    Clone my libraries repo: `StructBuild-Libraries`
2.  **Install Easy Socket:**
    ```bash
    cd StructBuild-Libraries/easy_socket
    make
    sudo make install
    ```

## Configuration

Before running the code, you must point it to your specific Sonoff device.

1.  Open `HomeAuto_Act1.c` in a text editor.
2.  Locate the defines at the top:
    ```c
    #define TARGET_IP "192.168.1.XXX" // <--- Change this to your Sonoff's IP Address
    #define TARGET_PORT 8081          // <--- Ensure this matches the port in your Arduino Sketch
    ```
3.  Save the file.

## Compilation & Usage

A `Makefile` is included to simplify the build process.

### 1. Compile
Run the following command in the terminal:
make
Note: If you get an error about -leasysocket not found, ensure you ran sudo make install in the library step above.

2. Run
Execute the binary:

Bash

./HomeAuto_Act1
3. Controls
Once the program is running, you will see a menu:

1: Turn Relay ON

2: Turn Relay OFF

3: TOGGLE Relay state

4: Check STATUS (If supported by your firmware)

9: EXIT the program

Troubleshooting
Connection Failed:

Check if the Sonoff is powered on and connected to WiFi.

Verify the IP address in HomeAuto_Act1.c is correct.

Ensure the Port (8081) matches what is set in the Sonoff firmware.

Make sure your firewall (UFW) isn't blocking the connection.

Disclaimer: This is educational code for a private home network. Ensure your devices are secured behind a router firewall.
