#include "Operacion.h"
#include "SistemaBCR.h"
#include "EntidadBancaria.h"
#include "Transportadora.h"
#include "Plaza.h"
#include "Boveda.h"
#include <iostream>

int main() {
    Plaza* arequipa = new Plaza("Arequipa");

    Transportadora* hermes = new Transportadora("Hermes");

    EntidadBancaria* bcp = new EntidadBancaria("BCP");
    EntidadBancaria* interbank = new EntidadBancaria("Interbank");

    bcp->agregarBoveda(new Boveda(arequipa));
    interbank->agregarBoveda(new Boveda(arequipa));

    SistemaBCR sistema;

    Operacion* op1 = new Operacion("08/05/2025", "entrega", bcp, interbank, hermes, arequipa,
                                   10, 20, 15, 5, 0, 3, 2);
    op1->aplicar();
    sistema.registrarOperacion(op1);

    Operacion* op2 = new Operacion("08/05/2025", "recojo", interbank, bcp, hermes, arequipa,
                                   5, 10, 5, 2, 1, 1, 0);
    op2->aplicar();
    sistema.registrarOperacion(op2);

    sistema.calcularSaldoBCR("08/05/2025");
    sistema.mostrarInformePorTipoMonedaYBien("08/05/2025");

    return 0;
}
