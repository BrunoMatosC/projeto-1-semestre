#include<stdio.h>
#include<locale.h>
#include<stdlib.h>
#include<string.h>
#include <time.h>

#define TP 15 //tamanho dos vetores(strings) dos atributos das structs
#define TG 50 //tamanho dos vetores(strings) maiores dos atributos das structs

int adminOUclient;//escolha do menu principal
int opcaoMenuADM;//escolha do menu ADM
int opcaoDashRel;//escolha do menu Dashboard ou Relatorios
int sequencia;//da sequencia no sistema pela escolha do utilizador
int contoleFread;//controla se existe dados no arquino
int ID;
int id = 1;
char loginCli[TP], passCli[TP];
int diaLevant, mesLevant, anoLevant, diaDevol, mesDevol, anoDevol;

//login ADM principal
char lAdm[6] = "admin";
int pAdm = 12345;
char loginAdm[6];
int passAdm;

int validaLoginADM(char user[], int pass);
void limpaEcra();
void linhaMenuPrincipal();
void linhaAdm();
void linhaCliente();
void menuPrincipal();
void menuADM();
void voltarMenuPrincipal();
void inserir_veiculo();
void listar_veiculo();
void inserir_cliente();
void listar_cliente();
void excluir_cliente();
void alugar_veiculo();
void cadastro_cliente();
void listar_reservas();
void dashboard();
void relatorios();

typedef struct
{
    int ID ;
    char marca[TP];
    char modelo[TP];
    char categoria[TP];
    char matricula[TP];
    float valorDia;
}veiculos;
veiculos  veiculo;
FILE *aVeiculos;

typedef struct
{
    char nome[TG];
    char morada[TG];
    char telefone[TP];
    char email[TG];
    char carta[TP];
    char nif[TP];
    char pass[TP];
}clientes;
clientes cliente;
FILE *aClientes;

typedef struct 
{
    char nome[TG];
    char veiculo[TP];
    char matricula[TP];
    int diaLevant, diaDevol;
    int mesLevant, mesDevol;
    int anoLevant, anoDevol;
    char lojaLevant[TG];
    char lojaDevol[TG];
    int numDias;
    float valorDia;
    float totalPagar;
    int numCartao;
}reservas;
reservas reserva;
FILE *aReservas;


//===================================== INICIO MAIN
int main()
{   
    
    setlocale(LC_ALL, "Portuguese");

    //MENU PRINCIPAL
    menuPrincipal();

    //********INICIO SISTEMA ADMINISTRADOR*********
    if (adminOUclient == 1)
    {
        do
        { 
            limpaEcra();
            linhaAdm();

            //login ADM
            printf("                      LOGIN                      \n");
            printf("Digite o Username: ");
            fgets(loginAdm, 6, stdin);
            fflush(stdin);
            printf("Digite a password: ");
            scanf("%d", &passAdm);
            fflush(stdin);

            if (validaLoginADM(loginAdm, passAdm) == 1)
            {  
                //MENU ADM
                do
                {
                    limpaEcra();
                    menuADM();

                    switch (opcaoMenuADM)
                    {
                        case 1:
                             //1-Inserir Veiculo 
                            inserir_veiculo();
                            break;

                        case 2:
                            //2-Listar Veiculos
                            listar_veiculo();
                            break;    
                        
                        case 3:
                            //3-Inserir Cliente
                            inserir_cliente();
                            break;

                        case 4:
                            //4-Listar/Editar Cliente 
                            listar_cliente();
                            break;

                        case 5:
                            //-Excluir Cliente
                            excluir_cliente();
                            break;

                        case 6:
                            //6-Dashboard 
                            dashboard();
                            break;

                        case 7: 
                            //7-Relatorios
                            relatorios();
                            break;     
                        
                        default:
                            sequencia = 1; 
                            printf("\aERRO! Opção inválida!\nTecle ENTER para tentar novamente..." ); 
                            getchar();
                            break;;
                    
                    }
                } while (sequencia == 1);   
            }
            else
            {
                printf("\n\aERRO! Login inválido!\nTecle ENTER para tentar novamente...");
                getchar();
            }
        }while (validaLoginADM(loginAdm, passAdm) != 1);
        
    }

    //********INICIO SISTEMA CLIENTE*********
    if (adminOUclient == 2)
    {
        alugar_veiculo();
    }
}


//===================================== FIM MAIN

//Funcoes e procedimentos
//===================================== VALIDA LOGIN 
int validaLoginADM(char user[], int pass)
{
    if (strstr(lAdm, user) && pAdm == pass)
    {
        return 1;
    }
    return -1;
}

//===================================== LIMPA ECRA
void limpaEcra()
{
    //system("clear");//para MacOS/Linux
    //system("cls");//para Windows
    system("clear||cls");//para Mac ou Windows/
}

//===================================== LINHA MENU PRINCIPAL
void linhaMenuPrincipal()
{
    printf("\n------------------BEM VINDO(A)-----------------\n");
}

//===================================== LINHA ADM
void linhaAdm()
{
    printf("\n------------------ADMINISTRADOR-----------------\n");
}

//===================================== LINHA CLIENTE
void linhaCliente()
{
    printf("\n----------------------CLIENTE-------------------\n");
}

