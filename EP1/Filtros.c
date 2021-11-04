/*
 * DCE05968 - Estruturas de Dados I
 * Funções responsaveis pelos filtros que podem ser aplicados na imagem.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "Imagem.h"  /* Tipos e protótipos de funções que manipulam imagens */
#include "Filtros.h" /* Protótipo das funções responsáveis pelos filtros das imagens */

/* Função responsável por escurecer uma imagem
 * A função recebe um ponteiro para um struct Imagem e altera/escurece
 * cada um de seus pixels em cada canal de cor (RGB).
 *
 * Analise essa função com bastante atenção. Ela irá te auxiliar no entendimento
 * do TAD Imagem e como outros filtros podem ser implementados.
 *
 * Você não precisa modificar essa função
 */
void escurecerImagem(Imagem *img){
    int v;
    printf("Digite o fator de escurecimento: ");
    scanf("%d", &v);
    /* Cada canal de cor (RGB) de cada pixel é reduzido 'v' do valor.
     * Note que devemos garantir que o valor esteja entre 0 e 255.
     * Como estamos subtraindo, verificamos apenas se o valor é >= 0
     * Note também a utilização de expressão ternária e o cast (conversão)
     * entre os valores Byte (unsigned int) e int. Esse cast evita erros nas
     * operações matemáticas.
     */
    for (int h = 0; h < obtemAltura(img); h++) {
        for (int w = 0; w < obtemLargura(img); w++) {
            //Obtém o pixel da posição (h, w) da imagem
            Pixel pixel = obtemPixel(img, h, w);
            //Modifica cada canal de cor do pixel
            pixel.cor[RED]   = (((int)pixel.cor[RED] - v) >= 0 ? ((int)pixel.cor[RED] - v) : 0);
            pixel.cor[GREEN] = (((int)pixel.cor[GREEN] - v) >= 0 ? ((int)pixel.cor[GREEN] - v) : 0);
            pixel.cor[BLUE]  = (((int)pixel.cor[BLUE] - v) >= 0 ? ((int)pixel.cor[BLUE] - v) : 0);
            //Grava o novo pixel na posição (h, w) da imagem
            recolorePixel(img, h, w, pixel);
        }
    }
}

/* Função responsável por clarear uma imagem
 * A função recebe um ponteiro para um struct Imagem e altera/clareia
 * cada um de seus pixels em cada canal de cor (RGB).
 */
void clarearImagem(Imagem *img){
    int v;
    printf("Digite o fator de clareamento: ");
    scanf("%d", &v);
    for (int h = 0; h < obtemAltura(img); h++) {
        for (int w = 0; w < obtemLargura(img); w++) {
            //Obtém o pixel da posição (h, w) da imagem
            Pixel pixel = obtemPixel(img, h, w);
            //Modifica cada canal de cor do pixel
            pixel.cor[RED]   = (((int)pixel.cor[RED] + v) <= 255 ? ((int)pixel.cor[RED] + v) : 255);
            pixel.cor[GREEN] = (((int)pixel.cor[GREEN] + v) <= 255 ? ((int)pixel.cor[GREEN] + v) : 255);
            pixel.cor[BLUE]  = (((int)pixel.cor[BLUE] + v) <= 255 ? ((int)pixel.cor[BLUE] + v) : 255);
            //Grava o novo pixel na posição (h, w) da imagem
            recolorePixel(img, h, w, pixel);
        }
    }
}

/* Função responsável por converter uma imagem colorida em escala de cinza
 * A função recebe um ponteiro para um struct Imagem e converte
 * cada um de seus pixels em cada canal de cor (RGB) em uma tonalidade de cinza.
 *
 * No pdf de descrição do EP existem duas estretégias para a implementação
 * desse filtro. Você deve implementar uma delas ou pesquisar por outras alternativas.
 */
