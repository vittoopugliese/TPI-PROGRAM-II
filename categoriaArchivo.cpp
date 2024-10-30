#include <iostream>
#include "categoria.h"
#include "categoriaArchivo.h"


CategoriaArchivo::CategoriaArchivo(const char *nombreArchivo) {
    strcpy(_nombreArchivo, nombreArchivo);
}

bool CategoriaArchivo::guardarArchivo(Categoria categoria) {
   FILE *p = fopen(_nombreArchivo, "ab");
   if (p==nullptr) return false;

   bool escribio = fwrite(&categoria, sizeof(Categoria), 1, p);
   fclose(p);

   return escribio;
 }

int CategoriaArchivo::contarRegistros() {
   Categoria categoria;
   FILE *p = fopen(_nombreArchivo, "rb");
   if (p==nullptr) return false;

   int contador = 0;
   while (fread (&categoria, sizeof(Categoria), 1,p)==1)
   {
     contador++;
   }
   fclose(p);
   return contador;
 }

 Categoria CategoriaArchivo::leerRegistro(int numero)
 {
   FILE *p = fopen(_nombreArchivo, "rb");
   if (p==nullptr) return Categoria();
   Categoria aux;

   fseek(p,numero*sizeof(Categoria), 0);
   fread(&aux, sizeof(Categoria), 1,p);
   fclose(p);
   return aux;
 }

 int CategoriaArchivo::buscar(int idCategoria)
 {
   int cantidad = contarRegistros();
   for (int i=0; i<cantidad; i++)
   {
     Categoria aux = leerRegistro(i);
     if (idCategoria == aux.getIdCategoria())
     {
       return i;
     }
   }
   return -1;
 }

 bool CategoriaArchivo::modificar(Categoria categoria, int pos)
 {
   FILE *p = fopen(_nombreArchivo, "rb+");
   if (p==nullptr) return false;

   fseek(p,pos*sizeof(categoria), 0);
   bool escribio = fwrite(&categoria, sizeof(Categoria), 1,p);
   fclose(p);
   return escribio;
 }