//===================================== MENU PRINCIPAL
void menuPrincipal()
{   
    setlocale(LC_ALL, "Portuguese");

    do
    {
        limpaEcra();   
        linhaMenuPrincipal();
        printf("Bem vindo(a) ao sistema IPCAR\n\n");
        
        printf("Digite:\n");
        printf("       1-Area Administrador\n       2-Area Cliente\n");
        scanf("%d", &adminOUclient);
        fflush(stdin);

        if (adminOUclient < 1 || adminOUclient > 2)
        {  
            printf("\aERRO! Opção inválida!\nTecle ENTER para tentar novamente..." );  
            getchar();   
        }
    
    } while (adminOUclient < 1 || adminOUclient > 2);
}

//===================================== MENU ADM
void menuADM()
{
    setlocale(LC_ALL, "Portuguese");
    limpaEcra();
    linhaAdm();
    printf("               MENU ADMINISTRADOR               \n");
    printf("Digite:\n");
    printf("       1-Inserir Veículo        2-Listar Veículos\n");
    printf("       3-Inserir Cliente        4-Listar/Editar Cliente\n");
    printf("       5-Excluir Cliente\n\n"); 
    printf("       6-Dashboard              7-Relatórios\n");   
    scanf("%d", &opcaoMenuADM);
    fflush(stdin);
}

//===================================== VOLTAR MENU PRINCIPAL
void voltarMenuPrincipal() //mostra somente a opcao de voltar ao menu principal
{
    do
    {
        printf("\n1-Menu Principal\n");
        scanf("%d", &sequencia);
        fflush(stdin);
        if (sequencia != 1)
        {
            printf("\aERRO! Opção inválida!\nTecle ENTER para tentar novamente..." );  
            getchar(); 
        } 
    } while (sequencia != 1);    
}

//===================================== VALIDA SEQUENCIA
void valida_sequencia()//valida a opcao que o utilizador digitou (0-Novo alguma coisa 1-Menu Principal)
{
    scanf("%d", &sequencia);
    fflush(stdin);
    if (sequencia < 0 || sequencia > 1)
    {
        printf("\aERRO! Opção inválida!\nTecle ENTER para tentar novamente..." );  
        getchar(); 
    }
}

//===================================== INSERIR VEICULO
void inserir_veiculo()
{
    do
    {
        limpaEcra();
        linhaAdm();
        

        aVeiculos = fopen("veiculos_bin", "a+b");//abertura arquivo
        if (aVeiculos == NULL)
        {
            printf("\aERRO na abertura do arquivo!"); 
        }
        else
        {
            printf("                 INSERIR VEÍCULO\n");
            printf("Digite a marca: ");
            fgets(veiculo.marca, TP, stdin);
            veiculo.marca[strcspn(veiculo.marca, "\n")] = '\0';
            fflush(stdin);
            printf("Digite o modelo: ");
            fgets(veiculo.modelo, TP, stdin);
            veiculo.modelo[strcspn(veiculo.modelo, "\n")] = '\0';
            fflush(stdin);
            printf("Digite a categoria: ");
            fgets(veiculo.categoria, TP, stdin);
            veiculo.categoria[strcspn(veiculo.categoria, "\n")] = '\0';
            fflush(stdin);
            printf("Digite a matrícula: ");
            fgets(veiculo.matricula, TP, stdin);
            veiculo.matricula[strcspn(veiculo.matricula, "\n")] = '\0';
            fflush(stdin);
            printf("Digite o valor por dia: ");
            scanf("%f", &veiculo.valorDia);
            fflush(stdin);

            fwrite(&veiculo, sizeof(veiculo), 1, aVeiculos);
            if (ferror(aVeiculos))//
            {
                printf("\aERRO! Veículo não foi salvo."); 
            }
            else
            {
                printf("\nVeículo salvo com sucesso!\n"); 
            }
            
            
        }  

        //fechar arquivo
        if (!fclose(aVeiculos)) //se fechado com sucesso retorna 0
        {
            //se fechado com sucesso nao mostra nada 
        }
        else
        {
            printf("\aERRO! O arquivo não pode ser fechado.");
        } 
        
        do
        {
            printf("\n0-Inserir novo veículo\n1-Menu Principal\n");
            valida_sequencia();  
        } while (sequencia < 0 || sequencia > 1);

    }while(sequencia == 0);

}

//===================================== LISTA VEICULO
void lista_veiculo()// monta a lista de veiculos
{
    id = 1;

    while (!feof(aVeiculos))
    {
        contoleFread = fread(&veiculo, sizeof(veiculo), 1, aVeiculos);//**para evitar que mostre o ultimo registo 2 vezes
        if (ferror(aVeiculos))//se retornar erro
        {
        printf("\aERRO! Arquivo não pode ser lido."); 
        }
        else
        {
            if (contoleFread !=0)//**
            {
                printf("ID: %d", id);
                printf("\nMarca: %s", veiculo.marca);
                printf("\nModelo: %s", veiculo.modelo);
                printf("\nCategoria: %s", veiculo.categoria);
                printf("\nMatricula: %s", veiculo.matricula);
                printf("\nValor por dia: %2.f", veiculo.valorDia);
                printf("\n\n");

                id++;
            }
        }
    }
}

//===================================== LISTAR/EDITAR VEICULO
void listar_veiculo()// chama a lista de veiculos
{
    limpaEcra();
    linhaAdm();

    aVeiculos = fopen("veiculos_bin", "rb");//abertura arquivo
    if (aVeiculos == NULL)
    {
        printf("\aERRO na abertura do arquivo!"); 
    }
    else
    {
        printf("              VEÍCULOS REGISTADOS\n");

        lista_veiculo();//monta a lista de veiculos
    }
    //fechar arquivo

    if (!fclose(aVeiculos)) //se fechado com sucesso retorna 0
    {
        //se fechado com sucesso nao mostra nada
        
    }
    else
    {
        printf("\aERRO! O arquivo não pode ser fechado.");
    } 

    voltarMenuPrincipal();
}

