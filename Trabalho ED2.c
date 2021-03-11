#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<locale.h>
#include<limits.h>

#define n 100000
#define p 100000


typedef struct {// Tipo Item para armazenar as informações do cliente
	int Conta;
	double Saldo;
	char Nome[50];
	long int Cod;
	
}tCliente;


void BubbleSort(tCliente *Client){ // Método de ordenação BubbleSort
	
	tCliente aux;
	long int Topo, Bolha;
	
	for(Topo=1;Topo<n;Topo++){
		for(Bolha=1;Bolha<n;Bolha++){
			if(Client[Bolha].Cod<Client[Bolha-1].Cod){
				aux=Client[Bolha];
				Client[Bolha]=Client[Bolha-1];
				Client[Bolha-1]=aux;
			}
		}
	}
}

void InsertionSort(tCliente *Client){ // Método de ordenação Insertion
	
	long int Chave, i;
	tCliente ChaveAtual; 
	
	for(Chave=0; Chave<n; Chave++){
		ChaveAtual=Client[Chave];
		i=Chave-1;
		while((i>=0)&&(Client[i].Cod>ChaveAtual.Cod)){
			Client[i+1]=Client[i];
			i--; 
		}
		Client[i+1]=ChaveAtual;
	}
}

void SelectionSort(tCliente *Client){ // Método de ordenação Selection
	
	long int Chave, j, MenorChave, Indice;
	tCliente aux;
	
	for(Chave=0; Chave<n-1; Chave++){
		MenorChave=Client[Chave].Cod;
		Indice=Chave;
		for(j=Chave+1; j<n; j++){
			if(Client[j].Cod<MenorChave){
				MenorChave=Client[j].Cod;
				Indice=j;
			}
		}
		aux=Client[Chave];
		Client[Chave]=Client[Indice];
		Client[Indice]=aux;
	}	
}

void ShellSort(tCliente *Client){ // Método de ordenação Shell
	
	int k=3, h=1, i, j;
	tCliente aux;
		
	while(h<=n){
		h=k*h+1;
	}
	while(h!=1){
		h=h/k;
		for(i=h; i<n; i++){
			aux=Client[i];
			j=i-h;
			while((j>=0)&&(aux.Cod<Client[j].Cod)){
				Client[j+h]=Client[j];
				j=j-h;
			}
			Client[j+h]=aux;
		}
	}
}

void Merge(tCliente *SubVet, long int esq, long int meio, long int dir){ // Função auxiliar do método de ordenação Merge
	
	long int n1, n2, i, j, k;
	
	n1=meio-esq+1;
	n2=dir-meio;
 
	tCliente *E = (malloc(sizeof(tCliente)*(n1+1))); // Cria um vetor de structs em um espaço de memória
	tCliente *D = (malloc(sizeof(tCliente)*(n2+1))); // Cria um vetor de structs em um espaço de memória
	
   	
	for(i=0;i<n1;i++){
		E[i]=SubVet[esq+i];
	} 
	for(i=0;i<n2;i++){
		D[i]=SubVet[meio+i+1];
	}
	E[n1].Cod=INT_MAX; 
	D[n2].Cod=INT_MAX;
	i=j=0;
	for(k=esq;k<=dir;k++){
		if(E[i].Cod<=D[j].Cod){
			SubVet[k]=E[i];
			i++;
		}else{
			SubVet[k]=D[j];
			j++;
		}
	}
}

void MergeSort(tCliente *Client, long int esq, long int dir){ // Método de ordenação Merge 
	
	long int meio;
	
	if(esq<dir){
		meio=(esq+dir)/2;
		MergeSort(Client, esq, meio);
		MergeSort(Client, meio+1, dir);
		Merge(Client, esq, meio, dir);
	}
}

void CriaHeap(tCliente *Client, long int i, long int f){ // Função que cria uma heap para o HeapSort
	
	long j;
	tCliente aux;
	
	aux=Client[i];
	j=i*2+1;
	while(j<=f){
		if(j<f){
			if(Client[j].Cod<Client[j+1].Cod){
				j++;
			}
		}
		if(aux.Cod<Client[j].Cod){
			Client[i]=Client[j];
			i=j;
			j=i*2+1;
		}else{
			j=f+1;
		}
	}
	Client[i]=aux;
}


