#ifndef TOOLS_H
#define TOOLS_H

#include <vector>
#include <map>

#include <Enums.h>
#include <Card.h>

Suit parseSuit(const char suit);
Rank parseRank(const char rank);

std::string highHandRankToString(const HighHandRank suit);
char cardRankToChar(const Rank rank);
std::vector<Card> cardSetupToVector(std::string str);

std::map<Rank, size_t>::const_iterator findNotSuitableCard(const std::map<Rank, size_t>& map);

bool operator<(const std::vector<Card>& lhs, const std::vector<Card>& rhs);

bool operator<(const std::map<Rank, size_t> &lhs, const std::map<Rank, size_t>& rhs);
bool operator==(const std::map<Rank, size_t>& lhs, const std::map<Rank, size_t>& rhs);
std::ostream& operator<<(std::ostream& os, const std::map<Rank, size_t>& cards);

#endif // TOOLS_H