//===================================== REGISTO CLIENTE
void resgisto_cliente() //monta o formulario de resgisto de cliente
{
    printf("Digite o nome: ");
    fgets(cliente.nome, TG, stdin);
    cliente.nome[strcspn(cliente.nome, "\n")] = '\0';
    fflush(stdin);
    printf("Digite a morada: ");
    fgets(cliente.morada, TG, stdin);
    cliente.morada[strcspn(cliente.morada, "\n")] = '\0';
    fflush(stdin);
    printf("Digite o telefone: ");
    fgets(cliente.telefone, TP, stdin);
    cliente.telefone[strcspn(cliente.telefone, "\n")] = '\0';
    fflush(stdin);
    printf("Digite e-mail: ");
    fgets(cliente.email, TG, stdin);
    cliente.email[strcspn(cliente.email, "\n")] = '\0';
    fflush(stdin);
    printf("Digite a carta de condução: ");
    fgets(cliente.carta, TP, stdin);
    cliente.carta[strcspn(cliente.carta, "\n")] = '\0';
    fflush(stdin);
    printf("Digite o NIF: ");
    fgets(cliente.nif, TP, stdin);
    cliente.nif[strcspn(cliente.nif, "\n")] = '\0';
    fflush(stdin);
    printf("Digite uma Password: ");
    fgets(cliente.pass, TP, stdin);
    cliente.pass[strcspn(cliente.pass, "\n")] = '\0';
    fflush(stdin);

}

//===================================== INSERIR CLIENTE
void inserir_cliente()//chama o formulario de registo de cliente e insere cliente no arquivo
{
    do
    {
        limpaEcra();
        linhaAdm();

        aClientes = fopen("clientes_bin", "a+b");//abertura arquivo
        if (aClientes == NULL)
        {
            printf("\aERRO na abertura do arquivo!"); 
        }
        else
        {
            printf("                 INSERIR CLIENTE\n");

            resgisto_cliente();//formulario de registo de cliente

            fwrite(&cliente, sizeof(cliente), 1, aClientes);
            if (ferror(aClientes))//
            {
                printf("\aERRO! Cliente não foi salvo."); 
            }
            else
            {
                printf("\nCliente salvo com sucesso!\n"); 
            }    
        }  
        //fechar arquivo

        if (!fclose(aClientes)) //se fechado com sucesso retorna 0
        {
            //se fechado com sucesso nao mostra nada
        
        }
        else
        {
            printf("\aERRO! O arquivo não pode ser fechado.");
        } 
        
        do
        {
            printf("\n0-Inserir novo cliente\n1-Menu Principal\n");
            valida_sequencia();  
        } while (sequencia < 0 || sequencia > 1);

    }while(sequencia == 0);

}

//===================================== LISTA CLIENTE
void lista_cliente() //monta a lista de clientes
{
    id = 1;
    while (!feof(aClientes))
    {
        contoleFread = fread(&cliente, sizeof(cliente), 1, aClientes);
        if (ferror(aClientes))//
        {
        printf("\aERRO! Arquivo não pode ser lido."); 
        }
        else
        {
            if (contoleFread !=0)
            {
                printf("ID: %d", id);
                printf("\nNome: %s", cliente.nome);
                printf("\nMorada: %s", cliente.morada);
                printf("\nTelefone: %s", cliente.telefone);
                printf("\nE-mail: %s", cliente.email);
                printf("\nCarta de condução: %s", cliente.carta);
                printf("\nNIF: %s", cliente.nif);
                printf("\n\n");

                id++;
            }  
        }
    }
}

