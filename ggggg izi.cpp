// Funções de Operações Bancárias

void aberturaDeConta() {
    char nome[100];
    double saldoInicial;

    printf("=== Abertura de Conta ===\n");
    printf("Digite o nome do cliente: ");
    scanf("%s", nome);

    printf("Digite o saldo inicial: ");
    scanf("%lf", &saldoInicial);

    ContaPoupanca novaConta;
    strcpy(novaConta.dados.nome, nome);
    novaConta.conta.saldo = saldoInicial;

    FILE *arquivo = fopen("contas_poupanca.bin", "ab");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    gravarContaPoupanca(&novaConta, arquivo);
    fclose(arquivo);

    printf("Conta para %s com saldo inicial de %.2lf foi aberta.\n", nome, saldoInicial);
}

void consultarDados() {
    ContaPoupanca conta;
    char nomeParaBuscar[100];
    FILE *arquivo = fopen("contas_poupanca.bin", "rb");
    
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo 'contas_poupanca.bin'");
        return;
    }

    printf("=== Consultar Dados ===\n");
    printf("Digite o nome do cliente: ");
    scanf("%s", nomeParaBuscar);

    int encontrado = 0;
    while (lerContaPoupanca(&conta, arquivo)) {
        if (strcmp(conta.dados.nome, nomeParaBuscar) == 0) {
            printf("Dados da conta:\n");
            printf("Nome: %s\n", conta.dados.nome);
            printf("Agência: %s\n", conta.conta.agencia);
            printf("Número da Conta: %s\n", conta.conta.numero_da_conta);
            printf("Saldo: %.2lf\n", conta.conta.saldo);
            encontrado = 1;
            break;
        }
    }

    fclose(arquivo);

    if (!encontrado) {
        printf("Conta não encontrada.\n");
    }
}

void encerramentoDeConta() {
    printf("=== Encerramento de Conta ===\n");

    if (!validarSenhaAdmin()) {
        printf("Senha incorreta. Retornando ao menu...\n");
        return;
    }

    ContaPoupanca conta;
    FILE *arquivo = fopen("contas_poupanca.bin", "rb");
    FILE *temp = fopen("temp.bin", "wb");
    if (arquivo == NULL || temp == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    char nomeParaEncerrar[100];
    printf("Digite o nome do cliente para encerrar a conta: ");
    scanf("%s", nomeParaEncerrar);

    int encontrado = 0;
    while (lerContaPoupanca(&conta, arquivo)) {
        if (strcmp(conta.dados.nome, nomeParaEncerrar) != 0) {
            gravarContaPoupanca(&conta, temp);
        } else {
            encontrado = 1;
        }
    }

    fclose(arquivo);
    fclose(temp);

    remove("contas_poupanca.bin");
    rename("temp.bin", "contas_poupanca.bin");

    if (encontrado) {
        printf("Conta encerrada com sucesso.\n");
    } else {
        printf("Conta não encontrada. Retornando ao menu...\n");
    }
}

void alterarDados() {
    ContaPoupanca conta;
    FILE *arquivo = fopen("contas_poupanca.bin", "rb+");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    printf("Digite o nome do cliente: ");
    scanf("%s", conta.dados.nome);

    int encontrado = 0;
    while (lerContaPoupanca(&conta, arquivo)) {
        if (strcmp(conta.dados.nome, conta.dados.nome) == 0) {
            printf("Digite o novo saldo: ");
            scanf("%lf", &conta.conta.saldo);

            fseek(arquivo, -sizeof(ContaPoupanca), SEEK_CUR);
            gravarContaPoupanca(&conta, arquivo);
            encontrado = 1;
            break;
        }
    }

    fclose(arquivo);

    if (encontrado) {
        printf("Dados alterados com sucesso.\n");
    } else {
        printf("Conta não encontrada.\n");
    }
}

void cadastroDeFuncionarios() {
    if (!validarSenhaAdmin()) {
        printf("Senha incorreta. Acesso negado.\n");
        return;
    }

    Funcionario novoFuncionario;

    printf("Digite o nome do funcionário: ");
    scanf("%s", novoFuncionario.nome);
    printf("Digite o cargo do funcionário: ");
    scanf("%s", novoFuncionario.cargo);
    printf("Digite o ID do funcionário: ");
    scanf("%d", &novoFuncionario.id);

    FILE *arquivo = fopen("funcionarios.bin", "ab");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    fwrite(&novoFuncionario, sizeof(Funcionario), 1, arquivo);
    fclose(arquivo);

    printf("Funcionário cadastrado com sucesso.\n");
}

void gerarRelatorios() {
    ContaPoupanca conta;
    FILE *arquivo = fopen("contas_poupanca.bin", "rb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    printf("=== Relatório de Contas ===\n");
    while (lerContaPoupanca(&conta, arquivo)) {
        printf("Nome: %s\n", conta.dados.nome);
        printf("Agência: %s\n", conta.conta.agencia);
        printf("Número da Conta: %s\n", conta.conta.numero_da_conta);
        printf("Saldo: %.2lf\n", conta.conta.saldo);
        printf("\n");
    }

    fclose(arquivo);
}

