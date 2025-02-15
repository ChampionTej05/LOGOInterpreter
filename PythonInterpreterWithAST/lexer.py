
import re
class LogoLexer():

    def __init__(self, statement):
        self.statement = statement
        self.pattern = "REPEAT|FD|BK|RT|LT|\d+|\]|\["
    def tokenize(self):

        parsed_tokens = re.findall(self.pattern, self.statement, re.IGNORECASE)
        self.tokens = [ token.upper().strip() if token.isalpha() else token for token in parsed_tokens]
        return self.tokens

    def __repr__(self):
        return "{}".format(self.tokens)
    


# statement = "REPEAT 4 [ FD 40 RT 90 ]"

# obj = LogoLexer(statement)
# tokens = obj.tokenize()
# print(tokens)