////===================================== LISTAR CLIENTE
void listar_cliente()//chama a lista de clientes
{
    do
    {
        char opcao;
        limpaEcra();
        linhaAdm();

        aClientes = fopen("clientes_bin", "r+b");//abertura arquivo
        if (aClientes == NULL)
        {
            printf("\aERRO na abertura do arquivo!"); 
        }
        else
        {
            printf("                 LISTAR CLIENTES\n");

            lista_cliente();
        }

        do
        {
        printf("\n0-Editar Cliente\n1-Menu Principal\n");
        valida_sequencia();
        } while (sequencia < 0 || sequencia > 1);

        if (sequencia==0)
        {

            printf("Digite o ID do cliente que deseja editar: ");
            scanf("%d", &ID);
            getchar();
            ID--;

            if (ID >= 0 && ID < id -1)
            {   
                // ler o cliente atual do arquivo
                fseek(aClientes, ID*sizeof(cliente), SEEK_SET);
                fread(&cliente, sizeof(cliente), 1, aClientes);

                // perguntar quais campos o usuário quer editar
                printf("Deseja editar o nome? (s/n): ");
                scanf("%c", &opcao);
                getchar();
                if (opcao == 's' || opcao == 'S')
                {
                    printf("Digite o novo nome: ");
                    fgets(cliente.nome, TG, stdin);
                    cliente.nome[strcspn(cliente.nome, "\n")] = '\0';
                    fflush(stdin);
                }

                printf("Deseja editar a morada? (s/n): ");
                scanf("%c", &opcao);
                getchar();
                if (opcao == 's' || opcao == 'S')
                {
                    printf("Digite a nova morada: ");
                    fgets(cliente.morada, TG, stdin);
                    cliente.morada[strcspn(cliente.morada, "\n")] = '\0';
                    fflush(stdin);
                }

                printf("Deseja editar o telefone? (s/n): ");
                scanf("%c", &opcao);
                getchar();
                if (opcao == 's' || opcao == 'S')
                {
                    printf("Digite o novo telefone: ");
                    fgets(cliente.telefone, TP, stdin);
                    cliente.telefone[strcspn(cliente.telefone, "\n")] = '\0';
                    fflush(stdin);
                }
                
                printf("Deseja editar o e-mail? (s/n): ");
                scanf("%c", &opcao);
                getchar();
                if (opcao == 's' || opcao == 'S')
                {
                    printf("Digite o novo e-mail: ");
                    fgets(cliente.email, TP, stdin);
                    cliente.email[strcspn(cliente.email, "\n")] = '\0';
                    fflush(stdin);
                }

                printf("Deseja editar a carta? (s/n): ");
                scanf("%c", &opcao);
                getchar();
                if (opcao == 's' || opcao == 'S')
                {
                    printf("Digite a nova carta: ");
                    fgets(cliente.carta, TP, stdin);
                    cliente.carta[strcspn(cliente.carta, "\n")] = '\0';
                    fflush(stdin);
                }

                printf("Deseja editar o NIF? (s/n): ");
                scanf("%c", &opcao);
                getchar();
                if (opcao == 's' || opcao == 'S')
                {
                    printf("Digite o novo NIF: ");
                    fgets(cliente.nif, TP, stdin);
                    cliente.nif[strcspn(cliente.nif, "\n")] = '\0';
                    fflush(stdin);
                }

                printf("Deseja editar a password? (s/n): ");
                scanf("%c", &opcao);
                getchar();
                if (opcao == 's' || opcao == 'S')
                {
                    printf("Digite a nova password: ");
                    fgets(cliente.pass, TP, stdin);
                    cliente.pass[strcspn(cliente.pass, "\n")] = '\0';
                    fflush(stdin);
                }

                //escrever as alteracoes no arquivo
                fseek(aClientes, ID*sizeof(cliente), SEEK_SET);
                fwrite(&cliente, sizeof(cliente), 1, aClientes);

                if (ferror(aClientes))//
                {
                    printf("\aERRO! Cliente não foi alterado."); 
                }
                else
                {
                    printf("\nCliente editado com sucesso!\n"); 
                }

                do
                {
                printf("\n0-Verificar edição\n1-Menu Principal\n");
                valida_sequencia(); 
                }while (sequencia < 0 || sequencia > 1);

            }
               
        }
        if (!fclose(aClientes)) //se fechado com sucesso retorna 0
        {
            //se fechado com sucesso não mostra nada
              
        }
        else
        {
            printf("\aERRO! O arquivo não pode ser fechado.");
        } 

    } while(sequencia == 0);  
}

//===================================== EXCLUIR CLIENTE
void excluir_cliente()
{
    limpaEcra();
    linhaAdm();

    id = 1;

    aClientes = fopen("clientes_bin", "r+b");//abertura arquivo
    if (aClientes == NULL)
    {
        printf("\aERRO na abertura do arquivo!"); 
    }
    else
    {
        printf("                 EXCLUIR CLIENTE\n");

        lista_cliente();//monta a lista de clientes
    }  

    printf("Digite o ID do cliente que deseja excluir: ");
    scanf("%d", &ID);
    getchar();
    ID--;

    // cria um novo arquivo temporário
    FILE *temp = fopen("temp_bin", "w+b");
    if (temp == NULL)
    {
        printf("\aERRO na criação do arquivo temporário!");
    }
    else
    {
        // volta o ponteiro do arquivo original para o início
        rewind(aClientes);
        // copia todos os registros, exceto o que tem o ID informado, para o arquivo temporário
        int i = 0; // contador de registros
        while (!feof(aClientes))
        {
            contoleFread = fread(&cliente, sizeof(cliente), 1, aClientes);
            if (ferror(aClientes))
            {
                printf("\aERRO! Arquivo não pode ser lido.");
            }
            else
            {
                if (contoleFread != 0)
                {
                    // se o registro não for o que quer excluir, copia para o temporário
                    if (i != ID)
                    {
                        fwrite(&cliente, sizeof(cliente), 1, temp);
                        if (ferror(temp))
                        {
                            printf("\aERRO! Arquivo temporário não pode ser escrito.");
                        }
                    }
                    i++;
                }
            }
        }
    }

    // fecha os arquivos
     if (!fclose(aClientes)) //se fechado com sucesso retorna 0
    {
        //se fechado com sucesso nao mostra nada
            
    }
    else
    {
        printf("\aERRO! O arquivo não pode ser fechado.");
    }

     if (!fclose(temp)) //se fechado com sucesso retorna 0
    {
        //se fechado com sucesso nao mostra nada
            
    }
    else
    {
        printf("\aERRO! O arquivo não pode ser fechado.");
    }    

    // remove o arquivo original
    remove("clientes_bin");

    // renomeia o arquivo temporário para o nome do original
    rename("temp_bin", "clientes_bin");

    // mostra uma mensagem de sucesso
    printf("\nCliente excluído com sucesso!");

    voltarMenuPrincipal();
}

