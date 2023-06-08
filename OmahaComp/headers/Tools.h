#ifndef TOOLS_H
#define TOOLS_H

#include <vector>

#include <Enums.h>
#include <Card.h>

Suit parseSuit(const char suit);
std::string highHandRankToString(const HighHand suit);
int parseWeight(const char rank);
void removeDuplicates(std::vector<Card>& vec);
void changeAceWeight(std::vector<Card>::iterator& It);
bool operator<(const std::vector<Card>& lhs, const std::vector<Card>& rhs);
std::vector<Card>::iterator findHighAce(std::vector<Card>& vec);
std::vector<Card>::const_iterator findNotSuitableCard(std::vector<Card>& vec);
void handleExceptionalStraightFlush(std::vector<Card>&);

#endif // TOOLS_H