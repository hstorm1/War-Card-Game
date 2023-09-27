/** *********************************************************************
 * @file
 *
 * @brief plays a game of war between 2 full decks of cards
 ***********************************************************************/

 /** ********************************************************************
 *
 * @mainpage Take Home Programming Exam 3 - War Card Game
 *
 * @section course_section Course Information
 *
 * @authors David Hill
 *
 * @date May 2, 2022
 *
 * @par Instructor:
 *         Prof. Schrader
 *
 * @par Course:
 *         CSC 215 - Section 2 - 1:00 pm
 *
 * @par Location:
 *         Classroom Building - Room 329
 *
 * @section program_section Program Information
 *
 * @details This program will play a card game of war between two
 * shuffled decks of cards. It can be run through 2 integer
 * seeds to generate random numbers, or through 2 files with
 * numbers in them. It will then play rounds until one hand
 * runs out of cards. It then prints out how many round it took
 * the winning hand to win along with printing out the hand
 * of cards.
 *
 * @section compile_section Compiling and Usage
 *
 * @par Compiling Instructions:
 *      None
 *
 * @par Usage:
   @verbatim
   c:\> thpe3.exe -s firstPlayerSeed secondPlayerSeed
   c:\> thpe3.exe -f file1.txt file2.txt
   d:\> c:\bin\thpe3.exe -s firstPlayerSeed secondPlayerSeed
   d:\> c:\bin\thpe3.exe -f file1.txt file2.txt

        firstPlayerSeed - the integer seed for the first hand
        secondPlayerSeed - the integer seed for the second hand
        file1.txt - the integer file for the first hand
        file2.txt - the integer file for the second hand
   @endverbatim
 *
 * @section todo_bugs_modification_section Todo, Bugs, and Modifications
 *
 * @bug no known bugs
 *
 * @par Modifications and Development Timeline:

   Gitlab commit log, <a href = "https://gitlab.cse.sdsmt.edu/
   101061288/csc215s22programs/-/commits/master" target="_blank">
   Click Here.</a>
 *
 ***********************************************************************/

#define CATCH_CONFIG_RUNNER
#include "..\\catch.hpp"
#include "thpef.h"

 /** *********************************************************************
  * @author David Hill
  *
  * @par Description:
  * This is the starting point to the program. It will check command line
  * arguments. If there is an incorrect number of them, it will output an
  * error message and exit the program. Otherwise, it will output the
  * results of the war card game.
  *
  *
  * @param[in] argc - the number of arguments from the command prompt.
  * @param[in] argv - a 2d array of characters containing the arguments.
  *
  * @returns an integer if the program executed correctly or not
  *
  * @verbatim
    see usage statement above.
    @endverbatim
  *
  ***********************************************************************/

