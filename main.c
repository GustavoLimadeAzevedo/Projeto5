#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_CONTATOS 255

struct Contato {
    char nome[50];
    char sobrenome[50];
    char email[100];
    char telefone[15];
};

struct Contato listaContatosPessoais[MAX_CONTATOS];
struct Contato listaContatosTrabalho[MAX_CONTATOS];
int numContatosPessoais = 0;
int numContatosTrabalho = 0;

bool validarEmail(const char *email) {
    int i, at = 0, dot = 0;
    for (i = 0; email[i] != '\0'; i++) {
        if (email[i] == '@') at++;
        else if (email[i] == '.') dot++;
    }
    return (at == 1 && dot >= 1);
}

bool verificarTelefoneUnico(const char *telefone, struct Contato *listaContatos, int numContatos) {
    for (int i = 0; i < numContatos; i++) {
        if (strcmp(listaContatos[i].telefone, telefone) == 0)
            return false;
    }
    return true;
}

void salvarContatos(const char *arquivo, struct Contato *listaContatos, int numContatos) {
    FILE *arq;
    arq = fopen(arquivo, "wb");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    fwrite(&numContatos, sizeof(int), 1, arq);
    fwrite(listaContatos, sizeof(struct Contato), numContatos, arq);

    fclose(arq);
    printf("Contatos salvos com sucesso!\n");
}

void carregarContatos(const char *arquivo, struct Contato *listaContatos, int *numContatos) {
    FILE *arq;
    arq = fopen(arquivo, "rb");
    if (arq == NULL) {
        printf("Arquivo de contatos não encontrado ou vazio.\n");
        return;
    }

    fread(numContatos, sizeof(int), 1, arq);
    fread(listaContatos, sizeof(struct Contato), *numContatos, arq);

    fclose(arq);
    printf("Contatos carregados com sucesso!\n");
}

void adicionarContato(struct Contato *listaContatos, int *numContatos) {
    if (*numContatos < MAX_CONTATOS) {
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

        if (!verificarTelefoneUnico(novoContato.telefone, listaContatos, *numContatos)) {
            printf("Este número de telefone já está em uso!\n");
            return;
        }

        listaContatos[(*numContatos)++] = novoContato;
        printf("Contato adicionado com sucesso!\n");
    } else {
        printf("A lista de contatos está cheia!\n");
    }
}

void listarContatos(struct Contato *listaContatos, int numContatos) {
    printf("\nListagem de contatos:\n\n");
    for (int i = 0; i < numContatos; ++i) {
        printf("Nome: %s %s\n", listaContatos[i].nome, listaContatos[i].sobrenome);
        printf("Email: %s\n", listaContatos[i].email);
        printf("Telefone: %s\n\n", listaContatos[i].telefone);
    }
}

void deletarContato(const char *telefone, struct Contato *listaContatos, int *numContatos) {
    int i;
    for (i = 0; i < *numContatos; i++) {
        if (strcmp(listaContatos[i].telefone, telefone) == 0) {
            for (int j = i; j < *numContatos - 1; j++) {
                listaContatos[j] = listaContatos[j + 1];
            }
            (*numContatos)--;
            printf("Contato deletado com sucesso!\n");
            return;
        }
    }
    printf("Contato com o telefone %s não encontrado.\n", telefone);
}

void deletarContatoMenu(struct Contato *listaContatos, int *numContatos) {
    char telefone[15];
    printf("Digite o telefone do contato que deseja excluir: ");
    scanf("%s", telefone);
    deletarContato(telefone, listaContatos, numContatos);
}

void alterarContato(const char *telefone, struct Contato *listaContatos, int numContatos) {
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

            if (!verificarTelefoneUnico(listaContatos[i].telefone, listaContatos, numContatos)) {
                printf("Este número de telefone já está em uso!\n");
                return;
            }

            printf("Contato alterado com sucesso!\n");
            return;
        }
    }
    printf("Contato com o telefone %s não encontrado.\n", telefone);
}

void alterarContatoMenu(struct Contato *listaContatos, int numContatos) {
    char telefone[15];
    printf("Digite o telefone do contato que deseja alterar: ");
    scanf("%s", telefone);
    alterarContato(telefone, listaContatos, numContatos);
}

int main() {
    int opcao;

    do {
        // Menu de opções
        printf("\nMenu:\n");
        printf("1. Adicionar contato pessoal\n");
        printf("2. Adicionar contato de trabalho\n");
        printf("3. Listar contatos pessoais\n");
        printf("4. Listar contatos de trabalho\n");
        printf("5. Salvar contatos\n");
        printf("6. Carregar contatos\n");
        printf("7. Deletar contato pessoal\n");
        printf("8. Deletar contato de trabalho\n");
        printf("9. Alterar contato pessoal\n");
        printf("10. Alterar contato de trabalho\n");
        printf("11. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                adicionarContato(listaContatosPessoais, &numContatosPessoais);
                break;
            case 2:
                adicionarContato(listaContatosTrabalho, &numContatosTrabalho);
                break;
            case 3:
                listarContatos(listaContatosPessoais, numContatosPessoais);
                break;
            case 4:
                listarContatos(listaContatosTrabalho, numContatosTrabalho);
                break;
            case 5:
                salvarContatos("contatos_pessoais.bin", listaContatosPessoais, numContatosPessoais);
                salvarContatos("contatos_trabalho.bin", listaContatosTrabalho, numContatosTrabalho);
                break;
            case 6:
                carregarContatos("contatos_pessoais.bin", listaContatosPessoais, &numContatosPessoais);
                carregarContatos("contatos_trabalho.bin", listaContatosTrabalho, &numContatosTrabalho);
                break;
            case 7:
                deletarContatoMenu(listaContatosPessoais, &numContatosPessoais);
                break;
            case 8:
                deletarContatoMenu(listaContatosTrabalho, &numContatosTrabalho);
                break;
            case 9:
                alterarContatoMenu(listaContatosPessoais, numContatosPessoais);
                break;
            case 10:
                alterarContatoMenu(listaContatosTrabalho, numContatosTrabalho);
                break;
            case 11:
                printf("Encerrando o programa...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 11);

    return 0;
}