void escalaDeCinzaImagem(Imagem *img){
    for (int h = 0; h < obtemAltura(img); h++) {
        for (int w = 0; w < obtemLargura(img); w++) {
            //Obtém o pixel da posição (h, w) da imagem
            Pixel pixel = obtemPixel(img, h, w);
            //Modifica cada canal de cor do pixel
            int fatorEscalaCinza = ((0.3*(int)pixel.cor[RED]+0.59*(int)pixel.cor[GREEN]+0.11*(int)pixel.cor[BLUE]));
            pixel.cor[RED]   = fatorEscalaCinza;
            pixel.cor[GREEN] = fatorEscalaCinza;
            pixel.cor[BLUE]  = fatorEscalaCinza;
            //Grava o novo pixel na posição (h, w) da imagem
            recolorePixel(img, h, w, pixel);
        }
    }
}

/* Função responsável por aplicar o filtro de Sobel na imagem.
 * Leia o pdf do EP para obter mais informações de como o filtro é implementado.
 */
void filtroSobel(Imagem *img){

    Imagem *copia = copiaImagem(img);
    int h = obtemAltura(copia);
    int w = obtemLargura(copia);

    int fatorGy;
    int fatorGx;
    int magnitude;

    Pixel newPixel;
    Pixel new1, new2, new3, new4, new5, new6;

    for(int i=1; i<h-1; i++){
        for(int j=1; j<w-1; j++){
            new1 = obtemPixel(copia,i-1,j-1);
            fatorGy = 1 * (int)new1.cor[RED];
            new2 = obtemPixel(copia,i-1,j);
            fatorGy += 2 * (int)new2.cor[RED];
            new3 = obtemPixel(copia,i-1,j+1);
            fatorGy += 1 * (int)new3.cor[RED];
            new4 = obtemPixel(copia,i+1,j-1);
            fatorGy += (-1) * (int)new4.cor[RED];
            new5 = obtemPixel(copia,i+1,j);
            fatorGy += (-2) * (int)new5.cor[RED];
            new6 = obtemPixel(copia,i+1,j+1);
            fatorGy += (-1) * (int)new6.cor[RED];

            new1 = obtemPixel(copia,i-1,j-1);
            fatorGx = 1 * (int)new1.cor[RED];
            new2 = obtemPixel(copia,i,j-1);
            fatorGx += 2 * (int)new2.cor[RED];
            new3 = obtemPixel(copia,i+1,j-1);
            fatorGx += 1 * (int)new3.cor[RED];
            new4 = obtemPixel(copia,i-1,j+1);
            fatorGx += (-1) * (int)new4.cor[RED];
            new5 = obtemPixel(copia,i,j+1);
            fatorGx += (-2) * (int)new5.cor[RED];
            new6 = obtemPixel(copia,i+1,j+1);
            fatorGx += (-1) * (int)new6.cor[RED];

            magnitude = sqrt(pow(fatorGx,2) + pow(fatorGy,2));

            if(magnitude <= 0)
                magnitude = 0;
            else if(magnitude >= 255)
                magnitude = 255;

            newPixel.cor[RED] = (Byte)magnitude;

            new1 = obtemPixel(copia,i-1,j-1);
            fatorGy = 1 * (int)new1.cor[GREEN];
            new2 = obtemPixel(copia,i-1,j);
            fatorGy += 2 * (int)new2.cor[GREEN];
            new3 = obtemPixel(copia,i-1,j+1);
            fatorGy += 1 * (int)new3.cor[GREEN];
            new4 = obtemPixel(copia,i+1,j-1);
            fatorGy += (-1) * (int)new4.cor[GREEN];
            new5 = obtemPixel(copia,i+1,j);
            fatorGy += (-2) * (int)new5.cor[GREEN];
            new6 = obtemPixel(copia,i+1,j+1);
            fatorGy += (-1) * (int)new6.cor[GREEN];

            new1 = obtemPixel(copia,i-1,j-1);
            fatorGx = 1 * (int)new1.cor[GREEN];
            new2 = obtemPixel(copia,i,j-1);
            fatorGx += 2 * (int)new2.cor[GREEN];
            new3 = obtemPixel(copia,i+1,j-1);
            fatorGx += 1 * (int)new3.cor[GREEN];
            new4 = obtemPixel(copia,i-1,j+1);
            fatorGx += (-1) * (int)new4.cor[GREEN];
            new5 = obtemPixel(copia,i,j+1);
            fatorGx += (-2) * (int)new5.cor[GREEN];
            new6 = obtemPixel(copia,i+1,j+1);
            fatorGx += (-1) * (int)new6.cor[GREEN];

            magnitude = sqrt(pow(fatorGx,2) + pow(fatorGy,2));

            if(magnitude <= 0)
                magnitude = 0;
            else if(magnitude >= 255)
                magnitude = 255;

            newPixel.cor[GREEN] = (Byte)magnitude;

            new1 = obtemPixel(copia,i-1,j-1);
            fatorGy = 1 * (int)new1.cor[BLUE];
            new2 = obtemPixel(copia,i-1,j);
            fatorGy += 2 * (int)new2.cor[BLUE];
            new3 = obtemPixel(copia,i-1,j+1);
            fatorGy += 1 * (int)new3.cor[BLUE];
            new4 = obtemPixel(copia,i+1,j-1);
            fatorGy += (-1) * (int)new4.cor[BLUE];
            new5 = obtemPixel(copia,i+1,j);
            fatorGy += (-2) * (int)new5.cor[BLUE];
            new6 = obtemPixel(copia,i+1,j+1);
            fatorGy += (-1) * (int)new6.cor[BLUE];

            new1 = obtemPixel(copia,i-1,j-1);
            fatorGx = 1 * (int)new1.cor[BLUE];
            new2 = obtemPixel(copia,i,j-1);
            fatorGx += 2 * (int)new2.cor[BLUE];
            new3 = obtemPixel(copia,i+1,j-1);
            fatorGx += 1 * (int)new3.cor[BLUE];
            new4 = obtemPixel(copia,i-1,j+1);
            fatorGx += (-1) * (int)new4.cor[BLUE];
            new5 = obtemPixel(copia,i,j+1);
            fatorGx += (-2) * (int)new5.cor[BLUE];
            new6 = obtemPixel(copia,i+1,j+1);
            fatorGx += (-1) * (int)new6.cor[BLUE];

            magnitude = sqrt(pow(fatorGx,2) + pow(fatorGy,2));

            if(magnitude <= 0)
                magnitude = 0;
            else if(magnitude >= 255)
                magnitude = 255;

            newPixel.cor[BLUE] = (Byte)magnitude;
            recolorePixel(img,i,j,newPixel);
            }
        }
    liberaImagem(copia);
}

