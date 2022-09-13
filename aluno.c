#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

/* Registro do aluno composto por: matricula, nome e media
   menu com:
   1) cadastrar aluno
   2) listagem de todos os alunos
   3) Consultar aluno por matrícula
   4) Excluir aluno
   5) Alterar media 
   6) Sair do programa
 */

typedef struct Aluno{
  char nome[100];
  int matricula, media;
}Aluno;

Aluno aluno;

//Protótipo de funções:
void cadastrarAluno();
void listarAlunos();
void consultarPorM();
void excluir();
void excluirAluno();
void alterarMedia();

int matriculaAluno(int matriculaBuscar){

  FILE *arquivoAluno = fopen("./ex.dat", "rb");

  while(fread(&aluno,sizeof(Aluno),1,arquivoAluno)){
    if(matriculaBuscar==aluno.matricula) return 1;
  }
  fclose(arquivoAluno);
  return 0;
}

void cadastrarAluno (){
  Aluno aluno;
  int matricula, test=0;

  do{
    system("cls");
    printf("Matricula do aluno: ");
    scanf("%d",&matricula);
    setbuf(stdin,NULL);
    test = matriculaAluno(matricula);

    if(test==1){
      printf("\n\tMatricula nao disponivel");
      system("pause");
    }
  }while(test==1);
  aluno.matricula=matricula;

  printf("Nome do aluno: ");
  fgets(aluno.nome, sizeof(aluno.nome), stdin);
  setbuf(stdin, NULL);

  printf("Media do aluno: ");
  scanf("%d", &aluno.media);
  setbuf(stdin, NULL);

  FILE *arquivoAluno;

  arquivoAluno = fopen("./ex.dat", "ab");

  if(arquivoAluno==NULL){
    printf("Error\n");
    exit(1);
  }

  fwrite(&aluno, sizeof(aluno), 1, arquivoAluno);

  fclose(arquivoAluno);
  printf("Pressione enter");
  getchar();
  system("cls");
}

void listarAlunos(){

  system("cls");

  FILE *arquivoAluno = fopen("./ex.dat", "rb");

  if(arquivoAluno==NULL){
    printf("\nNao ha nenhum aluno matriculado!\n");
  }
  
  while(fread(&aluno,sizeof(Aluno),1,arquivoAluno)){
    printf("\n");
    printf("\nMatricula: %d", aluno.matricula);
    printf("\nNome do aluno: %s", aluno.nome);
    printf("Media do aluno: %d", aluno.media);
    printf("\n");
    printf("\n");
  }
  system("pause");

  fclose(arquivoAluno);
  printf("\n\n\nPressione qualquer tecla para voltar\n");
  getchar();
  system("cls");
}

void consultarPorM(){

  system("cls");

  FILE *arquivoAluno = fopen("./ex.dat", "rb");
  int encontrou = FALSE;
  int matriculaBuscar;

  printf("Matricula do aluno que deseja buscar: \n");
  scanf("%d", &matriculaBuscar);
  setbuf(stdin, NULL);

  while(fread(&aluno,sizeof(Aluno),1,arquivoAluno)){
    if(matriculaBuscar==aluno.matricula){
      encontrou=TRUE;
      printf("\n");
      printf("\nMatricula: %d", aluno.matricula);
      printf("\nNome do aluno: %s", aluno.nome);
      printf("Media do aluno: %d", aluno.media);
      printf("\n");
      printf("\n");

      break;
    }
  }
  setbuf(stdin, NULL);

  if(!encontrou){
    printf("Matricula nao existe");
    getchar();
    system("cls");
    return;
  }

  system("pause");

  fclose(arquivoAluno);
  printf("\n\n\nPressione qualquer tecla para voltar\n");
  getchar();
  system("cls");
}

