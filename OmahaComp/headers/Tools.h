#ifndef TOOLS_H
#define TOOLS_H

#include <vector>

#include <Enums.h>
#include <Card.h>

Suit parseSuit(const char suit);
Rank parseRank(const char rank);

std::string highHandRankToString(const HighHandRank suit);
char cardRankToChar(const Rank rank);

void removeDuplicates(std::vector<Card>& vec);
std::vector<Card>::iterator findHighAce(std::vector<Card>& vec);
void makeLowAce(std::vector<Card>::iterator& It);
std::vector<Card>::const_iterator findNotSuitableCard(std::vector<Card>& vec);

bool operator<(const std::vector<Card>& lhs, const std::vector<Card>& rhs);

void handleExceptionalStraightFlush(std::vector<Card>&);

#endif // TOOLS_H