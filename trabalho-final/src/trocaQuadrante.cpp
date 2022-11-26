/*
 * =====================================================================================
 *
 *       Filename:  trocaQuadrante.cpp
 *
 *    Description:  -
 *
 *        Version:  1.0
 *        Created:  26/11/2022 07:45:24
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Isaac Vinicius, Hugo Bessa
 *                  isaacvinicius2121@alu.ufc.br, hugobessa@alu.ufc.br
 *   Organization:  UFC-Quixadá
 *
 * =====================================================================================
 */

#include <bits/stdc++.h>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "../inc/trocaQuadrante.hpp"


/*Funcao que recebe uma imagem transformada para melhor visualizacao do espectro de magnitude*/
void trocaQuadrantes(cv::Mat &image){
    
    cv::Mat aux, A, B, C, D;

    // se a imagem tiver tamanho impar, recorta a regiao para o maior
    // tamanho par possivel (-2 = 1111...1110)
    image = image(cv::Rect(0, 0, image.cols & -2, image.rows & -2));

    int centerX = image.cols / 2;
    int centerY = image.rows / 2;

    /*rearranja os quadrantes da transformada de Fourier de forma que a origem fique no centro da imagem
    A B -> D C
    C D -> B A
    */

    A = image(cv::Rect(0, 0, centerX, centerY));
    B = image(cv::Rect(centerX, 0, centerX, centerY));
    C = image(cv::Rect(0, centerY, centerX, centerY));
    D = image(cv::Rect(centerX, centerY, centerX, centerY));

    /*troca quadrantes: (superior esquerdo com inferior direito)*/
    A.copyTo(aux);
    D.copyTo(A);
    aux.copyTo(D);

    /*
    A B -> D C
    C D -> B A
    */
    /*troca quadrantes: (superior direito com inferior esquerdo)*/
    C.copyTo(aux);
    B.copyTo(C);
    aux.copyTo(B);
}