void HeapSort(tCliente *Client){ // Método de ordenação Heap
	
	long int i;
	tCliente aux;
	
	for(i=(n-1)/2; i>=0; i--){
		CriaHeap(Client, i, n-1);
	}
	for(i=n-1; i>0; i--){
		aux=Client[0];
		Client[0]=Client[i];
		Client[i]=aux;
		CriaHeap(Client, 0, i-1);
	}
}

int Particiona(int *Cod, int inicio, int fim){ // Função auxiliar do método de ordenação Quick Sort
	
	int esq, dir, pivo, aux;
	
	esq=inicio;
	dir=fim;
	pivo=Cod[inicio];
	while(esq < dir){
		while(Cod[esq]<=pivo){
			esq++;
		}
		while(Cod[dir]>pivo){
			dir--;
		}
		if(esq<dir){
			aux=Cod[esq];
			Cod[esq]=Cod[dir];
			Cod[dir]=aux;
		}
	}
	Cod[inicio]=Cod[dir];
	Cod[dir]=pivo;
	return dir;
}


void QuickSort(int *Cod, int inicio, int fim){ // Método de ordenação Quick
	
	int pivo=0;
	
	if(fim>inicio){
		pivo=Particiona(Cod, inicio, fim);
		QuickSort(Cod, inicio, pivo-1);
		QuickSort(Cod, pivo+1, fim);
	}
}

void BuscaSequencial(tCliente *Client, long int *Chave){ // Função que executa uma busca sequencial
	
	int i=0, encontrado=0, chave, j;
	
	
	while((i<n) &&(encontrado!=1)){
		for(j=0;j<p;j++){
			if (Client[i].Cod==chave){
				encontrado=1;
				break;
			} 
		}
		i++;
	}
}

void BuscaBinaria(tCliente *Client, long int *Chave){
	
	long int dir=n-1, esq=0, meio, encontrado=0, i=0; // Função que executa uma busca binária
	
	while((esq<=dir)&&(encontrado!=1)){
		meio=(esq+dir)/2;
		if(Client[meio].Cod==Chave[i]){
			encontrado=1;
		}else if(Chave[i]<Client[meio].Cod){
			dir=meio-1;
		}else{
			esq=meio+1;
		}
		i++;
		if(i==p-1){
			break;
		}
	}
}

void GerarCodigo(long int *Cod){ // Função que gera os códigos
	
	long int i, j;
	
	for(i=0; i<=n; i++){	
		Cod[i]=((1+(rand()*rand()%1000000))); // Gera um código aleatório entre 1 e 1000000
		for(j=0;j<i; j++){ 
			if(Cod[i]==Cod[j]){ // Compara se existe um código igual, caso exista gera um outro número aleatório até que seja um inexistente no vetor
				Cod[i]=((1+(rand()*rand())%1000000));
				j=-1;
			}
		}
	}
}

void GerarNome(char Nome[]){ // Função que gera os nomes 
	
	long int i;
	long int *aux=(long int*)(malloc(sizeof(long int)*n*50));
	char alfabeto[]={'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'}; // Cada posição de mémória existe uma letra específica 
	
	for(i=0; i<n*7; i++){	
		aux[i]=rand()%25; //Gera um número aleatório
		Nome[i]=alfabeto[aux[i]];
	}
}

void GerarConta(int *Conta){ // Função que gera a conta aleatoriamente

	long int i;
	
	for(i=0; i<n; i++){	
		Conta[i]=rand()%32766+1; //Gera um número aleatório
	}
}

void GerarSaldo(double *Saldo){ // Função que gera o saldo aleatoriamente
	
	long int i;
	
	for(i=0; i<n; i++){	
		Saldo[i]=rand()%999999+1; //Gera um número aleatório
	}
}

int CriaArquivo(){ // Função para a criação do arquivo 
	
	FILE *Entrada; // Cria um ponteiro que aponta a localização do arquivo
	
	long int aux=1, i, aux2;
	
	if((Entrada=fopen("entrada.dat", "w"))==NULL){ // Verifica se o arquivo foi aberto com sucesso, se existir, sobrescreve o arquivo já existente, caso não exista cria um novo
		printf("Erro ao abrir o arquivo entrada");
		return 0;
	}
	
	long int *Cod = (long int*)(malloc(sizeof(long int)*n)); // Aloca um espaço de memória para os códigos
	char *Nome = (char*)(malloc(sizeof(char)*n*10)); // Aloca um espaço de memória para os nomes
	double *Saldo = (double*)(malloc(sizeof(double)*n)); // Aloca um espaço de memória para os saldos
	int *Conta = (int*)(malloc(sizeof(int)*n)); // Aloca um espaço de memória para os saldos
	
	GerarCodigo(Cod);
	GerarNome(Nome);
	GerarConta(Conta);
	GerarSaldo(Saldo);
	
	for(i=0;i<n;i++){
		aux2=i;
		fprintf(Entrada, "%ld ", Cod[i]); // Escreve no arquivo
		for(i=aux;i<=n*7;i++){
			fprintf(Entrada, "%c", Nome[i-1]); 
			if((i%7)==0){ // verifica se o nome já contém 7 caracteres, caso aja, sai do laço de repetição 
				break;
			}	
		}	
		aux=i+1;
		i=aux2;
		fprintf(Entrada, " %d %.2lf\n", Conta[i], Saldo[i]);
	}
}

