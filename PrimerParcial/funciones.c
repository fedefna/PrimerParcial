#include "funciones.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


void inicializarEstados(eProductos lista[], int tam){
    for(int i=0; i<tam;i++){
        lista[i].estado=1;
    }
}

int obtenerEspacioLibre(eProductos lista[],int tam){
    int pos=-1;
    for (int i=0; i<tam;i++){
            if (lista[i].estado==1){
                pos = i;
                break;
            }
    }
    return pos;
}

int elegirProveedor(eProveedores proveedores[], int tam){
    int opcionElejida;
    printf("\nElija un proveedor:");
    for(int i=0;i<tam;i++){
        printf("\n%s: %d.",proveedores[i].descripcion,proveedores[i].codigoProveedor);
    }
    printf("\nOpcion:");
    fflush(stdin);
    scanf("%d",&opcionElejida);
    return opcionElejida;
}


void agregarProducto(eProductos lista[], int pos, int tam,eProveedores proveedores[], int tam2, int codigo){
    eProductos prod;

    printf("\nIngresar importe: ");
    scanf("%d",&prod.importe);
    printf("\nIngresar cantidad: ");
    scanf("%d",&prod.cantidad);
    fflush(stdin);
    printf("\nIngresar descripcion: ");
    fflush(stdin);
    gets(prod.descripcion);
    prod.idProveedor=elegirProveedor(proveedores,tam2);
    prod.estado=0;
    prod.codigoProducto=codigo;
    lista[pos]=prod;

    printf("\nEl producto ha sido ingresado.\n");

    system("pause");
    return codigo;
}

int buscarProducto(eProductos lista[],int tam,int codigo){
    int pos=-1;
    for(int i=0; i<tam;i++){
        if(lista[i].codigoProducto==codigo && lista[i].estado==0){
            pos=i;
            break;
        }
    }
    return pos;
}

void mostrarProducto(eProductos producto,eProveedores proveedores[],int tam){
    printf("\nCodigo: %d.\n",producto.codigoProducto);
    printf("Descripcion: %s.\n",producto.descripcion);
    printf("Cantidad: %d.\n",producto.cantidad);
    printf("Importe: $%d.\n",producto.importe);
    for(int i=0;i<tam;i++){
        if(producto.idProveedor==proveedores[i].codigoProveedor){
            printf("Proveedor: %s. \n",proveedores[i].descripcion);
            break;
        }
    }
}

void modificarProducto(eProductos lista[],int tam, eProveedores proveedores[], int tams){
    int codigo;
    printf("\nIngrese el codigo: ");
    scanf("%d",&codigo);

    int esta = buscarProducto(lista,tam,codigo);
    if(esta!=-1){
        mostrarProducto(lista[esta],proveedores,tams);
        int auxImporte;
        int auxCantidad;
        char auxDescripcion[50];
        char respuesta;
        printf("\nIngrese el nuevo importe: $");
        fflush(stdin);
        scanf("%d",&auxImporte);
        fflush(stdin);
        printf("\nIngrese la nueva cantidad: ");
        scanf("%d",&auxCantidad);
        fflush(stdin);
        printf("\nIngrese la nueva descripcion: ");
        gets(auxDescripcion);
        printf("\nEsta seguro que desea modificar el producto? (s/n): ");
        fflush(stdin);
        scanf("%c",&respuesta);
        if (respuesta=='s'){
            lista[esta].importe=auxImporte;
            lista[esta].cantidad=auxCantidad;
            strcpy (lista[esta].descripcion,auxDescripcion);
            printf("\nSe realizo la modificacion.");
        }else{
            printf("\nSe cancelo la modificacion.");
        }
    }else {
        printf("\nNo existe dicho legajo.");
    }
    system("pause");
}

void borrarProducto(eProductos lista[],int tam){
    int codigo;
    int aux=0;
    printf("\nIngresar el codigo del producto a borrar: ");
    scanf("%d",&codigo);
    for(int i=0; i<tam;i++){
        if (lista[i].codigoProducto==codigo && lista[i].estado==0){
            lista[i].estado=1;
            aux=1;
            printf("\nEl producto ha sido borrado.\n");
            break;
        }
    }
    if(aux==0){
        printf("\nNo se encontro un producto con el codigo ingresado.\n");
    }
    system("pause");
}

