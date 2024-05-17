#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_CONTATOS 100

struct Contato {
    char nome[50];
    char sobrenome[50];
    char email[100];
    char telefone[15];
};

struct Contato listaContatos[MAX_CONTATOS];
int numContatos = 0;

bool validarEmail(const char *email) {
    int i, at = 0, dot = 0;
    for (i = 0; email[i] != '\0'; i++) {
        if (email[i] == '@') at++;
        else if (email[i] == '.') dot++;
    }
    return (at == 1 && dot >= 1);
}

bool verificarTelefoneUnico(const char *telefone) {
    for (int i = 0; i < numContatos; i++) {
        if (strcmp(listaContatos[i].telefone, telefone) == 0)
            return false;
    }
    return true;
}

void salvarContatos() {
    FILE *arquivo;
    arquivo = fopen("contatos.bin", "wb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    fwrite(&numContatos, sizeof(int), 1, arquivo);
    fwrite(listaContatos, sizeof(struct Contato), numContatos, arquivo);

    fclose(arquivo);
    printf("Contatos salvos com sucesso!\n");
}

void carregarContatos() {
    FILE *arquivo;
    arquivo = fopen("contatos.bin", "rb");
    if (arquivo == NULL) {
        printf("Arquivo de contatos não encontrado ou vazio.\n");
        return;
    }

    fread(&numContatos, sizeof(int), 1, arquivo);
    fread(listaContatos, sizeof(struct Contato), numContatos, arquivo);

    fclose(arquivo);
    printf("Contatos carregados com sucesso!\n");
}

void adicionarContato() {
    if (numContatos < MAX_CONTATOS) {
        struct Contato novoContato;

        printf("Nome: ");
        scanf("%s", novoContato.nome);

        printf("Sobrenome: ");
        scanf("%s", novoContato.sobrenome);

        printf("Email: ");
        scanf("%s", novoContato.email);

        if (!validarEmail(novoContato.email)) {
            printf("Email inválido!\n");
            return;
        }

        printf("Telefone: ");
        scanf("%s", novoContato.telefone);

        if (!verificarTelefoneUnico(novoContato.telefone)) {
            printf("Este número de telefone já está em uso!\n");
            return;
        }

        listaContatos[numContatos++] = novoContato;
        printf("Contato adicionado com sucesso!\n");
    } else {
        printf("A lista de contatos está cheia!\n");
    }
}

void listarContatos() {
    printf("\nListagem de contatos:\n\n");
    for (int i = 0; i < numContatos; ++i) {
        printf("Nome: %s %s\n", listaContatos[i].nome, listaContatos[i].sobrenome);
        printf("Email: %s\n", listaContatos[i].email);
        printf("Telefone: %s\n\n", listaContatos[i].telefone);
    }
}

void deletarContato(const char *telefone) {
    int i;
    for (i = 0; i < numContatos; i++) {
        if (strcmp(listaContatos[i].telefone, telefone) == 0) {
            for (int j = i; j < numContatos - 1; j++) {
                listaContatos[j] = listaContatos[j + 1];
            }
            numContatos--;
            printf("Contato deletado com sucesso!\n");
            return;
        }
    }
    printf("Contato com o telefone %s não encontrado.\n", telefone);
}

void deletarContatoMenu() {
    char telefone[15];
    printf("Digite o telefone do contato que deseja excluir: ");
    scanf("%s", telefone);
    deletarContato(telefone);
}

void alterarContato(const char *telefone) {
    for (int i = 0; i < numContatos; i++) {
        if (strcmp(listaContatos[i].telefone, telefone) == 0) {
            printf("Novo nome: ");
            scanf("%s", listaContatos[i].nome);

            printf("Novo sobrenome: ");
            scanf("%s", listaContatos[i].sobrenome);

            printf("Novo email: ");
            scanf("%s", listaContatos[i].email);

            if (!validarEmail(listaContatos[i].email)) {
                printf("Email inválido!\n");
                return;
            }

            printf("Novo telefone: ");
            scanf("%s", listaContatos[i].telefone);

            if (!verificarTelefoneUnico(listaContatos[i].telefone)) {
                printf("Este número de telefone já está em uso!\n");
                return;
            }

            printf("Contato alterado com sucesso!\n");
            return;
        }
    }
    printf("Contato com o telefone %s não encontrado.\n", telefone);
}

void alterarContatoMenu() {
    char telefone[15];
    printf("Digite o telefone do contato que deseja alterar: ");
    scanf("%s", telefone);
    alterarContato(telefone);
}

int main() {
    int opcao;

    do {
        // Menu de opções
        printf("\nMenu:\n");
        printf("1. Adicionar contato\n");
        printf("2. Listar contatos\n");
        printf("3. Salvar contatos\n");
        printf("4. Carregar contatos\n");
        printf("5. Deletar contato\n");
        printf("6. Alterar contato\n");
        printf("7. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                adicionarContato();
                break;
            case 2:
                listarContatos();
                break;
            case 3:
                salvarContatos();
                break;
            case 4:
                carregarContatos();
                break;
            case 5:
                deletarContatoMenu();
                break;
            case 6:
                alterarContatoMenu();
                break;
            case 7:
                printf("Encerrando o programa...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 7);

    return 0;
}
