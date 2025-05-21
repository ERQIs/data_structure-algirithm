# Peg Solitire Simulation

## Peg Solitire

Peg Solitaire, Solo Noble, Solo Goli, Marble Solitaire or simply Solitaire is a board game for one player involving movement of pegs on a board with holes. Some sets use marbles in a board with indentations. The game is known as solitaire in Britain and as peg solitaire in the US where 'solitaire' is now the common name for patience.

The first evidence of the game can be traced back to the court of Louis XIV, and the specific date of 1697, with an engraving made ten years later by Claude Auguste Berey of Anne de Rohan-Chabot, Princess of Soubise, with the puzzle by her side. The August 1697 edition of the French literary magazine Mercure galant contains a description of the board, rules and sample problems. This is the first known reference to the game in print.

The standard game fills the entire board with pegs except for the central hole. The objective is, making valid moves, to empty the entire board except for a solitary peg in the central hole.

## Board

There are two traditional boards ('.' as an initial peg, 'o' as an initial hole):

### English

```comment
     · · ·
     · · ·
 · · · · · · · 
 · · · o . · · 
 · · · · · · · 
     · · ·
     · · ·
```

### European

```comment
     · · ·
   · · · · ·
 · · · · · · · 
 · · · o · · · 
 · · · · · · · 
   · · · · ·
     · · ·
```

## Play

A valid move is to jump a peg orthogonally over an adjacent peg into a hole two positions away and then to remove the jumped peg.

In the diagrams which follow, · indicates a peg in a hole, \* emboldened indicates the peg to be moved, and o indicates an empty hole. A blue ¤ is the hole the current peg moved from; a red \* is the final position of that peg, a red o is the hole of the peg that was jumped and removed.

Thus valid moves in each of the four orthogonal directions are:

```comment
* · o  →  ¤ o *  Jump to right

o · *  →  * o ¤  Jump to left

*     ¤
·  →  o  Jump down
o     *

o     *
·  →  o  Jump up
*     ¤
```

On an English board, the first three moves might be:

```comment
    · · ·             · · ·             · · ·             · · · 
    · * ·             · ¤ ·             · o ·             · * · 
· · · · · · ·     · · · o · · ·     · ¤ o * · · ·     · o o o · · ·
· · · o · · ·     · · · * · · ·     · · · · · · ·     · · · ¤ · · ·
· · · · · · ·     · · · · · · ·     · · · · · · ·     · · · · · · ·
    · · ·             · · ·             · · ·             · · ·
    · · ·             · · ·             · · ·             · · ·
```

## Input

An initial board as mentioned above. But there is some other ways to represent the board and mark the positions:

```comment
   English          European
    a b c             a b c
    d e f           y d e f z
g h i j k l m     g h i j k l m
n o p x P O N     n o p x P O N
M L K J I H G     M L K J I H G
    F E D           Z F E D Y
    C B A             C B A
```

Input will be one of these, with x representing initial empty hole. And also, the last peg should be at the centre.

Input contains 7 rows with each consist of 7 chars. So the blank area is refilled with space ' '.

## Output

some readable way that indicates the steps to reach the solution. Perhaps something like this:

```comment
solution 0:
o -> x
F -> p
...
```
