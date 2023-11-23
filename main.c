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
        } else if(opcao == 4){
            ativo = menuFuncionarios();
        } else if(opcao == 5){
            ativo = menuBeneficiarios();
        } else if(opcao == 6){
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
    
    FILE * arquivo;
    arquivo = fopen("projetos.txt", "r+");
    if(arquivo == NULL){
        printf("Erro ao tentar abrir o arquivo");
        return menuProjetos();
    }

    Projeto projeto;
    int linhas = contarLinhas(arquivo);
    rewind(arquivo);
    
    for(int i = 1; i <= linhas; i++){
       
        if (i == cod){           
            fscanf(arquivo, "%[^|]|%[^|]|%[^|]|%f|%[^\n]\n", projeto.nome, projeto.descricao, projeto.dataInicial, &projeto.valorEstimado, projeto.situacao);        
        } else{
            fscanf(arquivo, "%*[^\n]"); // Consome a linha a ser excluída
            fscanf(arquivo, "\n"); // Consome a quebra de linha
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
    fclose(arquivo);
    removeLinha("projetos.txt", cod);
    criaLinhaProjetos(projeto);

    printf("Projeto alterado com sucesso");
    
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

// FUNCIONARIOS

typedef struct Func{
    //int cod;
    char nome[20];
    char funcao[20];
    char dataAdimissao[11];
    float salario;
    
}Funcionario;

int criaLinhaFuncionarios(Funcionario funcionario){
    FILE *arquivo;
    
    arquivo = fopen("funcionarios.txt", "a+");
    if(arquivo == NULL){
        printf("Erro ao abrir o arquivo funcionarios.txt\n");
        return menuFuncionarios();
    }

    fprintf(arquivo, "%s|%s|%s|%f\n", funcionario.nome, funcionario.funcao, funcionario.dataAdimissao, funcionario.salario);

    fclose(arquivo);
}

int exibirFuncionarios(){
    
    FILE * arquivo;
    arquivo = fopen("funcionarios.txt", "r+");
    if(arquivo == NULL){
        printf("Erro ao abrir o arquivo funcionarios.txt\n");
        return 1;
    }
    int linhas = contarLinhas(arquivo);
    rewind(arquivo);
    
    
    for(int i = 1; i <= linhas; i++){
        Funcionario funcionario;

        fscanf(arquivo, "%[^|]|%[^|]|%[^|]|%f\n", funcionario.nome, funcionario.funcao, funcionario.dataAdimissao, &funcionario.salario);
        printf("%-2d%-20s%-20s%-20s%-20.2f\n", i, funcionario.nome, funcionario.funcao, funcionario.dataAdimissao, funcionario.salario);       
    
    }   
    fclose(arquivo);
}

int consultarFuncionarios(){
    printf("\nLista de Projetos:\n\n");
    printf("  %-20s%-20s%-20s%-20s\n", "Nome", "Funcao", "Data de Admissao", "Salario");
    exibirFuncionarios();
    printf("\n");
    return menuFuncionarios();
}

int cadastrarFuncionario(){
    
    Funcionario * novo = malloc(sizeof(Funcionario));

    printf("Qual o nome do novo funcionario?\n");
    scanf(" %[^\n]", novo->nome);

    printf("Qual a funcao?\n");
    scanf(" %[^\n]", novo->funcao);
    
    printf("Qual a data de admissao? (dd/mm/aa)\n");
    scanf(" %s", novo->dataAdimissao);

    printf("Qual a valor do salario?\n");
    scanf(" %f", &novo->salario);
 
    FILE *arquivo;
    
    arquivo = fopen("funcionarios.txt", "a+");
    if(arquivo == NULL){
        printf("Erro ao abrir o arquivo funcionarios.txt\n");
        return menuFuncionarios();
    }

    fprintf(arquivo, "%s|%s|%s|%f\n", novo->nome, novo->funcao, novo->dataAdimissao, novo->salario);

    fclose(arquivo);
    free(novo);
    printf("Funcionario cadastrado com sucesso!\n");
    return menuFuncionarios();
}

int alterarFuncionario(){
    int opcao, cod;
    exibirFuncionarios();
    printf("\nQual o codigo do funcionario que voce deseja alterar?\n");
    scanf(" %d", &cod);
    
    FILE * arquivo;
    arquivo = fopen("funcionarios.txt", "r+");
    if(arquivo == NULL){
        printf("Erro ao tentar abrir o arquivo");
        return menuFuncionarios();
    }

    Funcionario funcionario;
    int linhas = contarLinhas(arquivo);
    rewind(arquivo);
    
    for(int i = 1; i <= linhas; i++){
       
        if (i == cod){           
            fscanf(arquivo, "%[^|]|%[^|]|%[^|]|%f\n", funcionario.nome, funcionario.funcao, funcionario.dataAdimissao, &funcionario.salario);        
        } else{
            fscanf(arquivo, "%*[^\n]"); // Consome a linha a ser excluída
            fscanf(arquivo, "\n"); // Consome a quebra de linha
        }
    }
    
    printf("1 - Alterar nome\n");
    printf("2 - Alterar funcao\n");
    printf("3 - Alterar data de admissao\n");
    printf("4 - Alterar salario\n");
    printf("5 - Voltar\n");
    scanf(" %d",  &opcao);

    if(opcao == 1){
        printf("Digite o novo nome: \n");
        scanf(" %[^\n]", funcionario.nome);
    }else if (opcao == 2){
        printf("Digite a nova funcao: \n");
        scanf(" %[^\n]", funcionario.funcao);
    }else if (opcao == 3){
        printf("Digite a nova data de admissao: \n");
        scanf(" %[^\n]", funcionario.dataAdimissao);
    }else if (opcao == 4){
        printf("Digite o novo salario: \n");
        scanf(" %[^\n]", &funcionario.salario);
    }else if (opcao == 5){
        return menuFuncionarios();
    }
    fclose(arquivo);
    removeLinha("funcionarios.txt", cod);
    criaLinhaFuncionarios(funcionario);

    printf("Funcionario alterado com sucesso");
    
    return menuFuncionarios();
}

int excluirFuncionario(){
    int opcao;
    exibirFuncionarios();
    printf("\nQual o codigo do funcionario que voce deseja excluir?\n");
    scanf(" %d", &opcao);
    removeLinha("funcionarios.txt", opcao);

    printf("Funcionario excluido com sucesso");
    return menuFuncionarios();

}

int menuFuncionarios(){
    int opcao = 0;
    printf("\nNGO Manager\n\n");
    printf("Funcionarios\n\n");

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
        return cadastrarFuncionario();
    } else if (opcao == 3){
        return alterarFuncionario();
    } else if (opcao == 4){
        return excluirFuncionario();
    } else if (opcao == 5){
        return 1;
    } else if (opcao == 6){
        return 0;
    }  
}

// BENEFICIARIOS

int exibirBeneficiarios(){
    FILE *file;
    file = fopen("beneficiarios.txt", "r");
    if(file == NULL){
        printf("Erro ao abrir o arquivo beneficiarios.txt\n");
        return menuBeneficiarios();
    }
    char caractere;
    while((caractere = fgetc(file)) != EOF){
        printf("%c", caractere);
    }
    printf("\n");
    getchar();
}

int consultarBeneficiarios(){
    exibirBeneficiarios();
    return menuBeneficiarios();
}

int cadastrarBeneficiario(){
    char nomeBeneficiario[100], descricao[500], dataEntradaBeneficiario[11], descricaoBeneficio[500];
    int idade;

    printf("Qual o nome do beneficiario?\n");
    scanf(" %[^\n]", nomeBeneficiario);

    printf("Descreva o beneficiario:\n");
    scanf(" %[^\n]", descricao);

    printf("Qual a idade do beneficiario?\n");
    scanf("%d", &idade);

    printf("Qual a data de entrada do beneficiario? (dd/mm/aa)\n");
    scanf(" %s", dataEntradaBeneficiario);

    printf("Descreva o beneficio do beneficiario:\n");
    scanf(" %[^\n]", descricaoBeneficio);

    FILE *file;
    file = fopen("beneficiarios.txt", "a");
    if(file == NULL){
        printf("Erro ao abrir o arquivo beneficiarios.txt\n");
        return menuBeneficiarios();
    }

    fprintf(file, "%s|%s|%d\n", nomeBeneficiario, descricao, idade);

    fclose(file);
    printf("Beneficiario cadastrado com sucesso!\n");
    return menuBeneficiarios();
}

int menuBeneficiarios(){
    int opcao = 0;
    printf("\nNGO Manager\n\n");
    printf("Beneficiarios\n\n");

    printf("1 - Consultar beneficiarios\n");
    printf("2 - Cadastrar beneficiario\n");
    printf("3 - Alterar beneficiario\n");
    printf("4 - Excluir beneficiario\n");
    printf("5 - Voltar ao menu inicial\n");
    printf("6 - Sair\n");

    scanf("%d", &opcao);
    switch(opcao){
        case 1:
            return consultarBeneficiarios();
        case 2:
            return cadastrarBeneficiario();
        // lembrar de implementar a funcao de exluir e alterar
        case 5:
            return 1; 
        case 6:
            return 0; 
        default:
            printf("Opcao invalida. Tente novamente.\n");
            return menuBeneficiarios();
    }
}

int main(){

    menuInicial();
    return 0;
}