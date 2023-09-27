#include "thpef.h"
#include "queue.h"
#include "..\\catch.hpp"

TEST_CASE("queue class - testing isEmpty function")
{
    Queue<card> p1;
    REQUIRE(p1.isEmpty() == true);
    REQUIRE(p1.size() == 0);
}


TEST_CASE("queue class - testing enque function")
{
    Queue<card> p1;
    card card1;
    card1.faceValue = 3;
    card1.suit = 0;
    card card2;
    card2.faceValue = 9;
    card2.suit = 2;
    REQUIRE(p1.enque(card1) == true);
    REQUIRE(p1.enque(card2) == true);
    REQUIRE(p1.size() == 2);
    //p1.print();
}


TEST_CASE("queue class - testing deque function")
{
    Queue<card> p1;
    card card1;
    card1.faceValue = 3;
    card1.suit = 0;
    card card2;
    card2.faceValue = 9;
    card2.suit = 2;
    card poppedCard;
    p1.enque(card1);
    p1.enque(card2);
    p1.deque(poppedCard);
    REQUIRE(poppedCard.faceValue == 3);
    REQUIRE(poppedCard.suit == 0);
    REQUIRE(p1.size() == 1);
    //p1.print();
}


TEST_CASE("queue class - testing front function")
{
    Queue<card> p1;
    card card1;
    card1.faceValue = 3;
    card1.suit = 0;
    card card2;
    card2.faceValue = 9;
    card2.suit = 2;
    card topCard;
    p1.enque(card1);
    p1.enque(card2);
    p1.front(topCard);
    REQUIRE(topCard.faceValue == 3);
    REQUIRE(topCard.suit == 0);
    REQUIRE(p1.size() == 2);
    //p1.print();
}


TEST_CASE("playRound - first card makes player 1 win")
{
    Queue<card> p1;
    Queue<card> p2;
    card card1;
    card card2;
    card card3;
    card card4;
    card1.faceValue = 9;
    card1.suit = 0;
    p1.enque(card1);
    card2.faceValue = 4;
    card2.suit = 2;
    p1.enque(card2);
    card3.faceValue = 8;
    card3.suit = 1;
    p2.enque(card3);
    card4.faceValue = 11;
    card4.suit = 2;
    p2.enque(card4);
    playRound(p1, p2);
    REQUIRE(p1.size() > p2.size());
    //p1.print();
    //cout << endl;
    //p2.print();
}


TEST_CASE("playRound - first card makes player 2 win")
{
    Queue<card> p1;
    Queue<card> p2;
    card card1;
    card card2;
    card card3;
    card card4;
    card1.faceValue = 3;
    card1.suit = 0;
    p1.enque(card1);
    card2.faceValue = 10;
    card2.suit = 2;
    p1.enque(card2);
    card3.faceValue = 4;
    card3.suit = 1;
    p2.enque(card3);
    card4.faceValue = 11;
    card4.suit = 2;
    p2.enque(card4);
    playRound(p1, p2);
    REQUIRE(p1.size() < p2.size());
    //p1.print();
    //cout << endl;
    //p2.print();
}


TEST_CASE("playRound - first card is a tie with no more cards left")
{
    Queue<card> p1;
    Queue<card> p2;
    card card1;
    card card2;
    card1.faceValue = 3;
    card1.suit = 0;
    p1.enque(card1);
    card2.faceValue = 3;
    card2.suit = 2;
    p2.enque(card2);
    playRound(p1, p2);
    REQUIRE(p1.size() == p2.size());
    //p1.print();
    //cout << endl;
    //p2.print();
}


TEST_CASE("playRound - first card is a tie with 1 card left to break the tie")
{
    Queue<card> p1;
    Queue<card> p2;
    card card1;
    card card2;
    card card3;
    card card4;
    card1.faceValue = 3;
    card1.suit = 0;
    p1.enque(card1);
    card2.faceValue = 10;
    card2.suit = 2;
    p1.enque(card2);
    card3.faceValue = 3;
    card3.suit = 1;
    p2.enque(card3);
    card4.faceValue = 11;
    card4.suit = 2;
    p2.enque(card4);
    playRound(p1, p2);
    REQUIRE(p1.size() < p2.size());
    //p1.print();
    //cout << endl;
    //p2.print();
}


