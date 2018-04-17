from enum import Enum


class Operation(Enum):
    """Operations"""

    DELETED = 1
    INSERTED = 2
    SUBSTITUTED = 3

    def __str__(self):
        return str(self.name.lower())


def distances(a, b):
    """Calculate edit distance from a to b"""
    """
        iterative_levenshtein(s, t) -> ldist
        ldist is the Levenshtein distance between the strings
        s and t.
        For all i and j, dist[i,j] will contain the Levenshtein
        distance between the first i characters of s and the
        first j characters of t
    """
    rows = len(a) + 1
    cols = len(b) + 1
    dist = [[0 for x in range(rows)] for x in range(cols)]
    # source prefixes can be transformed into empty strings
    # by deletions:
    for i in range(1, rows):
        dist[i][0] = i  # ISSIAISKINTI KAIP APIBREZIAMAS TUPLE PYTHON TUPLE IN PYTHON
        dist[i][0][1] = Operation.DELETED
    # target prefixes can be created from an empty source string
    # by inserting the characters
    for i in range(1, cols):
        dist[0][i][0] = i
        dist[0][i][1] = Operation.INSERTED

    for col in range(1, cols):
        for row in range(1, rows):
            if a[row - 1] == b[col - 1]:
                cost = 0
            else:
                cost = 1
            dist[row][col][0] = min(dist[row - 1][col][0] + 1,      # deletion
                                    dist[row][col - 1][0] + 1,      # insertion
                                    dist[row - 1][col - 1][0] + cost)  # substitution

            if (dist[row - 1][col][0] + 1) == min(dist[row - 1][col][0] + 1, dist[row][col - 1][0] + 1, dist[row - 1][col - 1][0] + cost):
                dist[row][col][1] = Operation.DELETED
            elif (dist[row][col - 1][0] + 1) == min(dist[row - 1][col][0] + 1, dist[row][col - 1][0] + 1, dist[row - 1][col - 1][0] + cost):
                dist[row][col][1] = Operation.INSERTED
            else:
                dist[row][col][1] = Operation.SUBSTITUTED
    return dist
    # TODO
    # return [[]]
