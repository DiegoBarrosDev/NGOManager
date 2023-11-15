#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void exibirProjetos(){
    FILE * file;
    file = fopen("projetos.txt", "r");
    if(file == NULL){
        printf("Erro ao abrir o arquivo projetos.txt\n");
        return menuProjetos();
    }
    char caractere;
    while((caractere = fgetc(file)) != EOF){
        printf("%c", caractere);
    }
    printf("\n");
    getchar();
}

int consultarProjetos(){
    exibirProjetos();
    return menuProjetos();
}

int cadastrarProjeto(){
    char nomeProjeto[100], descricao[500], dataInicio[11], status_string[20];
    int status;
    float gastoEstimado;

    printf("Qual o nome do seu novo projeto?\n");
    scanf(" %[^\n]", nomeProjeto);

    printf("Descreva o seu projeto?\n");
    scanf(" %[^\n]", descricao);
    
    printf("Qual a data de inicio do seu projeto? (dd/mm/aa)\n");
    scanf(" %s", dataInicio);

    printf("Qual a estimativa de gastos do seu projeto?\n");
    scanf(" %f", &gastoEstimado);

    printf("Qual a atual situacao do seu projeto?\n1 - A iniciar\n2 - Em andamento\n3 - Finalizado\n");
    scanf(" %d", &status);
   if (status == 1) {
        strcpy(status_string, "A iniciar");
    } else if (status == 2) {
        strcpy(status_string, "Em andamento");
    } else if (status == 3) {
        strcpy(status_string, "Finalizado");
    }

    FILE *file;
    file = fopen("projetos.txt", "r+");
    if(file == NULL){   
        file = fopen("projetos.txt", "a");
        if(file == NULL){
            printf("Erro ao abrir o arquivo projetos.txt\n");
            return menuProjetos();
        }
    }
    int cod = 1;
    char caractere;
    while((caractere = fgetc(file)) != EOF){
        if(caractere == '\n'){
            cod++;
        }
    }
    
    fprintf(file, "%d|%s|%s|%s|%f|%s\n", cod, nomeProjeto, descricao, dataInicio, gastoEstimado, status_string);

    fclose(file);
    printf("Projeto cadastrado com sucesso!\n");
    return menuProjetos();
}

int alterarProjeto(){
    int cod, opcao;
    exibirProjetos();
    printf("Digite o codigo do projeto que voce deseja alterar:");
    scanf(" %d", &cod);
    printf("1 - Alterar nome\n");
    printf("2 - Alterar descricao\n");
    printf("3 - Alterar data de inicio\n");
    printf("4 - Alterar gasto estimado\n");
    printf("5 - Alterar o status do projeto\n");
    printf("6 - Voltar\n");
    scanf(" %d",  &opcao);

    return 1;
}

int menuProjetos(){
    int opcao = 0;
    printf("\nNGO Manager\n\n");
    printf("Meus Projetos\n\n");

    printf("1 - Consultar projetos\n");
    printf("2 - Cadastrar projeto\n");
    printf("3 - Alterar projeto\n");
    printf("4 - Excluir projeto\n");
    printf("5 - Voltar ao menu inicial\n");
    printf("6 - Sair\n");
    
    scanf("%d", &opcao);
    if(opcao == 1){
        return consultarProjetos();
    } else if (opcao == 2){
        return cadastrarProjeto();
    } else if (opcao == 3){
        return alterarProjeto();
//    } else if (opcao == 4){
        //return excluirProjeto();
    } else if (opcao == 5){
        return 1;
    } else if (opcao == 6){
        return 0;
    } 
}

int menuFinanceiro(){
    printf("\nNGO Manager\n\n");
    printf("Financeiro\n\n");
    printf("1 - Consultar saldo\n");
    printf("2 - Cadastrar lancamento\n");
    printf("3 - Alterar lancamento\n");
    printf("4 - Excluir lancamento\n");
    printf("5 - Voltar ao menu inicial\n");
    printf("6 - Sair\n");
    
}
/*
int menuDoadores(){
    int opcao = 0;
    printf("\nNGO Manager\n\n");
    printf("Doadores\n\n");

    printf("1 - Consultar doador\n");
    printf("2 - Cadastrar doador\n");
    printf("3 - Alterar doador\n");
    printf("4 - Excluir doador\n");
    printf("5 - Voltar ao menu inicial\n");
    printf("6 - Sair\n");
    
    scanf("%d", &opcao);
    if(opcao == 1){
        return consultarDoador();
    } else if (opcao == 2){
        return cadastrarDoador();
    } else if (opcao == 3){
        return alterarDoador();
    } else if (opcao == 4){
        return excluirDoador();
    } else if (opcao == 5){
        return 1;
    } else if (opcao == 6){
        return 0;
    }  
}

int menuFuncionarios(){
    int opcao = 0;
    printf("\nNGO Manager\n\n");
    printf("Funcionários\n\n");

    printf("1 - Consultar funcionarios\n");
    printf("2 - Cadastrar funcionarios\n");
    printf("3 - Alterar funcionarios\n");
    printf("4 - Excluir funcionarios\n");
    printf("5 - Voltar ao menu inicial\n");
    printf("6 - Sair\n");
    
    scanf("%d", &opcao);
    if(opcao == 1){
        return consultarFuncionarios();
    } else if (opcao == 2){
        return cadastrarFuncionarios();
    } else if (opcao == 3){
        return alterarFuncionarios();
    } else if (opcao == 4){
        return excluirFuncionarios();
    } else if (opcao == 5){
        return 1;
    } else if (opcao == 6){
        return 0;
    }  
}

int menuBeneficiarios(){
    int opcao = 0;
    printf("\nNGO Manager\n\n");
    printf("Beneficiarios\n\n");

    printf("1 - Consultar beneficiario\n");
    printf("2 - Cadastrar beneficiario\n");
    printf("3 - Alterar beneficiario\n");
    printf("4 - Excluir beneficiario\n");
    printf("5 - Voltar ao menu inicial\n");
    printf("6 - Sair\n");
    
    scanf("%d", &opcao);
    if(opcao == 1){
        return consultarBeneficiario();
    } else if (opcao == 2){
        return cadastrarBeneficiario();
    } else if (opcao == 3){
        return alterarBeneficiario();
    } else if (opcao == 4){
        return excluirBeneficiario();
    } else if (opcao == 5){
        return 1;
    } else if (opcao == 6){
        return 0;
    }  
}
*/


int main(){

    int ativo = 1;

    while(ativo == 1){
        int opcao = 0;
        printf("\nNGO Manager\n\n");
        printf("Menu inicial:\n\n");
        printf("1 - Projetos\n");
        printf("2 - Financeiro\n");
        printf("3 - Doadores\n");
        printf("4 - Funcionarios\n");
        printf("5 - Beneficiarios\n");
        printf("6 - Sair\n");

        scanf("%d", &opcao);
        if(opcao == 1){
            ativo = menuProjetos();
        } /* else if(opcao == 1){
            ativo = menuFinanceiro();
        } else if(opcao == 1){
            ativo = menuDoadores();
        } else if(opcao == 1){
            ativo = menuFuncionarios();
        } else if(opcao == 1){
            ativo = menuBeneficiarios();
        }*/ else if(opcao == 6){
            ativo = 0;
        }        
    }

    return 0;
}