//===================================== CADASTRO CLIENTE
void cadastro_cliente()
{
    limpaEcra();
    linhaCliente();

    aClientes = fopen("clientes_bin", "a+b");//abertura arquivo
    if (aClientes == NULL)
    {
        printf("\aERRO na abertura do arquivo!"); 
    }
    else
    {
        printf("                 CADASTRO\n");

        resgisto_cliente(); //monta o formulario de resgisto

        fwrite(&cliente, sizeof(cliente), 1, aClientes);
        if (ferror(aClientes))//
        {
            printf("\aERRO! Cliente não foi salvo."); 
        }
        else
        {       
            printf("\nCadastrado com sucesso!\n"); 
            printf("\nTecle ENTER para continiuar com a reserva...\n"); 
            getchar();
        }


    }  
    //fechar arquivo

    if (!fclose(aClientes)) //se fechado com sucesso retorna 0
    {
        //se fechado com sucesso nao mostra nada

        }
    else
    {
        printf("\aERRO! O arquivo não pode ser fechado.");
    } 
}

//===================================== LER DATA
struct tm ler_data(int dia, int mes, int ano)//ler uma data do teclado e armazenar em uma estrutura tm
{
    struct tm data; // Declara uma variável do tipo struct tm
   
    // Preenche os campos da estrutura data com os valores lidos
    data.tm_mday = dia; // Dia
    data.tm_mon = mes - 1; // Mês (subtrai 1 pois a contagem começa em 0)
    data.tm_year = ano - 1900; // Ano (subtrai 1900 pois a contagem começa em 1900)
    data.tm_hour = 0; // Hora
    data.tm_min = 0; // Minuto
    data.tm_sec = 0; // Segundo
    data.tm_isdst = -1; // Indica que não se sabe se é horário de verão ou não
    return data; // Retorna a estrutura data
}

//===================================== CALCULAR DIAS
int calcular_dias(struct tm data1, struct tm data2) //calcular o número de dias entre duas datas
{
    time_t t1, t2; // Declara duas variáveis do tipo time_t
    int dias; // Declara uma variável do tipo int
    t1 = mktime(&data1); // Converte a estrutura data1 em um valor do tipo time_t
    t2 = mktime(&data2); // Converte a estrutura data2 em um valor do tipo time_t
    dias = (t2 - t1) / 86400; // Calcula o número de dias entre as duas datas
    return dias; // Retorna o número de dias
}

//===================================== FAZER RESERVAS
void fazer_reserva()//mostra e armazena os datos de uma reserva
{
    limpaEcra();
    linhaCliente(); 

    aReservas = fopen("reservas_bin", "a+b");//abertura arquivo
    if (aClientes == NULL)
    {
        printf("\aERRO na abertura do arquivo!"); 
    }
    else
    {
        printf("\n                       RESERVA");
        printf("\nNome: %s", cliente.nome);
        strcpy(reserva.nome, cliente.nome);

        printf("\nVeículo: %s", veiculo.modelo);
        strcpy(reserva.veiculo, veiculo.modelo);
        printf("\nMatricula: %s", veiculo.matricula);
        strcpy(reserva.matricula, veiculo.matricula);
        printf("\n\n");

        struct tm data_inicio, data_fim; // Declara duas variáveis do tipo struct tm
        int dias;

        reserva.diaLevant = diaLevant;
        reserva.mesLevant = mesLevant;
        reserva.anoLevant = anoLevant;
        reserva.diaDevol = diaDevol;
        reserva.mesDevol = mesDevol;
        reserva.anoDevol = anoDevol;

        printf("Data de levantamento: %2d %2d %4d\n",reserva.diaLevant, reserva.mesLevant, reserva.anoLevant );
        data_inicio = ler_data(reserva.diaLevant, reserva.mesLevant, reserva.anoLevant); // Chama a função para ler a data de início
        printf("Data de devolução: %2d %2d %4d\n",reserva.diaDevol, reserva.mesDevol, reserva.anoDevol);
        data_fim = ler_data(reserva.diaDevol, reserva.mesDevol, reserva.anoDevol); // Chama a função para ler a data de fim
        dias = calcular_dias(data_inicio, data_fim)+1; // Chama a função para calcular o número de dias

        fflush(stdin);
        printf("Digite a loja de levantamento:\n");
        fgets(reserva.lojaLevant, TG, stdin);
        reserva.lojaLevant[strcspn(reserva.lojaLevant, "\n")] = '\0';
        fflush(stdin);
        printf("Digite a loja de devolução:\n");
        fgets(reserva.lojaDevol, TG, stdin);
        reserva.lojaDevol[strcspn(reserva.lojaDevol, "\n")] = '\0';
        fflush(stdin);

        printf("Número de dias: %d\n", dias); // Imprime o número de dias na tela
        reserva.numDias = dias;

        int valor = veiculo.valorDia;
        printf("Valor por dia: %d", valor);
        reserva.valorDia = veiculo.valorDia;

        printf("\n\nTOTAL A PAGAR: %d", valor*dias);
        reserva.totalPagar = valor*dias;

        printf("\n\n*****PAGAMENTO*****");
        printf("\n\nDigite o numero do cartão: ");
        scanf("%d", &reserva.numCartao);

        fflush(stdin);
        printf("\n\nReveja o seu pedido e escolha uma opção: ");
        printf("\n1-Efetuar Pedido\n2-Cancelar Simulação");
        scanf("%d", &sequencia);

        if (sequencia == 1)
        {
            fwrite(&reserva, sizeof(reserva), 1, aReservas);
            if (!fclose(aReservas)) //se fechado com sucesso retorna 0
            {
            //se fechado com sucesso nao mostra nada
            printf("\n\n*********** RESERVA EFETUADA COM SUCESSO **********");

            }
            else
            {
                printf("\aERRO! O arquivo não pode ser fechado.");
            } 
        }
        else
        {
            printf("\n\n*********** PEDIDO CANCELADO **********");
            if (!fclose(aReservas)) //se fechado com sucesso retorna 0
            {
            //se fechado com sucesso nao mostra nada

            }
            else
            {
                printf("\aERRO! O arquivo não pode ser fechado.");
            } 
        }
    } 
}

