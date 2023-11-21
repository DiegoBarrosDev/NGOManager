#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//  TELA INICIAL
void menuInicial(){
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
        } */else if(opcao == 3){
            ativo = menuDoadores();
        } /*else if(opcao == 1){
            ativo = menuFuncionarios();
        } else if(opcao == 1){
            ativo = menuBeneficiarios();
        }*/ else if(opcao == 6){
            ativo = 0;
        }        
    }

}

// FUNCOES UTEIS

int contarLinhas(FILE * arquivo) {
    
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return -1; // Retorna -1 em caso de erro
    }

    int linhas = 0;
    char caractere;
    while ((caractere = fgetc(arquivo)) != EOF) {
        if (caractere == '\n') {
            linhas++;
        }
    }

    return linhas;
}

int removeLinha(char * nomeArquivo, int numLinha){
    
    FILE * arquivoTemporario;
    arquivoTemporario = fopen("temp.txt", "w+");
    FILE * arquivo;
    arquivo = fopen(nomeArquivo, "r+");

    if(arquivoTemporario == NULL || arquivo == NULL){
        printf("Erro ao tentar abrir o arquivo");
        return menuProjetos();
    }

    int linhas = contarLinhas(arquivo);
    rewind(arquivo);
    for(int i = 1; i<= linhas; i++){
        char linha[500];
        if (i != numLinha) {
            fscanf(arquivo, " %[^\n]\n", linha);
            fprintf(arquivoTemporario, "%s\n", linha);
        } else {
            fscanf(arquivo, "%*[^\n]"); // Consome a linha a ser excluída
            fscanf(arquivo, "\n"); // Consome a quebra de linha
        }
    }
   
    fclose(arquivo);
    fclose(arquivoTemporario);
    
    remove(nomeArquivo);

    rename("temp.txt", nomeArquivo);
}


// PROJETOS

typedef struct Proj{
    //int cod;
    char nome[20];
    char descricao[50];
    char dataInicial[11];
    float valorEstimado;
    char situacao[20];
}Projeto;

int criaLinhaProjetos(Projeto projeto){
    FILE *arquivo;
    
    arquivo = fopen("projetos.txt", "a+");
    if(arquivo == NULL){
        printf("Erro ao abrir o arquivo projetos.txt\n");
        return menuProjetos();
    }

    fprintf(arquivo, "%s|%s|%s|%f|%s\n", projeto.nome, projeto.descricao, projeto.dataInicial, projeto.valorEstimado, projeto.situacao);

    fclose(arquivo);
}

int exibirProjetos(){
    
    FILE * arquivo;
    arquivo = fopen("projetos.txt", "r+");
    if(arquivo == NULL){
        printf("Erro ao abrir o arquivo projetos.txt\n");
        return 1;
    }
    int linhas = contarLinhas(arquivo);
    rewind(arquivo);
    
    
    for(int i = 1; i <= linhas; i++){
        Projeto projeto;

        fscanf(arquivo, "%[^|]|%[^|]|%[^|]|%f|%[^\n]\n", projeto.nome, projeto.descricao, projeto.dataInicial, &projeto.valorEstimado, projeto.situacao);
        printf("%-2d%-20s%-50s%-20s%-20.2f%-12s\n", i, projeto.nome, projeto.descricao, projeto.dataInicial, projeto.valorEstimado, projeto.situacao);       
    
    }   
    fclose(arquivo);
}

int consultarProjetos(){
    printf("\nLista de Projetos:\n\n");
    printf("  %-20s%-50s%-20s%-20s%-12s\n", "Nome", "Descricao", "Data  de inicio", "Valor do Projeto", "Situacao");
    exibirProjetos();
    printf("\n");
    return menuProjetos();
}