void excluir(){
  system("cls");

  Aluno dados;

  FILE* arquivoAluno = fopen("./ex.dat", "rb");
  int encontrou = FALSE;
  int matriculaBuscar;

  printf("Matricula do aluno a ser excluido: \n");
  scanf("%d", &matriculaBuscar);
  setbuf(stdin, NULL);

  while(fread(&aluno, sizeof(Aluno), 1, arquivoAluno)){
    if (matriculaBuscar==aluno.matricula){
      fclose(arquivoAluno);
      excluirAluno(dados);
    }
  }

  fclose(arquivoAluno);
  
  printf("Matricula do aluno incorreta!\n");
  system("pause");
  system("cls");
}

void excluirAluno(Aluno antigo) {
  system("cls");

  FILE *arquivoAluno, *aux;
  Aluno passar;

  arquivoAluno = fopen("./ex.dat", "rb");
  aux = fopen("./exAux.dat", "wb");

  while(fread(&passar,sizeof(Aluno),1,arquivoAluno)){
    if(antigo.matricula!=passar.matricula){
      fwrite(&passar,sizeof(Aluno),1,aux);
    }
  }
  fclose(arquivoAluno);
  fclose(aux);

  arquivoAluno = fopen("./ex.dat", "wb");
  aux = fopen("./exAux.dat", "rb");
  while(fread(&passar,sizeof(Aluno),1,arquivoAluno)){
    fwrite(&passar,sizeof(Aluno),1,arquivoAluno);
  }

  fclose(arquivoAluno);
  fclose(aux);

  printf("Dados apagados com sucesso!");
  getch();
  system("cls");
  main();
}

void alterarMedia() {

  FILE *arquivoAluno = fopen("./ex.dat", "rb");
  int encontrou = FALSE;
  int matriculaBuscar;

  printf("Matricula do aluno: \n");
  scanf("%d", &matriculaBuscar);
  setbuf(stdin, NULL);

  while(fread(&aluno, sizeof(Aluno), 1, arquivoAluno)){
    if(matriculaBuscar==aluno.matricula){
      encontrou = TRUE;
      break;
    }
  }

  setbuf(stdin, NULL);

  //NAO ENCONTROU

  if(!encontrou){
    printf("nao encontrou");
    getchar();
    system("cls");
    return;
  }

  printf("Novos dados\n");

  printf("INFORME A NOVA MEDIA: ");
  scanf("%d", &aluno.media);
	setbuf(stdin, NULL);

  FILE *arqAux = fopen("./exAux.dat", "ab");
  rewind(arquivoAluno);

  if(arquivoAluno == NULL || arqAux == NULL){
    printf("Error\n");
  }else {
    fwrite(&aluno,sizeof(Aluno),1,arqAux);
    while(fread(&aluno,sizeof(Aluno),1,arquivoAluno)){
      if(matriculaBuscar!=aluno.matricula){ // <<<<<<<
        fwrite(&aluno,sizeof(Aluno),1,arqAux);
      }
    }
  }

  fclose(arquivoAluno);
  fclose(arqAux);

  remove("./ex.dat");
  rename("./exAux.dat", "./ex.dat");

  printf("Pressione enter");
  getchar();
  system("cls");
}

int main() {

system("cls");
  SetConsoleTitle("Cadastro de Alunos");

  int opcao;

  do{
    // menu
    printf("\t\t\t\t\t\t CADASTRO DE ALUNOS \t\t\n");
    printf("\n(1) - Cadastrar Aluno\n");
    printf("\n(2) - Listar todos os alunos\n");
    printf("\n(3) - Consultar aluno por matricula\n");
    printf("\n(4) - Excluir aluno\n");
    printf("\n(5) - Alterar media do aluno\n");
    printf("\n(6) - SAIR: \n");
    scanf("%d", &opcao);
    setbuf(stdin, NULL);

    system("cls");

    switch(opcao)
    {
      case 1:
        system("cls");
        cadastrarAluno();
        break;
      case 2:
        system("cls");
        listarAlunos();
        break;
      case 3:
        system("cls");
        consultarPorM();
        break;
      case 4:
        system("cls");
        excluir();
        break;
      case 5:
        system("cls");
        alterarMedia();
        break;
      case 6:
        system("cls");
        return 0;
        
    }
  }while (opcao != 0);

}