/* Função responsável por aplicar a detecçõa de bordas de Laplace na imagem.
 * Leia o pdf do EP para obter mais informações de como o filtro é implementado.
 */
void deteccaoBordasLaplace(Imagem *img) {
    Imagem *copia = copiaImagem(img);
    int h = obtemAltura(copia);
    int w = obtemLargura(copia);

    int fatorLaplace;

    Pixel newPixel;
    Pixel new1, new2, new3, new4, new5;

    for(int i=1; i<h-1; i++){
        for(int j=1; j<w-1; j++){
            new1 = obtemPixel(copia,i-1,j);
            fatorLaplace = (-1) * (int)new1.cor[RED];
            new2 = obtemPixel(copia,i,j-1);
            fatorLaplace += (-1) * (int)new2.cor[RED];
            new3 = obtemPixel(copia,i,j);
            fatorLaplace += (4) * (int)new3.cor[RED];
            new4 = obtemPixel(copia,i,j+1);
            fatorLaplace += (-1) * (int)new4.cor[RED];
            new5 = obtemPixel(copia,i+1,j);
            fatorLaplace += (-1) * (int)new5.cor[RED];

            if(fatorLaplace <= 0)
                fatorLaplace = 0;
            else if(fatorLaplace >= 255)
                fatorLaplace = 255;

            newPixel.cor[RED] = (Byte)fatorLaplace;

            new1 = obtemPixel(copia,i-1,j);
            fatorLaplace = (-1) * (int)new1.cor[GREEN];
            new2 = obtemPixel(copia,i,j-1);
            fatorLaplace += (-1) * (int)new2.cor[GREEN];
            new3 = obtemPixel(copia,i,j);
            fatorLaplace += (4) * (int)new3.cor[GREEN];
            new4 = obtemPixel(copia,i,j+1);
            fatorLaplace += (-1) * (int)new4.cor[GREEN];
            new5 = obtemPixel(copia,i+1,j);
            fatorLaplace += (-1) * (int)new5.cor[GREEN];

            if(fatorLaplace <= 0)
                fatorLaplace = 0;
            else if(fatorLaplace >= 255)
                fatorLaplace = 255;

            newPixel.cor[GREEN] = (Byte)fatorLaplace;

            new1 = obtemPixel(copia,i-1,j);
            fatorLaplace = (-1) * (int)new1.cor[BLUE];
            new2 = obtemPixel(copia,i,j-1);
            fatorLaplace += (-1) * (int)new2.cor[BLUE];
            new3 = obtemPixel(copia,i,j);
            fatorLaplace += (4) * (int)new3.cor[BLUE];
            new4 = obtemPixel(copia,i,j+1);
            fatorLaplace += (-1) * (int)new4.cor[BLUE];
            new5 = obtemPixel(copia,i+1,j);
            fatorLaplace += (-1) * (int)new5.cor[BLUE];

            if(fatorLaplace <= 0)
                fatorLaplace = 0;
            else if(fatorLaplace >= 255)
                fatorLaplace = 255;

            newPixel.cor[BLUE] = (Byte)fatorLaplace;
            recolorePixel(img,i,j,newPixel);
        }
    }
    liberaImagem(copia);
}