//===================================== LISTAR RESERVAS
void listar_reservas()
{
    id = 1;

    aReservas = fopen("reservas_bin", "rb");//abertura arquivo
    if (aReservas == NULL)
    {
        printf("\aERRO na abertura do arquivo!"); 
    }
    else
    {
        printf("                 LISTAR RESERVAS\n");

        while (!feof(aReservas))
        {
            contoleFread = fread(&reserva, sizeof(reserva), 1, aReservas);//**para evitar que mostre o ultimo registo 2 vezes
            if (ferror(aReservas))//se retornar erro
            {
            printf("\aERRO! Arquivo não pode ser lido."); 
            }
            else
            {
                if (contoleFread !=0)//**
                {
                    printf("ID: %d", id);
                    printf("\nNome Cliente: %s", reserva.nome);
                    printf("\nVeiculo: %s", reserva.veiculo);
                    printf("\nMatricula: %s", reserva.matricula);
                    printf("\nData Levantamento: %d %d %d", reserva.diaLevant, reserva.mesLevant, reserva.anoLevant);
                    printf("\nData Devolucao: %d %d %d", reserva.diaDevol, reserva.mesDevol, reserva.anoDevol);
                    printf("\nLoja Levantamento: %s", reserva.lojaLevant);
                    printf("\nLoja Devolucao: %s", reserva.lojaDevol);
                    printf("\nNumero de dias: %d", reserva.numDias);
                    printf("\nValor por dia: %f", reserva.valorDia);
                    printf("\nTotal a pagar: %f", reserva.totalPagar);
                    printf("\nNumero cartao: %d", reserva.numCartao);
                    
                    printf("\n\n");

                    id++;
                }
            }
        }
    }
    //fechar arquivo

    if (!fclose(aReservas)) //se fechado com sucesso retorna 0
    {
        //se fechado com sucesso nao mostra nada
        
    }
    else
    {
        printf("\aERRO! O arquivo não pode ser fechado.");
    } 
}

//===================================== VEICULO RESERVADO
int veiculo_reservado(veiculos v, reservas r, FILE *aReservas, int diaLevant, int mesLevant, int anoLevant, int diaDevol, int mesDevol, int anoDevol)//verifica se um veículo está reservado em uma data
{
    fread(&r, sizeof(reservas), 1, aReservas);

    // voltar o ponteiro do arquivo para o início
    rewind(aReservas);

    // ler uma reserva do arquivo
    fread(&r, sizeof(reservas), 1, aReservas);

    // percorrer o arquivo de reservas até o final
    while (!feof(aReservas))
    {
        // verificar se a matrícula do veículo coincide com a da reserva
        if (strcmp(v.matricula, r.matricula) == 0)
        {
            // verificar se o intervalo digitado intersecta com o intervalo da reserva
            if ((anoLevant > r.anoLevant || (anoLevant == r.anoLevant && mesLevant > r.mesLevant) || (anoLevant == r.anoLevant && mesLevant == r.mesLevant && diaLevant >= r.diaLevant)) && (anoLevant < r.anoDevol || (anoLevant == r.anoDevol && mesLevant < r.mesDevol) || (anoLevant == r.anoDevol && mesLevant == r.mesDevol && diaLevant <= r.diaDevol)))
            {
                // o intervalo de levantamento digitado intersecta com o intervalo da reserva
                return 1;
            }
            else if ((anoDevol > r.anoLevant || (anoDevol == r.anoLevant && mesDevol > r.mesLevant) || (anoDevol == r.anoLevant && mesDevol == r.mesLevant && diaDevol >= r.diaLevant)) && (anoDevol < r.anoDevol || (anoDevol == r.anoDevol && mesDevol < r.mesDevol) || (anoDevol == r.anoDevol && mesDevol == r.mesDevol && diaDevol <= r.diaDevol)))
            {
                // o intervalo de devolução digitado intersecta com o intervalo da reserva
                return 1;
            }
            else if ((anoLevant < r.anoLevant || (anoLevant == r.anoLevant && mesLevant < r.mesLevant) || (anoLevant == r.anoLevant && mesLevant == r.mesLevant && diaLevant <= r.diaLevant)) && (anoDevol > r.anoDevol || (anoDevol == r.anoDevol && mesDevol > r.mesDevol) || (anoDevol == r.anoDevol && mesDevol == r.mesDevol && diaDevol >= r.diaDevol)))
            {
                // o intervalo digitado contém o intervalo da reserva
                return 1;
            }
        }
        // ler a próxima reserva do arquivo
        fread(&r, sizeof(reservas), 1, aReservas);
    }
    // o veículo não está reservado no intervalo digitado
    return 0;
}

