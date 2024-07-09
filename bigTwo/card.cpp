#include "card.h"
#include <QApplication>

const QMap<Card::Suit, QString> Card::suitMap = {
    {Hearts, "Hearts"},
    {Diamonds, "Diamonds"},
    {Clubs, "Clubs"},
    {Spades, "Spades"}
};

const QMap<Card::Rank, QString> Card::rankMap = {
    {Three, "Three"},
    {Four, "Four"},
    {Five, "Five"},
    {Six, "Six"},
    {Seven, "Seven"},
    {Eight, "Eight"},
    {Nine, "Nine"},
    {Ten, "Ten"},
    {Jack, "Jack"},
    {Queen, "Queen"},
    {King, "King"},
    {Ace, "Ace"},
    {Two, "Two"}
};

Card::Card()
{
}

Card::Card(Suit suit, Rank rank): card_suit(suit), card_rank(rank)
{
}

Card::Suit Card::getSuit() const
{
    return card_suit;
}

Card::Rank Card::getRank() const
{
    return card_rank;
}

QString Card::getSuitString() const
{
    return suitMap.value(card_suit);
}

QString Card::getRankString() const
{
    return rankMap.value(card_rank);
}