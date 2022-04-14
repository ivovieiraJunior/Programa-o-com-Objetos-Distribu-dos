
#include <string>
#include <stdio.h>
#include <socket.hpp>
#include <windows.h>

using namespace SOCKETS_P;

const std::string arquivo("tinyxml2.h");

int main()
{
    uint32_t size;
    int read;
    char buff[40000];
    FILE* file;
    TCPServer server;
    TCPClient* client;

    file = fopen(arquivo.c_str(), "rb");

    if(!file)
    {
        perror("fopen");
        return 0;
    }

    fseek(file, 0,SEEK_END);
    size = ftell(file);
    rewind(file);

    std::cout<<"Tamanho do arquivo(bytes): "<<size<<std::endl;

    try
    {
        Socket::initWinApiSock();
        server.setMaxConnections(5);
        server.start(5050);

        std::cout<<"Aguardando conexao..."<<std::endl;
        while(!server.canRead())
            Sleep(1000);

        server.acceptConnection();
        client = server.getLastClient();

        std::cout<<"Enviando arquivo..."<<std::endl;

        //envia o tamanho do arquivo
        client->sendMessage(&size, sizeof(uint32_t));

        while(!feof(file))
        {
            read = fread(buff, sizeof(char), 40000, file);
            client->sendMessage(buff, read);
        }
        std::cout<<"Arquivo enviado."<<std::endl;

        //Aguarda fim da conexão pelo cliente.
        client->readMessage(buff, 1);

        Socket::shutDownWinApiSock();
    }
    catch(Exception ex)
    {
        if(ex.getErrorId() == END_CONNECTION)
            std::cout<<"Conexão encerrada."<<std::endl;
        else
            std::cout<<"Error: "<<ex.getErrorCause()<<std::endl;
    }

    fclose(file);

    return 0;
}

 
