﻿# Omaha Hi-Lo Poker
 
 ## Project objective
 To design the algorithm and write a C++ program to determine which of the two Omaha Hi-Lo poker hands is the winning hand for High and which is the winning hand for Low (if any).

 ## Notation
 I use a two-character notation for cards that shows the card rank and the card suit, for example:
  - Ad (Ace diamonds)
  - Kc (King clubs)
  - Qh (Queen hearts)
  - Js (Jack spades)
  - Td (10 diamonds)
  - 9s (9 spades)

## Poker ranking
### Poker rankings for High Hand
Poker High rankings for any hand containing 5 cards are defined in the following order - from highest to lowest (examples shown):

![Poker High rankings](https://github.com/user-attachments/assets/8ffcbbd8-0a26-4413-a1bb-5fef39ac247c)

If two hands are of the same ranking, the winner is the one having the higher cards. For example, a Flush with an Ace high beats a Flush with a King high. If the highest cards of each hand are of the same rank, then it is the highest card not being held in common (called the "kicker") that determines the winner. For example, One Pair As-Ad-Qh-Jd-9c wins against Ac-Ah-Qs-Jc-8d using the "9 kicker".

In the event of hands being identical in ranking, it is a tie and the pot will be split evenly between the two or more winning players.

Notes:
1. In Poker unlike Bridge the suit has no impact on the ranking (e.g. Ks is as strong as Kd)
2. An Ace can be used in straights as the highest card or as the lowest card. For example, the following hands are both straights: As-Kd-Qd-Jd-Tc and 5c-4c-3d-2s-Ad (but the hand 4c-3d-2s-Ac-Kd is not a straight, but High Card).
3. When two hands of "Full House" ranking are compared, 3 of a kind are compared first. For example, A-A-A-5-5 wins against K-K-K-Q-Q
4. When two hands of "Two Pair" ranking are compared the higher pairs are compared first. For example, K-K-2-2-5 wins against Q-Q-J-J-T.

### Poker rankings for Low 8 Hand
There are two required qualifications for a hand with 5 cards to qualify for a low-8 hand:
1. All 5 cards should have different rank
2. None of the cards should be higher than 8. Aces are always considered to have a value of 1 for low-hand evaluation.

Any qualified low hand beats a hand that did not qualify for low. If no hand qualifies for low, then all chips are awarded to the winner(s) of the high hand.

Examples of hands that don't qualify for low:
```
ATQ23: some cards higher than 8
95432: some cards higher than 8
73322: not all cards are of different ranks
```

If both hands qualify for low, the hand containing the higher card loses, i.e. 5432A beats 86743. If senior card or cards are equal, then the first card that is different decides the hand. For example, 7632A beats 76432, because the third card for the second hand is higher than the third card for the first hand.

## Omaha Hi/Lo Definition
In OMAHA Hi/Lo each player receives 4 cards and 5 cards are placed on the board seen by all players. A player must combine any two of his cards with any three cards from the board to obtain 5 cards with the highest possible ranking for high hand, and combine any other (or same) two of his cards with any other (or same) three cards from the board to obtain 5 cards with lowest possible low hand.

It is important to realize that in all cases the best 5-card combination of one player will be compared to the best 5-card combination of another player to determine the winner.

## Program Requirements
The program reads 2 parameters from the command line:
```
omahacomp input.txt output.txt
```

File “input.txt” contains the list of card combinations on each line
```
HandA:card1-card2-card3-card4 HandB:card1-card2-card3-card4 Board:card1-card2-card3-card4-card5
```

File “output.txt” contains the results of hand evaluation, including input line, winner hand, and combination for High and Low hands (see examples below for required format).

## Examples
```
omahacomp input.txt output.txt
```

input.txt:
```
HandA:Ac-Kd-Jd-3d HandB:5c-5d-6c-7d Board:Ah-Kh-5s-2s-Qd
HandA:Ac-Kd-Jd-3d HandB:5c-5d-6c-6d Board:Ad-Kh-5s-2d-Qd
HandA:Qc-Jd-Td-3d HandB:Tc-Jc-8h-6d Board:Ad-Kh-Qs-2d-3c
HandA:Qh-4d-Tc-8s HandB:Qc-8c-7d-2h Board:Ad-As-3c-3d-5d
HandA:Ah-2s-Qd-9S HandB:Ac-2d-6s-Jh Board:Kd-4h-Kh-5s-3c
HandA:Ah-2s-Qd-9S HandB:Ac-2d-As-Jh Board:Kd-4h-Kh-5s-3c
HandA:6d-6c-Kc-4d HandB:Jh-Js-Qs-8h Board:2s-3h-9c-As-Ac
HandA:6d-Kh-Ac-4d HandB:Jh-2s-Ah-8h Board:Js-3h-9c-As-6c
HandA:Qc-Jd-Td-3d HandB:3s-3h-8h-6d Board:Ad-Kh-Qs-Qd-3c
```

output.txt:
```
HandA:Ac-Kd-Jd-3d HandB:5c-5d-6c-7d Board:Ah-Kh-5s-2s-Qd
=> HandB wins Hi (3-of-a-Kind); HandB wins Lo (7652A)

HandA:Ac-Kd-Jd-3d HandB:5c-5d-6c-6d Board:Ad-Kh-5s-2d-Qd
=> HandA wins Hi (Flush); No hand qualified for Low

HandA:Qc-Jd-Td-3d HandB:Tc-Jc-8h-6d Board:Ad-Kh-Qs-2d-3c
=> Split Pot Hi (Straight); HandB wins Lo (8632A)

HandA:Qh-4d-Tc-8s HandB:Qc-8c-7d-2h Board:Ad-As-3c-3d-5d
=> HandA wins Hi (One Pair); HandB wins Lo (7532A)

HandA:Ah-2s-Qd-9S HandB:Ac-2d-6s-Jh Board:Kd-4h-Kh-5s-3c
=> HandB wins Hi (Straight); Split Pot Lo (5432A)

HandA:Ah-2s-Qd-9S HandB:Ac-2d-As-Jh Board:Kd-4h-Kh-5s-3c
=> Split Pot Hi (Straight); Split Pot Lo (5432A)

HandA:6d-6c-Kc-4d HandB:Jh-Js-Qs-8h Board:2s-3h-9c-As-Ac
=> HandB wins Hi (Two Pair); HandA wins Lo (6432A)

HandA:6d-Kh-Ac-4d HandB:Jh-2s-Ah-8h Board:Js-3h-9c-As-6c
=> HandB wins Hi (Two Pair); HandB wins Lo (8632A)

HandA:Qc-Jd-Td-3d HandB:3s-3h-8h-6d Board:Ad-Kh-Qs-Qd-3c
=> HandA wins Hi (Full House); No hand qualified for Low
```