/* Função responsável por aplicar na imagem o filtro definido por você. Seja criativo!
 * Filtros que apenas fazem algumas modificações simples em cada pixel
 * (por exemplo, negativo, espelhar a imagem) não serão considerados.
 */

void meuFiltro(Imagem *img){

    Imagem *copia = copiaImagem(img);
    Imagem *copiaSV = copiaImagem(img);

    /* DEIXA A IMAGEM ORIGINAL EM ESCALA DE CINZA */
    for (int h = 0; h < obtemAltura(copia); h++) {
        for (int w = 0; w < obtemLargura(copia); w++) {
            //Obtém o pixel da posição (h, w) da imagem
            Pixel pixel = obtemPixel(copia, h, w);
            //Modifica cada canal de cor do pixel
            int fatorEscalaCinza = ((0.3*(int)pixel.cor[RED]+0.59*(int)pixel.cor[GREEN]+0.11*(int)pixel.cor[BLUE]));
            pixel.cor[RED]   = fatorEscalaCinza;
            pixel.cor[GREEN] = fatorEscalaCinza;
            pixel.cor[BLUE]  = fatorEscalaCinza;
            //Grava o novo pixel na posição (h, w) da imagem
            recolorePixel(img, h, w, pixel);
        }
    }

    for (int h = 0; h < obtemAltura(copia); h++){
        for (int w = 5; w < obtemLargura(copia); w++){
            Pixel pixel = obtemPixel(copia, h, w-5);
            pixel.cor[RED] = 0;
            recolorePixel(copiaSV,h,w,pixel);
        }
    }

    for (int h = 0; h < obtemAltura(copia); h++){
        for (int w = 5; w < obtemLargura(copia); w++){

            Pixel pixelEscalaCinza = obtemPixel(img, h, w);
            Pixel newPixel = obtemPixel(copiaSV, h, w-5);

            pixelEscalaCinza.cor[GREEN] = newPixel.cor[GREEN];
            pixelEscalaCinza.cor[BLUE] = newPixel.cor[GREEN];

            recolorePixel(img, h, w, pixelEscalaCinza);
        }
    }

    Imagem *copiaSG = copiaImagem(copia);

    for (int h = 0; h < obtemAltura(copia); h++){
        for (int w =10; w < obtemLargura(copia); w++){
            Pixel pixel = obtemPixel(copia, h, w-10);
            pixel.cor[GREEN] = 0;
            recolorePixel(copiaSG,h,w,pixel);
        }
    }

    for (int h = 0; h < obtemAltura(copia); h++){
        for (int w = 10; w < obtemLargura(copia); w++){

            Pixel pixelEscalaCinza = obtemPixel(img, h, w);
            Pixel newPixel = obtemPixel(copiaSG, h, w-10);

            pixelEscalaCinza.cor[RED] = newPixel.cor[BLUE];
            pixelEscalaCinza.cor[BLUE] = newPixel.cor[BLUE];

            recolorePixel(img, h, w, pixelEscalaCinza);
        }
    }

    liberaImagem(copiaSG);
    liberaImagem(copiaSV);
    liberaImagem(copia);
}