int AbrirArquivo(tCliente *Client){ // Função que abre o arquivo 
	
	FILE *Abrir; // Cria um ponteiro que aponta a localização do arquivo
	
	long int i=0;
	
	if((Abrir=fopen("entrada.dat", "r"))==NULL){ // Verifica se o arquivo foi aberto com sucesso, somente para leitura
		printf("Erro ao abrir o arquivo entrada");
		return 0;
	} 
	
	while(!feof(Abrir)){ // Executa enquanto não chegar ao fim do arquivo
		fscanf(Abrir, "%ld %s %d %lf", &Client[i].Cod, &Client[i].Nome, &Client[i].Conta, &Client[i].Saldo); // Lê os dados do arquivos e os armazena 
		i++;
	}
	
	fclose(Abrir); // Comando que fecha o arquivo
}

int SaidaArquivo(double tempoGasto1, double tempoGasto2, double tempoGasto3, double tempoGasto4, double tempoGasto5, double tempoGasto6, double tempoGasto7){
	
	long int l=p;
	FILE *Saida;
	
	if((Saida=fopen("saida.txt", "w"))==NULL){
		printf("Erro ao abrir o arquivo saida");
		return 0;
	}
	
	//if(tempoGasto1>tempoGasto2){
		fprintf(Saida, "-Analise: Busca Sequencial x Busca Binaria + Bubble Sort: \n");
		fprintf(Saida, "Quantidade de chaves buscadas: %ld\n", l);
		fprintf(Saida, "Tempo (s) Busca Sequencial: %.3lf\n", tempoGasto1);
		fprintf(Saida, "Tempo (s) Busca Binaria: %.3lf\n\n", tempoGasto2);
//	}
	
	//if(tempoGasto1>tempoGasto3){
		fprintf(Saida, "-Analise: Busca Sequencial x Busca Binaria + Insertion Sort: \n");
		fprintf(Saida, "Quantidade de chaves buscadas: %ld\n", l);
		fprintf(Saida, "Tempo (s) Busca Sequencial: %.3lf\n", tempoGasto1);
		fprintf(Saida, "Tempo (s) Busca Binaria: %.3lf\n\n", tempoGasto3);
	//}
	
	//if(tempoGasto1>tempoGasto4){
		fprintf(Saida, "-Analise: Busca Sequencial x Busca Binaria + Selection Sort: \n");
		fprintf(Saida, "Quantidade de chaves buscadas: %ld\n", l);
		fprintf(Saida, "Tempo (s) Busca Sequencial: %.3lf\n", tempoGasto1);
		fprintf(Saida, "Tempo (s) Busca Binaria: %.3lf\n\n", tempoGasto4);
	//}
	
//	if(tempoGasto1>tempoGasto5){ // 280 chaves
		fprintf(Saida, "-Analise: Busca Sequencial x Busca Binaria + Shell Sort: \n");
		fprintf(Saida, "Quantidade de chaves buscadas: %ld\n", l);
		fprintf(Saida, "Tempo (s) Busca Sequencial: %.3f\n", tempoGasto1);
		fprintf(Saida, "Tempo (s) Busca Binaria: %.3lf\n\n", tempoGasto5);
//	}
	
	//if(tempoGasto1>tempoGasto6){ 550 chaves
		fprintf(Saida, "-Analise: Busca Sequencial x Busca Binaria + Merge Sort: \n");
		fprintf(Saida, "Quantidade de chaves buscadas: %ld\n", l);
		fprintf(Saida, "Tempo (s) Busca Sequencial: %.3lf\n", tempoGasto1);
		fprintf(Saida, "Tempo (s) Busca Binaria: %.3lf\n\n", tempoGasto6);
	//}
	
	//if(tempoGasto1>tempoGasto7){ // 250 chaves
		fprintf(Saida, "-Analise: Busca Sequencial x Busca Binaria + Heap Sort: \n");
		fprintf(Saida, "Quantidade de chaves buscadas: %ld\n", l);
		fprintf(Saida, "Tempo (s) Busca Sequencial: %.3lf\n", tempoGasto1);
		fprintf(Saida, "Tempo (s) Busca Binaria: %.3lf\n\n", tempoGasto7);
	//}
}

