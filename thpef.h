/** *********************************************************************
 * @file
 *
 * @brief has the prototypes for the functions
 ***********************************************************************/

#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <cctype>
#include <random>
#include <stack>
#include "queue.h"

using namespace std;

/*!
 * @brief card the card which contains face value and suit
 */

struct card
{
    /*!
 * @brief faceValue the face value of the card
 */
    int faceValue;
    /*!
 * @brief suit the suit of the card
 */
    int suit;
};

bool openInput(ifstream& in, string file);

bool openOutput(ofstream& out, string file);

void playRound(Queue<card>& player1, Queue<card>& player2);