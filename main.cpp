bool CPTUProgramDlg::FindPTU(u_short port, const char * Destaddress){
    {
        //Data to send
        char packet_data[10] = {0x44,0x43,0x55,0x44,0x5f,0x50,0x49,0x4e,0x47,0x00};
        int packet_size=10;

        SOCKET sock;
        struct sockaddr_in addr;

        sock = socket(AF_INET, SOCK_DGRAM, 0);

        // set SO_BROADCAST on a socket to true (1): (so we can transmit to 255 addr)
        //In order to use broadcast the options of socket must change
        char broadcastON = 1;
        setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &broadcastON, sizeof broadcastON);

        if (sock < 0)
            return false;

        addr.sin_family = AF_INET;
        addr.sin_port = htons(port);
        addr.sin_addr.s_addr = inet_addr(Destaddress); // Specify dest IP

        sendto(sock, packet_data, packet_size, 0, (struct sockaddr*)&addr, sizeof(addr));

        if (bind(sock,(struct sockaddr*) &addr,sizeof(addr)) != -1){
            char Buff[512];
            recv(sock,Buff,512,0);
        }

        closesocket(sock);
    }

    return 1;
}