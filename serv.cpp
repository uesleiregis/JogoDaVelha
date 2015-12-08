//Wilson Felinto Praxedes  Ueslei Regis da Costa Marques  Marcelo de Lima Queiroz
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <time.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "tictac.h"
#define  PORT "9987";

using namespace std;

int main(int argc, char *argv[])
{
	int sockfd, novosockfd, port_no, bindfd, listenfd, bytes_enviados, bytes_recvd;
	char sbuffer[512], cli_ip[16], snome[64], cnome[64];
	char *ptr_buff, *ptr_port;
	const char *ptr_cli_ip;
	struct sockaddr_in serv_addr, cli_addr;
	socklen_t serv_size, cli_tamanho;

	int inp_true = 0, count = 0, inp, ni, x, y, toss;
	char serv_escolha, cli_escolha, nc;
	char escolha_buffer[2], coordenadas_buffer[2], toss_buffer;

	system("clear");
	ptr_buff = &sbuffer[0];
	ptr_port = (char *)&PORT;

	//criando socket
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1)
	{
		perror("Analisando tamanho do socket!");
		return 1;
	}

	memset(&serv_addr, 0, sizeof(serv_addr));
	port_no = atoi(ptr_port);

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port_no);
	serv_addr.sin_addr.s_addr = INADDR_ANY;

	//ligando socket
	bindfd = bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
	if (bindfd == -1)
	{
		perror("Falha para bind!");
		return 1;
	}

	//ouvindo conexoes de entrada
	cout<<"Entre com seu nome : ";
	cin>>snome;
	cout<<"Servidor criado!"<<endl<<"esperando po um jogador..."<<endl;

	ouvirfd = ouvir(sockfd, 5);
	if (ouvirfd == -1)
	{
		perror("Falha para ouvir!");
		return 1;
	}

	serv_size = sizeof(serv_addr);
	cli_tamanho = sizeof(cli_addr);
	novosockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &cli_tamanho);

	if (novosockfd == -1)
	{
		perror("cliente nao aceitou!");
		return 1;
	}

	ptr_cli_ip = inet_ntop(AF_INET, &cli_addr.sin_addr, cli_ip, cli_tamanho);
	cout<<"servidor recebeu conexao de "<<cli_ip<<endl;

	memset(&cnome, 0, sizeof(cnome));
	do
	{
		static int flag = 0;
		bytes_recvd = recv(novosockfd, &cnome, sizeof(cnome), 0);
		if (bytes_recvd == -1 && flag == 0)
		{
			memset(&cnome, 0, sizeof(cnome));
			cout<<"Não foi possível obter informações do Jogador!"<<endl<<"tentar novamente..."<<endl;
			continue;
		}
		else
		{
			flag = 1;
			bytes_enviados = send(novosockfd, &snome, sizeof(snome), 0);
			if (bytes_enviados == -1)
				cout<<"Não foi possível enviar dados do jogador!"<<"tentar novamente..."<<endl;
			else
				cout<<cnome<<" tem juntado ao jogo."<<endl;
		}
	}while(bytes_recvd == -1 || bytes_enviados == -1);

	cout<<"Criando jogo. Por favor espere!..."<<endl;
	sleep(2);
	cout<<endl<<"Game criado!"<<endl<<endl<<"fazer um lançe...";
	srand(time(NULL));
	toss = rand() % 2;
	sleep(1);
	sprintf(&toss_buffer, "%d", toss);
	bytes_enviados = enviar(novosockfd, &toss_buffer, sizeof(toss_buffer), 0);
	if (bytes_enviados == -1)
	{
		perror("TOSS BUFFER nao enviado!");
		return 1;
	}

	if (toss == 0)
	{
		cout<<endl<<"voce venceu o toss!"<<endl;
		do
    	{
    		cout<<snome<<" Entre com sua escolha (X ou O): ";
			cin>>serv_escolha;
			if (serv_escolha == 'X' || serv_escolha == 'x')
			{
	    		serv_escolha = 'X';
	    		cli_escolha = 'O';
	    		inp_true = 1;
				cout<<endl<<cnome<<" obtenha O."<<endl<<endl<<"vamos jogar!"<<endl<<endl;
			}
			else if (serv_escolha == 'O' || serv_escolha == 'o' || serv_escolha == '0')
			{
			    serv_escolha = 'O';
        		cli_escolha = 'X';
	    		inp_true = 1;
	    		cout<<endl<<cnome<<" obtenha X."<<endl<<endl<<"vamos jogar!"<<endl<<endl;
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

		bytes_enviados = enviar(novosockfd, &escolha_buffer, sizeof(escolha_buffer), 0);
		if (bytes_enviados == -1)
		{
			perror("ESCOLHA buffer não pôde ser enviada!");
			return 1;
		}
	}
	else
	{
		cout<<endl<<cnome<<" venceu o toss."<<endl;
		cout<<cnome<<" esta escolhendo. Por favor espera..."<<endl<<endl;

		memset(&escolha_buffer, 0, sizeof(escolha_buffer));
		bytes_recvd = recv(novosockfd, &escolha_buffer, sizeof(escolha_buffer), 0);
		if (bytes_recvd == -1)
		{
			perror("escolha de BUFFER nao recebida!");
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

	if (serv_escolha == 'X')
	{
		inp = 1;
		cout<<"voce jogara  primeiro."<<endl<<endl;
	}
	else
	{
		inp = 2;
		cout<<cnome<<" jogarah primeiro."<<endl<<endl;
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
			cout<<endl<<"Sua vez. Digite coordenadas separadas por um espaço : ";
			cin>>x>>y;
			ni = input(serv_escolha, x, y);
			if (ni == 0)
			{
				inp ++;
				sprintf(&coordenadas_buffer[0], "%d", x);
				sprintf(&coordenadas_buffer[1], "%d", y);
				cout<<endl<<"atualizando Matriz..."<<endl;

				bytes_enviados = enviar(novosockfd, &coordenadas_buffer, sizeof(coordenadas_buffer), 0);
				if (bytes_enviados == -1)
				{
					perror("coordenadas BUFFER nao enviada!");
					return 1;
				}
			}
		}
		else
		{
			cout<<endl<<cnome<<"'s rodar. Por favor espere..."<<endl;
			bytes_recvd = recv(novosockfd, &coordenadas_buffer, sizeof(coordenadas_buffer), 0 );
			if (bytes_recvd == -1)
			{
				perror("coordenadas BUFFER nao recebidas!");
				return 1;
			}
			x = coordenadas_buffer[0] - '0';
			y = coordenadas_buffer[1] - '0';
			ni = input(cli_escolha, x, y);
			if (ni == 0)
			{
				inp ++;
				cout<<endl<<cnome<<" tem jogado. atualizando Matriz..."<<endl;
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
				cout<<endl<<"parabens! voce venceu!!!"<<endl<<cnome<<" perder."<<endl;
				break;
			}
			else if (cli_escolha == nc)
			{
				cout<<endl<<"voce perdeu."<<endl<<cnome<<" tem vencido."<<endl;
				break;
			}
		}
	}

	if (nc == 'f')
		cout<<endl<<"acabou o jogo ocorreu um empate."<<endl;

	cout<<endl<<"obrigado por jogar o jogo da velha"<<endl;
	close(novosockfd);
	close(sockfd);
	return 0;
}