//===================================== LISTAR VEICULO DISPONIVEL
void listar_veiculoDisponivel(veiculos v)//listar um veículo disponivel
{
    printf("\nID: %d", id);
    printf("\nMarca: %s", v.marca);
    printf("\nModelo: %s", v.modelo);
    printf("\nCategoria: %s", v.categoria);
    printf("\nMatricula: %s", v.matricula);
    printf("\nValor por dia: %2.f", v.valorDia);
    printf("\n");
}

//===================================== LISTAR VEICULO OCUPADO
void listar_veiculoOcupado(veiculos v)//listar um veículo ocupado
{
    printf("\nID: %d", id*0);
    printf("\nMarca: %s", v.marca);
    printf("\nModelo: %s", v.modelo);
    printf("\nCategoria: %s", v.categoria);
    printf("\nMatricula: %s", v.matricula);
    printf("\nValor por dia: %2.f", v.valorDia);
    printf("\n");
}

//===================================== ALUGAR VEICULO
void alugar_veiculo()// recolhe os dados para alugar um veículo
{
    limpaEcra();
    linhaMenuPrincipal(); 

    printf("Para visualizar os veículos disponíneis digite\n\n");
    printf("Data de levantamento pretendida (dd mm aaa): \n");
    scanf("%2d %2d %4d", &diaLevant, &mesLevant, &anoLevant);
    printf("Data de devolução pretendida (dd mm aaa): \n");
    scanf("%2d %2d %4d", &diaDevol, &mesDevol, &anoDevol);

    // abrir o arquivo de veículos
    aVeiculos = fopen("veiculos_bin", "rb");
    if (aVeiculos == NULL)
    {
        printf("\aERRO na abertura do arquivo!"); 
    }
    else
    {
        // abrir o arquivo de reservas
        aReservas = fopen("reservas_bin", "r+b");
        if (aReservas == NULL)
        {
            printf("\aERRO na abertura do arquivo Reservas!"); 
        }
        else
        {
            // ler o número de veículos do arquivo
            fseek(aVeiculos, 0, SEEK_END);
            long int tamanho = ftell(aVeiculos);
            int registos = tamanho / sizeof(veiculo);
            rewind(aVeiculos);//voltar o ponteiro para o inicio do arquivo

            fread(&reserva, sizeof(reservas), 1, aReservas);

            // usar um laço for para percorrer o arquivo de veículos
            for (int i = 0; i < registos; i++)
            {
                // ler um veículo do arquivo
                while (!feof(aVeiculos))
                {
                    contoleFread = fread(&veiculo, sizeof(veiculos), 1, aVeiculos);
                    

                    // verificar se o veículo está reservado no intervalo digitado
                    if (veiculo_reservado(veiculo, reserva, aReservas, diaLevant, mesLevant, anoLevant, diaDevol, mesDevol, anoDevol))
                    {
                        // mostrar o veículo e dizer que está indisponível
                        if (contoleFread !=0)//**
                        {
                            listar_veiculoOcupado(veiculo);
                            printf("OCUPADO! Escolha uma data de levantamento após %2d %2d %4d para este veiculo.\n", reserva.diaDevol, reserva.mesDevol, reserva. anoDevol);
                        }
                    }
                    else
                    {
                        // mostrar o veículo e dizer que está disponível
                        if (contoleFread !=0)//**
                        {
                            listar_veiculoDisponivel(veiculo);
                            printf("DISPONÍVEL! Você pode reservar este veículo nesta data.\n");
                        }
                    } 

                    id++;
                }
                
            }
        }

    }
    
    printf("Digite o ID do veículo que deseja alugar: ");
    scanf("%d", &ID);
    getchar();
    ID--;

    if (ID >= 0 && ID < id -1)
    {
        limpaEcra();
        linhaCliente(); 

        fseek(aVeiculos, ID*sizeof(veiculo), SEEK_SET);
        fread(&veiculo, sizeof(veiculo), 1, aVeiculos);

        printf("\nO veículo escolhido foi:\n\n");
        printf("\nMarca: %s", veiculo.marca);
        printf("\nModelo: %s", veiculo.modelo);
        printf("\nCategoria: %s", veiculo.categoria);
        printf("\nMatricula: %s", veiculo.matricula);
        printf("\nValor por dia: %2.f", veiculo.valorDia);
        printf("\n");

        printf("\n1-Fazer Cadastro\n2-Login\n");
        scanf("%d", &sequencia);
        fflush(stdin);

        if (sequencia == 1)// se cadastrar
        {
            cadastro_cliente();
            fazer_reserva();
            printf("\n\n");
        }

        if (sequencia == 2)// login
        {
            
            printf("                      LOGIN\n");
            printf("Digite seu NIF: ");
            fgets(loginCli, TP, stdin);
            loginCli[strcspn(loginCli, "\n")] = '\0';
            fflush(stdin);
            printf("Digite sua password: ");
            fgets(passCli, TP, stdin);
            passCli[strcspn(passCli, "\n")] = '\0';
            fflush(stdin);

            aClientes = fopen("clientes_bin", "rb");//abertura arquivo
            if (aClientes == NULL) //verificação de erro
            {
                printf("\aERRO na abertura do arquivo!\n");
            }
            else
            {
                while (fread(&cliente, sizeof(cliente), 1, aClientes) == 1)
                {
                    
                    if (!strcmp(loginCli, cliente.nif) && !strcmp(passCli, cliente.pass))
                    {
                        fazer_reserva();
                        break;
                    }
                }
            }
        }
    }
    // fechar os arquivos
    if (!fclose(aVeiculos)) //se fechado com sucesso retorna 0
    {
        //se fechado com sucesso nao mostra nada
        
    }
    else
    {
        printf("\aERRO! O arquivo não pode ser fechado.");
    } 

    if (!fclose(aReservas)) //se fechado com sucesso retorna 0
    {
        //se fechado com sucesso nao mostra nada
        
    }
    else
    {
        printf("\aERRO! O arquivo não pode ser fechado.");
    } 
}

