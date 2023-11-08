#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int menuProjetos(){
    int opcao = 0;
    printf("\nNGO Manager\n\n");
    printf("Meus Projetos\n\n");

    printf("1 - Consultar projeto\n");
    printf("2 - Cadastrar projeto\n");
    printf("3 - Alterar projeto\n");
    printf("4 - Excluir projeto\n");
    printf("5 - Voltar ao menu inicial\n");
    printf("6 - Sair\n");
    
    scanf("%d", &opcao);
    if(opcao == 1){
        return consultarProjeto();
    } else if (opcao == 2){
        return cadastrarProjeto();
    } else if (opcao == 3){
        return alterarProjeto();
    } else if (opcao == 4){
        return excluirProjeto();
    } else if (opcao == 5){
        return 1;
    } else if (opcao == 6){
        return 0;
    } 
}

int menuFinanceiro(){
    printf("\nNGO Manager\n\n");
    printf("Financeiro\n\n");

    
}

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
        } else if(opcao == 1){
            ativo = menuFinanceiro();
        } else if(opcao == 1){
            ativo = menuDoadores();
        } else if(opcao == 1){
            ativo = menuFuncionarios();
        } else if(opcao == 1){
            ativo = menuBeneficiarios();
        } else if(opcao == 6){
            ativo = 0;
        }        
    }

    return 0;
}