int mostrarImportes(eProductos lista[],int tam){
    int total=0;
    float promedio=0;
    int cant=0;
    for(int i=0;i<tam;i++){
        if(lista[i].estado==0){
            total=total+lista[i].importe;
            cant++;
        }
    }
    promedio=total/cant;
    printf("\nTotal: $%d.",total);
    printf("\nPromedio: $%.2f.",promedio);
    return promedio;
}

void mostrarProductosSuperanPromedio(eProductos lista[],int tam, int promedio){
    int cant=0;
    for(int i=0;i<tam;i++){
        if(lista[i].estado==0){
            if(lista[i].importe>promedio){
                cant++;
            }
        }
    }
    printf("\nCantidad de productos que superan el promedio: %d.",cant);
}

void mostrarProductosDebajoDelPromedio(eProductos lista[],int tam, int promedio){
    int cant=0;
    for(int i=0;i<tam;i++){
        if(lista[i].estado==0){
            if(lista[i].importe<promedio){
                cant++;
            }
        }
    }
    printf("\nCantidad de productos que NO superan el promedio: %d.",cant);
}

void mostrarStockMenorIgualDiez(eProductos lista[],int tam){
    int cant=0;
    for(int i=0;i<tam;i++){
        if(lista[i].estado==0){
            if(lista[i].cantidad<=10){
                cant++;
            }
        }
    }
    printf("Cantidad de productos con stock menor o igual a 10: %d.",cant);
}

void mostrarStockMayorDiez(eProductos lista[],int tam){
    int cant=0;
    for(int i=0;i<tam;i++){
        if(lista[i].estado==0){
            if(lista[i].cantidad>10){
                cant++;
            }
        }
    }
    printf("Cantidad de productos con stock mayor a 10: %d.\n",cant);
}

void mostrarInformes(eProductos lista[],int tam){
    printf("\n....************INFORMES************....\n");
    printf("\n....******Informe A******....\n");
    mostrarProductosSuperanPromedio(lista,tam,(mostrarImportes(lista,tam)));
    printf("\n\n******Informe B******\n");
    mostrarProductosDebajoDelPromedio(lista,tam,(mostrarImportes(lista,tam)));
    printf("\n\n******Informe C******\n");
    mostrarStockMenorIgualDiez(lista,tam);
    printf("\n\n******Informe D******\n");
    mostrarStockMayorDiez(lista,tam);
}

void listarProductosOrdenados(eProductos lista[],int tam){
    eProductos aux;
    for(int i=0; i<tam-1; i++){
        for(int j=i+1; j<tam; j++)
        {
            if(lista[i].importe>lista[j].importe)
            {
                aux = lista[i];
                lista[i] = lista[j];
                lista[j] = aux;
            }
            else
            {
                if(lista[i].importe == lista[j].importe)
                {
                    if(strcmp(lista[i].descripcion, lista[j].descripcion)>0)
                    {
                        aux = lista[i];
                        lista[i] = lista[j];
                        lista[j] = aux;
                    }
                }
            }
        }
    }
    printf("\nCodigo    Descripcion     Importe     Cantidad\n");
    for(int i=0;i<tam;i++){
        if(lista[i].estado==0){
            printf("%d         %s        $%d         %d\n",lista[i].codigoProducto,lista[i].descripcion,lista[i].importe,lista[i].cantidad);
        }
    }
}

void listarProdCantMenorIgualDiez(eProductos lista[],int tam){
    printf("\nCodigo    Descripcion     Importe     Cantidad\n");
    for(int i=0;i<tam;i++){
        if(lista[i].estado==0){
            if(lista[i].cantidad<=10){
                printf("%d         %s        $%d         %d\n",lista[i].codigoProducto,lista[i].descripcion,lista[i].importe,lista[i].cantidad);
            }
        }
    }
}

void listarProdCantMayorDiez(eProductos lista[],int tam){
    printf("\nCodigo    Descripcion     Importe     Cantidad\n");
    for(int i=0;i<tam;i++){
        if(lista[i].estado==0){
            if(lista[i].cantidad>10){
                printf("%d         %s        $%d         %d\n",lista[i].codigoProducto,lista[i].descripcion,lista[i].importe,lista[i].cantidad);
            }
        }
    }
}

