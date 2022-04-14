#include <string>
#include <stdio.h>
#include <socket.hpp>
#include <windows.h>

using namespace SOCKETS_P;

const std::string arquivo("tinyxml2.h");

int main(int argc, char* argv[])
{
    InternetAddress addr(AF_INET, "127.0.0.1", 5050);
    uint32_t downloaded = 0, size = 0;
    std::string read;
    FILE* file;
    TCPClient client;

    if(argc > 1)
        addr.setHost(argv[1]);

    file = fopen(arquivo.c_str(), "wb");

    if(!file)
    {
        perror("fopen");
        return 0;
    }

    try
    {
        Socket::initWinApiSock();

        client.connectTo(addr);

        std::cout<<"Conectado ao servidor("<<addr.getIp()<<")."<<std::endl;
        std::cout<<"Aguardando arquivo!"<<std::endl;

        //O loop fica disposto desta maneira para caso o servidor falhe e atrase no envio de mensagens, o cliente continue esperando pelos dados
        //!obs: usar contador para time_out.
        while(!client.canRead())
        {
            Sleep(1000);

            while(client.canRead())
            {
                if(!size)
                {
                    client.readMessage(&size, sizeof(uint32_t));
                    std::cout<<"Tamanho do arquivo(bytes): "<<size<<std::endl;
                }
                else
                {
                    downloaded += client.readMessage(read, 40000);
                    fwrite(read.c_str(), read.size()*sizeof(char), 1, file);
                }
            }

            if(downloaded == size)
                break;
        }
        std::cout<<"Arquivo baixado!"<<std::endl;

        Socket::shutDownWinApiSock();
    }
    catch(Exception ex)
    {
        std::cout<<"Error: "<<strerror(ex.getErrorId())<<std::endl;
    }

    fclose(file);

    return 0;
}
