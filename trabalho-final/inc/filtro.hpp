/*
 * =====================================================================================
 *
 *       Filename:  filtro.hpp
 *
 *    Description:  -
 *
 *        Version:  1.0
 *        Created:  26/11/2022 07:39:52
 *       Revision:  none
 *       Compiler:  -
 *
 *         Author:  Isaac Vinicius, Hugo Bessa
 *                  isaacvinicius2121@alu.ufc.br, hugobessa@alu.ufc.br
 *   Organization:  UFC-Quixadá
 *
 * =====================================================================================
 */

#ifndef FILTRO_H
#define FILTRO_H
#include <opencv2/imgcodecs.hpp>

/*-----------------------------------------------------------------------------
 *  Function prototype
 *-----------------------------------------------------------------------------*/
void makeFilter(const cv::Mat &image, cv::Mat &filter);

#endif
/*****************************END OF FILE**************************************/