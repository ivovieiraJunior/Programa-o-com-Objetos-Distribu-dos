struct sockaddr_in {
	short sin_family;
	u_short sim_port;
	struct in_addr sim_add;
	char sin_zero[8];
};
int WSAStartup(WORD wVersionRequested,LPWSADATA lpWSADATA);
