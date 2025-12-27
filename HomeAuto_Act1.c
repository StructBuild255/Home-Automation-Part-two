//========================================================================================
//INCLUDES
//========================================================================================

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <arpa/inet.h>
#include <sys/socket.h>

//========================================================================================
//DEFINES
//========================================================================================
#define TARGET_IP "Sonof IP ADDR"
#define TARGET_PORT "your port"
#define ON_HOUR 8      // 7:00 AM
#define ON_MINUTE 0
#define OFF_HOUR 9     // 8:00 AM
#define OFF_MINUTE 0


//========================================================================================
//GLOBALS
//========================================================================================





//========================================================================================
//FUNCTIONS
//========================================================================================

void send_sonoff_command(const char* command) {
    int sock;
    struct sockaddr_in server_addr;
    char buffer[1024] = {0};

    // 1. Create Socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation error");
        return;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(TARGET_PORT);

    // Convert IPv4 and Connect
    if (inet_pton(AF_INET, TARGET_IP, &server_addr.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        return;
    }

    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection Failed");
        return;
    }

    // 2. Send Command (Must send \n because Arduino uses readStringUntil('\n'))
    char payload[50];
    sprintf(payload, "%s\n", command);
    send(sock, payload, strlen(payload), 0);
    printf("[Falco] Sent: %s", payload);

    // 3. Optional: Read Response (The Arduino replies with ON/OFF)
    int valread = read(sock, buffer, 1024);
    if(valread > 0) {
        printf("[Falco] Sonoff Replied: %s\n", buffer);
    }

    // 4. Close
    close(sock);
}




//========================================================================================
//MAIN FUNCTION
//========================================================================================

int main() {
    printf("Falco Backend V1 - Test Mode Started on Debian.\n");
    printf("Targeting Sonoff at %s:%d\n", TARGET_IP, TARGET_PORT);
    
    // 0 = OFF, 1 = ON
    int current_state = 0; 

    while(1) {
        if (current_state == 0) {
            printf("[Falco] Cycle: Turning ON\n");
            send_sonoff_command("ON");
            current_state = 1;
        } 
        else {
            printf("[Falco] Cycle: Turning OFF\n");
            send_sonoff_command("OFF");
            current_state = 0;
        }

        // Wait 10 seconds before the next toggle
        sleep(10);
    }

    return 0;
}