int cadastrarProjeto(){
    
    Projeto * novo = malloc(sizeof(Projeto));
    int status;

    printf("Qual o nome do seu novo projeto?\n");
    scanf(" %[^\n]", novo->nome);

    printf("Descreva o seu projeto?\n");
    scanf(" %[^\n]", novo->descricao);
    
    printf("Qual a data de inicio do seu projeto? (dd/mm/aa)\n");
    scanf(" %s", novo->dataInicial);

    printf("Qual a valor do seu projeto?\n");
    scanf(" %f", &novo->valorEstimado);

    printf("Qual a atual situacao do seu projeto?\n1 - A iniciar\n2 - Em andamento\n3 - Finalizado\n");
    scanf(" %d", &status);
    if (status == 1) {
        strcpy(novo->situacao, "A iniciar");
    } else if (status == 2) {
        strcpy(novo->situacao, "Em andamento");
    } else if (status == 3) {
        strcpy(novo->situacao, "Finalizado");
    }

    
    FILE *arquivo;
    
    arquivo = fopen("projetos.txt", "a+");
    if(arquivo == NULL){
        printf("Erro ao abrir o arquivo projetos.txt\n");
        return menuProjetos();
    }

    fprintf(arquivo, "%s|%s|%s|%f|%s\n", novo->nome, novo->descricao, novo->dataInicial, novo->valorEstimado, novo->situacao);

    fclose(arquivo);
    free(novo);
    printf("Projeto cadastrado com sucesso!\n");
    return menuProjetos();
}

int alterarProjeto(){
    int opcao, cod;
    exibirProjetos();
    printf("\nQual o codigo do projeto que voce deseja alterar?\n");
    scanf(" %d", &cod);
    FILE * arquivo = fopen("projetos.txt", "r+");
    
    Projeto projeto;
    int linhas = contarLinhas(arquivo);
    rewind(arquivo);
    for(int i = 1; i <= linhas; i++){
        if (i != cod){
            continue;
        }else{
            fscanf(arquivo, "%[^|]|%[^|]|%[^|]|%f|%[^\n]\n", projeto.nome, projeto.descricao, projeto.dataInicial, &projeto.valorEstimado, projeto.situacao);
            break;
        }
    }
    
    printf("1 - Alterar nome\n");
    printf("2 - Alterar descricao\n");
    printf("3 - Alterar data de inicio\n");
    printf("4 - Alterar valor do projeto\n");
    printf("5 - Alterar o status do projeto\n");
    printf("6 - Voltar\n");
    scanf(" %d",  &opcao);

    if(opcao == 1){
        printf("Digite o novo nome: \n");
        scanf(" %[^\n]", projeto.nome);
    }else if (opcao == 2){
        printf("Digite a nova descricao: \n");
        scanf(" %[^\n]", projeto.descricao);
    }else if (opcao == 3){
        printf("Digite a nova data inicial: \n");
        scanf(" %[^\n]", projeto.dataInicial);
    }else if (opcao == 4){
        printf("Digite o novo valor: \n");
        scanf(" %[^\n]", &projeto.valorEstimado);
    }else if (opcao == 5){
        printf("Digite a nova situacao do projeto: \n");
        scanf(" %[^\n]", projeto.situacao);
    }else if (opcao == 6){
        return menuProjetos();
    }
    criaLinhaProjetos(projeto);
    removeLinha("projetos.txt", cod);
    fclose(arquivo);
    return 1;
}

int excluirProjeto(){
    int opcao;
    exibirProjetos();
    printf("\nQual o codigo do projeto que voce deseja excluir?\n");
    scanf(" %d", &opcao);
    removeLinha("projetos.txt", opcao);

    printf("Projeto excluido com sucesso");
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
    } else if (opcao == 4){
        return excluirProjeto();
    } else if (opcao == 5){
        return 1;
    } else if (opcao == 6){
        return 0;
    } 
}

// FINANCEIRO
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

// DOADORES

struct Doador {
    char nome[50];
    int doacao;
    char data[11];
    int cpf;
};