//===================================== GERAR MEDIA MENSAL
void gerar_mediaMensal()
{
    int mes;
    int totalReservas = 0;
    float mediaReservas = 0;
    limpaEcra();
    linhaAdm();
    printf("Digite o mês que deseja informações:\n");
    scanf("%d", &mes);

    aReservas = fopen("reservas_bin", "rb");//abertura arquivo
    if (aReservas == NULL)
    {
        printf("\aERRO na abertura do arquivo!"); 
    }
    else
    {
        while (!feof(aReservas))
        {
            contoleFread = fread(&reserva, sizeof(reserva), 1, aReservas);//**para evitar que mostre o ultimo registo 2 vezes
            if (ferror(aReservas))//se retornar erro
            {
            printf("\aERRO! Arquivo não pode ser lido."); 
            }
            else
            {
                if (contoleFread !=0)//**
                {
                    if (reserva.mesLevant == mes)
                    {
                        totalReservas ++;
                        mediaReservas += reserva.totalPagar;
                    } 
                }
            }
        }
        mediaReservas = mediaReservas / totalReservas;

        printf("\nO total de reservas para o mes %d foi: %d", mes, totalReservas);
        printf("\nA média de valores para o mes %d foi: %.2f€\n\n", mes, mediaReservas);
    }
    //fechar arquivo

    if (!fclose(aReservas)) //se fechado com sucesso retorna 0
    {
        //se fechado com sucesso nao mostra nada
        
    }
    else
    {
        printf("\aERRO! O arquivo não pode ser fechado.");
    } 
}

//===================================== DASHBOARD
void dashboard()
{
    limpaEcra();
    linhaAdm();
    printf("                 DASHBOARD\n");

    printf("Digite:\n");
    printf("       1-Listar Reservas\n       2-Média de alugueres mensal\n");
    scanf("%d", &opcaoDashRel);
    fflush(stdin);

    switch (opcaoDashRel)
    {
    case 1:
        listar_reservas();
        break;
    case 2:
        gerar_mediaMensal();
        break;

    default:
        break;
    }
}

//===================================== GERAR RELATORIOS
void gerar_relatorios(int opcao)
{
    limpaEcra();
    linhaAdm();
    int mes, ano;
    float faturacao = 0;

    aReservas = fopen("reservas_bin", "rb");//abertura arquivo
    if (aReservas == NULL)
    {
        printf("\aERRO na abertura do arquivo!"); 
    }
    else
    {
        switch (opcao)
        {
            case 1:
                printf("Digite o mês e ano (mm aaaa) que deseja a faturação:\n");
                scanf("%d %d", &mes, &ano);

                while (!feof(aReservas))
                {
                    contoleFread = fread(&reserva, sizeof(reserva), 1, aReservas);//**para evitar que mostre o ultimo registo 2 vezes
                    if (ferror(aReservas))//se retornar erro
                    {
                        printf("\aERRO! Arquivo não pode ser lido."); 
                    }
                    else
                    {
                        if (contoleFread !=0)//**
                        {
                            if (reserva.mesLevant == mes && reserva.anoLevant == ano)
                            {
                                faturacao += reserva.totalPagar;
                            } 
                        }
                    }
                }
                printf("\nA faturação do mês %d/%d foi: %.2f€\n\n", mes, ano, faturacao);
            break;

            case 2:
                printf("Digite o ano que deseja a faturação:\n");
                scanf("%d", &ano);

                while (!feof(aReservas))
                {
                    contoleFread = fread(&reserva, sizeof(reserva), 1, aReservas);//**para evitar que mostre o ultimo registo 2 vezes
                    if (ferror(aReservas))//se retornar erro
                    {
                        printf("\aERRO! Arquivo não pode ser lido."); 
                    }
                    else
                    {
                        if (contoleFread !=0)//**
                        {
                            if (reserva.anoLevant == ano)
                            {
                                faturacao += reserva.totalPagar;
                            } 
                        }
                    }
                }
                printf("\nA faturação do ano %d foi: %.2f€\n\n", ano, faturacao);
            break;

            default:
            break;
        }
    }    
    //fechar arquivo

    if (!fclose(aReservas)) //se fechado com sucesso retorna 0
    {
        //se fechado com sucesso nao mostra nada
        
    }
    else
    {
        printf("\aERRO! O arquivo não pode ser fechado.");
    } 
}

//===================================== RELATORIOS
void relatorios()
{
    limpaEcra();
    linhaAdm();
    printf("                 RELATORIOS\n");

    printf("Digite:\n");
    printf("       1-Faturação mensal\n       2-Faturação anual\n");
    scanf("%d", &opcaoDashRel);
    fflush(stdin);

    switch (opcaoDashRel)
    {
    case 1:
        gerar_relatorios(opcaoDashRel);
        getchar();
        break;
    case 2:
        gerar_relatorios(opcaoDashRel);
        getchar();
        break;

    default:
        break;
    }
}