void listarProductosSuperanPromedio(eProductos lista[],int tam, float promedio){
    printf("\nCodigo    Descripcion     Importe     Cantidad\n");
    for(int i=0;i<tam;i++){
        if(lista[i].estado==0){
            if(lista[i].importe>promedio){
                printf("%d         %s        $%d         %d\n",lista[i].codigoProducto,lista[i].descripcion,lista[i].importe,lista[i].cantidad);
            }
        }
    }
}

void listarProductosDebajoDelPromedio(eProductos lista[],int tam, float promedio){
    printf("\nCodigo    Descripcion     Importe     Cantidad\n");
    for(int i=0;i<tam;i++){
        if(lista[i].estado==0){
            if(lista[i].importe<promedio){
                printf("%d         %s        $%d         %d\n",lista[i].codigoProducto,lista[i].descripcion,lista[i].importe,lista[i].cantidad);
            }
        }
    }
}

void listarProveedores(eProductos lista[],int tam, eProveedores listaProv[], int tamProv){
    printf("\nDescripcion     Codigo\n");
    for(int i=0;i<tam;i++){
        if(lista[i].cantidad<=10){
            for(int j=0;j<tamProv;j++){
                if(listaProv[j].codigoProveedor==lista[i].idProveedor){
                    printf("\n%s     %d.",listaProv[j].descripcion,listaProv[j].codigoProveedor);
            }
            }
        }
    }
}

void listarProductosPorProveedor(eProductos lista[],int tam, eProveedores listaProv[], int tamProv){
    for(int j=0;j<tamProv;j++){
        printf("\nProveedor:%s Codigo:%d:",listaProv[j].descripcion,listaProv[j].codigoProveedor);
        printf("\nCodigo    Descripcion     Importe     Cantidad\n");
        for(int i=0;i<tam;i++){
            if(listaProv[j].codigoProveedor==lista[i].idProveedor){
                printf("%d         %s        $%d         %d\n",lista[i].codigoProducto,lista[i].descripcion,lista[i].importe,lista[i].cantidad);
            }
        }
    }
}

void listarProductosSegunProveedor(eProductos lista[],int tam, eProveedores listaProv[], int tamProv){
    printf("\nLista de prodcutos segun proveedor seleccionado:\n");
    int idProveedor = elegirProveedor(listaProv,tamProv);
    printf("\nCodigo    Descripcion     Importe     Cantidad\n");
    for(int i=0;i<tam;i++){
        if(idProveedor==lista[i].idProveedor){
            printf("%d         %s        $%d         %d\n",lista[i].codigoProducto,lista[i].descripcion,lista[i].importe,lista[i].cantidad);
        }
    }
}

void listarProveedorConMasProductos(eProductos lista[],int tam, eProveedores listaProv[], int tamProv){
    int max;
    int codProv;
    int codProvMax;
    int flag=0;
    for(int j=0;j<tamProv;j++){
        int cant=0;
        for(int i=0;i<tam;i++){
            if(listaProv[j].codigoProveedor==lista[i].idProveedor){
                cant++;
                codProv=lista[i].idProveedor;
            }
        }
        if(cant>max || flag==0){
            flag=1;
            max=cant;
            codProvMax=codProv;
        }
    }
    printf("\nCodigo de proveedor con mas productos: %d:\n",codProvMax);
    printf("\nCodigo    Descripcion     Importe     Cantidad\n");
    for(int i=0;i<tam;i++){
        if(codProvMax==lista[i].idProveedor){
            printf("%d         %s        $%d         %d\n",lista[i].codigoProducto,lista[i].descripcion,lista[i].importe,lista[i].cantidad);
        }
    }
}