void glitchRAB(Imagem *img){

    /* FILTRO GLITCH PRETO E BRANCO */
    Imagem *copia = copiaImagem(img);
    Imagem *copiaSV = copiaImagem(img);

    /* DEIXA A IMAGEM ORIGINAL EM ESCALA DE CINZA */
    for (int h = 0; h < obtemAltura(copia); h++) {
        for (int w = 0; w < obtemLargura(copia); w++) {
            //Obtém o pixel da posição (h, w) da imagem
            Pixel pixel = obtemPixel(copia, h, w);
            //Modifica cada canal de cor do pixel
            int fatorEscalaCinza = ((0.3*(int)pixel.cor[RED]+0.59*(int)pixel.cor[GREEN]+0.11*(int)pixel.cor[BLUE]));
            pixel.cor[RED]   = fatorEscalaCinza;
            pixel.cor[GREEN] = fatorEscalaCinza;
            pixel.cor[BLUE]  = fatorEscalaCinza;
            //Grava o novo pixel na posição (h, w) da imagem
            recolorePixel(img, h, w, pixel);
        }
    }

    for (int h = 0; h < obtemAltura(copia); h++){
        for (int w = 5; w < obtemLargura(copia); w++){
            Pixel pixel = obtemPixel(copia, h, w-5);
            pixel.cor[RED] = 0;
            recolorePixel(copiaSV,h,w,pixel);
        }
    }

    for (int h = 0; h < obtemAltura(copia); h++){
        for (int w = 5; w < obtemLargura(copia); w++){

            Pixel pixelEscalaCinza = obtemPixel(img, h, w);
            Pixel newPixel = obtemPixel(copiaSV, h, w-5);

            pixelEscalaCinza.cor[GREEN] = newPixel.cor[GREEN];
            pixelEscalaCinza.cor[BLUE] = newPixel.cor[GREEN];

            recolorePixel(img, h, w, pixelEscalaCinza);
        }
    }


    liberaImagem(copiaSV);
    liberaImagem(copia);
}


void glitchGAM(Imagem *img){
    /* FILTRO GLITCH VERDE E ROXO */
    Imagem *copia = copiaImagem(img);
    Imagem *copiaSG = copiaImagem(img);

    /* DEIXA A IMAGEM ORIGINAL EM ESCALA DE CINZA */
    for (int h = 0; h < obtemAltura(copia); h++) {
        for (int w = 0; w < obtemLargura(copia); w++) {
            //Obtém o pixel da posição (h, w) da imagem
            Pixel pixel = obtemPixel(copia, h, w);
            //Modifica cada canal de cor do pixel
            int fatorEscalaCinza = ((0.3*(int)pixel.cor[RED]+0.59*(int)pixel.cor[GREEN]+0.11*(int)pixel.cor[BLUE]));
            pixel.cor[RED]   = fatorEscalaCinza;
            pixel.cor[GREEN] = fatorEscalaCinza;
            pixel.cor[BLUE]  = fatorEscalaCinza;
            //Grava o novo pixel na posição (h, w) da imagem
            recolorePixel(img, h, w, pixel);
        }
    }

    for (int h = 0; h < obtemAltura(copia); h++){
        for (int w = 5; w < obtemLargura(copia); w++){
            Pixel pixel = obtemPixel(copia, h, w-5);
            pixel.cor[GREEN] = 0;
            recolorePixel(copiaSG,h,w,pixel);
        }
    }

    for (int h = 0; h < obtemAltura(copia); h++){
        for (int w = 5; w < obtemLargura(copia); w++){

            Pixel pixelEscalaCinza = obtemPixel(img, h, w);
            Pixel newPixel = obtemPixel(copiaSG, h, w-5);

            pixelEscalaCinza.cor[RED] = newPixel.cor[BLUE];
            pixelEscalaCinza.cor[BLUE] = newPixel.cor[BLUE];

            recolorePixel(img, h, w, pixelEscalaCinza);
        }
    }

    liberaImagem(copiaSG);
    liberaImagem(copia);
}
