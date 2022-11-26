/*
 * =====================================================================================
 *
 *       Filename:  filtro.cpp
 *
 *    Description:  -
 *
 *        Version:  1.0
 *        Created:  26/11/2022 07:42:05
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
#include "../inc/filtro.hpp"

/*funcao responsavel por criar o filtro de frequencia, passando a imagem trasnformada e o destino*/
void makeFilter(const cv::Mat &image, cv::Mat &filter){
    cv::Mat_<float> filter2D(image.rows, image.cols);
    int centerX = image.cols / 2;
    int centerY = image.rows / 2;
    int radius = 20;
    /*aplica o valor 1 no centro da imagem ate 20 pixels*/
    for(int i = 0; i < image.rows; i++){
        for(int j = 0; j < image.cols; j++){
            if(pow(i - centerY, 2) + pow(j - centerX, 2) <= pow(radius, 2)){
                filter2D.at<float>(i, j) = 1;
            }else{
                filter2D.at<float>(i, j) = 0;
            }
        }
    }
    /*criacao do vetor de matriz com dois canais: parte real e imaginaria*/
    cv::Mat planes[] = {cv::Mat_<float>(filter2D), cv::Mat::zeros(filter2D.size(), CV_32F)};

    /*combinando os canais em uma unica estrutura de dados complexa (numero complexo)*/
    cv::merge(planes, 2, filter);
}