int main(int argc, char** argv)
{
    string seed1String;
    string seed2String;
    string file1;
    string file2;
    int seed1Int;
    int seed2Int;
    int i;
    int j;
    ifstream in1;
    ifstream in2;
    card usedP1[52];
    card usedP2[52];
    Queue<card> p1;
    Queue<card> p2;
    int count = 0;
    
    // catch variables for test cases
    const bool RUNCATCH = true;
    Catch::Session session;
    int result;

    if (RUNCATCH)
    {
        result = session.run();
        if (result != 0)
        {
            cout << "Test cases didn't pass." << endl;
            return result;
        }
    }
    // error check for number of arguments
    if (argc != 4)
    {
        cout << "Usage: thpef.exe -s firstPlayerSeed secondPlayerSeed"
            << endl
            << "or   : thpef.exe -f file1.txt file2.txt"
            << endl;
        exit(0);
    }
    string firstArg = argv[1];
    // error check for second argument
    if (firstArg != "-s" && firstArg != "-f")
    {
        cout << "Usage: thpef.exe -s firstPlayerSeed secondPlayerSeed"
            << endl
            << "or   : thpef.exe -f file1.txt file2.txt"
            << endl;
        exit(0);
    }
    if (firstArg == "-s")
    {
        // create 2 random number generators
        seed1String = argv[2];
        seed2String = argv[3];
        seed1Int = std::stoi(seed1String);
        seed2Int = std::stoi(seed2String);
        default_random_engine generator1(seed1Int);
        default_random_engine generator2(seed2Int);
        uniform_int_distribution<int> distribution(0, 51);

        for (i = 0; i < 52; i++)
        {
            // generate a random card number
            // suit is that number / 13
            // and face value is that number % 13
            int temp = i;
            card aCard;
            int cardValue;
            cardValue = distribution(generator1);

            aCard.faceValue = cardValue % 13;
            aCard.suit = cardValue / 13;
            for (j = 0; j < 52; j++)
            {
                // check if that number has already been used with 
                // a separate "used" array
                if (aCard.faceValue == usedP1[j].faceValue
                    && aCard.suit == usedP1[j].suit)
                {
                    i--;
                }
            }
            // if it was not used add it to the queue
            if (temp == i)
            {
                p1.enque(aCard);
                usedP1[i] = aCard;
            }
        }
        // repeat for the second queue
        for (i = 0; i < 52; i++)
        {
            int temp = i;
            card aCard;
            int cardValue;
            cardValue = distribution(generator2);

            aCard.faceValue = cardValue % 13;
            aCard.suit = (int) cardValue / 13;
            for (j = 0; j < 52; j++)
            {
                if (aCard.faceValue == usedP2[j].faceValue
                    && aCard.suit == usedP2[j].suit)
                {
                    i--;
                }
            }
            if (temp == i)
            {
                p2.enque(aCard);
                usedP2[i] = aCard;
            }
        }
        // keep playing rounds until one queue is empty
        while (!p1.size() == 0 && !p2.size() == 0)
        {
            playRound(p1, p2);
            count += 1;
        }
        // depending on which queue is empty, output the results
        if (p2.size() == 0)
        {
            cout << "Player 1 wins after " << count << " rounds." << endl
                << "Player 1 hand: ";
            p1.print();
            cout << endl
                << "Player 2 hand: ";
            p2.print();
            cout << endl;
        }
        if (p1.size() == 0)
        {
            cout << "Player 2 wins after " << count << " rounds." << endl
                << "Player 1 hand: ";
            p1.print();
            cout << endl
                << "Player 2 hand: ";
            p2.print();
            cout << endl;
        }
    }
    if (firstArg == "-f")
    {
        file1 = argv[2];
        file2 = argv[3];
        // check if both input files opened correctly
        if (!openInput(in1, file1))
        {
            in1.close();
            exit(0);
        }
        if (!openInput(in2, file2))
        {
            in2.close();
            exit(0);
        }
        // add numbers to each queue until end of file is reached
        while (!in1.eof())
        {
            card aCard;
            int cardValue;
            in1 >> cardValue;

            aCard.faceValue = cardValue % 13;
            aCard.suit = cardValue / 13;
            p1.enque(aCard);
        }
        while (!in2.eof())
        {
            card aCard;
            int cardValue;
            in2 >> cardValue;

            aCard.faceValue = cardValue % 13;
            aCard.suit = cardValue / 13;
            p2.enque(aCard);
        }
        // play rounds until one queue is empty
        while (!p1.size() == 0 && !p2.size() == 0)
        {
            playRound(p1, p2);
            count += 1;
        }
        // output results depending on which queue is empty
        if (p2.size() == 0)
        {
            cout << "Player 1 wins after " << count << " rounds." << endl
                << "Player 1 hand: ";
            p1.print();
            cout << endl
                << "Player 2 hand: ";
            p2.print();
            cout << endl;
        }
        if (p1.size() == 0)
        {
            cout << "Player 2 wins after " << count << " rounds." << endl
                << "Player 1 hand: ";
            p1.print();
            cout << endl
                << "Player 2 hand: ";
            p2.print();
            cout << endl;
        }
    }

    return 0;
}

/** ***************************************************************************
 * @author David Hill
 *
 * @par Description
 * This function plays out one round of war and updates the queues accordingly
 *
 * @param[in] player1 - the first player queue
 * @param[in] player2 - the second player queue
 * 
 * @par Example
 * @verbatim

    card card1;
    card card2;
    card1.faceValue = 2;
    card2.faceValue = 9;
    card1.suit = 0;
    card2.suit = 0;
    Queue<int> q1;
    Queue<int> q2;
    q1.enque(card1);
    q2.enque(card2);
    playRound(q1, q2);
    // q2 would now contain 2 and then 9
    // and q1 would be empty

   @endverbatim
 *****************************************************************************/

