/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  Uma aplicacao usando a Transformada de Fourier em Processamento de Imagens
 *
 *        Version:  1.0
 *        Created:  21/11/2022 20:06:37
 *       Revision:  none
 *       Compiler:  g++
 *
 *         Author:  Isaac Vinicius, Hugo Bessa 
 *                  isaacvinicius2121@alu.ufc.br, hugobessa@alu.ufc.br
 *   Organization:  UFC-Quixadá
 *
 * =====================================================================================
 */

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <bits/stdc++.h>
#include "../inc/trocaQuadrante.hpp"
#include "../inc/filtro.hpp"

int main(int argc, char **argv){

  /*Carregando imagem a ser usada no trabalho e fazendo a leitura da mesma*/
  std::string path1 = "./img/teste2.jpg";
  cv::Mat img1 = cv::imread(path1);

  // verificando se o caminho foi especificado corretamente, caso nao tenha, encerre
  if(img1.empty()){
    std::cout << "Imagem nao encontrada!" << "\n";
    return -1;
  }

  /*Caso a imagem seja grande, fazer o redimensionamento para ser usada na aplicacao*/
  cv::Mat imagem_redimensionada;
  cv::resize(img1, imagem_redimensionada, cv::Size(img1.size().width / 2, img1.size().height / 2));

  /*Carregando a imagem em formato de escala de tons de cinza*/
  cv::cvtColor(imagem_redimensionada, imagem_redimensionada, cv::COLOR_BGR2GRAY);

 /*-----------------------------------------------------------------------------
  *  APLICACAO COM A TRANSFORMADA DE FOURIER
  *-----------------------------------------------------------------------------*/

  /*expandindo a imagem para uma melhor eficiencia do DFT*/
  /*Para tamanhos de imagem que sao multiplos dos digitos dois, tres e cinco, e o mais rapido*/
  int dft_linha = cv::getOptimalDFTSize(imagem_redimensionada.rows);
  int dft_coluna = cv::getOptimalDFTSize(imagem_redimensionada.cols);

  cv::Mat preenchimento_borda;
  /*array que sera usado para passar os canais (real e imaginaria) do espectro*/
  std::vector<cv::Mat> planos_espectro;
  cv::Mat img_complexa;

  /*função para expandir as bordas de uma imagem (os pixels anexados são inicializados com zero)*/
  cv::copyMakeBorder(imagem_redimensionada, preenchimento_borda, 0, dft_linha - imagem_redimensionada.rows, 0, dft_coluna - imagem_redimensionada.cols, cv::BORDER_CONSTANT, cv::Scalar::all(0));

  /*parte real contendo a imagem de entrada, no caso a imagem que foi preenchida com zeros*/
  planos_espectro.push_back(cv::Mat_<float>(preenchimento_borda));
  /*parte imaginaria com valores nulos*/
  planos_espectro.push_back(cv::Mat::zeros(preenchimento_borda.size(), CV_32F));

  /*combinando os planos_espectro (canais), em uma unica estrutura de dados complexa (numero complexo)*/
  cv::merge(planos_espectro, img_complexa);

  /*armazena o resultado da DFT*/
  cv::Mat dft_saida;

  /*calculando a Transformada Discreta de Fourier da matriz*/
  cv::dft(img_complexa, dft_saida, cv::DFT_COMPLEX_OUTPUT);
  trocaQuadrantes(dft_saida);
  cv::split(dft_saida, planos_espectro);

  /*recebem o valor do calculo do espectro de magnitude*/
  cv::Mat dft_magn_imagem;

  /*Calculando o espectro de magnitudes de um campo vetorial bidimensional*/
  /*            real[0], imaginario[1]*/
  cv::magnitude(planos_espectro[0], planos_espectro[1], dft_magn_imagem);
  dft_magn_imagem += cv::Scalar::all(1);

  /*valores altos irao aparecer como pontos brancos, e valores baixos como pontos pretos.
  Convertendo a escala linear em logaritmica para usar os valores da escala de cinza para vizualizacao*/
  cv::log(dft_magn_imagem, dft_magn_imagem);

  /*Realizando a normalizacao(contraste) para vizualizar melhor*/
  cv::normalize(dft_magn_imagem, dft_magn_imagem, 0, 1, cv::NORM_MINMAX);

  cv::imshow("Original", imagem_redimensionada);
  cv::imshow("Espectro de magnitude", dft_magn_imagem);

 /*-----------------------------------------------------------------------------
  *  FILTRAGEM NO DOMINIO DA FREQUENCIA: REDUZIR O RUIDO DA IMAGEM
  *-----------------------------------------------------------------------------*/

  /*array que sera usado para passar os canais (real e imaginaria) da filtragem de frequencia*/
  std::vector<cv::Mat> planos_filtro;
  cv::Mat img_complexa_filtro;

  /*parte real contendo a imagem de entrada, no caso a imagem que foi preenchida com zeros*/
  planos_filtro.push_back(cv::Mat_<float>(preenchimento_borda));

  /*parte imaginaria com valores nulos*/
  planos_filtro.push_back(cv::Mat::zeros(preenchimento_borda.size(), CV_32F));

  /*combinando os canais para o filtro, em uma unica estrutura de dados complexa (numero complexo)*/
  cv::merge(planos_filtro, img_complexa_filtro);

  /*calculando a Transformada Discreta de Fourier da matriz*/
  cv::dft(img_complexa_filtro, img_complexa_filtro, cv::DFT_COMPLEX_OUTPUT);
  trocaQuadrantes(img_complexa_filtro);

  /*cria o filtro ideal e aplica a filtragem de frequencia*/
  cv::Mat filtro;
  makeFilter(img_complexa_filtro, filtro);
  /*multiplicacao por elemento de dois espectros de Fourier*/
  cv::mulSpectrums(img_complexa_filtro, filtro, img_complexa_filtro, cv::DFT_ROWS);

  /*calculando a Transformada Discreta Inversa de Fourier da matriz*/
  trocaQuadrantes(img_complexa_filtro);
  cv::idft(img_complexa_filtro, img_complexa_filtro);
  cv::split(img_complexa_filtro, planos_filtro);

  /*selecionando uma regiao de interesse na imagem*/
  cv::Rect roi(0, 10, imagem_redimensionada.cols, imagem_redimensionada.rows);
  cv::Mat resultado = planos_filtro[0](roi);

  /*Realizando a normalizacao(contraste) para vizualizar melhor*/
  cv::normalize(resultado, resultado, 1, 0, cv::NORM_MINMAX);
  cv::imshow("Imagem sem ruido", resultado);

  cv::waitKey(0);
  return (0);
}