void listarProveedorConMenosProductos(eProductos lista[],int tam, eProveedores listaProv[], int tamProv){
    int min;
    int codProv;
    int codProvMin;
    int flag=0;
    for(int j=0;j<tamProv;j++){
        int cant=0;
        for(int i=0;i<tam;i++){
            if(listaProv[j].codigoProveedor==lista[i].idProveedor){
                cant++;
                codProv=lista[i].idProveedor;
            }
        }
        if(cant<min || flag==0){
            flag=1;
            min=cant;
            codProvMin=codProv;
        }
    }
    printf("\nCodigo de proveedor con menos productos: %d:\n",codProvMin);
    printf("\nCodigo    Descripcion     Importe     Cantidad\n");
    for(int i=0;i<tam;i++){
        if(codProvMin==lista[i].idProveedor){
            printf("%d         %s        $%d         %d\n",lista[i].codigoProducto,lista[i].descripcion,lista[i].importe,lista[i].cantidad);
        }
    }
}

void listarProveedorConProductoMasCaro(eProductos lista[],int tam, eProveedores listaProv[], int tamProv){
    int precioProdMasCaro;
    int flag=0;
    int codProvMasCaro;
    for(int i=0;i<tam;i++){
        if(precioProdMasCaro<lista[i].importe || flag==0){
            flag=1;
            precioProdMasCaro=lista[i].importe;
            codProvMasCaro=lista[i].idProveedor;
        }
    }
    printf("\nCodigo de proveedor con producto mas caro: %d:\n",codProvMasCaro);
    printf("\nCodigo    Descripcion     Importe     Cantidad\n");
    for(int i=0;i<tam;i++){
        if(codProvMasCaro==lista[i].idProveedor && precioProdMasCaro==lista[i].importe){
            printf("%d         %s        $%d         %d\n",lista[i].codigoProducto,lista[i].descripcion,lista[i].importe,lista[i].cantidad);
        }
    }
}

void listarProveedorConProductoMasBarato(eProductos lista[],int tam, eProveedores listaProv[], int tamProv){
    int precioProdMasBarato;
    int flag=0;
    int codProvMasBarato;
    for(int i=0;i<tam;i++){
        if(precioProdMasBarato>lista[i].importe || flag==0){
            flag=1;
            precioProdMasBarato=lista[i].importe;
            codProvMasBarato=lista[i].idProveedor;
        }
    }
    printf("\nCodigo de proveedor con producto mas barato: %d:\n",codProvMasBarato);
    printf("\nCodigo    Descripcion     Importe     Cantidad\n");
    for(int i=0;i<tam;i++){
        if(codProvMasBarato==lista[i].idProveedor && precioProdMasBarato==lista[i].importe){
            printf("%d         %s        $%d         %d\n",lista[i].codigoProducto,lista[i].descripcion,lista[i].importe,lista[i].cantidad);
        }
    }
}

void listar(eProductos lista[],int tam, eProveedores listaProv[], int tamProv){
    //obtengo el promedio de los importes de los productos activos
    int total=0;
    float promedio=0;
    int cant=0;
    for(int i=0;i<tam;i++){
        if(lista[i].estado==0){
            total=total+lista[i].importe;
            cant++;
        }
    }
    promedio=total/cant;

    printf("\n....************LISTAR************....\n");
    printf("\n....******Listar A******....\n");
    listarProductosOrdenados(lista,tam);
    printf("\n....******Listar B******....\n");
    listarProdCantMenorIgualDiez(lista,tam);
    printf("\n....******Listar C******....\n");
    listarProdCantMayorDiez(lista,tam);
    printf("\n....******Listar D******....\n");
    listarProductosSuperanPromedio(lista,tam,promedio);
    printf("\n....******Listar E******....\n");
    listarProductosDebajoDelPromedio(lista,tam,promedio);
    printf("\n....******Listar F******....\n");
    listarProveedores(lista,tam,listaProv,tamProv);
    printf("\n....******Listar G******....\n");
    listarProductosPorProveedor(lista,tam,listaProv,tamProv);
    printf("\n....******Listar H******....\n");
    listarProductosSegunProveedor(lista,tam,listaProv,tamProv);
    printf("\n....******Listar I******....\n");
    listarProveedorConMasProductos(lista,tam,listaProv,tamProv);
    printf("\n....******Listar J******....\n");
    listarProveedorConMenosProductos(lista,tam,listaProv,tamProv);
    printf("\n....******Listar K******....\n");
    listarProveedorConProductoMasCaro(lista,tam,listaProv,tamProv);
    printf("\n....******Listar L******....\n");
    listarProveedorConProductoMasBarato(lista,tam,listaProv,tamProv);
}