int menuDoadores() {
    int opcao = 0;
    FILE *arquivo;
    
    printf("\nNGO Manager\n\n");
    printf("Doadores\n\n");
    printf("1 - Consultar doadores\n");
    printf("2 - Cadastrar doador\n");
    printf("3 - Excluir doador\n");
    printf("4 - Voltar ao menu inicial\n");
    printf("5 - Sair\n");

    scanf("%d", &opcao);
    if (opcao == 1) {
        arquivo = fopen("doadores.txt", "r");
        if (arquivo == NULL) {
            printf("Erro ao abrir o arquivo.\n");
            int voltar = 0;
            printf("\nVoltar?\n1: Sim\n2: Não\n");
            scanf("%d", &voltar);
            if (voltar == 1){
                return menuDoadores();
            }else{
                return 0;
            }
        }
        consultarDoador(arquivo);
        fclose(arquivo);
        int voltar = 0;
        printf("\nVoltar?\n1: Sim\n2: Não\n");
        scanf("%d", &voltar);
        if (voltar == 1){
            return menuDoadores();
        }else{
            return 0;
        }
    } else if (opcao == 2) {
        struct Doador doador;
        printf("Nome: \n");
        scanf(" %[^\n]", doador.nome);
        printf("Doacao: ");
        scanf("%d", &doador.doacao);
        printf("Data: ");
        scanf("%s", doador.data);
        printf("CPF do doador: ");
        scanf("%d", &doador.cpf);
        cadastrarDoador(doador);
        return menuDoadores();
    } else if (opcao == 3) {
        int cpf_excluir;
        printf("Digite o CPF do doador a ser excluído: ");
        scanf("%d", &cpf_excluir);
        arquivo = fopen("doadores.txt", "r+");
        if (arquivo == NULL) {
            printf("Erro ao abrir o arquivo.\n");
            excluirDoador(arquivo, cpf_excluir);
            fclose(arquivo);
            int voltar = 0;
            printf("\nVoltar?\n1: Sim\n2: Não");
            scanf("%d", &voltar);
            if (voltar = 1){
                return menuDoadores();
            }else{
                return 0;
            }
        }
        excluirDoador(arquivo, cpf_excluir);
        fclose(arquivo);
        int voltar = 0;
        printf("\nVoltar?\n1: Sim\n2: Não");
        scanf("%d", &voltar);
        if (voltar = 1){
            return menuDoadores();
        }else{
            return 0;
        }
        return menuDoadores();
    } else if (opcao == 4) {
        return 1;
    } else if (opcao == 5) {
        return 0;
    } else {
        printf("Opção inválida.\n");
    }

    return 0;
}

void cadastrarDoador(struct Doador doador) {
    FILE *arquivo;
    arquivo = fopen("doadores.txt", "a+");
    
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    fprintf(arquivo, "%s %d %s %d\n", doador.nome, doador.doacao, doador.data, doador.cpf);

    fclose(arquivo);

    printf("Doador cadastrado.\n");
}

void excluirDoador(FILE *arquivo, int cpf_excluir) {
    FILE *tempFile;
    tempFile = fopen("temp.txt", "w");

    if (tempFile == NULL) {
        printf("Erro ao abrir o arquivo temporário.\n");
        return;
    }

    struct Doador doador;

    while (fscanf(arquivo, "%s %d %s %d", doador.nome, &doador.doacao, doador.data, &doador.cpf) == 4) {
        if (doador.cpf != cpf_excluir) {
            fprintf(tempFile, "%s %d %s %d\n", doador.nome, doador.doacao, doador.data, doador.cpf);
        }
    }

    fclose(arquivo);
    fclose(tempFile);

    remove("doadores.txt");

    rename("temp.txt", "doadores.txt");

    arquivo = fopen("doadores.txt", "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
    }
}

void consultarDoador(FILE *arquivo) {
    struct Doador doador;

    printf("\nLista de Doadores:\n");
    printf("%-20s%-10s%-12s%-11s\n", "Nome", "Doacao", "Data", "CPF");

    while (fscanf(arquivo, "%s %d %s %d", doador.nome, &doador.doacao, doador.data, &doador.cpf) == 4) {
        printf("%-20s%-10d%-12s%-11d\n", doador.nome, doador.doacao, doador.data, doador.cpf);
    }

    fclose(arquivo);
    arquivo = fopen("doadores.txt", "r");

    if (arquivo == NULL) {
        printf("Erro ao reabrir o arquivo.\n");
    }
    
}

/*

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

    menuInicial();
    return 0;
}