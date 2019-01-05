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

    # TODO
    # Creates a matrix w = len(b) + 1, h = len(a) + 1 items, all set to 0
    w, h = len(b) + 1, len(a) + 1
    matrix = [[0 for x in range(w)] for y in range(h)]
    # initialize left corner matrix element
    matrix[0][0] = (0, None)
    # initialize the first row and first column
    for j in range(1, w):
        matrix[0][j] = (j, Operation.INSERTED)
    for i in range(1, h):
        matrix[i][0] = (i, Operation.DELETED)

    for j in range(1, w):
        for i in range(1, h):
            # calculate the cost
            if a[i - 1] == b[j - 1]:
                cost = min(matrix[i - 1][j - 1][0], matrix[i][j - 1][0] + 1, matrix[i - 1][j][0] + 1)
            else:
                cost = min(matrix[i - 1][j - 1][0] + 1, matrix[i][j - 1][0] + 1, matrix[i - 1][j][0] + 1)
            # get the last operation
            if cost == matrix[i - 1][j - 1][0] or cost == matrix[i - 1][j - 1][0] + 1:
                operation = Operation.SUBSTITUTED
            elif cost == matrix[i][j - 1][0] + 1:
                operation = Operation.INSERTED
            elif cost == matrix[i - 1][j][0] + 1:
                operation = Operation.DELETED
            # write out the matrix element
            matrix[i][j] = (cost, operation)
    # return the entire matrix
    return matrix