TEST_CASE("playRound - first card is a tie with 1 card left that is also a tie")
{
    Queue<card> p1;
    Queue<card> p2;
    card card1;
    card card2;
    card card3;
    card card4;
    card1.faceValue = 3;
    card1.suit = 0;
    p1.enque(card1);
    card2.faceValue = 11;
    card2.suit = 1;
    p1.enque(card2);
    card3.faceValue = 3;
    card3.suit = 1;
    p2.enque(card3);
    card4.faceValue = 11;
    card4.suit = 2;
    p2.enque(card4);
    playRound(p1, p2);
    REQUIRE(p1.size() == p2.size());
    //p1.print();
    //cout << endl;
    //p2.print();
}


TEST_CASE("playRound - first card is a tie with 2 cards left which will break the tie")
{
    Queue<card> p1;
    Queue<card> p2;
    card aCard;
    int i;
    int p1Cards[3] = { 3, 4, 11 };
    int p2Cards[3] = { 3, 7, 9 };
    for (i = 0; i < 3; i++)
    {
        aCard.faceValue = p1Cards[i];
        aCard.suit = 0;
        p1.enque(aCard);
    }
    for (i = 0; i < 3; i++)
    {
        aCard.faceValue = p2Cards[i];
        aCard.suit = 0;
        p2.enque(aCard);
    }
    playRound(p1, p2);
    REQUIRE(p1.size() > p2.size());
    //p1.print();
    //cout << endl;
    //p2.print();
}


TEST_CASE("playRound - first card is a tie with 2 cards left which is also a tie")
{
    Queue<card> p1;
    Queue<card> p2;
    card aCard;
    int i;
    int p1Cards[3] = { 3, 4, 11 };
    int p2Cards[3] = { 3, 7, 11 };
    for (i = 0; i < 3; i++)
    {
        aCard.faceValue = p1Cards[i];
        aCard.suit = 0;
        p1.enque(aCard);
    }
    for (i = 0; i < 3; i++)
    {
        aCard.faceValue = p2Cards[i];
        aCard.suit = 0;
        p2.enque(aCard);
    }
    playRound(p1, p2);
    REQUIRE(p1.size() == p2.size());
    //p1.print();
    //cout << endl;
    //p2.print();
}


TEST_CASE("playRound - first card is a tie with 3 cards left which will break the tie")
{
    Queue<card> p1;
    Queue<card> p2;
    card aCard;
    int i;
    int p1Cards[4] = { 3, 4, 11, 6 };
    int p2Cards[4] = { 3, 7, 11, 9 };
    for (i = 0; i < 4; i++)
    {
        aCard.faceValue = p1Cards[i];
        aCard.suit = 0;
        p1.enque(aCard);
    }
    for (i = 0; i < 4; i++)
    {
        aCard.faceValue = p2Cards[i];
        aCard.suit = 0;
        p2.enque(aCard);
    }
    playRound(p1, p2);
    REQUIRE(p1.size() < p2.size());
    //p1.print();
    //cout << endl;
    //p2.print();
}


TEST_CASE("playRound - first card is a tie with 3 cards left which will also be a tie")
{
    Queue<card> p1;
    Queue<card> p2;
    card aCard;
    int i;
    int p1Cards[4] = { 3, 4, 11, 9 };
    int p2Cards[4] = { 3, 7, 11, 9 };
    for (i = 0; i < 4; i++)
    {
        aCard.faceValue = p1Cards[i];
        aCard.suit = 0;
        p1.enque(aCard);
    }
    for (i = 0; i < 4; i++)
    {
        aCard.faceValue = p2Cards[i];
        aCard.suit = 0;
        p2.enque(aCard);
    }
    playRound(p1, p2);
    REQUIRE(p1.size() == p2.size());
    //p1.print();
    //cout << endl;
    //p2.print();
}


TEST_CASE("playRound - first card is a tie with 5 cards left which will break the tie")
{
    Queue<card> p1;
    Queue<card> p2;
    card aCard;
    int i;
    int p1Cards[6] = { 3, 4, 11, 4, 8, 2 };
    int p2Cards[6] = { 3, 7, 11, 2, 3, 5 };
    for (i = 0; i < 6; i++)
    {
        aCard.faceValue = p1Cards[i];
        aCard.suit = 0;
        p1.enque(aCard);
    }
    for (i = 0; i < 6; i++)
    {
        aCard.faceValue = p2Cards[i];
        aCard.suit = 0;
        p2.enque(aCard);
    }
    playRound(p1, p2);
    REQUIRE(p1.size() > p2.size());
    //p1.print();
    //cout << endl;
    //p2.print();
}
