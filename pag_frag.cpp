#include <iostream>
using namespace std;

const int MEM_SIZE  = 8192;
const int PAGE_SIZE = 1024;

int main() {

    cout << "[Inicializando] Simulador de Paginação & Fragmentação\n" << endl;

    // Memória dividida em 8 quadros de 1024 "bytes"
    int memoria[8] = {
        PAGE_SIZE, PAGE_SIZE, PAGE_SIZE, PAGE_SIZE,
        PAGE_SIZE, PAGE_SIZE, PAGE_SIZE, PAGE_SIZE
    };

    // Seus quadros começam desocupados
    bool ocupada[8] = {0};

    // Logo, nenhum processo tá associado a nenhum quadro
    int processo_alocado[8] = {0};

    int num_processos;
    cout << "Quantos processos pra hoje, chefe?\nDigite o número: ";
    cin >> num_processos;

    // Para cada processo...
    for (int i = 0; i < num_processos; ++i) {

        // Primeiro se mostra a tabela de paginação
        cout << "--[TABELA DE PÁGINA]--\n";
        cout << "|Quadro|Processo|Frag|\n";
        cout << "----------------------\n";
        for (int p = 0; p < 8; ++p) {
            cout << "| [" << p+1 << "]  |"
            << " {P" << processo_alocado[p] << "}   "
            << "|" << memoria[p] << "|"
            << "\n|--------------------|" << endl;
        }


        // é preciso saber seu tamanho,
        int tam_processo;
        cout << "Manda o tamanho do processo n° " << i + 1 << ", em bytes: ";
        cin >> tam_processo;

        // calcular quantas páginas ele vai tomar
        int paginas_necessarias = tam_processo / PAGE_SIZE;

        // e atribuí-lo às páginas
        for (int j = 0; j < paginas_necessarias; ++j) {
            
            bool pagina_livre_encontrada = false;

            for (int k = 0; k < 8; ++k) {
                
                if (!ocupada[k]) {
                    bool alocou_tudo = false;

                    if (tam_processo > PAGE_SIZE) {
                        tam_processo -= PAGE_SIZE;
                        memoria[k] = 0;
                    }
                    else {
                        memoria[k] -= tam_processo;
                        alocou_tudo = true;
                    }

                    ocupada[k] = true;
                    pagina_livre_encontrada = true;
                    processo_alocado[k] = i+1;
                    if (alocou_tudo) break;

                }
            }

            // Não tem como alocar o processo se não tem páginas suficientes pra ele
            if (!pagina_livre_encontrada) {
                cout << "Não deu pra alocar o processo n° " << i + 1 << "(falta de página).\n";
                break;
            }
        }
    }

    return 0;
}