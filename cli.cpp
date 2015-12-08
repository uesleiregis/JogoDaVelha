//Wilson Felinto Praxedes  Ueslei Regis da Costa Marques  Marcelo de Lima Queiroz
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <time.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include "tictac.h"
#define  PORT "9987"

using namespace std;

int main(int argc, char *argv[])
{
	int sockfd, novosockfd, port_no, n, connectfd, bytes_enviados, bytes_recvd;
	char cbuffer[512], snome[64], cnome[64];
	char *ptr = &cbuffer[0];
	char *ptr_port = (char *)&PORT;
	struct sockaddr_in serv_addr;
	struct hostent *he;

	int count = 0, inp, x, y, ni, inp_true = 0, toss;
	char serv_escolha, cli_escolha, nc;
	char escolha_buffer[2], coordenadas_buffer[2], toss_buffer;

	system("clear");

	if (argc != 2)
	{
		perror("Argumentos incompletos!");
		return 1;
	}
	port_no = atoi(ptr_port);
	he = gethostbyname(argv[1]);
	if (he == NULL)
	{
		perror("analisando contato com o anfitriao!");
		return 1;
	}

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd == -1)
	{
		perror("Desculpa. Socket pode nao ser criado!");
		return 1;
	}

    memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port_no);
	serv_addr.sin_addr = *((struct in_addr *)he->h_addr);

	connectfd = connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
	if (connectfd == -1)
	{
		perror("Desculpa. Pode nao ter conectado ao server.");
		return 1;
	}

	cout<<"Entre com seu nome : ";
	cin>>cnome;
	do
	{
		static int flag = 0;
		bytes_enviados = enviar(sockfd, &cnome, sizeof(cnome), 0);
		if (bytes_enviados == -1 && flag == 0)
		{
			cout<<"Dados do jogador nao enviados!"<<endl<<"Tentando novamente...";
			continue;
		}
		else
		{		cli_escolha = 'X';

			flag = 1;
			memset(&snome, 0, sizeof(snome));
			bytes_recvd = recv(sockfd, &snome, sizeof(snome), 0);
			if (bytes_recvd == -1)
				cout<<"pode nao ter adquirido informacoes do jogador!"<<endl<<"Tentando novamente..."<<endl;
			else
				cout<<"voce tem se juntado "<<snome<<" para o jogo da velha."<<endl;
		}
	}while(bytes_enviados == -1 || bytes_recvd == -1);

	cout<<"Criando jogo. Por favor espere..."<<endl;
	sleep(2);
	cout<<endl<<"Game criado!"<<endl<<endl<<"fazendo um toss...";

	bytes_recvd = recv(sockfd, &toss_buffer, sizeof(toss_buffer), 0);
	if (bytes_recvd == -1)
	{
		perror("TOSS BUFFER nao recebido");
		return 1;
	}

	toss = toss_buffer - '0';
	if (toss == 0)
	{
		cout<<endl<<snome<<" venceu o toss."<<endl;
		cout<<snome<<" esta escolhendo. Por favor espere..."<<endl<<endl;
		memset(&escolha_buffer, 0, sizeof(escolha_buffer));
		bytes_recvd = recv(sockfd, &escolha_buffer, sizeof(escolha_buffer), 0);
		if (bytes_recvd == -1)
		{
			perror("ESCOLHA BUFFER nao recebida!");
			return 1;
		}
		else
		{
			serv_escolha = escolha_buffer[0];
			cli_escolha = escolha_buffer[1];
			cout<<snome<<" tem escolhido "<<serv_escolha<<endl<<endl<<"voce jogara com "<<cli_escolha<<endl;
			cout<<endl<<"vamos jogar!"<<endl<<endl;
		}
	}
	else
	{
		cout<<endl<<"voce venceu o TOSS!"<<endl;
		do
    	{
    		cout<<cnome<<" entre com sua escolha (X ou O): ";
			cin>>cli_escolha;
			if (cli_escolha == 'X' || cli_escolha == 'x')
			{
	    		serv_escolha = 'O';
	    		cli_escolha = 'X';
	    		inp_true = 1;
				cout<<endl<<snome<<" obtenha O."<<endl<<endl<<"vamos jogar!"<<endl<<endl;
			}
			else if (cli_escolha == 'O' || cli_escolha == 'o' || cli_escolha == '0')
			{
			    serv_escolha = 'X';
        		cli_escolha = 'O';
	    		inp_true = 1;
	    		cout<<endl<<snome<<" obtenha X."<<endl<<endl<<"vamos jogar!"<<endl<<endl;
			}
			else
			{
	    		cout<<"\nescolha invalida! por favor escolha novamente..."<<endl;
	    		inp_true == 0;
			}
    	}while(inp_true == 0);

		memset(&escolha_buffer, 0, sizeof(escolha_buffer));
		escolha_buffer[0] = serv_escolha;
		escolha_buffer[1] = cli_escolha;

		bytes_enviados = enviar(sockfd, &escolha_buffer, sizeof(escolha_buffer), 0);
		if (bytes_enviados == -1)
		{
			perror("ESCOLHA buffer não pôde ser enviada!");
			return 1;
		}

	}

	if (serv_escolha == 'X')
	{
		inp = 1;
		cout<<snome<<" jogara primeiro."<<endl<<endl;

	}
	else
	{
		inp = 2;
		cout<<"voce jogara primeiro."<<endl<<endl;
	}


	init();
	cout<<endl<<"iniciando jogo..."<<endl;
	sleep(3);
	display();

	while (count < 9)
	{
		memset(&coordenadas_buffer, 0, sizeof(coordenadas_buffer));

		if (inp % 2 != 0 )
		{
			cout<<endl<<snome<<"'s giro. Por favor espere..."<<endl;
			bytes_recvd = recv(sockfd, &coordenadas_buffer, sizeof(coordenadas_buffer), 0);
			if (bytes_recvd == -1)
			{
				perror("coordenadas BUFFER nao recebidas!");
				return 1;
			}
			x = coordenadas_buffer[0] - '0';
			y = coordenadas_buffer[1] - '0';
			ni = input(serv_escolha, x, y);
			if (ni == 0)
			{
				inp ++;
				cout<<endl<<snome<<" tem jogado. atualizando Matriz..."<<endl;
			}
		}
		else
		{
			cout<<endl<<"Seu giro. entre com coordenadas separadas por um espaco : ";
			cin>>x>>y;
			ni = input(cli_escolha, x, y);
			if (ni == 0)
			{
				inp ++;
				sprintf(&coordenadas_buffer[0], "%d", x);
				sprintf(&coordenadas_buffer[1], "%d", y);
				cout<<endl<<"Atualizando Matriz..."<<endl;

				bytes_enviados = enviar(sockfd, &coordenadas_buffer, sizeof(coordenadas_buffer), 0);
				if (bytes_enviados == -1)
				{
					perror("coordenadas BUFFER nao enviada!");
					return 1;
				}
			}
		}

		count ++;
		sleep(2);
		system("clear");
		display();

		if (count >=5)
		{
			nc = check();
			if (nc == 'f')
				continue;
			else if (serv_escolha == nc)
			{
				cout<<endl<<"voce perdeu."<<endl<<snome<<" tem vencido."<<endl;
				break;
			}
			else if (cli_escolha == nc)
			{
				cout<<endl<<"parabens! voce tem vencido!!!"<<endl<<snome<<" perdeu."<<endl;
				break;
			}
		}

	}

	if (nc == 'f')
		cout<<endl<<"fim do jogo em um empate."<<endl;

	cout<<endl<<"obrigado por ter jogado o jogo da velha"<<endl;
	close(sockfd);
	return 0;
}


