|     | <          | \>       | /        | letter (*) | $          | S`  | S   | A   | L   | R   | C   |
|-----|------------|----------|----------|------------|------------|-----|-----|-----|-----|-----|-----|
| 0   | shift 3    |          |          |            |            |     | 1   |     | 2   |     |     |
| 1   |            |          |          |            | accepted   |     |     |     |     |     |     |
| 2   | shift 3    |          |          | shift 7    |            |     |     | 4   | 6   |     | 5   |
| 3   |            |          |          | shift 9    |            |     |     |     |     |     | 8   |
| 4   | shift 11   |          |          |            |            |     |     |     |     | 10  |     |
| 5   | S -> LAR   |          |          | shift 7    |            |     |     |     |     |     | 12  |
| 6   | shift 3    |          |          | shift 7    |            |     |     | 13  | 6   |     | 5   |
| 7   | C -> *     |          |          | C -> *     |            |     |     |     |     |     |     |
| 8   |            | shift 14 |          | shift 9    |            |     |     |     |     |     | 15  |
| 9   |            | C -> *   |          | C -> *     |            |     |     |     |     |     |     |
| 10  |            |          |          |            | S` -> S    |     |     |     |     |     |     |
| 11  |            |          | shift 16 |            |            |     |     |     |     |     |     |
| 12  | C -> CC    |          |          | C -> CC    |            |     |     |     |     |     | 12  |
| 13  | shift 18   |          |          |            |            |     |     |     |     | 17  |     |
| 14  | L -> \<C>  |          |          | L -> \<C>  |            |     |     |     |     |     |     |
| 15  |            | C -> CC  |          | C -> CC    |            |     |     |     |     |     | 15  |
| 16  |            |          |          | shift 9    |            |     |     |     |     |     | 19  |
| 17  | A -> LAR   |          |          |            |            |     |     |     |     |     |     |
| 18  |            |          | shift 20 |            |            |     |     |     |     |     |     |
| 19  |            | shift 21 |          | shift 9    |            |     |     |     |     |     | 15  |
| 20  |            |          |          | shift 9    |            |     |     |     |     |     | 22  |
| 21  |            |          |          |            | R -> \</C> |     |     |     |     |     |     |
| 22  |            | shift 23 |          | shift 9    |            |     |     |     |     |     | 15  |
| 23  | R -> \</C> |          |          |            |            |     |     |     |     |     |     |