void CriaChave(long int *Chave){ // Função para criar chaves aleatórias para busca

	long int i, cont=0;
	
	for(i=0; i<p; i++){	
		Chave[i]=((1+(rand()*rand()%1000000))); // Gera um código aleatório entre 1 e 1000000
	}
}


void MostraVet(tCliente *Client){ // Mostra o vetor ordenado, irei excluir depois
	
	long int i;
	
	for(i=0;i<n;i++){
		printf("%ld %s %d %lf\n", Client[i].Cod, Client[i].Nome, Client[i].Conta, Client[i].Saldo);
	}
}


void OrdenaBin(tCliente *Client, long int *Chave){ // Função que executa e chama todos métodos de ordenação com a busca binária
	
	clock_t tempoInicial, tempoFinal;
	double tempoGasto1, tempoGasto2, tempoGasto3, tempoGasto4, tempoGasto5, tempoGasto6, tempoGasto7;


	printf("Executando...");
	
	
	tempoInicial=clock();
	BuscaSequencial(Client, Chave);
	tempoFinal=clock();
	tempoGasto1 = (tempoFinal-tempoInicial)/(double)(CLOCKS_PER_SEC);

	

	tempoInicial = clock();
	BubbleSort(Client);
	BuscaBinaria(Client, Chave);
	tempoFinal = clock();
	tempoGasto2 = (tempoFinal-tempoInicial)/(double)(CLOCKS_PER_SEC);
	AbrirArquivo(Client);
	

	tempoInicial = clock();
	InsertionSort(Client);
	BuscaBinaria(Client, Chave);
	tempoFinal = clock();
	tempoGasto3 = (tempoFinal-tempoInicial)/(double)(CLOCKS_PER_SEC);
	AbrirArquivo(Client);
	

	tempoInicial = clock();
	SelectionSort(Client);
	BuscaBinaria(Client, Chave);
	tempoFinal = clock();
	tempoGasto4 = (tempoFinal-tempoInicial)/(double)(CLOCKS_PER_SEC);
	AbrirArquivo(Client);
	
	
	tempoInicial=clock();
	ShellSort(Client);
	BuscaBinaria(Client, Chave);
	tempoFinal = clock();
	tempoGasto5 = (tempoFinal-tempoInicial)/(double)(CLOCKS_PER_SEC);
	AbrirArquivo(Client);
	

	tempoInicial = clock();
	MergeSort(Client, 0, n-1); 
	BuscaBinaria(Client, Chave);
	tempoFinal = clock();
	tempoGasto6 = (tempoFinal-tempoInicial)/(double)(CLOCKS_PER_SEC);
	AbrirArquivo(Client);
	

	tempoInicial = clock();
	HeapSort(Client);
	BuscaBinaria(Client, Chave);
	tempoFinal = clock();
	tempoGasto7 = (tempoFinal-tempoInicial)/(double)(CLOCKS_PER_SEC);
	
	SaidaArquivo(tempoGasto1, tempoGasto2, tempoGasto3, tempoGasto4, tempoGasto5, tempoGasto6, tempoGasto7);
}



main(){
	
	srand(time(NULL)); // Utilizada para gerar os números aleatórios 
	 
	clock_t tempoInicial, tempoFinal;
	double tempoGasto;
	
	long int *Chave = (long int *)(malloc(sizeof(long int)*p));  // Cria um ponteiro de tamanho p para Long int
	tCliente *Client = (tCliente *)(malloc(sizeof(tCliente)*n)); // Cria um ponteiro de tamanho n para tCliente
	
	//CriaArquivo(); // Chama a função que cria o arquivo
	
	AbrirArquivo(Client); // Chama a função que abre o arquivo
		
	CriaChave(Chave); // Chama a função que cria a chave
	
	OrdenaBin(Client, Chave); // Chama a função que ordena os codigos e executa busca binária
	
	system("cls");
	printf("Finalizado.");
}
