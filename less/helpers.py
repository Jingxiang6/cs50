from nltk.tokenize import sent_tokenize


def lines(a, b):
    """Return lines in both a and b"""

    # TODO
    list_a_line = a.splitlines()
    list_b_line = b.splitlines()
    common_line = []
    for line in list_a_line:
        if (line in list_b_line) and (line not in common_line):
            common_line.append(line)
    return common_line


def sentences(a, b):
    """Return sentences in both a and b"""

    # TODO
    list_a_sent = sent_tokenize(a, language='english')
    list_b_sent = sent_tokenize(b, language='english')
    common_sent = []
    for sent in list_a_sent:
        if (sent in list_b_sent) and (sent not in common_sent):
            common_sent.append(sent)
    return common_sent


def substrings(a, b, n):
    """Return substrings of length n in both a and b"""

    # TODO
    substrings_a = substrings_list(a, n)
    substrings_b = substrings_list(b, n)
    common_sub = []
    for string in substrings_a:
        if string in substrings_b and string not in common_sub:
            common_sub.append(string)
    return common_sub


def substrings_list(a, n):
    substr = []
    for i in range(0, len(a) - n + 1, 1):
        if a[i: i + n] not in substr:
            substr.append(a[i: i + n])
    return substr