void playRound(Queue<card>& player1, Queue<card>& player2)
{
    stack<card> s1;
    stack<card> s2;
    card c1;
    card c2;
    player1.deque(c1);
    player2.deque(c2);
    s1.push(c1);
    s2.push(c2);
    // handles ties when both queues are greater than 3 
    // meaning we can place 3 more cards down
    while (c1.faceValue == c2.faceValue && player1.size() >= 3 &&
        player2.size() >= 3)
    {
        player1.deque(c1);
        s1.push(c1);
        player1.deque(c1);
        s1.push(c1);
        player1.deque(c1);
        s1.push(c1);
        player2.deque(c2);
        s2.push(c2);
        player2.deque(c2);
        s2.push(c2);
        player2.deque(c2);
        s2.push(c2);
    }
    // handles if there is still a tie and player 1's size is less than 3
    if (c1.faceValue == c2.faceValue && player1.size() < 3)
    {
        // if it's 0, each player picks up their own cards
        if (player1.size() == 0)
        {
            while (s1.size() > 0)
            {
                player1.enque(c1);
                s1.pop();
                if (s1.size() > 0)
                {
                    c1 = s1.top();
                }
                player2.enque(c2);
                s2.pop();
                if (s2.size() > 0)
                {
                    c2 = s2.top();
                }
            }
            return;
        }
        // otherwise place as many cards as player 1 has left down
        while (player1.size() > 0)
        {
            player1.deque(c1);
            s1.push(c1);
            player2.deque(c2);
            s2.push(c2);
        }
        // again, if the last value is still equal to player 2's
        // each player picks up their own cards
        if (c1.faceValue == c2.faceValue)
        {
            while (s1.size() > 0)
            {
                player1.enque(c1);
                s1.pop();
                if (s1.size() > 0)
                {
                    c1 = s1.top();
                }
                player2.enque(c2);
                s2.pop();
                if (s2.size() > 0)
                {
                    c2 = s2.top();
                }
            }
            return;
        }
    }
    // same thing but if player 2's size is less than 3
    else if (c1.faceValue == c2.faceValue && player2.size() < 3)
    {
        if (player2.size() == 0)
        {
            while (s2.size() > 0)
            {
                player2.enque(c2);
                s2.pop();
                if (s2.size() > 0)
                {
                    c2 = s2.top();
                }
                player1.enque(c1);
                s1.pop();
                if (s1.size() > 0)
                {
                    c1 = s1.top();
                }
            }
            return;
        }
        while (player2.size() > 0)
        {
            player2.deque(c2);
            s2.push(c2);
            player1.deque(c1);
            s1.push(c1);
        }
        if (c1.faceValue == c2.faceValue)
        {
            while (s2.size() > 0)
            {
                player2.enque(c2);
                s2.pop();
                if (s2.size() > 0)
                {
                    c2 = s2.top();
                }
                player1.enque(c1);
                s1.pop();
                if (s1.size() > 0)
                {
                    c1 = s1.top();
                }
            }
            return;
        }
    }
    // if player 1 wins
    if (c1.faceValue > c2.faceValue)
    {
        // pick up player 2's cards, then player 1's
        while (s2.size() > 0)
        {
            player1.enque(c2);
            s2.pop();
            if (s2.size() > 0)
            {
                c2 = s2.top();
            }
        }
        while (s1.size() > 0)
        {
            player1.enque(c1);
            s1.pop();
            if (s1.size() > 0)
            {
                c1 = s1.top();
            }
        }
    }
    // if player 2 wins
    else if (c2.faceValue > c1.faceValue)
    {
        // pick up player 1's cards, then player 2's
        while (s1.size() > 0)
        {
            player2.enque(c1);
            s1.pop();
            if (s1.size() > 0)
            {
                c1 = s1.top();
            }
        }
        while (s2.size() > 0)
        {
            player2.enque(c2);
            s2.pop();
            if (s2.size() > 0)
            {
                c2 = s2.top();
            }
        }
    }
}